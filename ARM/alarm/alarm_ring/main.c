#include "..\..\inc\swilib.h"
#include "..\..\inc\cfg_items.h"
#include "conf_loader.h"
#include "..\lgp.h"


#ifdef NEWSGOLD
#define DEFAULT_DISK "4"
#define PROFILE_PD_DISC "1"
#else
#define DEFAULT_DISK "0"
#define PROFILE_PD_DISC "0"
#endif

unsigned short maincsm_name_body[140];
unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;
extern const char melody[64];
extern const unsigned int play_;
extern const unsigned int vibra_power;
extern const char shcut[64];
GBSTMR mytmr;
int count;
void LightOff();
const int minus11=-11;
extern char IMG[];
WSHDR *ws;
int scr_w;
int scr_h;

int old_light_kb;
int old_light_d;

//#define sndVolume 15
extern const int sndVolume;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
  WSHDR *ws1;
  WSHDR *ws2;
  int i1;
}MAIN_GUI;

int get_file_size(char* fname)
{
  int f;
  unsigned int err;
  FSTATS fs;
  if ((f=GetFileStats(fname,&fs,&err))==-1)
    return f;
  return (fs.size);
}

int tmp;

void Play(const char *fname)
{
    FSTATS fstats;
    unsigned int err;
    if (GetFileStats(fname,&fstats,&err)!=-1)
    {
      PLAYFILE_OPT _sfo1;
      WSHDR* sndPath=AllocWS(128);
      WSHDR* sndFName=AllocWS(128);
      char s[128];
      const char *p=strrchr(fname,'\\')+1;
      str_2ws(sndFName,p,128);
      strncpy(s,fname,p-fname);
      s[p-fname]='\0';
      str_2ws(sndPath,s,128);
      
      zeromem(&_sfo1,sizeof(PLAYFILE_OPT));
      _sfo1.repeat_num=1;
      _sfo1.time_between_play=0;
      _sfo1.play_first=0;
      _sfo1.volume=sndVolume;
#ifdef NEWSGOLD
      _sfo1.unk6=1;
      _sfo1.unk7=1;
      _sfo1.unk9=2;
      tmp=PlayFile(0x10, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
#ifdef X75
      _sfo1.unk4=0x80000000;
      _sfo1.unk5=1;
      tmp=PlayFile(0xC, sndPath, sndFName, 0,GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#else
      _sfo1.unk5=1;
      tmp=PlayFile(0xC, sndPath, sndFName, GBS_GetCurCepid(), MSG_PLAYFILE_REPORT, &_sfo1);
#endif
#endif
      FreeWS(sndPath);
      FreeWS(sndFName);
    }
}

void play_standart_melody()
{
  int f;
  int i=0;
  unsigned int err;
  char* buf;
  char *fn=PROFILE_PD_DISC":\\system\\hmi\\profile.pd";
  unsigned int fsize=get_file_size(fn);
  
if((f=fopen(fn,A_ReadOnly+A_BIN,P_READ,&err))==-1) return;
  buf=malloc(fsize+1);
  fread(f,buf,fsize,&err);
  fclose(f,&err);
  
  buf=strstr(buf,"Alarm_Clock_3=");
  buf+=14;
  
  while ((buf[i]!=10)&&(buf[i+1]!=13))
  {
      i++;
  }
  buf[i+1]=0;
  Play(buf);
}

//////////////////////////////////////////////////////
void LightOn()
{
  if(vibra_power) SetVibration(vibra_power);
  SetIllumination(0,1,100,0);
  SetIllumination(1,1,100,0);
  GBS_StartTimerProc(&mytmr,100,LightOff);
}

void LightOff()
{
  SetVibration(0);
  if (count)
  {
    GBS_StartTimerProc(&mytmr,100,LightOn);
  }
  else
  {
    GBS_StopTimer(&mytmr);
    GBS_DelTimer(&mytmr);
    
    SetIllumination(0,1,old_light_d,0);
    SetIllumination(1,1,old_light_kb,0);
    if(vibra_power) SetVibration(0);
  }
}
//////////////////////////////////////////////////////

typedef struct
{
  char signature[16];
  unsigned short picnum;
  unsigned short unk1;
  char w; 
  char h; 
  char Compr_Bits;  
}PICHDR;

DrwImg(IMGHDR *img, int x, int y, char *pen, char *brush)
{
  RECT rc;
  DRWOBJ drwobj;
  StoreXYWHtoRECT(&rc,x,y,img->w,img->h);
  SetPropTo_Obj5(&drwobj,&rc,0,img);
  SetColor(&drwobj,pen,brush);
  DrawObject(&drwobj);
}

void draw_pic()
{
    IMGHDR img;
    img.w = 52;
    img.h = 52;
    img.bpnum = 0x88;
    //img.zero = 0;
    img.bitmap = IMG;
    DrwImg(&img,37,5, GetPaletteAdrByColorIndex(1), GetPaletteAdrByColorIndex(0));
}

void OnRedraw()
{
  DrawRoundedFrame(0,0,scr_w,scr_h,0,0,0,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(20));
  draw_pic();
  
  TDate date; TTime time;
  GetDateTime(&date,&time);
  wsprintf(ws,"%d:%02d",time.hour,time.min);
  DrawString(ws,0,75,scr_w,172,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  wsprintf(ws,"%02d-%02d-%04d",date.day, date.month,date.year);
  DrawString(ws,0,90,scr_w,scr_h,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
  
  wsprintf(ws, "%t",alarm_name);
  DrawString(ws,0,60,scr_w,scr_h,FONT_SMALL,3,GetPaletteAdrByColorIndex(2),GetPaletteAdrByColorIndex(23));
  
  TDate date1;
  GetDateTime(&date1,0);
  char wd = GetWeek(&date1);
  wsprintf(ws, "%t",wd2[wd]);
  DrawString(ws,0,105,scr_w,scr_h,FONT_SMALL,3,GetPaletteAdrByColorIndex(0),GetPaletteAdrByColorIndex(23));
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int))
{
  ws=AllocWS(128);
  SetIllumination(1,1,100,0);
  SetIllumination(0,1,100,0);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  FreeWS(ws);
  data->gui.state=0;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();
  data->gui.state=2;
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg)
{
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
    case RIGHT_SOFT:  return(1);
#ifdef NEWSGOLD
    case RED_BUTTON:  return(1);
#endif
    }
  }
  return(0);
}

  extern void kill_data(void *p, void (*func_p)(void *));
#ifdef NEWSGOLD
void onDestroy(MAIN_GUI *data, void (*mfree_adr)(void *))
{
  kill_data(data,mfree_adr);
}
#endif

int method8(void){return(0);}
int method9(void){return(0);}
const void * const gui_methods[11]={
  (void *)OnRedraw,
  (void *)onCreate,
  (void *)onClose,
  (void *)onFocus,
  (void *)onUnfocus,
  (void *)OnKey,
  0,
  #ifdef NEWSGOLD
  (void *)onDestroy,
  #else
  (void *)kill_data,
  #endif
  (void *)method8,
  (void *)method9,
  0
};

const RECT Canvas={0,0,129,129};
void maincsm_oncreate(CSM_RAM *data)
{
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM*csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  main_gui->gui.canvas=(void *)(&Canvas);
  main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
  
  //if(vibra_power)
  //{
    count=1;
    LightOn();
  //}
}

void ElfKiller(void)
{
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

void maincsm_onclose(CSM_RAM *csm)
{
  //if(vibra_power)
  //{
    count=0;
  //}
  PlayMelody_StopPlayback(tmp);
  SUBPROC((void *)ElfKiller);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if ((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }
  return(1);
}

const struct
{
  CSM_DESC maincsm;
  WSHDR maincsm_name;
}MAINCSM =
{
  {
  maincsm_onmessage,
  maincsm_oncreate,
#ifdef NEWSGOLD
  0,
  0,
  0,
  0,
#endif
  maincsm_onclose,
  sizeof(MAIN_CSM),
  1,
  &minus11
  },
  {
    maincsm_name_body,
    NAMECSM_MAGIC1,
    NAMECSM_MAGIC2,
    0x0,
    139
  }
};

void UpdateCSMname(void)
{
  wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"Alarm ring");
}

void play_sound()
{
  switch (play_)
  {
  case 1:
      {
        LockSched();
        char dummy[sizeof(MAIN_CSM)];
        UpdateCSMname();
        MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
        UnlockSched();
        play_standart_melody();
      } 
      break;
  case 0:
    {
      LockSched();
      char dummy[sizeof(MAIN_CSM)];
      UpdateCSMname();
      MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
      UnlockSched();
      Play(melody);
    } break;
#ifndef NEWSGOLD
  case 2: AlarmClockRing(); break;
  case 3:
    {
      typedef void (*voidfunc)();
      voidfunc pp=(voidfunc)GetFunctionPointer((char *)shcut);
      if(pp!=0) pp();
    }
/*#else
  case 3:
    {
      typedef void (*voidfunc)();
      voidfunc pp=(voidfunc)((int)GetFunctionPointer((char *)shcut)+0x10);
      if(pp!=0) pp();
    }*/
#endif
  }
}

void stop_sound()
{
  KbdUnlock();
  GBS_SendMessage(MMI_CEPID,KEY_DOWN,RED_BUTTON);
  GBS_SendMessage(MMI_CEPID,KEY_UP,RED_BUTTON);
}

int main(char *exename, char *fname)
{
  InitConfig();
  scr_w=ScreenW()-1;
  scr_h=ScreenH()-1;
  
  char *illum=GetIlluminationDataTable()+3;
  old_light_d=*illum;
  illum+=152;
  old_light_kb=*illum;
  
  if (!IsCalling())
  {
    play_sound();
  }
  else
  {
    GBSTMR *calltmr;
    GBS_StartTimerProc(&calltmr,216*60*5,play_sound);
  }
  return 0;
}