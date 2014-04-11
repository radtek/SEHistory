#if !defined(AFX_TBLWOHIST_H__9FD85458_8180_4F7F_8BA3_2D19E86D2E6A__INCLUDED_)
#define AFX_TBLWOHIST_H__9FD85458_8180_4F7F_8BA3_2D19E86D2E6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TblWOHist.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TblWOHist recordset

class TblWOHist : public CRecordset
{
public:
	TblWOHist(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TblWOHist)

// Field/Param Data
	//{{AFX_FIELD(TblWOHist, CRecordset)
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
	//{{AFX_VIRTUAL(TblWOHist)
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

#endif // !defined(AFX_TBLWOHIST_H__9FD85458_8180_4F7F_8BA3_2D19E86D2E6A__INCLUDED_)
