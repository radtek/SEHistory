#if !defined(AFX_TBLMACHINEHISTORY_H__36F0F01E_A201_4B08_A0DC_1F9DC2BE3A05__INCLUDED_)
#define AFX_TBLMACHINEHISTORY_H__36F0F01E_A201_4B08_A0DC_1F9DC2BE3A05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TblMachineHistory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TblMachineHistory recordset

class TblMachineHistory : public CRecordset
{
public:
	TblMachineHistory(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TblMachineHistory)

// Field/Param Data
	//{{AFX_FIELD(TblMachineHistory, CRecordset)
	long	m_ID;
	CString	m_Workorder;
	CTime	m_Date_Created;
	CTime	m_Date_Modified;
	CString	m_Machine_Name;
	int		m_Machine_Number;
	CString	m_Machine_Type;
	CString	m_Cell;
	CString	m_Production_Line;
	CString	m_Production_System;
	CString	m_Tool;
	CString	m_Tool_2;
	float	m_Production_Time;
	float	m_Uptime;
	float	m_Fault_Time;
	float	m_Setup_Time;
	float	m_Cleanup_Time;
	long	m_Fault_Count;
	long	m_Pieces_In;
	long	m_Pieces_Out;
	long	m_Machine_Good_Qty;
	CString	m_Machine_Good_Qty_Unit_of_Measure;
	long	m_Cycle_Count;
	float	m_Calc_Cycle_Time;
	float	m_Designed_Cycle_Time;
	float	m_Yield;
	float	m_Efficiency;
	float	m_Availability;
	float	m_Se;
	CTime	m_Start_Time;
	CTime	m_End_Time;
	int		m_Badge_1;
	int		m_Badge_2;
	int		m_Badge_3;
	int		m_Badge_4;
	int		m_Badge_5;
	CString	m_Comment;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TblMachineHistory)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TBLMACHINEHISTORY_H__36F0F01E_A201_4B08_A0DC_1F9DC2BE3A05__INCLUDED_)
