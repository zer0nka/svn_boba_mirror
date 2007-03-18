#include "../inc/swilib.h"
#include "main.h"
#include "clist_util.h"
#include "history.h"
#include "message_list.h"
#include "jabber_util.h"
#include "string_util.h"

//-------------�����. ����� ������ :)

#ifdef STD_PALETTE

//����� ���
#define MESSAGEWIN_BGCOLOR 0
//���������
#define MESSAGEWIN_TITLE_BGCOLOR 21
//���� ������
#define MESSAGEWIN_TITLE_FONT 1
#define MESSAGEWIN_CHAT_FONT 1

//���������
#define MESSAGEWIN_MY_BGCOLOR 0
//��������
#define MESSAGEWIN_CH_BGCOLOR 22
#define MESSAGEWIN_GCHAT_BGCOLOR_1 13
#define MESSAGEWIN_GCHAT_BGCOLOR_2 10
#define MESSAGEWIN_SYS_BGCOLOR 0
#define MESSAGEWIN_STATUS_BGCOLOR 0

#else

RGBA MESSAGEWIN_BGCOLOR =         {255, 255, 255, 100};
RGBA MESSAGEWIN_TITLE_BGCOLOR =   {  0,   0, 255, 100};
RGBA MESSAGEWIN_TITLE_FONT =      {255, 255, 255, 100};
RGBA MESSAGEWIN_MY_BGCOLOR =      {233, 255, 233, 100};
RGBA MESSAGEWIN_CH_BGCOLOR =      {233, 233, 233, 100};
RGBA MESSAGEWIN_CURSOR_BGCOLOR =  {0xFF, 0xFF, 0x00, 0x64};
RGBA MESSAGEWIN_GCHAT_BGCOLOR_1 =  {255, 255, 255, 100};
RGBA MESSAGEWIN_GCHAT_BGCOLOR_2 =  {233, 233, 233, 100};
RGBA MESSAGEWIN_SYS_BGCOLOR =     {255, 233, 233, 100};
RGBA MESSAGEWIN_STATUS_BGCOLOR =  {233, 233, 255, 100};
RGBA MESSAGEWIN_CHAT_FONT =       {  0,   0,   0, 100};
  
#endif

//------------------


char MsgList_Quit_Required = 0;

TRESOURCE* Resource_Ex = NULL;


int Message_gui_ID;


#pragma inline
void patch_header(HEADER_DESC* head)
{
  head->rc.x=0;
  head->rc.y=YDISP;
  head->rc.x2=ScreenW()-1;
  head->rc.y2=HeaderH()+YDISP;
}
#pragma inline
void patch_input(INPUTDIA_DESC* inp)
{
  inp->rc.x=0;
  inp->rc.y=HeaderH()+1+YDISP;
  inp->rc.x2=ScreenW()-1;
  inp->rc.y2=ScreenH()-SoftkeyH()-1;
}


WSHDR* ws_eddata = NULL;
int Terminate=0;
//---------------------------------------------------------------------------
// Test edit dialog
//---------------------------------------------------------------------------
int inp_onkey(GUI *gui, GUI_MSG *msg)
{

  if(msg->gbsmsg->submess==GREEN_BUTTON)
  {
    Terminate = 1;
    return 1;
  }

  if (msg->keys==0x18)
  {
    ShowMSG(1,(int)"/part ��� ������ �� ����� :)");
    return(-1); //do redraw
  }
  return(0); //Do standart keys

}

void inp_redraw(void *data)
{
}


