#include "..\deleaker\mem2.h"
#include "..\include\Lib_Clara_DLL.h"
#include "header\cl.h"

MyBOOK *MyBook=0;
static void __onClose(BOOK* bk)
{
  ((CBook*)bk)->onClose();
};

CBook::CBook(char* pBookName, const PAGE_DESC * bp)
{
  CreateBook( this, &__onClose, bp, pBookName, -1, 0);
  MyBook=this;
};

void CBook::destroy()
{
  FreeBook((BOOK*)this);
};

CBook::~CBook()
{
};

void CBook::onClose()
{
};
