
#if !defined(AFX_SEHIST_H__8E060648_4864_4CF1_91F5_5672EC14C3A6__INCLUDED_)
#define AFX_SEHIST_H__8E060648_4864_4CF1_91F5_5672EC14C3A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"

#define DSN_WCSEHIST "DSN=ProductionHistoryWC"
#define MINCHARVAL           20 // minimum character value in text fields
#define MAXCHARVAL          126 // maximum character value in text fields 
#define WONUMLEN              8
#define PARTNAMELEN          18 
#define MOLDNAMELEN          18 
#define MAXFIELDS            20 // Number of defined field tags
#define MAXRECORDS            0 // Number of define records
#define MAXHISTORY           50 // Maximum nunber of history occurrence to read
#define StdCycleTimeNameLen  16 // StdCycleTimeDef records name length 
#define MMStartupHistNameLen 18 // MMStartupHistDef records name length 
#define WOHistNameLen        16 // WOHistDef records name length 
#define MachEventNameLen     16 // MachineEventDef record name length
#define MAXWOEVENTS        1200 // maximum nuber of workorder event occurrences
#define MAXFAULTCOUNTS       10 // maximum number of machine event occurrences
#define WOEVENT_BLANK         0 // WOEvent codes
#define WOEVENT_PRINTED       1
#define WOEVENT_SCHEDULE      2
#define WOEVENT_UNSCHEDULE    3
#define WOEVENT_START         4
#define WOEVENT_STOP          5
#define WOEVENT_CLOSE         6

#define WOEVENTNAME "WOEvent"

static char  fieldname[MAXFIELDS][20] = { 
                "# LOG RECORDS",      "LOG DateDone",    "LOG WORK ORDER",
                "LOG MACH NUMBER",    "LOG PART NAME",   "LOG MoldName",
                "LOG WIPQty",         "LOG DoneQty",     "LOG RejQty",
                "LOG CYCLE COUNT",    "LOG RunTime",     "LOG Yield",
                "Interrupt Duration", "Startup Time",    "LOG STD CYCLE",
                "WONum",              "MachNum",         "LOG_TIME",
                "LOG VALUE",          "LOG FAULT COUNT"};
                                 
static long  NUMLOGRECORDS_FT,     LOGDATEDONE_FT,      LOGWORKORDER_FT,
             LOGMACHNUMBER_FT,     LOGPARTNAME_FT,      LOGMOLDNAME_FT,
             LOGWIPQTY_FT,         LOGDONEQTY_FT,       LOGREJQTY_FT,
             LOGCYCLECOUNT_FT,     LOGRUNTIME_FT,       LOGYIELD_FT,
             INTERRUPTDURATION_FT, STARTUPTIME_FT,      LOGSTDCYCLE_FT,
             WONUM_FT,             MACHNUM_FT,          LOG_TIME_FT,
             LOGVALUE_FT,          LOGFAULTCOUNT_FT;
                                
static ERRBLOCK IP21Error;
static ERRARRAY IP21ErrorMsg;
static short IP21ErrorLength;
long   WOEventID = 0;

// ----------------------------------------------------------------------------

void InitIP21(void);
void InitProgVars(void);
void ReadWCSEHist(long RecID);
void UpdateMachineHistory(void);
void CollectSEData(void);
void UpdateRejectHistory(void);
void LookupMfgSysInfo(void);
void UpdateWorkorderHistory(void);

#endif // !defined(AFX_SEHIST_H__8E060648_4864_4CF1_91F5_5672EC14C3A6__INCLUDED_)




