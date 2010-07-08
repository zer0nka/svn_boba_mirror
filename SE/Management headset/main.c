#include "..\\include\Lib_Clara_DLL.h"
#include "..\\include\Dir.h"
#include "..\\include\cfg_items.h"
#include "config_data.h"
#include "conf_loader.h"

#define ELFNAME "Management v.2.3"
#define ABOUT L"Management\nv.2.3\n\n(c)Ploik & BigHercules\n\nRespect: Slawwan\nUltraShot"

enum mode_t {
    SHORT_PRESS  = 0,
    LONG_PRESS   = 1,
    DOUBLE_PRESS = 2
};

static char myappname[]=ELFNAME;

BOOK * AP = 0;
BOOK * FM = 0;

int dbl   = 0;
u16 timer = 0;
u16 timer_call_off = 0;
int Connect = 0;

int NewKey(int key, int r1 , int mode);
int ControlKey(int key, int r1 , int mode);

int isMTCallBook(BOOK *bk)
{
  if (strcmp(bk->xbook->name,"MTCallBook")==0) { return 1; }
  else { return 0; }
};

int OnAccChangedEvent(void* r0,BOOK* b)
{
  AP = FindBook(isAudioPlayerBook());
  FM = FindBook(isFmRadioBook());
  
 //if (PHF_GetState ())
  //{
  if(!AP && !FM && turn_on==1)
  {
    if(turn_on_pr==0)
    {
       UI_Event(UI_MEDIAPLAYER_CONTROL_EVENT);
    }
     else
    {
        UI_Event(UI_FMRADIO_CONTROL_EVENT);
    }
   //}
 }
    return (1);      
}

int OffAccChangedEvent(void* r0,BOOK* b)
{
  AP = FindBook(isAudioPlayerBook());
  FM = FindBook(isFmRadioBook());
  
  if(AP && FM && turn_off==1)
  {
    GoMusic();
  }
    return (1);    
}

int isManagementBook(BOOK * book)
{
        if(!strcmp(book->xbook->name,myappname)) return true;
        return false;
}

BOOK * ManagementBook;

int TerminateElf(void * ,BOOK* book)
{
        FreeBook(book);
        return(1);
}

typedef struct
{
        BOOK * book;
}MSG;

int ShowAuthorInfo(void *mess ,BOOK* book)
{
         MSG * msg = (MSG*)mess;
         MessageBox(EMPTY_SID, Str2ID(ABOUT, 0, SID_ANY_LEN), NOIMAGE, 1, 5000, msg->book);
         return(1);
}

void onTimer_Call (u16 timerID, LPARAM lparam)
{
    ModifyKeyHook(NewKey,1);
}

enum
{
         CALLMANAGER_IDLE            =0,
         CALLMANAGER_CALL_CONNECTED  =1, /*�������� ������*/
         CALLMANAGER_CALL_SETUP      =2, /*������� �������*/
         CALLMANAGER_CALL_ALERT      =4, /*�������� �����*/
         CALLMANAGER_CALL_WAITING    =5,
         CALLMANAGER_CALL_TERMINATED =6  /*���������� ����������*/
};

int OnCallManagerEvent(void* r0,BOOK* b)
{
    switch(((CALLMANAGER_EVENT_DATA*)r0)->CallState)
       {
         /*�������� ������*/
         case CALLMANAGER_CALL_CONNECTED:
         {
           ModifyKeyHook(ControlKey,0);
         }
         break;
         /*�������� �����*/
         case CALLMANAGER_CALL_ALERT:
         {
          ModifyKeyHook(NewKey,0);
          ModifyKeyHook(ControlKey,1);
          if(timer)
          {
           Timer_Kill(&timer);
           timer = 0;
           dbl = 0;
          }
         }
         break;
         /*������� �������*/
         case CALLMANAGER_CALL_SETUP:
         {
          ModifyKeyHook(NewKey,0);
          if(timer)
          {
           Timer_Kill(&timer);
           timer = 0;
           dbl = 0;
          }
         }
         break;
         /*���������� ����������*/
         case CALLMANAGER_CALL_TERMINATED:
         {
          ModifyKeyHook(ControlKey,0);
          timer_call_off=Timer_Set(2000,onTimer_Call,0);
         }
      break;
    }
  return 1;
}


