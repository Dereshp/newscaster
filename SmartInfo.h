#ifndef _SYS_INFO_DEFS_H_
#define _SYS_INFO_DEFS_H_

#include "ShlObj.h"
#include "LMCONS.H"
#include "windows.h"
#include "shlwapi.h"
#include "math.h"
#include "WinIoCtl.h"


CString GetCommandError();
CString QueryHDDSmartCommand( int driveNumber, int smartCommand, long &resultData );
int QueryHDDSmartTemp( int driveNumber );

//
// Declare a global structure to help print the data.
// NOTE: Per ATA3 and ATA4 specs, these attribute definitions are defined by the drive vendor
// and hence their attributes may vary between vendors.
//
#define MAX_KNOWN_ATTRIBUTES	12
static PCHAR pAttrNames[]=
{
	"No Attribute Here       ", //0
	"Raw Read Error Rate     ", //1
	"Throughput Performance  ", //2
	"Spin Up Time            ", //3
	"Start/Stop Count        ", //4
	"Reallocated Sector Count", //5
	"Read Channel Margin     ", //6
	"Seek Error Rate         ", //7
	"Seek Time Performance   ", //8
	"Power On Hours Count    ", //9
	"Spin Retry Count        ", //10
	"Calibration Retry Count ", //11
	"Power Cycle Count       ", //12
	"(Unknown attribute)     "
};

#define MAX_KNOWN_ATTRIBUTES2	7
static PCHAR pAttrNamesEx[]=
{
	"Power Off Retract Count ", //C0
	"Load Cycle Count        ", //C1
	"Temperature             ", //C2
	"ECC Recovered Count     ", //C3
	"Relocated Event Count   ", //C4
	"Current Pending Sector  ", //C5
	"Offline Uncorrectable   ", //C6
	"(Unknown attribute)     "
};

enum {
	SMART_POWEROFFCYCLE = 0xC0,
	SMART_LOADCYCLE,
	SMART_TEMP,
	SMART_ECCRECOVER,
	SMART_RELOCEVENTCOUNT,
	SMART_CURRENTPS,
	SMART_OFFLINE
};

#define MAX_OF_HARD_DISKS	24
static char HardDiskLetters[MAX_OF_HARD_DISKS][4]={
	"c:\\",	"d:\\",	"e:\\",	"f:\\",	"g:\\",	"h:\\",
	"i:\\",	"j:\\",	"k:\\",	"l:\\",	"m:\\",	"n:\\",
	"o:\\",	"p:\\",	"q:\\",	"r:\\",	"s:\\",	"t:\\",
	"u:\\",	"v:\\",	"w:\\",	"x:\\",	"y:\\",	"z:\\"
};
#endif //_SYS_INFO_DEFS_H_
