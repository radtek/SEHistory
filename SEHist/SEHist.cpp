// SEHist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SEHist.h"
#include "Logger.h"
#include "cSEHistData.h"
#include "TblMachineHistory.h"
#include "TblRejectHistory.h"
#include "TblWOHist.h"
#include "cMfgSysInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CLogger Log;
cSEHistData SEHistData;
CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

  if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
    InitIP21();
	}
	return nRetCode;
}
/* -------------------------------------------------------------------------
   Initialize IP21 and wait for activations
---------------------------------------------------------------------------- */
void InitIP21(void)
{
  CString LogMsgTxt;
  long  TskRecID,        // external task record ID
        ActRecID,        // activated record ID
        ActField;        // field tag of activation field
  short Startup = TRUE,
        ActCode,         // record activation code
        Priority;        // activation priority
  char  COSFlag;         // COS flag
  
  if (!INISETC())
  {
    printf("\n IP.21 is NOT running....\n\n");
    exit(0);
  }
  #ifdef _DEBUG
    NAME_PROCESS("TSK_WCSE", 8, &IP21Error);
  #endif

  Log.APPVER = "1.5"; // set the application version number to display
  EXTSKINI(&TskRecID, &IP21Error);
  InitProgVars();
  LogMsgTxt = "WC System Effectiveness History Startup - Version " + Log.APPVER;
  Log.LogMessage(2, (LPCTSTR) LogMsgTxt);
  while (IP21Error.ERRCODE == SUCCESS)
  {
    EXTASKCHK(&ActRecID, &ActField, &Priority, &ActCode, &COSFlag, &IP21Error);
    if (!ActRecID)
    {
      EXTSKWAI();
    }
    else
    {
      switch(ActCode)
      {
        case 0:
          break;

        case 1: // activation from WCSEHist records
          ReadWCSEHist(ActRecID);
          break;

        default:
          break;
      }
    }
  }   
  ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
  LogMsgTxt.Format("WC System Effectiveness History Shutdown - %.*s\n\n", IP21ErrorLength, IP21ErrorMsg);
  Log.LogMessage(2, (LPCTSTR) LogMsgTxt);
  ENDSETC();         
}
/* -------------------------------------------------------------------------
   Get the machine and workorder number for the SE data collection
   ------------------------------------------------------------------------- */
