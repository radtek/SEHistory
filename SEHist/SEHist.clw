; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=TblWorkorderHistory
LastTemplate=CRecordset
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SEHist.h"
LastPage=0

ClassCount=6

ResourceCount=0
Class1=TblCycleTimes
Class2=TblMachineHistory
Class3=TblRejectHistory
Class4=cMfgSysInfo
Class5=TblWorkorderHistory
Class6=TblWOHist

[CLS:TblCycleTimes]
Type=0
HeaderFile=TblCycleTimes.h
ImplementationFile=TblCycleTimes.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:TblCycleTimes]
DB=1
DBType=ODBC
ColumnCount=7
Column1=[ID], 4, 4
Column2=[Part], 12, 64
Column3=[Machine Name], 12, 48
Column4=[Tool], 12, 48
Column5=[Design Cycle Time], 7, 4
Column6=[Unit of Measure], 12, 48
Column7=[Prefered Machine], -7, 1

[CLS:TblMachineHistory]
Type=0
HeaderFile=TblMachineHistory.h
ImplementationFile=TblMachineHistory.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:TblMachineHistory]
DB=1
DBType=ODBC
ColumnCount=37
Column1=[ID], 4, 4
Column2=[Workorder], 12, 16
Column3=[Date Created], 11, 16
Column4=[Date Modified], 11, 16
Column5=[Machine Name], 12, 48
Column6=[Machine Number], 5, 2
Column7=[Machine Type], 12, 30
Column8=[Cell], 12, 30
Column9=[Production Line], 12, 30
Column10=[Production System], 12, 30
Column11=[Tool], 12, 48
Column12=[Tool 2], 12, 48
Column13=[Production Time], 7, 4
Column14=[Uptime], 7, 4
Column15=[Fault Time], 7, 4
Column16=[Setup Time], 7, 4
Column17=[Cleanup Time], 7, 4
Column18=[Fault Count], 4, 4
Column19=[Pieces In], 4, 4
Column20=[Pieces Out], 4, 4
Column21=[Machine Good Qty], 4, 4
Column22=[Machine Good Qty Unit of Measure], 12, 16
Column23=[Cycle Count], 4, 4
Column24=[Calc Cycle Time], 7, 4
Column25=[Designed Cycle Time], 7, 4
Column26=[Yield], 7, 4
Column27=[Efficiency], 7, 4
Column28=[Availability], 7, 4
Column29=[Se], 7, 4
Column30=[Start Time], 11, 16
Column31=[End Time], 11, 16
Column32=[Badge 1], 5, 2
Column33=[Badge 2], 5, 2
Column34=[Badge 3], 5, 2
Column35=[Badge 4], 5, 2
Column36=[Badge 5], 5, 2
Column37=[Comment], 12, 80

[CLS:TblRejectHistory]
Type=0
HeaderFile=TblRejectHistory.h
ImplementationFile=TblRejectHistory.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:TblRejectHistory]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[ID], 4, 4
Column2=[Workorder], 12, 16
Column3=[Machine Name], 12, 48
Column4=[Reject Type], 12, 30
Column5=[Reject Qty], 4, 4
Column6=[Reject Qty Unit of Measure], 12, 16
Column7=[Timestamp], 11, 16
Column8=[Badge], 5, 2

[CLS:cMfgSysInfo]
Type=0
HeaderFile=cMfgSysInfo.h
ImplementationFile=cMfgSysInfo.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r

[DB:cMfgSysInfo]
DB=1
DBType=ODBC
ColumnCount=5
Column1=[ToolID], 12, 48
Column2=[MoldName], 12, 48
Column3=[MfgSystem], 12, 80
Column4=[CellName], 12, 32
Column5=[Cavities], 4, 4

[CLS:TblWorkorderHistory]
Type=0
HeaderFile=TblWorkorderHistory.h
ImplementationFile=TblWorkorderHistory.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=TblWorkorderHistory

[DB:TblWorkorderHistory]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[Workorder], 12, 16
Column2=[Part Number], 12, 64
Column3=[Product Line], 12, 30
Column4=[Good Qty], 4, 4
Column5=[Good Qty Unit of Measure], 12, 16
Column6=[Start Date], 11, 16
Column7=[Close Date], 11, 16
Column8=[Status], 12, 16

[CLS:TblWOHist]
Type=0
HeaderFile=TblWOHist.h
ImplementationFile=TblWOHist.cpp
BaseClass=CRecordset
Filter=N
VirtualFilter=r
LastObject=TblWOHist

[DB:TblWOHist]
DB=1
DBType=ODBC
ColumnCount=8
Column1=[Workorder], 12, 16
Column2=[Part Number], 12, 30
Column3=[Product Line], 12, 30
Column4=[Good Qty], 4, 4
Column5=[Good Qty Unit of Measure], 12, 16
Column6=[Start Date], 11, 16
Column7=[Close Date], 11, 16
Column8=[Status], 12, 16

