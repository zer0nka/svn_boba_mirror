#include "..\inc\swilib.h"
#include "mc.h"
#include "mui.h"
#include "lng.h"
#include "ColorMap.h"
#include "config.h"

const int minus11=-11; // �������� ���������
unsigned short maincsm_name_body[140];
volatile int GUIStarted = 0; //Elf ������
volatile int Terminate = 0; // ���� ������������� ���������� ������
volatile int Busy = 0;

unsigned int MAINCSM_ID = 0;
unsigned int MAINGUI_ID = 0;

unsigned int err;

#ifdef LOG
int flog=-1;
#endif

WSHDR *guibuf;
WSHDR *wsbuf;
char *pathbuf;
char *pathbuf2;
char *pathbuf_fn;
char *msgbuf;

typedef struct
{
  CSM_RAM csm;
  int gui_id;
}MAIN_CSM;

typedef struct
{
  GUI gui;
//  WSHDR *ws1;
//  WSHDR *ws2;
//  int i1;
}MAIN_GUI;


void FreeData()
{
  LockSched();
  GBS_DelTimer(&sctm);
  GBS_DelTimer(&cmtm);
  if(LOAD_CS)SaveCS(NULL);
#ifdef DUMP_MUI
  void SaveMUI2(char* filename);
  SaveMUI2(NULL);
#else  
  if(LOAD_MUI)SaveMUI(NULL);
#endif  
  SaveCfg();
  if(guibuf)FreeWS(guibuf);
  if(wsbuf)FreeWS(wsbuf);
  if(pathbuf) mfree(pathbuf);
  if(pathbuf2) mfree(pathbuf2);
  if(pathbuf_fn) mfree(pathbuf_fn);
  if(msgbuf) mfree(msgbuf);
  guibuf=wsbuf=0;
  pathbuf=pathbuf2=pathbuf_fn=msgbuf=0;
  for(int ii=0;ii<MAX_TABS+1;ii++)
  {
    DelFiles(ii);
    FreeTab(ii);
  } 
  FreeExt();
  FreeMUI();
  fn_free(&buffer);
  UnlockSched();
#ifdef LOG
  _WriteLog("FreeData");
  fclose(flog,&err);
#endif
}

void OnRedraw(MAIN_GUI *data) // OnRedraw
{
  if(!GUIStarted)
  {
    GUIStarted = 1;
    guibuf=AllocWS(MAX_PATH*2);
    wsbuf=AllocWS(MAX_PATH*2);
    pathbuf=malloc(MAX_PATH);
    pathbuf2=malloc(MAX_PATH);
    pathbuf_fn=malloc(MAX_PATH);
    msgbuf=malloc(256);
    SUBPROC((void *)LoadKeys);
#ifdef LOG
_WriteLog("LoadExts");
#endif
    LoadExts();
#ifdef LOG
_WriteLog("LoadCfg");
#endif
    LoadCfg();

    for(int ii=0;ii<MAX_TABS+1;ii++)
     InitTab(ii);
    
    if(in_open_path[0])
      cd(0, in_open_path);
    else 
    if(SAVE_PATH)
    {
#ifdef LOG
_WriteLog("Init Last Dirs");
#endif
      for(int ii=0;ii<MAX_TABS;ii++)
      {
       int srt=MCConfig.tabs[ii].sort;
       int srtH=(srt & STD_MASK);
       int srtL=(srt & STV_MASK);
       srt=(srtL<=ST_LAST?srtL:0) | srtH;
       tabs[ii]->sort=srt;
       if(MCConfig.tabs[ii].LastPath[0] /*&& isdir(MCConfig.tabs[ii].LastPath, &err)*/)
       {
        cd(ii, MCConfig.tabs[ii].LastPath);
        SetTabIndex(ii, MCConfig.tabs[ii].LastInd, 0);
       }
      } 
      curtab = MCConfig.curtab;
    }  
#ifdef LOG
_WriteLog("InitCS");
#endif
    InitScr();
    InitCS();
    InitAllMD();
    if(LOAD_MUI)
      LoadMUI(NULL);
    else
      InitMUI();
#ifdef LOG
_WriteLog("Work...");
#endif
    if(SCROLL_TEXT_SPEED)
     GBS_StartTimerProc(&sctm,SCROLL_TEXT_SPEED,DrwName);
   }
  else
  {
  }
  
  if(IsGuiOnTop(MAINGUI_ID))
  {
   if(!progr_start)
     ShowFiles(); 
   else
     ShowProgr();
  } 
}

