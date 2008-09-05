#include "..\\include\Lib_Clara.h"
#include "..\\include\Dir.h"

DISP_OBJ * StatusIndication;
int Height,Width;
u16 ftimer;

int _x=100;
int _y=100;
int _dx=2;
int _dy=3;

void (*SIonRedraw)(DISP_OBJ *,int r1,int r2,int r3);
void Draw(DISP_OBJ * db,int r1, int r2,int r3);

typedef struct
{
  BOOK * book;
}MSG;

void Send_REDRAW_RELEASE()
{
  // �������� ����  ������� �� ������ � ����� �������� Redraw
  SBY_REDRAW_RELEASE_MESSAGE * sbm= new SBY_REDRAW_RELEASE_MESSAGE;
  sbm->OldonRedraw=SIonRedraw;
  sbm->NewonRedraw=Draw;
  UI_Event_wData(SBY_REDRAW_RELEASE_EVENT ,sbm,(void (*)(void*))mfree_adr());
}

int TerminateSBDraw(void * ,BOOK* book)
{
  Send_REDRAW_RELEASE();
  FreeBook(book);
  return(1);
}

int ShowAuthorInfo(void *mess ,BOOK* book)
{
  MSG * msg = (MSG*)mess;
  MessageBox(0x6fFFFFFF,STR("StandBy Draw test..."),0, 1 ,5000,msg->book);
  return(1);
}


int SB_ELF_Killed(void *mess ,BOOK* book)
{
  // ���� ��� ���� ���� �������� �� �� ��� ������ ����� ������������ ������
  SBY_REDRAW_RELEASE_MESSAGE * sbm=(SBY_REDRAW_RELEASE_MESSAGE*)mess;

  // ��� �� ����� �� ���������� � �������� oldRedraw?
  if (sbm->NewonRedraw==SIonRedraw)
  {
    SBY_REDRAW_RELEASE_MESSAGE * ms= new SBY_REDRAW_RELEASE_MESSAGE;

    // ���� �� ��� ����, �� �������� ���� oldRedraw �� ���..
    if (sbm->OldonRedraw) SIonRedraw=sbm->OldonRedraw;

    // ������ �d�� ����� ������
    DISP_DESC_SetOnRedraw(DISP_OBJ_GetDESC(StatusIndication),Draw);

    // � ��� ������� �����, ���� ��������� ����� ������� ���� �����
    ms->OldonRedraw=0;
    ms->NewonRedraw=Draw;
    UI_Event_wData(SBY_REDRAW_RELEASE_EVENT ,ms,(void (*)(void*))mfree_adr());
  }
  return(1);
}



const PAGE_MSG SBDraw_PageEvents[]@ "DYN_PAGE" ={
  SBY_REDRAW_RELEASE_EVENT  , SB_ELF_Killed,
  ELF_TERMINATE_EVENT       , TerminateSBDraw,
  ELF_SHOW_INFO_EVENT       , ShowAuthorInfo,
  NIL_EVENT_TAG             , NULL

};

PAGE_DESC base_page ={"SBDraw_BasePage",0,SBDraw_PageEvents};

void elf_exit(void)
{
  kill_data(&ELF_BEGIN, (void(*)(void*))mfree_adr());
}

void onfTimer (u16 tmr , void *)
{
  InvalidateRect(StatusIndication,0);
  Timer_ReSet(&ftimer,20,onfTimer,0);
}

void Draw(DISP_OBJ * db,int r1, int r2,int r3)
{
  // �������� ������ onRedraw.
  SIonRedraw(db,r1,r2,r3);

  DrawRect(_x,_y,_x+10,_y+10,clRed,clRed);
  if ((_x>Width-11) && (_dx>0)) _dx=0-_dx;
  if ((_x<9) && (_dx<0)) _dx=0-_dx;
  if ((_y>Height-50) && (_dy>0)) _dy=0-_dy;
  if ((_y<20) && (_dy<0)) _dy=0-_dy;
  _x+=_dx;
  _y+=_dy;
}

void onCloseMyBook(BOOK * book)
{
  if (book)
  {
    Timer_Kill(&ftimer);
    DISP_DESC_SetOnRedraw(DISP_OBJ_GetDESC(StatusIndication),SIonRedraw);
    SUBPROC(elf_exit);
  }
}

BOOK * CreateSBDBook()
{
  BOOK * SBDBook= new BOOK;
  CreateBook(SBDBook,onCloseMyBook,&base_page,"SBDraw_Test",-1,0);
  return(SBDBook);
}

//
// ������������� ������ ��������� �� StandBy.
// ��������� ��������� ����� �����. ����� ������� ������ ���������� ����� �� StandBy.
//
// ��� ��������� �������� OnRedraw � StatusIndication �� ����. ������ �������� � ���� ������.
// ��� ���������� ������ �������� ���������(��.Send_REDRAW_RELEASE())
// ��� �� ���� ����������� ������������ SBY_REDRAW_RELEASE_EVENT
//
int main (void)
{
  Height=Display_GetHeight(0);
  Width=Display_GetWidth(0);;
  CreateSBDBook();

  StatusIndication=((GUI*)SBY_GetStatusIndication(Find_StandbyBook()))->DISP_OBJ;
  SIonRedraw=DISP_OBJ_GetOnRedraw(StatusIndication);
  DISP_DESC_SetOnRedraw(DISP_OBJ_GetDESC(StatusIndication),Draw);
  ftimer=Timer_Set(20,onfTimer,0);
  return(0);
}

