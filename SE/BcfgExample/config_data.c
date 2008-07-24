#include "..\\include\cfg_items.h"
#include "config_data.h"

#pragma diag_suppress=Pe177

__root const CFG_HDR cfghdr0={CFG_CHECKBOX,"Is Enabled",0,0};
__root const int IS_ENABLED=1;

__root const CFG_HDR cfghdr1={CFG_COORDINATES,"XY Position",0,0};
__root const int X_POS=1;
__root const int Y_POS=1;

__root const CFG_HDR cfghdr_2={CFG_LEVEL,"Setup Colors",1,0};
  __root const CFG_HDR cfghdr3={CFG_COLOR_INT,"Monitor Pen Color",0,0};
  __root const unsigned int PEN_COLOR=0xFF000000;
  
  __root const CFG_HDR cfghdr4={CFG_COLOR_INT,"Monitor Brush Color",0,0};
  __root const unsigned int BRUSH_COLOR=0xFFFFFFFF;
__root const CFG_HDR cfghdr_5={CFG_LEVEL,"",0,0};

__root const CFG_HDR cfghdr6={CFG_CBOX,"Show",0,3};
__root const int SHOW_IF_LOCKED=0;
__root const CFG_CBOX_ITEM cfgcbox1[3]={"If Unlocked","If Locked","Always"};

__root const CFG_HDR cfghdr7={CFG_UINT,"Refresh Time",0,10000};
__root const unsigned int REFRESH_TIME=500;

__root const CFG_HDR cfghdr8={CFG_INT,"Signed int test",-100,100};
__root const int INT_TEST=0;

__root const CFG_HDR cfghdr9={CFG_STR_WIN1251,"WisStr test",0,63};
__root const char WIN_TEST[64]="������";

__root const CFG_HDR cfghdr10={CFG_STR_PASS,"PassStr test",0,63};
__root const char PASS_TEST[64]="�����";