void ReadWCSEHist(long RecID)
{
  long ReadTags[2] = {WONUM_FT, MACHNUM_FT};
  short ReadTypes[2] = {WONUMLEN, DTYPLONG};
  struct { char WO[WONUMLEN];
           long MM;} ReadData; 
  short rNum,
        j;
  int   WOLen;
  CString LogMsgTxt;
  SEHistData.ClearSEData();
  RDBVALS(RecID, 2, ReadTags, ReadTypes, &ReadData, &rNum, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("ReadWCSEHist: data read error - %.*s", IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  // validate data
  for (j=0; j<WONUMLEN; j++)
  {
    if ((ReadData.WO[j] > 20) && (ReadData.WO[j] < 123))
    {
      SEHistData.Workorder +=  ReadData.WO[j];  
    }
  }
  WOLen = SEHistData.Workorder.GetLength();
  if ((WOLen == WONUMLEN) && (ReadData.MM > 0))
  {    
    SEHistData.MachineNumber = ReadData.MM;
    CollectSEData();
  }
}
/* -------------------------------------------------------------------------
   Collect SE data from various IP21 records
   ------------------------------------------------------------------------- */
void CollectSEData(void)
{
  CString LogMsgTxt,
          WOBuf;
  char  StdCycleRecName[StdCycleTimeNameLen],
        StartupHistRecName[MMStartupHistNameLen],
        WOHistRecName[WOHistNameLen],
        MachEventRecName[MachEventNameLen],
        TmBuf[24],
        TmErr;
  long  NumLogOccs       = 0,
        StdCycleRecID    = 0,
        StartupHistRecID = 0,
        WOHistRecID      = 0,
        MachEventRecID   = 0;
  long  dbTime;
  int   CmpResult        = 0;
  short ftOK,
        occOK,
        EventOcc,
        PrintOK,
        StartOK,
        StopOK,
        j,
        k;

  void  *ptrData[11];
  long  ptrTags[11];
  short ptrTypes[11];
  
  char  LogWONum[MAXHISTORY][WONUMLEN],
        LogPartName[MAXHISTORY][PARTNAMELEN],
        LogMoldName[MAXHISTORY][MOLDNAMELEN];
  float LogStdCycleTime[MAXHISTORY],
        LogYield[MAXHISTORY];
  unsigned long TotalInterruptDuration = 0,
                TotalStartupTime       = 0,
                LogInterruptDuration[MAXHISTORY],
                LogStartupTime[MAXHISTORY],
                LogDateDone[MAXHISTORY],
                LogMachNum[MAXHISTORY],
                LogWIPQty[MAXHISTORY],
                LogDoneQty[MAXHISTORY],
                LogRejQty[MAXHISTORY],
                LogCycleCount[MAXHISTORY],
                LogRunTime[MAXHISTORY];
  long          LogFaultCount[MAXFAULTCOUNTS];
  long          WOEvent_Time[MAXWOEVENTS];
  char          WOEvent_WONum[MAXWOEVENTS][WONUMLEN];
  short         WOEvent_Type[MAXWOEVENTS];


  // debug - remove after testing ----------------------------------------
    LogMsgTxt.Format("Collecting SE data for workorder %s on machine %d",
                     SEHistData.Workorder, SEHistData.MachineNumber);
    Log.LogMessage(0, (LPCTSTR) LogMsgTxt);
  // ---------------------------------------------------------------------

  // decode the required data records
  sprintf(StdCycleRecName, "MM%-dStdCycle", SEHistData.MachineNumber);
  sprintf(StartupHistRecName, "MM%-dStartupHist", SEHistData.MachineNumber);
  sprintf(WOHistRecName, "MM%-dWOHist", SEHistData.MachineNumber);
  sprintf(MachEventRecName, "MM%-dEvent", SEHistData.MachineNumber);
  DECODNAM(StdCycleRecName, (strlen(StdCycleRecName)), &StdCycleRecID, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData - %s decode error - %.*s", StdCycleRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  DECODNAM(StartupHistRecName, (strlen(StartupHistRecName)), &StartupHistRecID, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s decode error - %.*s", StartupHistRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  DECODNAM(WOHistRecName, (strlen(WOHistRecName)), &WOHistRecID, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData - %s decode error - %.*s", WOHistRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  DECODNAM(MachEventRecName, (strlen(MachEventRecName)), &MachEventRecID, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData - %s decode error - %.*s", MachEventRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  // read and store data from MMxxxStdCycle record
  DB2LONG(StdCycleRecID, NUMLOGRECORDS_FT, &NumLogOccs, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s number of log records read error - %.*s",
                      StdCycleRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  if (NumLogOccs > MAXHISTORY)
    NumLogOccs = MAXHISTORY;
  ptrTypes[0] = WONUMLEN;
  ptrTypes[1] = DTYPREAL;
  ptrTags[0]  = LOGWORKORDER_FT;
  ptrTags[1]  = LOGSTDCYCLE_FT;
  ptrData[0]  = (short*)LogWONum;
  ptrData[1]  = (short*)LogStdCycleTime;
  MRDBOCCS(StdCycleRecID, 2, ptrTags, ptrTypes, 1, NumLogOccs, ptrData, &occOK, &ftOK, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s data read error - %.*s",
                      StdCycleRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  for (j=0; j<occOK; j++)
  {
    WOBuf.Empty();
    for (k=0; k<WONUMLEN; k++)
      WOBuf += LogWONum[j][k]; 
     
    if (SEHistData.Workorder == WOBuf) 
    {
      SEHistData.DesignCycleTime = LogStdCycleTime[j];
      break;
    }
  }
  // read and store data from MMxxxStartupHist record
  DB2LONG(StartupHistRecID, NUMLOGRECORDS_FT, &NumLogOccs, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s number of log records read error - %.*s",
                      StartupHistRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  if (NumLogOccs > MAXHISTORY)
    NumLogOccs = MAXHISTORY;
  ptrTypes[0] = WONUMLEN;
  ptrTypes[1] = DTYPLONG;
  ptrTypes[2] = DTYPLONG;
  ptrTags[0]  = LOGWORKORDER_FT;
  ptrTags[1]  = INTERRUPTDURATION_FT;
  ptrTags[2]  = STARTUPTIME_FT;
  ptrData[0]  = (short*)LogWONum;
  ptrData[1]  = (short*)LogInterruptDuration;
  ptrData[2]  = (short*)LogStartupTime;
  MRDBOCCS(StartupHistRecID, 3, ptrTags, ptrTypes, 1, NumLogOccs, ptrData, &occOK, &ftOK, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s data read error - %.*s",
                      StartupHistRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  for (j=0; j<occOK; j++)
  {
    WOBuf.Empty();
    for (k=0; k<WONUMLEN; k++)
      WOBuf += LogWONum[j][k]; 
      
    if (SEHistData.Workorder == WOBuf) 
    {
      TotalInterruptDuration += LogInterruptDuration[j];
      TotalStartupTime       += LogStartupTime[j];
    }
  }
  SEHistData.FaultTime = TotalInterruptDuration;
  SEHistData.SetupTime = TotalStartupTime;

  // read and store data from MMxxxWOHist record
  DB2LONG(WOHistRecID, NUMLOGRECORDS_FT, &NumLogOccs, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s number of log records read error - %.*s",
                      WOHistRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  if (NumLogOccs > MAXHISTORY)
    NumLogOccs = MAXHISTORY;
  ptrTypes[0]  = DTYPTIME;
  ptrTypes[1]  = WONUMLEN;
  ptrTypes[2]  = DTYPLONG;
  ptrTypes[3]  = PARTNAMELEN;
  ptrTypes[4]  = MOLDNAMELEN;
  ptrTypes[5]  = DTYPLONG;
  ptrTypes[6]  = DTYPLONG;
  ptrTypes[7]  = DTYPLONG;
  ptrTypes[8]  = DTYPLONG;
  ptrTypes[9]  = DTYPLONG;
  ptrTypes[10] = DTYPREAL;
  ptrTags[0]   = LOGDATEDONE_FT;
  ptrTags[1]   = LOGWORKORDER_FT;
  ptrTags[2]   = LOGMACHNUMBER_FT;
  ptrTags[3]   = LOGPARTNAME_FT;
  ptrTags[4]   = LOGMOLDNAME_FT;
  ptrTags[5]   = LOGWIPQTY_FT;
  ptrTags[6]   = LOGDONEQTY_FT;
  ptrTags[7]   = LOGREJQTY_FT;
  ptrTags[8]   = LOGCYCLECOUNT_FT;
  ptrTags[9]   = LOGRUNTIME_FT;
  ptrTags[10]  = LOGYIELD_FT;
  ptrData[0]   = (short*)LogDateDone;
  ptrData[1]   = (short*)LogWONum;
  ptrData[2]   = (short*)LogMachNum;
  ptrData[3]   = (short*)LogPartName;
  ptrData[4]   = (short*)LogMoldName;
  ptrData[5]   = (short*)LogWIPQty;
  ptrData[6]   = (short*)LogDoneQty;
  ptrData[7]   = (short*)LogRejQty;
  ptrData[8]   = (short*)LogCycleCount;
  ptrData[9]   = (short*)LogRunTime;
  ptrData[10]  = (short*)LogYield;
  MRDBOCCS(WOHistRecID, 11, ptrTags, ptrTypes, 1, NumLogOccs, ptrData, &occOK, &ftOK, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s data read error - %.*s",
                      WOHistRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  for (j=0; j<occOK; j++)
  {
    WOBuf.Empty();
    for (k=0; k<WONUMLEN; k++)
      WOBuf += LogWONum[j][k]; 
    if (SEHistData.Workorder == WOBuf)  
    {
      TMST2ASCII(LogDateDone[j], TmBuf, 20, &TmErr); // convert IP21 timestamp
      TmBuf[18] = '\0';
      SEHistData.MachineNumber = LogMachNum[j];
      SEHistData.ProductionTime = ((float)LogRunTime[j] + (float)TotalInterruptDuration) / 36000;
      SEHistData.FaultTime = (float)TotalInterruptDuration / 36000;
      SEHistData.SetupTime = (float)TotalStartupTime / 36000;
      SEHistData.PiecesIn = LogWIPQty[j];
      SEHistData.PiecesOut = LogDoneQty[j] + LogRejQty[j];
      SEHistData.GoodQty = LogDoneQty[j];
      SEHistData.RejectQty = LogRejQty[j];
      SEHistData.CycleCount = LogCycleCount[j];
      SEHistData.UpTime = (float)LogRunTime[j] / 36000;
      SEHistData.Yield = LogYield[j] / 100; // convert back to decimal
      SEHistData.Availability = SEHistData.UpTime / SEHistData.ProductionTime;
      SEHistData.CalcCycleTime = ((float)LogRunTime[j] / (float)LogCycleCount[j]) / 10;
      SEHistData.Efficiency = SEHistData.DesignCycleTime / SEHistData.CalcCycleTime;
      SEHistData.SE = SEHistData.Availability * SEHistData.Efficiency * SEHistData.Yield;
      for (k=0; k<PARTNAMELEN; k++)
      {
        if ((LogPartName[j][k] > MINCHARVAL) && (LogPartName[j][k] < MAXCHARVAL))
        {
          SEHistData.PartName += LogPartName[j][k];
        }
      }
      for (k=0; k<MOLDNAMELEN; k++)
      {
        if ((LogMoldName[j][k] > MINCHARVAL) && (LogPartName[j][k] < MAXCHARVAL))
        {
          SEHistData.MoldName += LogMoldName[j][k];
        }
      }
      break;
    }
  }
  // read and store data from MMxxxEvent record
  DB2LONG(MachEventRecID, NUMLOGRECORDS_FT, &NumLogOccs, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s number of log records read error - %.*s",
                      MachEventRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  if (NumLogOccs > MAXFAULTCOUNTS)
    NumLogOccs = MAXFAULTCOUNTS;
  ptrTypes[0] = WONUMLEN;
  ptrTypes[1] = DTYPLONG;
  ptrTags[0]  = LOGWORKORDER_FT;
  ptrTags[1]  = LOGFAULTCOUNT_FT;
  ptrData[0]  = (short*)LogWONum;
  ptrData[1]  = (short*)LogFaultCount;
  MRDBOCCS(MachEventRecID, 2, ptrTags, ptrTypes, 1, NumLogOccs, ptrData, &occOK, &ftOK, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: %s data read error - %.*s",
                      MachEventRecName, IP21ErrorLength, IP21ErrorMsg);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  for (j=0; j<occOK; j++)
  {
    WOBuf.Empty();
    for (k=0; k<WONUMLEN; k++)
      WOBuf += LogWONum[j][k]; 
      
    if (SEHistData.Workorder == WOBuf) 
    {
      SEHistData.FaultCount = LogFaultCount[j];
    }
  }






  // read and store data from WOEvent record
  DB2LONG(WOEventID, NUMLOGRECORDS_FT, &NumLogOccs, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: number of log records read error (ID=%d) - %.*s",
                      IP21ErrorLength, IP21ErrorMsg, WOEventID);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  if (NumLogOccs > MAXWOEVENTS)
    NumLogOccs = MAXWOEVENTS;

  ptrTypes[0] = DTYPTIME;
  ptrTypes[1] = WONUMLEN;
  ptrTypes[2] = DTYPSHRT;
  ptrTags[0]  = LOG_TIME_FT; 
  ptrTags[1]  = LOGWORKORDER_FT;
  ptrTags[2]  = LOGVALUE_FT;
  ptrData[0]  = (short*)WOEvent_Time;
  ptrData[1]  = (short*)WOEvent_WONum;
  ptrData[2]  = (short*)WOEvent_Type;
  
  MRDBOCCS(WOEventID, 3, ptrTags, ptrTypes, 1, NumLogOccs, ptrData, &occOK, &ftOK, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    ERRMESS(&IP21Error, IP21ErrorMsg, &IP21ErrorLength);
    LogMsgTxt.Format("CollectSEData: data read error (ID=%d) - %.*s",
                      IP21ErrorLength, IP21ErrorMsg, WOEventID);
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    IP21Error.ERRCODE = SUCCESS; // reset error code   
    return;
  }
  // set all timestamps to current time
  dbTime = GETDBTIM();
  TMST2ASCII(dbTime, TmBuf, 18, &TmErr);
  SEHistData.DateCreated = TmBuf;
  SEHistData.DateStart = TmBuf;
  SEHistData.DateDone = TmBuf;
  PrintOK  = 0;
  StartOK  = 0;
  StopOK   = 0;
  EventOcc = 0;
    
  // search for the event timestamps
  while ((EventOcc<occOK) && ((PrintOK+StartOK+StopOK)<3))
  {
    WOBuf.Empty();
    for (k=0; k<WONUMLEN; k++)
      WOBuf += WOEvent_WONum[EventOcc][k]; 
    
    if (SEHistData.Workorder == WOBuf) 
    {
      if ((WOEvent_Type[EventOcc] == WOEVENT_PRINTED) && (PrintOK == 0))
      {
        TMST2ASCII(WOEvent_Time[EventOcc], TmBuf, 18, &TmErr); // convert IP21 timestamp
        SEHistData.DateCreated = TmBuf;
        PrintOK = 1;
      }
      if ((WOEvent_Type[EventOcc] == WOEVENT_START) && (StartOK == 0))
      {
        TMST2ASCII(WOEvent_Time[EventOcc], TmBuf, 18, &TmErr); // convert IP21 timestamp
        SEHistData.DateStart = TmBuf;
        StartOK = 1;
      } 
      if ((WOEvent_Type[EventOcc] == WOEVENT_STOP) && (StopOK == 0))
      {
        TMST2ASCII(WOEvent_Time[EventOcc], TmBuf, 18, &TmErr); // convert IP21 timestamp
        SEHistData.DateDone = TmBuf;
        StopOK = 1;
      }
    }
    EventOcc++;
  }       
  LookupMfgSysInfo();
  UpdateMachineHistory();
  UpdateWorkorderHistory();
}
/* -------------------------------------------------------------------------
   Lookup manufacturing system information
   ------------------------------------------------------------------------- */
void LookupMfgSysInfo(void)
{
  CDatabase db;
  CString LogMsgTxt,
          dbConn,
          strSQL;

  strSQL =  "SELECT ToolID, MoldName, MfgSystem, CellName ";
  strSQL += "FROM MfgSystemInfo WHERE MoldName = '";
  strSQL +=  SEHistData.MoldName;
  strSQL += "'";
  dbConn = DSN_WCSEHIST;

  try
  {
    if (db.OpenEx(dbConn,CDatabase::useCursorLib))
    {
      cMfgSysInfo rsMfgSysInfo(&db);
      if (rsMfgSysInfo.Open(CRecordset::snapshot, strSQL))
      {  
        if ((!rsMfgSysInfo.IsBOF()) && (!rsMfgSysInfo.IsEOF()))
        {          
          SEHistData.Cell = rsMfgSysInfo.m_CellName;
          SEHistData.MfgSystem = rsMfgSysInfo.m_MfgSystem;
          SEHistData.ToolID = rsMfgSysInfo.m_ToolID;
        }        
        rsMfgSysInfo.Close();
      }
    }      
    db.Close();
  }
  catch( CDBException* e )
  {
    LogMsgTxt += " ** ";
    LogMsgTxt += (LPCSTR) e->m_strError;
    Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    e->Delete();
  }
}
/* -------------------------------------------------------------------------
   Update the Machine History table
   ------------------------------------------------------------------------- */
void UpdateMachineHistory(void)
{
  short UpdateErr = 0;
  CString dbConn,
          MachNameBuf,
          LogMsgTxt;
  SYSTEMTIME systime;
  CDatabase db;

  GetLocalTime(&systime);
  dbConn = DSN_WCSEHIST;
  try
  {
    if (db.OpenEx(dbConn,CDatabase::useCursorLib))
    {
      TblMachineHistory rst(&db);
      rst.m_strFilter.Format("Workorder='%s'",SEHistData.Workorder); 
      if (rst.Open(CRecordset::snapshot))
      {
        if (!rst.IsEOF() && !rst.IsBOF())
        {
          rst.Edit();
          if (rst.m_Date_Created==NULL)
          {
            rst.m_Date_Created = CTime(systime, -1);
          }
          rst.m_Tool = (LPCTSTR) SEHistData.MoldName;
          rst.m_Machine_Name = MachNameBuf;
	        rst.m_Machine_Number = SEHistData.MachineNumber;
	        rst.m_Machine_Type = "Inj Mold";
          rst.m_Cell = SEHistData.Cell;
          rst.m_Production_System =SEHistData.MfgSystem;
          rst.m_Tool = SEHistData.MoldName;
	        rst.m_Tool_2 =  SEHistData.ToolID;
	        rst.m_Uptime = SEHistData.UpTime;    
          rst.m_Production_Time = SEHistData.ProductionTime;
	        rst.m_Fault_Time = SEHistData.FaultTime;
	        rst.m_Setup_Time = SEHistData.SetupTime;
	        rst.m_Availability = SEHistData.Availability;
	        rst.m_Se = SEHistData.SE;
          rst.m_Fault_Count = SEHistData.FaultCount;
	        rst.m_Pieces_In = SEHistData.PiecesIn;
	        rst.m_Pieces_Out = SEHistData.PiecesOut;
	        rst.m_Machine_Good_Qty = SEHistData.GoodQty;
	        rst.m_Machine_Good_Qty_Unit_of_Measure = "";
	        rst.m_Cycle_Count = SEHistData.CycleCount;
	        rst.m_Calc_Cycle_Time = SEHistData.CalcCycleTime;
	        rst.m_Designed_Cycle_Time = SEHistData.DesignCycleTime;
	        rst.m_Yield = SEHistData.Yield;
	        rst.m_Efficiency = SEHistData.Efficiency;
          if ((rst.m_Start_Time==NULL) || (rst.m_Start_Time.Format("%B %d %Y")==""))
            rst.m_Start_Time = SEHistData.ConvertTime(SEHistData.DateStart); 
          if ((rst.m_End_Time==NULL) || (rst.m_End_Time.Format("%B %d %Y")==""))
            rst.m_End_Time = SEHistData.ConvertTime(SEHistData.DateDone);
        }
        else
        {
          MachNameBuf.Format("M%d", SEHistData.MachineNumber);
          rst.AddNew();
          rst.m_Date_Created = CTime(systime, -1);
          rst.m_Workorder = (LPCTSTR) SEHistData.Workorder;
          rst.m_Tool = (LPCTSTR) SEHistData.MoldName;
          rst.m_Machine_Name = MachNameBuf;
	        rst.m_Machine_Number = SEHistData.MachineNumber;
	        rst.m_Machine_Type = "Inj Mold";
          rst.m_Cell = SEHistData.Cell;
          rst.m_Production_System =SEHistData.MfgSystem;
          rst.m_Production_Line = "";
          rst.m_Tool = SEHistData.MoldName;
	        rst.m_Tool_2 =  SEHistData.ToolID;
	        rst.m_Uptime = SEHistData.UpTime;
          rst.m_Production_Time = SEHistData.ProductionTime;
	        rst.m_Fault_Time = SEHistData.FaultTime;
	        rst.m_Setup_Time = SEHistData.SetupTime;
	        rst.m_Cleanup_Time = 0;
	        rst.m_Availability = SEHistData.Availability;
	        rst.m_Se = SEHistData.SE;
          rst.m_Fault_Count = SEHistData.FaultCount;
	        rst.m_Pieces_In = SEHistData.PiecesIn;
	        rst.m_Pieces_Out = SEHistData.PiecesOut;
	        rst.m_Machine_Good_Qty = SEHistData.GoodQty;
	        rst.m_Machine_Good_Qty_Unit_of_Measure = "";
	        rst.m_Cycle_Count = SEHistData.CycleCount;
	        rst.m_Calc_Cycle_Time = SEHistData.CalcCycleTime;
	        rst.m_Designed_Cycle_Time = SEHistData.DesignCycleTime;
	        rst.m_Yield = SEHistData.Yield;
	        rst.m_Efficiency = SEHistData.Efficiency;
          rst.m_Start_Time = SEHistData.ConvertTime(SEHistData.DateStart); 
          rst.m_End_Time = SEHistData.ConvertTime(SEHistData.DateDone);
        }  
          
        if (!rst.Update())
        {
          LogMsgTxt.Format("UpdateMachineHistory: %s update data error",SEHistData.Workorder);
          Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
          UpdateErr = 1;
        }
      }
      else
      {
        LogMsgTxt.Format("UpdateMachineHistory: database open error for workorder %s",SEHistData.Workorder);
        Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
      }
      
      if (rst.IsOpen())
        rst.Close();
    }
    if (db.IsOpen())
      db.Close();
  }
  catch( CDBException* e )
  {
    UpdateErr = 1;
    LogMsgTxt += " ** ";
    LogMsgTxt += (LPCSTR) e->m_strError;
    e->Delete();
  }
}
/* -------------------------------------------------------------------------
   Update the Workordder History table
   ------------------------------------------------------------------------- */
void UpdateWorkorderHistory(void)
{
  short UpdateErr = 0;
  CString dbConn,
          LogMsgTxt;  
  CDatabase db;

  dbConn = DSN_WCSEHIST;
  
  try
  {
    if (db.OpenEx(dbConn,CDatabase::useCursorLib))
    {
      TblWOHist rsWOHist(&db);
      if (rsWOHist.Open(CRecordset::snapshot))
      { 
        SEHistData.PartName.TrimRight();
        rsWOHist.AddNew();
        rsWOHist.m_Workorder = SEHistData.Workorder;
        rsWOHist.m_Part_Number = SEHistData.PartName;
        rsWOHist.m_Product_Line = " ";
        rsWOHist.m_Good_Qty = SEHistData.GoodQty;
        rsWOHist.m_Good_Qty_Unit_of_Measure = "pcs";
        rsWOHist.m_Start_Date = SEHistData.ConvertTime(SEHistData.DateStart); 
        rsWOHist.m_Close_Date = SEHistData.ConvertTime(SEHistData.DateDone);
        rsWOHist.m_Status = " ";
        if (!rsWOHist.Update())
        {
          LogMsgTxt.Format("UpdateWorkorderHistory: %s update data error",SEHistData.Workorder);
          Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
          UpdateErr = 1;
        }
      }
      else
      {
        LogMsgTxt.Format("UpdateWorkorderHistory: recordset open error for workorder %s",SEHistData.Workorder);
        Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
      }
      if (rsWOHist.IsOpen())
      {
        rsWOHist.Close();
      }
    }  
    else
    {
      LogMsgTxt.Format("UpdateWorkorderHistory: database open error for workorder %s",SEHistData.Workorder);
      Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
    }
    
    if (db.IsOpen())
    {
      db.Close();
    }
  
    // debug - - - - - - - - - - - - - - - - - - 
      LogMsgTxt = "UPDATE COMPLETE...";
      Log.LogMessage(0, (LPCTSTR) LogMsgTxt);
    // - - - - - - - - - - - - - - - - - - - - - 
  }
  catch( CDBException* e )
  {
    UpdateErr = 1;
    LogMsgTxt += " ** ";
    LogMsgTxt += (LPCSTR) e->m_strError;
    e->Delete();
  }
}
/* -------------------------------------------------------------------------
   Update the reject history table
   ------------------------------------------------------------------------- */
void UpdateRejectHistory(void)
{
  CString dbConn,
          LogMsgTxt;
  CDatabase db;

  dbConn = DSN_WCSEHIST;
  try
  {
    if (db.OpenEx(dbConn,CDatabase::useCursorLib))
    {
      TblRejectHistory rst(&db);
      if (rst.Open(CRecordset::snapshot))
      {
        rst.AddNew();
        rst.m_Workorder = SEHistData.Workorder;
        rst.m_Machine_Name =   SEHistData.MachineName;
        rst.m_Reject_Type = "";
	      rst.m_Reject_Qty = SEHistData.RejectQty;
        rst.m_Reject_Qty_Unit_of_Measure = "";
	      rst.m_Badge = 0;
        if (!rst.Update())
        {
          LogMsgTxt.Format("UpdateRejectHistory: %s update data error",SEHistData.Workorder);
          Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
        }
      }
      else
      {
          LogMsgTxt.Format("UpdateRejectHistory: database open error for workorder %s",SEHistData.Workorder);
          Log.LogMessage(1, (LPCTSTR) LogMsgTxt);
      }
      if (rst.IsOpen())
        rst.Close();
    }
    if (db.IsOpen())
      db.Close();
  }
  catch( CDBException* e )
  {
    LogMsgTxt += " ** ";
    LogMsgTxt += (LPCSTR) e->m_strError;
    e->Delete();
  }
}
/* -------------------------------------------------------------------------
   Initialize all program variables, record IDs and field tags.
   ------------------------------------------------------------------------- */
void InitProgVars(void)
{
  short NumChars,
        j;
  long  ft[MAXFIELDS];
  char  *PtrBuf;

  for (j=0; j<MAXFIELDS; j++)
  {    
    PtrBuf   = fieldname[j];
    NumChars = strlen(PtrBuf);
    DECODFT(PtrBuf, NumChars, &ft[j], &IP21Error);
    if (IP21Error.ERRCODE != SUCCESS)
    {
      printf("\n Initialization Failure - %s decode field tag error\n", PtrBuf);
      return; 
    }
    if(!ft[j])
    {
      IP21Error.ERRCODE = NOREC;
      return;
    }
  }
  PtrBuf = WOEVENTNAME;
  NumChars = strlen(PtrBuf);
  DECODNAM(PtrBuf, NumChars, &WOEventID, &IP21Error);
  if (IP21Error.ERRCODE != SUCCESS)
  {
    printf("\n Initialization Failure - %s decode record name error\n", PtrBuf);
    return; 
  }
  if (WOEventID < 1)
  {
    printf("\n Initialization Failure - %s decode record name error\n", PtrBuf);
    IP21Error.ERRCODE = NOREC;
    return; 
  }
  NUMLOGRECORDS_FT     = ft[0];
  LOGDATEDONE_FT       = ft[1];
  LOGWORKORDER_FT      = ft[2];
  LOGMACHNUMBER_FT     = ft[3];
  LOGPARTNAME_FT       = ft[4];
  LOGMOLDNAME_FT       = ft[5];
  LOGWIPQTY_FT         = ft[6];
  LOGDONEQTY_FT        = ft[7];
  LOGREJQTY_FT         = ft[8];
  LOGCYCLECOUNT_FT     = ft[9];
  LOGRUNTIME_FT        = ft[10];
  LOGYIELD_FT          = ft[11];
  INTERRUPTDURATION_FT = ft[12];
  STARTUPTIME_FT       = ft[13];
  LOGSTDCYCLE_FT       = ft[14];
  WONUM_FT             = ft[15];
  MACHNUM_FT           = ft[16];
  LOG_TIME_FT          = ft[17];
  LOGVALUE_FT          = ft[18];
  LOGFAULTCOUNT_FT     = ft[19];
}


