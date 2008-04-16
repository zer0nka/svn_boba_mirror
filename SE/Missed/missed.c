//#define DEBUG

#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"
#include "string.h"
#include "util.h"

#define ELFNAME "missed events"
#define LELFNAME L"missed events"
#define LELFVERSION L" v0.4\nby den_po"
#define LINIFILENAME _T("missed.ini")

static char myappname[]=ELFNAME;

#pragma swi_number=0x1BB
__swi __arm void Vibra(int t1, int t2, int t3);
#pragma swi_number=0x248
__swi __arm void Vibra_Off(int t1);

bool disabled=false;
int cfg_period=30;
u16 cfg_filepath[256];
u16 cfg_filename[256];

u16 timer;
u16 vibratimer;

int skipevents;
int checkevents;

void myVibraOff(u16 *timerID, LPARAM lparam)
{
        Vibra_Off(0);
        vibratimer=0;
}

void onTimer(u16 *timerID, LPARAM lparam)
{
        if(!disabled)
        {
                int* me=MissedEvents();
                char mestatus=*(char*)me;//some FWs use char :(
                if( mestatus & checkevents )
                {
                        if(!GetSilent())
                        {
                                char vol;
                                GetAudioSettings(2,&vol);
                                PlayFileV(cfg_filepath,cfg_filename,vol);
                        }
                        if(GetVibrator(0,0))
                        {
                                Vibra(400,50,1500);
                                vibratimer=Timer_Set(450*3,myVibraOff,NULL);
                        }
                }
#ifdef DEBUG
                if( mestatus & ~(skipevents|checkevents))
                {
                        u16 temp[256];
                        snwprintf(temp, MAXELEMS(temp), _T("unknown event status\n%x: %x"), me, mestatus &~(skipevents|checkevents));
                        MessageBox(0x6FFFFFFF, Str2ID(temp,0,MAXELEMS(temp)), 0xFFFF, 1, 0, 0);
                        skipevents|=mestatus;
                }
#endif
        }
        Timer_ReSet(&timer,cfg_period*1000,onTimer,lparam);
}

int getcfg()
{
        int fcfg;
        char* pcfg=NULL;

        if( (fcfg=_fopen(GetDir(DIR_INI), LINIFILENAME ,0x001,0x180,0))>=0)
        {
                FSTAT fstat;
                if (isFileExist(GetDir(DIR_INI), LINIFILENAME ,&fstat)==0)
                {
                        pcfg=(char*)malloc(fstat.fsize+1);
                        fread(fcfg,pcfg,fstat.fsize);

                        if(char* pfilepath=manifest_GetParam(pcfg,"[FILE]",0))
                        {
                                extractdir(cfg_filepath,cfg_filename,pfilepath);
                                mfree(pfilepath);
                        }
                        if(char* pperiod=manifest_GetParam(pcfg,"[PERIOD]",0))
                        {
                                cfg_period=str2int(pperiod);
                                mfree(pperiod);
                        }
                        mfree(pcfg);
                }
                fclose(fcfg);
                return 1;
        }
        return 0;
}