void inp_ghook(GUI *gui, int cmd)
{
  static SOFTKEY_DESC sk={0x0018, 0x0000,(int)"������"};
  EDITCONTROL ec;
  if (cmd==2)
  {
    //Called after onCreate
  }
  if (cmd==7)
  {
#ifdef NEWSGOLD
    SetSoftKey(gui,&sk,0);    
#else
    SetSoftKey(gui,&sk,2);
#endif   
    ExtractEditControl(gui,1,&ec);    
    wstrcpy(ws_eddata,ec.pWS);
  }
  
  if(cmd==0xA)
  {
    DisableIDLETMR();   // ��������� ������ ������ �� ��������
  }
  
  if(Terminate) 
 {
   ExtractEditControl(gui,1,&ec);    
   wstrcpy(ws_eddata,ec.pWS);
   //size_t xz = wstrlen(ws_eddata)*2;
   if(wstrlen(ws_eddata))
   {
    //char* body =  utf16_to_utf8((char**)ws_eddata,&xz);
    //body[xz]='\0';
     int res_len;
     char* body = malloc(wstrlen(ws_eddata)*2+1);
     ws_2utf8(ws_eddata, body, &res_len, wstrlen(ws_eddata)*2+1);
     body = realloc(body, res_len+1);
     body[res_len]='\0';
   char is_gchat = Resource_Ex->entry_type== T_CONF_ROOT ? 1: 0;
   char part_str[]="/part";
   
   if(!is_gchat)
   {
     CList_AddMessage(Resource_Ex->full_name, MSG_ME, body);
   }
   else
   if(strstr(body, part_str)==body)  // ���� � ������
   {
     CLIST* room=CList_FindContactByJID(CList_GetActiveContact()->full_name);
     Leave_Conference(room->JID);
     CList_MakeAllResourcesOFFLINE(room);
     Terminate = 0;
     mfree(body);    
     return;
   }
   IPC_MESSAGE_S *mess = malloc(sizeof(IPC_MESSAGE_S));
   mess->IsGroupChat = is_gchat;
   mess->body = body;
   SUBPROC((void*)SendMessage,Resource_Ex->full_name, mess);
   REDRAW();
   }
   else ShowDialog_Error(1,(int)"������ ������� ������ ���������");
   Terminate = 0;
 }
 
  if(cmd==0x03)     // onDestroy
  {
    FreeWS(ws_eddata);
    ws_eddata = NULL;
  } 
}

void inp_locret(void){}

SOFTKEY_DESC menu_sk[]=
{
  {0x0018,0x0000,(int)"�����"},
  {0x0001,0x0000,(int)"�����"},
  {0x003D,0x0000,(int)LGP_DOIT_PIC}
};

SOFTKEYSTAB menu_skt=
{
  menu_sk,0
};

INPUTDIA_DESC inp_desc=
{
  1,
  inp_onkey,
  inp_ghook,
  (void *)inp_locret,
  0,
  &menu_skt,
  {0,22,131,153},
  4,
  100,
  101,
  0,
  0,
  0x40000000
};

HEADER_DESC inp_hdr={0,0,0,0,NULL,(int)"�����...",LGP_NULL};



// ������� ���� ��������� ������ ���������
void Init_Message(TRESOURCE* ContEx, char *init_text)
{
  Resource_Ex = ContEx;
  patch_header(&inp_hdr);
  patch_input(&inp_desc);
  ws_eddata = AllocWS(MAX_MSG_LEN);
  if(init_text)
  {
    utf8_2ws(ws_eddata, init_text, MAX_MSG_LEN);    
  }
  EDITCONTROL ec;
  void *ma=malloc_adr();
  void *eq;
  PrepareEditControl(&ec);
  eq=AllocEQueue(ma,mfree_adr());
  ConstructEditControl(&ec,3,0x40,ws_eddata,MAX_MSG_LEN);
  AddEditControlToEditQend(eq,&ec,ma);
  CreateInputTextDialog(&inp_desc,&inp_hdr,eq,1,0);  
}
////////////////////////////////////////////////////////////////////////////////
DISP_MESSAGE* MessagesList = NULL;      // ������ ������
unsigned int DispMessList_Count = 0;        // ���������� ���������
unsigned int OLD_MessList_Count = 0;    // ����������� ���������� ���������
unsigned int Cursor_Pos = 0;            // ������� ������� � ������


// ����� ������ ���������
void KillDisp(DISP_MESSAGE* messtop)
{
  DISP_MESSAGE* cl=messtop;
  LockSched();
  messtop = NULL;
  int cnt=0;
  while(cl)
  {
    DISP_MESSAGE *p;
    if(cl->mess)FreeWS(cl->mess);
    p=cl;
    cl=cl->next;
    mfree(p);
    cnt++;
  }
  DispMessList_Count = 0;
  OLD_MessList_Count = 0;
  UnlockSched();
}

//===============================================================================================

char CurrentPage=1;
char CurrentMessage = 0;
char CurrentMessage_Lines = 0;
char lines_on_page;
char MaxPages=1;
unsigned short FontSize;
// ������������ ���������� GUI

// ������ ����������� ������� :)
void Calc_Pages_Data()
{
  MaxPages = sdiv(lines_on_page,DispMessList_Count);
  if(lines_on_page*MaxPages<DispMessList_Count)MaxPages++;
}

// ������ ����������� ������� :)
void Calc_Pages_Data_1()
{
  if((Cursor_Pos-1-(CurrentMessage_Lines)<=(CurrentPage-1)*lines_on_page) && CurrentPage>1)
    {
      CurrentPage--;
      Cursor_Pos--;
      //ShowMSG(1,(int)"Q");
      return;
    }
  else
  {
    //char q[20];
    //sprintf(q,"Cur=%d > %d", Cursor_Pos-1-(CurrentMessage_Lines), (CurrentPage-1)*lines_on_page);
    //ShowMSG(1,(int)q);
  }
}


