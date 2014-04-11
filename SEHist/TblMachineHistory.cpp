// TblMachineHistory.cpp : implementation file
//

#include "stdafx.h"
#include "TblMachineHistory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TblMachineHistory

IMPLEMENT_DYNAMIC(TblMachineHistory, CRecordset)

TblMachineHistory::TblMachineHistory(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TblMachineHistory)
	m_ID = 0;
	m_Workorder = _T("");
	m_Machine_Name = _T("");
	m_Machine_Number = 0;
	m_Machine_Type = _T("");
	m_Cell = _T("");
	m_Production_Line = _T("");
	m_Production_System = _T("");
	m_Tool = _T("");
	m_Tool_2 = _T("");
	m_Production_Time = 0.0f;
	m_Uptime = 0.0f;
	m_Fault_Time = 0.0f;
	m_Setup_Time = 0.0f;
	m_Cleanup_Time = 0.0f;
	m_Fault_Count = 0;
	m_Pieces_In = 0;
	m_Pieces_Out = 0;
	m_Machine_Good_Qty = 0;
	m_Machine_Good_Qty_Unit_of_Measure = _T("");
	m_Cycle_Count = 0;
	m_Calc_Cycle_Time = 0.0f;
	m_Designed_Cycle_Time = 0.0f;
	m_Yield = 0.0f;
	m_Efficiency = 0.0f;
	m_Availability = 0.0f;
	m_Se = 0.0f;
	m_Badge_1 = 0;
	m_Badge_2 = 0;
	m_Badge_3 = 0;
	m_Badge_4 = 0;
	m_Badge_5 = 0;
	m_Comment = _T("");
	m_nFields = 37;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString TblMachineHistory::GetDefaultConnect()
{
	return _T("ODBC;DSN=ProductionHistoryWC");
}

CString TblMachineHistory::GetDefaultSQL()
{
	return _T("[Machine History]");
}

void TblMachineHistory::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TblMachineHistory)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Workorder]"), m_Workorder);
	RFX_Date(pFX, _T("[Date Created]"), m_Date_Created);
	RFX_Date(pFX, _T("[Date Modified]"), m_Date_Modified);
	RFX_Text(pFX, _T("[Machine Name]"), m_Machine_Name);
	RFX_Int(pFX, _T("[Machine Number]"), m_Machine_Number);
	RFX_Text(pFX, _T("[Machine Type]"), m_Machine_Type);
	RFX_Text(pFX, _T("[Cell]"), m_Cell);
	RFX_Text(pFX, _T("[Production Line]"), m_Production_Line);
	RFX_Text(pFX, _T("[Production System]"), m_Production_System);
	RFX_Text(pFX, _T("[Tool]"), m_Tool);
	RFX_Text(pFX, _T("[Tool 2]"), m_Tool_2);
	RFX_Single(pFX, _T("[Production Time]"), m_Production_Time);
	RFX_Single(pFX, _T("[Uptime]"), m_Uptime);
	RFX_Single(pFX, _T("[Fault Time]"), m_Fault_Time);
	RFX_Single(pFX, _T("[Setup Time]"), m_Setup_Time);
	RFX_Single(pFX, _T("[Cleanup Time]"), m_Cleanup_Time);
	RFX_Long(pFX, _T("[Fault Count]"), m_Fault_Count);
	RFX_Long(pFX, _T("[Pieces In]"), m_Pieces_In);
	RFX_Long(pFX, _T("[Pieces Out]"), m_Pieces_Out);
	RFX_Long(pFX, _T("[Machine Good Qty]"), m_Machine_Good_Qty);
	RFX_Text(pFX, _T("[Machine Good Qty Unit of Measure]"), m_Machine_Good_Qty_Unit_of_Measure);
	RFX_Long(pFX, _T("[Cycle Count]"), m_Cycle_Count);
	RFX_Single(pFX, _T("[Calc Cycle Time]"), m_Calc_Cycle_Time);
	RFX_Single(pFX, _T("[Designed Cycle Time]"), m_Designed_Cycle_Time);
	RFX_Single(pFX, _T("[Yield]"), m_Yield);
	RFX_Single(pFX, _T("[Efficiency]"), m_Efficiency);
	RFX_Single(pFX, _T("[Availability]"), m_Availability);
	RFX_Single(pFX, _T("[Se]"), m_Se);
	RFX_Date(pFX, _T("[Start Time]"), m_Start_Time);
	RFX_Date(pFX, _T("[End Time]"), m_End_Time);
	RFX_Int(pFX, _T("[Badge 1]"), m_Badge_1);
	RFX_Int(pFX, _T("[Badge 2]"), m_Badge_2);
	RFX_Int(pFX, _T("[Badge 3]"), m_Badge_3);
	RFX_Int(pFX, _T("[Badge 4]"), m_Badge_4);
	RFX_Int(pFX, _T("[Badge 5]"), m_Badge_5);
	RFX_Text(pFX, _T("[Comment]"), m_Comment);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TblMachineHistory diagnostics

#ifdef _DEBUG
void TblMachineHistory::AssertValid() const
{
	CRecordset::AssertValid();
}

void TblMachineHistory::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
