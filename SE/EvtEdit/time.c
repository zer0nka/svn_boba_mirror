#include "mem.h"
#include "..\\include\Lib_Clara.h" 
#include "..\\include\Dir.h" 
#include "header\structs.h"
#include "..\\include\var_arg.h"
#include "header\pages.h"
#include "header\externals.h"
#include "header\lng.h"

#define TI_GET_HOUR(x) ((unsigned int)x&0xFF)
#define TI_GET_MIN(x) (((unsigned int)x>>8)&0xFF)
#define TI_GET_SEC(x) (((unsigned int)x>>16)&0xFF)

#define DI_GET_YEAR(x) ((unsigned int)x&0xFFFF)
#define TI_GET_MONTH(x) (((unsigned int)x>>16)&0xFF)
#define TI_GET_DAY(x) ((unsigned int)x>>24)

#define IDN_TIME_INPUT_ICON L"FR_INPUT_GUI_SET_TIME_ICN"
#define IDN_DATE_INPUT_ICON L"FR_INPUT_GUI_SET_DATE_ICN"

extern LIST *events;

int InitializeEvents(BOOK *myBook);
void DestroyEvents(BOOK *myBook);

void AcceptTIinput(BOOK *bk, void *data)
{
  MyBOOK *mbk=(MyBOOK *)bk;
  unsigned int i=TimeInput_GetTimeInt(data);
  TIME *time=mbk->curtime;
  time->hour=TI_GET_HOUR(i);
  time->min=TI_GET_MIN(i);
  mbk->TextInputType=6;
  mbk->inputType=IT_UNSIGNED_DIGIT;
  mbk->minint=0;
  mbk->maxint=59;
  BookObj_CallPage(bk, &bk_StringInput);
};

void CloseTIinput(BOOK * bk, void *)
{
  MyBOOK *mbk=(MyBOOK *)bk;
  mbk->curtime=0;
  BookObj_ReturnPage(bk, PREVIOUS_EVENT);
};

static int TI_OnEnter(void *,BOOK * bk)
{
  MyBOOK *mbk=(MyBOOK *)bk;
  TIME t;
  TIME *time=mbk->curtime;
  int time_format=4;
  char time_f;
  int icon_id;
  t.hour=time->hour;
  t.min=time->min;
  t.sec=time->sec;
  if (!REQUEST_TIMEFORMAT_GET(SYNC,&time_f)) time_format=time_f;
  mbk->tinput=CreateTimeInputVA(0,
                                VAR_HEADER_TEXT(Str2ID(lng[LNG_TIME],0,SID_ANY_LEN)),
                                VAR_TIMEINP_TIMEFORMAT(time_format),
                                VAR_TIMEINP_TIME(&t),
                                VAR_BOOK(&mbk->book),
                                0);
  GUIObject_Softkey_SetAction(mbk->tinput,ACTION_ACCEPT, AcceptTIinput);
  GUIObject_Softkey_SetText(mbk->tinput,ACTION_ACCEPT,GetStrID(L"CB_MESSAGE_RECEIVED_SAVE_SK"));
  GUIObject_SoftKey_SetVisible(mbk->tinput,ACTION_ACCEPT,1);
  GUIObject_Softkey_SetAction(mbk->tinput,ACTION_BACK, CloseTIinput);
  if (iconidname2id(IDN_TIME_INPUT_ICON,-1,&icon_id))
    InputFeedback_SetIcon(mbk->tinput,icon_id);
  return (1);
};

static int TI_OnExit(void *, BOOK * bk)
{
  MyBOOK *mbk=(MyBOOK *)bk;
  FREE_GUI(mbk->tinput);
  return (1);  
};

const PAGE_MSG bk_msglst_timeinput[] @ "DYN_PAGE"  = 
{
  PAGE_ENTER_EVENT_TAG,    TI_OnEnter,
  PAGE_EXIT_EVENT_TAG,     TI_OnExit,
  NIL_EVENT_TAG,           NULL
};

const PAGE_DESC bk_time_input = {"EvtEdit_TimeInput_Page",0,bk_msglst_timeinput};