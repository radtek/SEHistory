// Logger.cpp : implementation file
//

#include "stdafx.h"
#include "Logger.h"
#include <iostream.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogger

CLogger::CLogger()
{
  // Get the value of the SETCIMLOGS environment variable
 
  pFilePath = NULL;
  pFilePath = getenv("SETCIMLOGS");
  if( pFilePath != NULL )
  {
    strcat(pFilePath, "\\SEHist.log");
  }
  else
  {
    pFilePath = "C:\\Temp\\SEHist.log";
  }
}
CLogger::~CLogger()
{
}

BEGIN_MESSAGE_MAP(CLogger, CWnd)
	//{{AFX_MSG_MAP(CLogger)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CLogger message handlers
void CLogger::LogMessage(short msgid, LPCTSTR msgtxt)
{
  CStdioFile LogFile;
  CFileException e; 
  CString MsgBuf;
  SYSTEMTIME systime;
  char MsgType[3][4] = {"   ", "***", "+++"};

  GetLocalTime(&systime);
  MsgBuf.Empty();
  MsgBuf.Format("%s %02d/%02d/%04d %02d:%02d:%02d ",MsgType[msgid], systime.wMonth, systime.wDay,systime.wYear,
                      systime.wHour, systime.wMinute, systime.wSecond);
  MsgBuf += msgtxt;
  MsgBuf += "\n";
  if (LogFile.Open((LPCTSTR)pFilePath, CFile::modeWrite, &e))
  { 
    LogFile.SeekToEnd();
    LogFile.WriteString((LPCTSTR)MsgBuf);
    LogFile.Close();
  } 
  else
  {
    if (LogFile.Open((LPCTSTR)pFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &e))
    {
      CString LogHeading;
      LogHeading.Empty();
      LogHeading =  " WC Division          System Effectiveness Data Archiver          Ver " + APPVER + " wrc\n";
      LogHeading += "-------------------------------------------------------------------------------\n";
      LogFile.WriteString((LPCTSTR) LogHeading);
      LogFile.WriteString((LPCTSTR) MsgBuf);
      LogFile.Close();
    }
    else
    {
      cout << " Unable to Open SEHist.log file! " <<  e.m_cause << endl;
    }
  }
}
