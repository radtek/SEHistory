// cSEHistData.h: interface for the cSEHistData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CSEHISTDATA_H__D73AF657_7B91_481D_BE32_F7AD46745B37__INCLUDED_)
#define AFX_CSEHISTDATA_H__D73AF657_7B91_481D_BE32_F7AD46745B37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cSEHistData  
{
public:
	ClearSEData();
	CString RejectType;
	CString MachineName;
	CString Cell;
	CString DateCreated;
  CString DateStart;
  CString DateDone;
	CString Workorder;
  CString PartName;
  CString MoldName;
  CString MfgSystem;
  CString ToolID;
  short MachineNumber;
  long RejectQty;
	long BadgeNum;
	long CycleCount;
	long GoodQty;
	long PiecesOut;
	long PiecesIn;
	long FaultCount;
	float SE;
	float Availability;
	float Efficiency;
	float Yield;
	float DesignCycleTime;
	float CalcCycleTime;
	float SetupTime;  // this value is actually the time from machine interrupt until automode
	float FaultTime;
	float UpTime;
	float ProductionTime;
	
  CTime ConvertTime(CString);
  cSEHistData();
	virtual ~cSEHistData();

};

#endif // !defined(AFX_CSEHISTDATA_H__D73AF657_7B91_481D_BE32_F7AD46745B37__INCLUDED_)