void Calc_Pages_Data_2()
{
  if(Cursor_Pos+1>CurrentPage*lines_on_page)
  {
    CurrentPage++;
    Cursor_Pos++;
  }
}

void mGUI_onRedraw(GUI *data)
{
  
  if(Resource_Ex->total_msg_count!=OLD_MessList_Count)
  {
    //KillDisp(MessagesList);
    ParseMessagesIntoList(Resource_Ex);
    OLD_MessList_Count = Resource_Ex->total_msg_count;
  }
  
  Terminate = 0;
  // ������ ���������� ����� �� ����� ��������
  
  Calc_Pages_Data();
  // ��������� ����
  DrawRoundedFrame(0,0,ScreenW()-1,FontSize*2+1,0,0,0,
		   0,
		   color(MESSAGEWIN_TITLE_BGCOLOR));
  
  DrawRoundedFrame(0,FontSize+2,ScreenW()-1,ScreenH()-1,0,0,0,
		   0,
		   color(MESSAGEWIN_BGCOLOR));

  // ������ ���� �������� ������... :)
  WSHDR* ws_title = AllocWS(256);
  //str_2ws(ws_title, Resource_Ex->full_name,strlen(Resource_Ex->full_name));
  ascii2ws(ws_title, Resource_Ex->full_name);

  DrawString(ws_title,1,1,ScreenW()-1,FontSize+1,SMALL_FONT,0,color(MESSAGEWIN_TITLE_FONT),0);  
  
  DISP_MESSAGE* ml = MessagesList;
  int i_ctrl=0;

  int i = 0;
#ifdef STD_PALETTE
  char MsgBgColor;
#else 
  RGBA MsgBgColor;
#endif
  while(ml)
  {
    if((i_ctrl>=(CurrentPage-1)*lines_on_page) && (i_ctrl<CurrentPage*lines_on_page))
    {

      switch(ml->mtype)
      {
      case MSG_ME:{MsgBgColor=MESSAGEWIN_MY_BGCOLOR;break;}        
      case MSG_CHAT:{MsgBgColor=MESSAGEWIN_CH_BGCOLOR;break;}                                        
      case MSG_SYSTEM:{MsgBgColor=MESSAGEWIN_SYS_BGCOLOR;break;}                    
      case MSG_STATUS:{MsgBgColor=MESSAGEWIN_STATUS_BGCOLOR;break;}                            
      case MSG_GCHAT:
        {
          MsgBgColor=ml->log_mess_number %2==0? MESSAGEWIN_GCHAT_BGCOLOR_1 : MESSAGEWIN_GCHAT_BGCOLOR_2;
          break;
        }
      }
      if(CurrentMessage==ml->log_mess_number)
      { 
         MsgBgColor = MESSAGEWIN_CURSOR_BGCOLOR;
         Cursor_Pos = i_ctrl+1;                    // ��������� ������� �������
         CurrentMessage_Lines++;
      }
      
      DrawRoundedFrame(0,HIST_DISP_OFS+i*FontSize,ScreenW()-1,HIST_DISP_OFS+(i+1)*FontSize,0,0,0,
		   color(MsgBgColor),
		   color(MsgBgColor));
    
      DrawString(ml->mess,1,HIST_DISP_OFS+i*FontSize,ScreenW()-1,HIST_DISP_OFS+(i+1)*FontSize*2,SMALL_FONT,0,color(MESSAGEWIN_CHAT_FONT),0);      
      i++;
    }
    ml = ml->next;
    i_ctrl++;
  }  
  FreeWS(ws_title);
  Resource_Ex->has_unread_msg =0; // ������������� ��������� ������ ���

}

void mGUI_onCreate(GUI *data, void *(*malloc_adr)(int))
{
  data->state=1;
  MsgList_Quit_Required=0;
}

void mGUI_onClose(GUI *data, void (*mfree_adr)(void *))
{
  KillDisp(MessagesList);
  data->state=0;
}

void mGUI_onFocus(GUI *data, void *(*malloc_adr)(int), void (*mfree_adr)(void *))
{
  DisableIDLETMR();   // ��������� ������ ������ �� ��������
  data->state=2;
}

void mGUI_onUnfocus(GUI *data, void (*mfree_adr)(void *))
{
  if (data->state!=2) return;
  data->state=1;
}