void onCreate(MAIN_GUI *data, void *(*malloc_adr)(int)) //Create
{
#ifdef LOG
  _WriteLog("gui.onCreate");
#endif
//  data->ws1=AllocWS(256);
//  data->ws2=AllocWS(256);
  data->gui.state=1;
}

void onClose(MAIN_GUI *data, void (*mfree_adr)(void *)) //Close
{
#ifdef LOG
  _WriteLog("gui.onClose");
#endif
//  FreeWS(data->ws1);
//  FreeWS(data->ws2);
  data->gui.state=0;
  Terminate=progr_stop=1;
}

void onFocus(MAIN_GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))//Focus
{
  data->gui.state=2;
  if(Terminate && !Busy)
  {
    GeneralFuncF1(1); // ����� ������� ���. � ���������� �����������.
  } else
  DirectRedrawGUI();
}

void onUnfocus(MAIN_GUI *data, void (*mfree_adr)(void *)) //Unfocus
{
  if (data->gui.state!=2) return;
  data->gui.state=1;
}

void CB_Stop(int id)
{
  if(id==IDYES)progr_stop = 1;
}

int OnKey(MAIN_GUI *data, GUI_MSG *msg) //OnKey
{
  if (msg->gbsmsg->msg==KEY_DOWN || msg->gbsmsg->msg==LONG_PRESS)
  {
   if(progr_start)
   {
    if(msg->gbsmsg->submess==RIGHT_SOFT || msg->gbsmsg->submess==LEFT_SOFT)
      MsgBoxYesNo(1, (int) muitxt(ind_pmt_stop), CB_Stop);
   }
   else
   if(!Busy)
   {
    DoKey(msg->gbsmsg->submess);
    DirectRedrawGUI();
   }
  }
  return(0);
}

extern void kill_data(void *p, void (*func_p)(void *));

void Killer(void)
{
  FreeData();
  extern void *ELF_BEGIN;
  kill_data(&ELF_BEGIN,(void (*)(void *))mfree_adr());
}

int method8(void){return(0);}

int method9(void){return(0);}

const void * const gui_methods[11]={
  (void *)OnRedraw,	//Redraw
  (void *)onCreate,	//Create
  (void *)onClose,	//Close
  (void *)onFocus,	//Focus
  (void *)onUnfocus,	//Unfocus
  (void *)OnKey,	//OnKey
  0,
  (void *)kill_data,	//Destroy
  (void *)method8,
  (void *)method9,
  0
};

#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}
const RECT Canvas={0,0,0,0};

void maincsm_oncreate(CSM_RAM *data)
{
#ifdef LOG
  _WriteLog("maincsm_oncreate");
#endif
  MAIN_GUI *main_gui=malloc(sizeof(MAIN_GUI));
  MAIN_CSM *csm=(MAIN_CSM*)data;
  zeromem(main_gui,sizeof(MAIN_GUI));
  patch_rect((RECT*)&Canvas,0,0,ScreenW()-1,ScreenH()-1);
  main_gui->gui.canvas=(void *)(&Canvas);
  //main_gui->gui.flag30=2;
  main_gui->gui.methods=(void *)gui_methods;
  main_gui->gui.item_ll.data_mfree=(void (*)(void *))mfree_adr();
  csm->csm.state=0;
  csm->csm.unk1=0;
  csm->gui_id=CreateGUI(main_gui);
  MAINGUI_ID=csm->gui_id;
}


