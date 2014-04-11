#if !defined(AFX_TBLWORKORDERHISTORY_H__D7F6AECF_C1F4_4A3A_9E8D_22A038FAAC10__INCLUDED_)
#define AFX_TBLWORKORDERHISTORY_H__D7F6AECF_C1F4_4A3A_9E8D_22A038FAAC10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TblWorkorderHistory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TblWorkorderHistory recordset

class TblWorkorderHistory : public CRecordset
{
public:
	TblWorkorderHistory(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TblWorkorderHistory)

// Field/Param Data
	//{{AFX_FIELD(TblWorkorderHistory, CRecordset)
	CString	m_Workorder;
	CString	m_Part_Number;
	CString	m_Product_Line;
	long	m_Good_Qty;
	CString	m_Good_Qty_Unit_of_Measure;
	CTime	m_Start_Date;
	CTime	m_Close_Date;
	CString	m_Status;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TblWorkorderHistory)
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

#endif // !defined(AFX_TBLWORKORDERHISTORY_H__D7F6AECF_C1F4_4A3A_9E8D_22A038FAAC10__INCLUDED_)