int CheckConfig()
{
  wchar_t temp[256];
  char* err=NULL;

  int radio_short_press  = 0;
  int radio_long_press   = 0;
  int radio_double_press = 0;
  int player_short_press  = 0;
  int player_long_press   = 0;
  int player_double_press = 0;

  int radio_short_on_press  = 0;
  int radio_long_on_press   = 0;
  int player_short_on_press  = 0;
  int player_long_on_press   = 0;
  
  switch(radioOn){
  case SHORT_PRESS:
    radio_short_on_press++;
    break;
  case LONG_PRESS:
    radio_long_on_press++;
    break;
  }
  
  switch(radioOff){
  case SHORT_PRESS:
    radio_short_press++;
    break;
  case LONG_PRESS:
    radio_long_press++;
    break;
  case DOUBLE_PRESS:
    radio_double_press++;
    break;
  }

  switch(radioNext){
  case SHORT_PRESS:
    radio_short_press++;
    break;
  case LONG_PRESS:
    radio_long_press++;
    break;
  case DOUBLE_PRESS:
    radio_double_press++;
    break;
  }

  switch(radioPrev){
  case SHORT_PRESS:
    radio_short_press++;
    break;
  case LONG_PRESS:
    radio_long_press++;
    break;
  case DOUBLE_PRESS:
    radio_double_press++;
    break;
  }

  switch(playerOn){
  case SHORT_PRESS:
    player_short_on_press++;
    break;
  case LONG_PRESS:
    player_long_on_press++;
    break;
  }
  
  switch(playerOff){
  case SHORT_PRESS:
    player_short_press++;
    break;
  case LONG_PRESS:
    player_long_press++;
    break;
  case DOUBLE_PRESS:
    player_double_press++;
    break;
  }

  switch(playerNext){
  case SHORT_PRESS:
    player_short_press++;
    break;
  case LONG_PRESS:
    player_long_press++;
    break;
  case DOUBLE_PRESS:
    player_double_press++;
    break;
  }

  switch(playerPrev){
  case SHORT_PRESS:
    player_short_press++;
    break;
  case LONG_PRESS:
    player_long_press++;
    break;
  case DOUBLE_PRESS:
    player_double_press++;
    break;
  }

  if((radio_short_press > 1) || (radio_long_press > 1) || (radio_double_press > 1))
    #ifndef ENG
      err="����������� ���������������� ���������� �����!";
    #else
      err="Illegal radio configuration!";
    #endif
  else if((player_short_press > 1) || (player_long_press > 1) || (player_double_press > 1))
    #ifndef ENG
      err="����������� ���������������� ���������� �������!";
    #else
      err="Illegal walkman configuration!";
    #endif
  else if((radio_short_on_press ==  1 && player_short_on_press ==  1) || (radio_long_on_press == 1 && player_long_on_press ==  1))
    #ifndef ENG
      err="����������� ��������������� ������ �������!";
    #else
      err="Illegal key run configuration!";
    #endif
      
  if(err)
  {
    snwprintf(temp, MAXELEMS(temp), _T("Error!\n%s"),err);
    MessageBox(EMPTY_SID,Str2ID(temp,0,MAXELEMS(temp)),NOIMAGE,1,0,0);
    return 1;
  }
  return 0;
}

static int onReconfigElf(void *mess ,BOOK *book)
{
  RECONFIG_EVENT_DATA *reconf=(RECONFIG_EVENT_DATA *)mess;
  int result=0;
  if (wstrcmpi(reconf->path,successed_config_path)==0 && wstrcmpi(reconf->name,successed_config_name)==0)
  {
    InitConfig();
    CheckConfig();
    result=1;
  }
  return(result);
}
const PAGE_MSG Management_PageEvents[]@ "DYN_PAGE" =
{
         ELF_TERMINATE_EVENT,      TerminateElf,
         ELF_SHOW_INFO_EVENT,      ShowAuthorInfo,
         ELF_RECONFIG_EVENT,       onReconfigElf,
         ON_CALLMANAGER_EVENT_TAG, OnCallManagerEvent,
         ACCESSORIES_ACCESSORY_CONNECTED_EVENT_TAG,OnAccChangedEvent,
         ACCESSORIES_ACCESSORY_DISCONNECTED_EVENT_TAG,OffAccChangedEvent,
         NIL_EVENT_TAG,            NULL
};

