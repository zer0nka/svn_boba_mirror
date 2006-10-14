#include "..\inc\swilib.h"

#define RECONNECT_TIME (1000*10)

CSM_DESC icsmd;

int (*old_icsm_onMessage)(CSM_RAM*,GBS_MSG*);


const char binary_profile[0x204]=
{
    0x4E, 0x41, 0x54, 0x5F, 0x43, 0x48, 0x41, 0x4E,
/*  0x4E, 0x41, 0x50, 0x32, 0x00, 0x00, 0x00, 0x00, */0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x03, 0x6C, 0x69, 0x66, 0x65, 0x3A, 0x29, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x69, 0x6E, 0x74, 0x65, 0x72, 0x6E, 0x65, 0x74,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xFF, 0xE0, 0xF5, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

NAP_PARAM_CONT *nap_container;

GBSTMR mytmr;
void reconnect(void)
{
  void do_connect(void);
  SUBPROC((void *)do_connect);
}

void do_connect(void)
{
  REGSOCKCEPID_DATA rsc;
  LMAN_DATA lmd;
  NAP_PARAM_CONT *nc;

  //������������� ����������
  rsc._0x0080=0x0080;
  rsc._0xFFFF=0xFFFF;
  rsc._0x0000=0x0000;
  RegisterCepidForSocketWork(&rsc);
  nap_container=nc=malloc(sizeof(NAP_PARAM_CONT));
  nc->len=sizeof(NAP_PARAM_CONT);
  nc->ctx_napdef=&(nc->napdef);
  nc->zero=0;
  memcpy(&nc->napdef,binary_profile,sizeof(CTX_NAPDEF));
  lmd.zero=0;
  lmd.native_profile=NULL;
  lmd._1=1;
  lmd._4=4;
  lmd._0=0;
  lmd.NapParameterContainer=nc;
  RequestLMANConnect(&lmd);
  GBS_StartTimerProc(&mytmr,RECONNECT_TIME*2,reconnect);
}

void LogWriter(const char *s)
{
  TTime t;
  TDate d;
  char ss[100];
  unsigned int ul;
  int f=fopen("4:\\ZBin\\etc\\GprsD.log",A_ReadWrite+A_Create+A_Append,P_READ+P_WRITE,&ul);
  if (f!=-1)
  {
    GetDateTime(&d,&t);
    sprintf(ss,"%02d:%02d %02d-%02d-%04d: ",
	   t.hour,t.min,d.day,d.month,d.year);
    fwrite(f,ss,strlen(ss),&ul);
    fwrite(f,s,strlen(s),&ul);
    fwrite(f,"\r\n",2,&ul);
    fclose(f,&ul);
  }
}

int MyIDLECSM_onMessage(CSM_RAM* data,GBS_MSG* msg)
{
  int csm_result;
  char s[100];
  csm_result=old_icsm_onMessage(data,msg); //�������� ������ ���������� �������
  if (msg->msg==MSG_HELPER_TRANSLATOR)
  {
    int m=(int)msg->data0;
    sprintf(s,"MSG: %08X %08X %08X",msg->submess,msg->data0,msg->data1);
    LogWriter(s);
    if (m==LMAN_CONNECT_CNF)
    {
      GBS_StopTimer(&mytmr);
      strcpy(s,"Session started!");
      LogWriter(s);
      ShowMSG(1,(int)s);
    }else
    if ((m==LMAN_DISCONNECT_CNF)||(m==LMAN_CONNECT_REJ))
    {
      strcpy(s,"Session closed!");
      LogWriter(s);
      ShowMSG(1,(int)s);
      GBS_StartTimerProc(&mytmr,RECONNECT_TIME,reconnect);
    }/*else
    {
      sprintf(s,"MSG: %04X\n%04X %04X",msg->submess,msg->data0,msg->data1);
      ShowMSG(1,(int)s);
    }*/
  }
  return(csm_result);
}

int main()
{
  LockSched();
  CSM_RAM *icsm=FindCSMbyID(CSM_root()->idle_id);
  memcpy(&icsmd,icsm->constr,sizeof(icsmd));
  old_icsm_onMessage=icsmd.onMessage;
  icsmd.onMessage=MyIDLECSM_onMessage;
  icsm->constr=&icsmd;
  UnlockSched();
  SUBPROC((void*)do_connect);
  return 0;
}
