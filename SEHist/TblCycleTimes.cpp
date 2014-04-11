// TblCycleTimes.cpp : implementation file
//

#include "stdafx.h"
#include "TblCycleTimes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TblCycleTimes

IMPLEMENT_DYNAMIC(TblCycleTimes, CRecordset)

TblCycleTimes::TblCycleTimes(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TblCycleTimes)
	m_ID = 0;
	m_Part = _T("");
	m_Machine_Name = _T("");
	m_Tool = _T("");
	m_Design_Cycle_Time = 0.0f;
	m_Unit_of_Measure = _T("");
	m_Prefered_Machine = FALSE;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString TblCycleTimes::GetDefaultConnect()
{
	return _T("ODBC;DSN=ProductionHistoryWC");
}

CString TblCycleTimes::GetDefaultSQL()
{
	return _T("[CycleTimes]");
}

void TblCycleTimes::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TblCycleTimes)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Part]"), m_Part);
	RFX_Text(pFX, _T("[Machine Name]"), m_Machine_Name);
	RFX_Text(pFX, _T("[Tool]"), m_Tool);
	RFX_Single(pFX, _T("[Design Cycle Time]"), m_Design_Cycle_Time);
	RFX_Text(pFX, _T("[Unit of Measure]"), m_Unit_of_Measure);
	RFX_Bool(pFX, _T("[Prefered Machine]"), m_Prefered_Machine);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TblCycleTimes diagnostics

#ifdef _DEBUG
void TblCycleTimes::AssertValid() const
{
	CRecordset::AssertValid();
}

void TblCycleTimes::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