PAGE_DESC base_page ={"Management_BasePage",0,Management_PageEvents};


void elf_exit(void)
{
         kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}


void MakeAction(int mode)
{
  if (!AP && !FM)
  {
    if(mode == playerOn)  UI_Event(UI_MEDIAPLAYER_CONTROL_EVENT);
    if(mode == radioOn)   UI_Event(UI_FMRADIO_CONTROL_EVENT);
  }
  else if (AP)
  {
    if(mode == playerNext) PlayerControl(AP, 6);
    if(mode == playerPrev) PlayerControl(AP, 7);
    if(mode == playerOff)  UI_Event(UI_MEDIAPLAYER_CONTROL_EVENT);
    return;
  }
  else if (FM)
  {
    if(mode == radioNext) SwitchRadioStationFromList(FM, 0);
    if(mode == radioPrev) SwitchRadioStationFromList(FM, 1);
    if(mode == radioOff)  UI_Event(UI_FMRADIO_CONTROL_EVENT);
  }
}

void onTimer(u16 timerID, LPARAM lparam)
{
  if (dbl==1)
  {
    MakeAction(SHORT_PRESS);
  }
  else
  {
    MakeAction(DOUBLE_PRESS);
  }
  dbl=0;
}

int NewKey(int key, int r1 , int mode)
{
  AP = FindBook(isAudioPlayerBook());
  FM = FindBook(isFmRadioBook());
  if (key==KeyControl)
  {
    if (mode==KBD_SHORT_RELEASE)
    {
      if (!dbl) timer=Timer_Set(detectTime,onTimer,0);
      dbl++;
    }
    if (mode==KBD_LONG_PRESS)
    {
      MakeAction(LONG_PRESS);
    }
    return(-1);
  }
  return(0);
}

int ControlKey(int key, int r1 , int mode)
{
  BOOK *bk = FindBook(isMTCallBook);
  if (key==KeyControl)
  {
    if (mode==KBD_SHORT_RELEASE)
    {
      IncommingCall_Accept(bk);
    }
    if (mode==KBD_LONG_PRESS)
    {
      IncommingCall_Reject(bk);
    }
    return(-1);
  }
  return(0);
}
void onCloseManagementBook(BOOK * book)
{
  ModifyKeyHook(NewKey,0);
  ModifyKeyHook(ControlKey,0);
  if(timer) Timer_Kill(&timer);
  if(timer_call_off) Timer_Kill(&timer_call_off);
  SUBPROC(elf_exit);
}

int main (void)
{
  BOOK* alreadyrunned=FindBook(isManagementBook);
  if(alreadyrunned)
  {
    #ifndef ENG
      MessageBox(EMPTY_SID, STR("Management headset\n��� �������"), NOIMAGE, 1 ,5000, 0);
    #else
      MessageBox(EMPTY_SID, STR("Management headset\nalready runned"), NOIMAGE, 1 ,5000, 0);
    #endif
    SUBPROC(elf_exit);
  }
  else
  {
    InitConfig();
    if(CheckConfig())
    {
      SUBPROC(elf_exit);
      return 0;
    }

    ManagementBook = new BOOK;
    if(!CreateBook(ManagementBook, onCloseManagementBook, &base_page, ELFNAME, -1, 0))
    {
      delete ManagementBook;
      SUBPROC(elf_exit);
      return 0;
    }
    ModifyKeyHook(NewKey,1);
  }
  return(0);
}

/*
  Revision history.
    2
      + ��������� � ��������� ����������������� �����
      + ��������� ����������� ����������� ��������� ������ � ����� (�� ������ �������)

    1.4.4
      + ����������� ������������� ���������� ������
      + ��������� ������ ������.
*/