void DbgInfo()
{
  char q[200];
  sprintf(q,"Messlist_cnt=%d\nCurMessage=%d\nLines=%d\nCursor=%d, CurPage=%d",DispMessList_Count, CurrentMessage, CurrentMessage_Lines,Cursor_Pos, CurrentPage);
  ShowMSG(2,(int)q);
}

int mGUI_onKey(GUI *data, GUI_MSG *msg)
{
  if(MsgList_Quit_Required)return 1; //���������� ����� GeneralFunc ��� ���. GUI -> �������� GUI

  //DirectRedrawGUI();
  if (msg->gbsmsg->msg==KEY_DOWN)
  {
    switch(msg->gbsmsg->submess)
    {
      case '0':
      {
        // ����� ������ ���������
        //KillDisp(MessagesList);
        KillMsgList(Resource_Ex->log);
        Resource_Ex->log = NULL;
        Resource_Ex->has_unread_msg=0;
        Resource_Ex->total_msg_count=0;
        return 1;
      }
      
      case RIGHT_SOFT:
      {
        return 1;
      }
      
    case LEFT_SOFT:
      {
        DbgInfo();
        break;
      }
   
    case ENTER_BUTTON:
      {
        int i;
        char *init_txt = NULL;
        LOG_MESSAGE* log =Resource_Ex->log;
        for(i=0;i<Resource_Ex->total_msg_count;i++)
        {
          if(i+1==CurrentMessage)
          {
            init_txt = log->mess;
            break;
          }
          log = log->next;
        }
        
        if(log)Init_Message(Resource_Ex, init_txt);
        break;
      }
      
      case UP_BUTTON:
        {
          Calc_Pages_Data_1();
          CurrentMessage_Lines = 0;
          if(CurrentMessage>1)CurrentMessage--;
          REDRAW();
          break;         
        }
    case DOWN_BUTTON:
      {
          CurrentMessage_Lines = 0;
          if(CurrentMessage<Resource_Ex->total_msg_count)CurrentMessage++;
          Calc_Pages_Data_2();
          REDRAW();
          break;         
      }
    case GREEN_BUTTON:
      {
        Init_Message(Resource_Ex, NULL);
        break;
      }
    }    
  }
  return(0);
}


extern void kill_data(void *p, void (*func_p)(void *));

// ���
int mGUI_method8(void){return(0);}

int mGUI_method9(void){return(0);}

const void * const mgui_methods[11]={
  (void *)mGUI_onRedraw,	//Redraw
  (void *)mGUI_onCreate,	//Create
  (void *)mGUI_onClose,	//Close
  (void *)mGUI_onFocus,	//Focus
  (void *)mGUI_onUnfocus,	//Unfocus
  (void *)mGUI_onKey,	//OnKey
  0,
  (void *)kill_data, //onDestroy,	//Destroy
  (void *)mGUI_method8,
  (void *)mGUI_method9,
  0
};
////////////////////////////////////////////////////////////////////////////////
#pragma inline
void patch_rect(RECT*rc,int x,int y, int x2, int y2)
{
  rc->x=x;
  rc->y=y;
  rc->x2=x2;
  rc->y2=y2;
}


const RECT mCanvas={0,0,0,0};

/////////////////////////////////////////// ������ ����� ��� ������ ������������

// ���������, �����������, ��� �� ��� ������
typedef struct
{
  char mask[7];
  char replace;
}REPL_ARRAY;

// ���� ������ � �� ����������
const int Repl_chars_count = 5;
REPL_ARRAY Repl_chars[] = {"&apos;\0",0x27,
                           "&quot;\0",'"',
                           "&lt;\0\0\0", '<',
                           "&gt;\0\0\0", '>',
                           "&amp;\0\0", '&',                   
};

/*
    �������� ���������� �� ��� �����
IN: mask_begin - ������ ��������
    out_ofs - �����, � �������� ���������� ����� ������������ ������������������
OUT: out_ofs - �������� � ������, ������ ���������� �������������� ������
    <return> - ����������
*/
char GetSpecialSym(char *mask_begin, int *out_ofs)
{
  int i=0;
  int replen;
  char rep_ex[10];
  if(*mask_begin!='&')return *(mask_begin);
  for(i=0;i<Repl_chars_count;i++)
  {
    replen = strlen(Repl_chars[i].mask);  // ���������� ����� ��������� �����
    zeromem(rep_ex,10);
    strncpy(rep_ex,mask_begin,replen);    // �������� ������ ����� ����� � ������� �������
    if(!strcmp(rep_ex,Repl_chars[i].mask))// ���� ������� � ��������� ������
    {
      *out_ofs+=replen-1;                   // ����������� ������������ ����� �� ����� �����
      return Repl_chars[i].replace;       // ���������� ������ ��� ������
    }
  }
  return *(mask_begin);       //  ����� �� �������, ���������� ��� ����
}

