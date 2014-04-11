// cSEHistData.cpp: implementation of the cSEHistData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cSEHistData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cSEHistData::cSEHistData()
{

}

cSEHistData::~cSEHistData()
{

}

cSEHistData::ClearSEData()
{
  // clear all the SE data variables
	RejectType.Empty();
	MachineName.Empty();
	Cell.Empty();
	DateCreated.Empty();
  DateDone.Empty();
  DateStart.Empty();
 	Workorder.Empty();
  PartName.Empty();
  MoldName.Empty();
  MfgSystem.Empty();
  ToolID.Empty();
  MachineNumber   = 0;
  RejectQty       = 0;
	BadgeNum        = 0;
	CycleCount      = 0;
	GoodQty         = 0;
	PiecesOut       = 0;
	PiecesIn        = 0;
	FaultCount      = 0;
	SE              = 0;
	Availability    = 0;
	Efficiency      = 0;
	Yield           = 0;
	DesignCycleTime = 0;
	CalcCycleTime   = 0;
	SetupTime       = 0;
	FaultTime       = 0;
	UpTime          = 0;
	ProductionTime  = 0;
}

// ----------------------------------------
// convert InfoPlus time to CTime object
// ----------------------------------------
CTime cSEHistData::ConvertTime(CString strDT)
{
  CTime DTBuff = CTime::GetCurrentTime();
  CString MonthBuff,
          LogMsgTxt;
  CString MonthName[12];
  int imonth  = -1,
      iday    = -1,
      iyear   = -1,
      ihour   = -1,
      iminute = -1,
      isecond = -1,
      idst    = -1;
  int j;
  
  MonthName[0] =  "JAN";
  MonthName[1] =  "FEB";
  MonthName[2] =  "MAR";
  MonthName[3] =  "APR";
  MonthName[4] =  "MAY";
  MonthName[5] =  "JUN";
  MonthName[6] =  "JUL";
  MonthName[7] =  "AUG";
  MonthName[8] =  "SEP";
  MonthName[9] =  "OCT";
  MonthName[10] = "NOV";
  MonthName[11] = "DEC";
  MonthBuff = strDT.Left(3);
  for (j=0; j<12; j++)
  {
    if (MonthBuff.CompareNoCase(MonthName[j]) == 0)
    {      
      imonth = j+1;
      break;
    }
  }
  iday    = atoi(strDT.Mid(4,2));
  iyear   = atoi(strDT.Mid(7,2)) + 2000;
  ihour   = atoi(strDT.Mid(10,2));
  iminute = atoi(strDT.Mid(13,2));
  isecond = atoi(strDT.Mid(16,2));
  if (imonth > -1)
  {
    DTBuff = CTime(iyear, imonth, iday, ihour, iminute, isecond, idst);
  }
  return(DTBuff);
}
