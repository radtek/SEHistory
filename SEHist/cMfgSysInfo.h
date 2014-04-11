#if !defined(AFX_CMFGSYSINFO_H__D6720021_A081_4472_98F6_3DBBF42599D1__INCLUDED_)
#define AFX_CMFGSYSINFO_H__D6720021_A081_4472_98F6_3DBBF42599D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// cMfgSysInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// cMfgSysInfo recordset

class cMfgSysInfo : public CRecordset
{
public:
	cMfgSysInfo(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(cMfgSysInfo)

// Field/Param Data
	//{{AFX_FIELD(cMfgSysInfo, CRecordset)
	CString	m_ToolID;
	CString	m_MoldName;
	CString	m_MfgSystem;
	CString	m_CellName;
	long	m_Cavities;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cMfgSysInfo)
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

#endif // !defined(AFX_CMFGSYSINFO_H__D6720021_A081_4472_98F6_3DBBF42599D1__INCLUDED_)