void maincsm_onclose(CSM_RAM *csm)
{
#ifdef LOG
  _WriteLog("maincsm_onclose");
#endif
  SUBPROC((void *)Killer);
}

int maincsm_onmessage(CSM_RAM *data, GBS_MSG *msg)
{
#ifdef LOG
  _WriteLogHex("msg:", msg->msg);
#endif
  MAIN_CSM *csm=(MAIN_CSM*)data;
  if((msg->msg==MSG_GUI_DESTROYED)&&((int)msg->data0==csm->gui_id))
  {
    csm->csm.state=-3;
  }else
/*  if(msg->msg==0x16)
  {
    void CB_Exit(int id);
    CB_Exit(IDYES);
  }else */
  if(msg->msg==MSG_IDLETMR_EXPIRED) return(0);
   else
  if(msg->msg==MSG_RECONFIGURE_REQ) 
  {
//    ShowMSG(1,(int)muitxt(ind_reconfig));
    InitConfig();
    UpdateAll();
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
  if(wsbuf)
  {
   str_2ws(wsbuf,_CurPath,MAX_PATH);
   wsprintf((WSHDR *)(&MAINCSM.maincsm_name),"mc - %w", wsbuf);
  }
}

int main(char *exename, char *fname)
{
  guibuf=wsbuf=0;
  pathbuf=pathbuf2=pathbuf_fn=msgbuf=0;

  GetFileDir(exename, mcpath);
#ifdef LOG
  flog=fopen("0:\\mc.log",A_ReadWrite+A_Create+A_Truncate,P_READ+P_WRITE,&err);
  _WriteLog("Start");
#endif

#ifdef NEWSGOLD
  if(!isdir(etc_path, &err)) etc_path[0]='0';
#endif
#ifdef LOG
  _WriteLog("InitConfig");
#endif
  InitConfig();
  
  in_open_path[0]=0;
  if(fname && isdir(fname, &err))
     strcpy(in_open_path, fname);
  
  char* dummy=malloc(sizeof(MAIN_CSM));
  MAINCSM_ID = CreateCSM(&MAINCSM.maincsm,dummy,0);
  mfree(dummy);
  UpdateCSMname();
  return 0;
}




















#ifdef LOG
void _WriteLog(char *buf)
{
 if(flog!=-1)
 {  
  char msg[512];

  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  sprintf(msg, "%02d:%02d:%02d %s\n", t.hour,t.min,t.sec,buf);
//  sprintf(msg, "%s\n", buf);
  fwrite(flog,msg,strlen(msg),&err);
 } 
}
void _WriteLogWS(WSHDR *buf)
{
 if(flog!=-1)
 {  
  char msg[256];
  char msg2[256];
  ws_2str(buf, msg2, 256);

  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  sprintf(msg, "%02d:%02d:%02d %s\n", t.hour,t.min,t.sec,msg2);
//  sprintf(msg, "%s\n", buf);
  fwrite(flog,msg,strlen(msg),&err);
 } 
}

void _WriteLog2(char *buf1, char *buf2)
{
 if(flog!=-1)
 {  
  char msg[512];

  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  sprintf(msg, "%02d:%02d:%02d %s %s\n", t.hour,t.min,t.sec,buf1,buf2);
//  sprintf(msg, "%s\n", buf);
  fwrite(flog,msg,strlen(msg),&err);
 } 
}
void _WriteLogInt(char *buf, int ii)
{
 if(flog!=-1)
 {  
  char msg[512];
  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  sprintf(msg, "%02d:%02d:%02d %s %d\n", t.hour,t.min,t.sec,buf,ii);
  fwrite(flog,msg,strlen(msg),&err);
 } 
}
void _WriteLogHex(char *buf, int ii)
{
 if(flog!=-1)
 {  
  char msg[512];
  TTime t;
  TDate d;
  GetDateTime(&d,&t);
  sprintf(msg, "%02d:%02d:%02d %s %.8x\n", t.hour,t.min,t.sec,buf,ii);
  fwrite(flog,msg,strlen(msg),&err);
 } 
}
#endif
