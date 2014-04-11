// DateConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DateConverter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		MakeDate();
	}

  cin.ignore();
	return nRetCode;
}

void MakeDate(void)
{
  CString strDT = "DEC-06-04 12:36:16";
  CString MonthBuffer;
  CString MonthList[12];
  int imonth  = -1,
      iday    = -1,
      iyear   = -1,
      ihour   = -1,
      iminute = -1,
      isecond = -1;
  int j;
  
  MonthList[0] =  "JAN";
  MonthList[1] =  "FEB";
  MonthList[2] =  "MAR";
  MonthList[3] =  "APR";
  MonthList[4] =  "MAY";
  MonthList[5] =  "JUN";
  MonthList[6] =  "JUL";
  MonthList[7] =  "AUG";
  MonthList[8] =  "SEP";
  MonthList[9] =  "OCT";
  MonthList[10] = "NOV";
  MonthList[11] = "DEC";
  MonthBuffer = strDT.Left(3);
  
  for (j=0; j<12; j++)
  {
    if (MonthBuffer.CompareNoCase(MonthList[j]) == 0)
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
  CTime t( iyear, imonth, iday, ihour, iminute, isecond );
  CString s = t.Format( "%c" );
	cout << "CTime = " << s << endl;
}