// �������� ��������� ��������� DISP_MESSAGE ��� ����������� �� ������
void ParseMessagesIntoList(TRESOURCE* ContEx)
{
  if(!ContEx)return;
  int parsed_counter = 0; // ������� ��� ���� ���������� (=OLD_MessList_Count)
  LOG_MESSAGE* MessEx= ContEx->log;
  int cnt=0;
  char IsCaret = 0; // �������� �� ������ ��������� ������
//  int chars;
  DISP_MESSAGE* Disp_Mess_Ex, *tmp;  
  if(!MessEx)return;
  LockSched();

  WSHDR *temp_ws_1=NULL;
  WSHDR *temp_ws_2=NULL;
  
  // ���� �� ���� ����������
  while(MessEx)
  {
    
    if(parsed_counter>=OLD_MessList_Count)
    {
      temp_ws_1 = AllocWS(strlen(MessEx->mess)*2);
      utf8_2ws(temp_ws_1, MessEx->mess, strlen(MessEx->mess)*2);
      temp_ws_2 = AllocWS(CHAR_ON_LINE);
      int l=wstrlen(temp_ws_1);
      
        //char q[40];
        //sprintf(q,"UTF_len=%d, WSTR_len=%d", strlen(MessEx->mess),l);
        //ShowMSG(2,(int)q);
      
    int i=0;
    unsigned short *wschar;
    unsigned short symb;
    cnt=0;
    for(i=1;i<=l;i++)
    {
      //if(MessEx->mess+i=='\0')break;
      //symb = GetSpecialSym(MessEx->mess+i,&i);
      wschar = temp_ws_1->wsbody+i;
      symb = *wschar;
      IsCaret = symb==0x000A || symb==0x000D || symb==0x00A0 ? 1 : 0;
      if(!IsCaret && symb!=0x0 && cnt<CHAR_ON_LINE)
      {
        //*(msg_buf + cnt) = symb;
        wsAppendChar(temp_ws_2, symb);
        cnt++;
      }
      if(IsCaret || cnt>=CHAR_ON_LINE || i==l) // ������� ������
      {
        Disp_Mess_Ex = malloc(sizeof(DISP_MESSAGE));
        Disp_Mess_Ex->mess = AllocWS(cnt);
        wstrcpy(Disp_Mess_Ex->mess, temp_ws_2);
        CutWSTR(temp_ws_2, 0);
        Disp_Mess_Ex->mtype = MessEx->mtype;
        Disp_Mess_Ex->log_mess_number=parsed_counter+1;
        if(!MessagesList){MessagesList =Disp_Mess_Ex;Disp_Mess_Ex->next=NULL;}
        else
        {
          tmp= MessagesList;
          while(tmp->next)
          {
            tmp = tmp->next;
          }
          tmp->next = Disp_Mess_Ex;
          Disp_Mess_Ex->next=NULL;
        }
        cnt=0;
        DispMessList_Count++;
      }
    }
    FreeWS(temp_ws_1);
    FreeWS(temp_ws_2);
    }
    MessEx = MessEx->next;
    parsed_counter++;
  }
//  mfree(msg_buf);
  UnlockSched();
}


// ���������� ������ ���������
void Display_Message_List(TRESOURCE* ContEx)
{
  if(!ContEx)return;
// �������������
  OLD_MessList_Count = 0;
  MessagesList = NULL;
  DispMessList_Count = 0;
  Resource_Ex = ContEx;
  FontSize = GetFontYSIZE(SMALL_FONT);
  lines_on_page = sdiv(FontSize, ScreenH() - HIST_DISP_OFS);
  ParseMessagesIntoList(Resource_Ex);
  Calc_Pages_Data();
  CurrentPage = MaxPages;
  OLD_MessList_Count = Resource_Ex->total_msg_count;
  Cursor_Pos = DispMessList_Count;
  CurrentMessage = OLD_MessList_Count;
  
// ������� ���
  GUI *mess_gui=malloc(sizeof(GUI));
  zeromem(mess_gui, sizeof(GUI));
  patch_rect((RECT*)&mCanvas,0,0,ScreenW()-1,ScreenH()-1);
  mess_gui->canvas=(void *)(&mCanvas);
  mess_gui->flag30=2;
  mess_gui->methods=(void *)mgui_methods;
  mess_gui->item_ll.data_mfree=(void (*)(void *))mfree_adr();
  Message_gui_ID = CreateGUI(mess_gui);
}