//-------------------------------------------------------------------
void elf_exit(void)
{
        kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

//////////////////////////////////////////////////////////////////////////////////////////

void bookOnDestroy(BOOK * book)
{
        Timer_Kill(&timer);
        if(vibratimer)
        {
                Timer_Kill(&vibratimer);
                myVibraOff(0,0);
        }
        MessageBox(0x6FFFFFFF,Str2ID( LELFNAME L" has been stopped",0,SID_ANY_LEN),0xFFFF,1,5000,0);
        SUBPROC(elf_exit);
}

int onExit(void* r0,BOOK* b)
{
        FreeBook(b);
        return 1;
}

int onAbout(void* mess,BOOK* b)
{
        MessageBox(0x6fFFFFFF,Str2ID( LELFNAME LELFVERSION,0,SID_ANY_LEN),0xFFFF, 1 ,5000, *(BOOK**)mess);
        return 1;
}

struct  CALLMANAGER_EVENT_DATA
{
        char x0;
        char x1;
        char callstate;
        int  x4;
        char x8;
        char x9;
        char callcause;
};

enum
{
        CALLMANAGER_IDLE            =0,
        CALLMANAGER_CALL_CONNECTED  =1,
        CALLMANAGER_CALL_SETUP      =2,
        CALLMANAGER_CALL_ALERT      =4,
        CALLMANAGER_CALL_WAITING    =5,
        CALLMANAGER_CALL_TERMINATED =6
};

int OnCallManagerEvent(void* r0,BOOK* b)
{
        switch(((CALLMANAGER_EVENT_DATA*)r0)->callstate)
        {
        case CALLMANAGER_CALL_SETUP:
        case CALLMANAGER_CALL_ALERT:
                disabled=true;
                break;
        case CALLMANAGER_CALL_TERMINATED:
                Timer_ReSet(&timer,cfg_period*1000,onTimer, 0);
                disabled=false;
                break;
        }
        return 1;
}

const PAGE_MSG evtlist[] @ "DYN_PAGE"=
{
        ELF_TERMINATE_EVENT     ,onExit,
        ELF_SHOW_INFO_EVENT     ,onAbout,
        ON_CALLMANAGER_EVENT_TAG,OnCallManagerEvent,
        NIL_EVENT_TAG           ,NULL
};

const PAGE_DESC defaultpage = {"defaultpage",0,evtlist};

int isOurBook(BOOK * book)
{
        if(!strcmp(book->xbook->name,myappname)) return true;
        return false;
}

int main(u16* filename)
{
        BOOK* alreadyrunned=FindBook(isOurBook);
        if(alreadyrunned)
        {
                FreeBook(alreadyrunned);
                SUBPROC(elf_exit);
        }else
        {
                u16 temp[256];
                //check cfg params------
                char* badarg=NULL;
                FSTAT fstat;
                if(!getcfg())
                        badarg="INI";
                else
                        if(isFileExist(cfg_filepath,cfg_filename,&fstat)!=0)
                                badarg="[FILE]";
                        else
                                if(cfg_period<3)badarg="[PERIOD]";
                if(badarg)
                {
                        snwprintf(temp, MAXELEMS(temp), _T("bad '%s'\nconfig:\npath:%ls\nname:%ls\ntime:%d"),badarg
                                ,cfg_filepath,cfg_filename,cfg_period);
                        MessageBox(0x6FFFFFFF,Str2ID(temp,0,MAXELEMS(temp)),0xFFFF,1,0,0);
                        SUBPROC(elf_exit);
                        return 0;
                }
                //---------------------
                switch(GetChipID())
                {
                case 0x7100://db2000
                case 0x8000://db2010
                case 0x8040://db2010
                        skipevents=0;
                        checkevents=1|2|4|8;//MISSED_CALL|MISSED_SMS|MISSED_EMAIL|MISSED_MMS
                        break;
                case 0x9900:
                        skipevents=1|2;//KEYLOCKED|NOSOUND
                        checkevents=4|8|0x10|0x20;//MISSED_CALL|MISSED_SMS|MISSED_EMAIL|MISSED_MMS
                }

                BOOK *myBook=(BOOK*)malloc(sizeof(BOOK));
                memset(myBook,0,sizeof(BOOK));
                CreateBook(myBook,bookOnDestroy,&defaultpage,myappname,-1,0);

                timer=Timer_Set(cfg_period*1000, onTimer, 0);

                if(!wstrstr(filename,GetDir(DIR_ELFS_DAEMONS)))
                        MessageBox(0x6FFFFFFF,Str2ID( LELFNAME L" has been started",0,SID_ANY_LEN),0xFFFF,1,5000,0);
        }

        return 0;
}