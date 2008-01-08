#ifndef W800_R1BC002
#error W800_R1BC002 configuration needed for this header!
#else
#ifndef _W800_R1BC002_
#define _W800_R1BC002_

#define pKBD 0x4C05DD44
#define EXT_TABLE 0x4422C6D0
#define RUN_CHECK 0x450F2921
#define STR_START 0xA8F
#define STR_APPLICATION 0x0318
#define STR_Saved_in_Applications_on_Memory_Stick 0x0E6F
#define STR_Saved_in_Applications_in_phone_memory 0x0E6E
#define ELF_SMALL_ICON 0xE816
#define ROOT_APP 0x4C182528
#define PID_MMI 0x100E4
#define HELPER_SIG 0x6FF0
#define RAM_BASE (0x4C04B0C8)

#define PATH_AUDIO_INT 0x441EC49C
#define PATH_AUDIO_EXT 0x443FA95A
#define PATH_IMAGE_INT 0x441EC544
#define PATH_IMAGE_EXT 0x443FAA38
#define PATH_VIDEO_INT 0x441EC608
#define PATH_VIDEO_EXT 0x443FAB24
#define PATH_THEME_INT 0x441EC5E8
#define PATH_THEME_EXT 0x443FAAE6
#define PATH_OTHER_INT 0x441EC5C8
#define PATH_OTHER_EXT 0x443FAAA8

#define PATH_ELF_INT            (L"/tpa/user/other/ZBin")
#define PATH_ELF_EXT            (L"/card/MSSEMC/Media files/other/ZBin")
#define PATH_ELF_DAEMONS_INT    (L"/tpa/user/other/Daemons")
#define PATH_ELF_DAEMONS_EXT    (L"/card/MSSEMC/Media files/other/Daemons")
#define PATH_ELF_CONFIG_INT     (L"/tpa/user/other/Config")
#define PATH_ELF_CONFIG_EXT     (L"/card/MSSEMC/Media files/other/Config")
#define PATH_INI                (L"/tpa/user/other/ini")
#define PATH_DEFAULT            (L"/tpa/user/other")

#define ELF_RUN_PAGE_EV_0x10  0x450EF011
#define ELF_RUN_PAGE_EV_0x0F  0x450EF011
#define ELF_RUN_PAGE_EV_0x11  0x450EF019
#define ELF_RUN_PAGE_EV_0x06  0x450EF071

#define DB_CMD_SETSMALLICON 0x35
#define DB_DB_EXT_C1 0x258

#endif
#endif