#include "faery_state.h"

extern struct FaeryState *fstate;

static BOOL	hdrive = FALSE;
static BPTR	file;

/* 9 diskreqs: 5 landscape, 2 Terrain, 1 map, 1 sector, 1 monster */

struct MsgPort *diskport;
struct IOExtTD *diskreq1, diskreqs[10], *lastreq;

int AllocDiskIO()
{	short	i;
	BPTR	lock;

	if (lock = Lock("image",ACCESS_READ))
	{
		hdrive = TRUE;
		UnLock(lock);

		if ( (file = Open("image",MODE_OLDFILE)) == NULL ) return 30;
	}
	else
	{
		if ((diskport = (struct MsgPort *)CreatePort(0,0))==0) return 30;
		SETFN(AL_PORT);
		if ((diskreq1=(struct IOExtTD *)CreateExtIO(diskport,sizeof(struct IOExtTD)))==0) return 31;
		SETFN(AL_IOREQ);
		if (OpenDevice(TD_NAME,0,(struct IORequest *)diskreq1,0)) return 32;
		SETFN(AL_TDISK);
		for (i=0; i<9; i++)
		{	diskreqs[i] = *diskreq1;
		}
	}

	return 0;
}

void FreeDiskIO()
{
	if (file) Close(file);

	if (TSTFN(AL_TDISK)) CloseDevice((struct IORequest *)diskreq1);
	if (TSTFN(AL_IOREQ))  DeleteExtIO((struct IORequest *)diskreq1);
	if (TSTFN(AL_PORT)) DeletePort(diskport);
}

void WaitDiskIO(num) int num;
{
	if (hdrive == FALSE)
		WaitIO((struct IORequest *)&diskreqs[num]);
}

void InvalidDiskIO(num) int num;
{
	if (hdrive == FALSE)
		diskreqs[num].iotd_Req.io_Command = CMD_INVALID;
}

int CheckDiskIO(num) int num;
{
	if (hdrive == FALSE) return CheckIO((struct IORequest *)&diskreqs[num]);

	return TRUE;
}

int IsReadDiskIO(num) int num;
{
	if (hdrive == FALSE) return (diskreqs[num].iotd_Req.io_Command == CMD_READ);

	return FALSE;
}

void WaitLastDiskIO()
{
	if (hdrive == FALSE)
		WaitIO((struct IORequest *)lastreq);
}

void InvalidLastDiskIO()
{
	if (hdrive == FALSE)
		lastreq->iotd_Req.io_Command = CMD_INVALID;
}

int CheckLastDiskIO()
{
	if (hdrive == FALSE) return CheckIO((struct IORequest *)lastreq);

	return TRUE;
}

int IsReadLastDiskIO()
{
	if (hdrive == FALSE) return (lastreq->iotd_Req.io_Command == CMD_READ);

	return FALSE;
}

load_track_range(f_block,b_count,buffer,dr)
short f_block, b_count, dr; APTR buffer;
{	short error;

	if (hdrive == FALSE)
	{
		lastreq = &(diskreqs[dr]);
		if (lastreq->iotd_Req.io_Command == CMD_READ) WaitIO((struct IORequest *)lastreq);
		*lastreq = *diskreq1;
		lastreq->iotd_Req.io_Length = b_count * 512;
		lastreq->iotd_Req.io_Data = buffer;
		lastreq->iotd_Req.io_Command = CMD_READ;
		lastreq->iotd_Req.io_Offset = f_block * 512;
		SendIO((struct IORequest *)lastreq);
	}
	else
	{
		Seek(file,f_block * 512,OFFSET_BEGINNING);
		Read(file,buffer,b_count * 512);
	}
}

motor_off()
{
	if (hdrive == FALSE)
	{
		diskreqs[9] = *diskreq1;
		diskreqs[9].iotd_Req.io_Length = 0;
		diskreqs[9].iotd_Req.io_Command = TD_MOTOR;
		DoIO((struct IORequest *)&diskreqs[9]); 
	}
}

BOOL IsHardDrive(void)
{
	return hdrive;
}
