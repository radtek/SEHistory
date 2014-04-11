#if !defined(AFX_TBLCYCLETIMES_H__C917ADFD_2043_4696_855A_F9BC9967319F__INCLUDED_)
#define AFX_TBLCYCLETIMES_H__C917ADFD_2043_4696_855A_F9BC9967319F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TblCycleTimes.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TblCycleTimes recordset

class TblCycleTimes : public CRecordset
{
public:
	TblCycleTimes(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(TblCycleTimes)

// Field/Param Data
	//{{AFX_FIELD(TblCycleTimes, CRecordset)
	long	m_ID;
	CString	m_Part;
	CString	m_Machine_Name;
	CString	m_Tool;
	float	m_Design_Cycle_Time;
	CString	m_Unit_of_Measure;
	BOOL	m_Prefered_Machine;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TblCycleTimes)
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

#endif // !defined(AFX_TBLCYCLETIMES_H__C917ADFD_2043_4696_855A_F9BC9967319F__INCLUDED_)
