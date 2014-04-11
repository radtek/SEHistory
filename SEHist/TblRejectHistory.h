#if !defined(AFX_TBLREJECTHISTORY_H__B512FB27_9F6C_43E5_9DC3_EBCF60A2071D__INCLUDED_)
#define AFX_TBLREJECTHISTORY_H__B512FB27_9F6C_43E5_9DC3_EBCF60A2071D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TblRejectHistory.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TblRejectHistory recordset

class TblRejectHistory : public CRecordset
{
public:
	TblRejectHistory(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TblRejectHistory)

// Field/Param Data
	//{{AFX_FIELD(TblRejectHistory, CRecordset)
	long	m_ID;
	CString	m_Workorder;
	CString	m_Machine_Name;
	CString	m_Reject_Type;
	long	m_Reject_Qty;
	CString	m_Reject_Qty_Unit_of_Measure;
	CTime	m_Timestamp;
	int		m_Badge;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TblRejectHistory)
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

#endif // !defined(AFX_TBLREJECTHISTORY_H__B512FB27_9F6C_43E5_9DC3_EBCF60A2071D__INCLUDED_)
