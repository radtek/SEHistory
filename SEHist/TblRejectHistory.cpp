// TblRejectHistory.cpp : implementation file
//

#include "stdafx.h"
#include "TblRejectHistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TblRejectHistory

IMPLEMENT_DYNAMIC(TblRejectHistory, CRecordset)

TblRejectHistory::TblRejectHistory(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TblRejectHistory)
	m_ID = 0;
	m_Workorder = _T("");
	m_Machine_Name = _T("");
	m_Reject_Type = _T("");
	m_Reject_Qty = 0;
	m_Reject_Qty_Unit_of_Measure = _T("");
	m_Badge = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString TblRejectHistory::GetDefaultConnect()
{
	return _T("ODBC;DSN=ProductionHistoryWC");
}

CString TblRejectHistory::GetDefaultSQL()
{
	return _T("[Reject History]");
}

void TblRejectHistory::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TblRejectHistory)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Workorder]"), m_Workorder);
	RFX_Text(pFX, _T("[Machine Name]"), m_Machine_Name);
	RFX_Text(pFX, _T("[Reject Type]"), m_Reject_Type);
	RFX_Long(pFX, _T("[Reject Qty]"), m_Reject_Qty);
	RFX_Text(pFX, _T("[Reject Qty Unit of Measure]"), m_Reject_Qty_Unit_of_Measure);
	RFX_Date(pFX, _T("[Timestamp]"), m_Timestamp);
	RFX_Int(pFX, _T("[Badge]"), m_Badge);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TblRejectHistory diagnostics

#ifdef _DEBUG
void TblRejectHistory::AssertValid() const
{
	CRecordset::AssertValid();
}

void TblRejectHistory::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
