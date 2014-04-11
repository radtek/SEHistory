// cMfgSysInfo.cpp : implementation file
//

#include "stdafx.h"
#include "cMfgSysInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cMfgSysInfo

IMPLEMENT_DYNAMIC(cMfgSysInfo, CRecordset)

cMfgSysInfo::cMfgSysInfo(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(cMfgSysInfo)
	m_ToolID = _T("");
	m_MoldName = _T("");
	m_MfgSystem = _T("");
	m_CellName = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString cMfgSysInfo::GetDefaultConnect()
{
	return _T("ODBC;DSN=ProductionHistoryWC");
}

CString cMfgSysInfo::GetDefaultSQL()
{
	return _T("[MfgSystemInfo]");
}

void cMfgSysInfo::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(cMfgSysInfo)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ToolID]"), m_ToolID);
	RFX_Text(pFX, _T("[MoldName]"), m_MoldName);
	RFX_Text(pFX, _T("[MfgSystem]"), m_MfgSystem);
	RFX_Text(pFX, _T("[CellName]"), m_CellName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// cMfgSysInfo diagnostics

#ifdef _DEBUG
void cMfgSysInfo::AssertValid() const
{
	CRecordset::AssertValid();
}

void cMfgSysInfo::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
