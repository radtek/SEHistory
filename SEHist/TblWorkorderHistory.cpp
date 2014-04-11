// TblWorkorderHistory.cpp : implementation file
//

#include "stdafx.h"
//#include "SEHist.h"
#include "TblWorkorderHistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TblWorkorderHistory

IMPLEMENT_DYNAMIC(TblWorkorderHistory, CRecordset)

TblWorkorderHistory::TblWorkorderHistory(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TblWorkorderHistory)
	m_Workorder = _T("");
	m_Part_Number = _T("");
	m_Product_Line = _T("");
	m_Good_Qty = 0;
	m_Good_Qty_Unit_of_Measure = _T("");
	m_Status = _T("");
  m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TblWorkorderHistory::GetDefaultConnect()
{
	return _T("ODBC;DSN=ProductionHistoryWC");
}

CString TblWorkorderHistory::GetDefaultSQL()
{
	return _T("[Workorder History]");
}

void TblWorkorderHistory::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TblWorkorderHistory)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Workorder]"), m_Workorder);
	RFX_Text(pFX, _T("[Part Number]"), m_Part_Number);
	RFX_Text(pFX, _T("[Product Line]"), m_Product_Line);
	RFX_Long(pFX, _T("[Good Qty]"), m_Good_Qty);
	RFX_Text(pFX, _T("[Good Qty Unit of Measure]"), m_Good_Qty_Unit_of_Measure);
	RFX_Date(pFX, _T("[Start Date]"), m_Start_Date);
	RFX_Date(pFX, _T("[Close Date]"), m_Close_Date);
	RFX_Text(pFX, _T("[Status]"), m_Status);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TblWorkorderHistory diagnostics

#ifdef _DEBUG
void TblWorkorderHistory::AssertValid() const
{
	CRecordset::AssertValid();
}

void TblWorkorderHistory::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
