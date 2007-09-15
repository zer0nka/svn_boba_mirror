/*
    SieNatJabber Project
 Language
*/
#ifndef _LANG_H_
#define _LANG_H_

#define LG_COPYRIGHT "Siemens natJabber Client\n(c)Kibab, Ad, Borman99\n%s r%d\nCompiled %s"

#define LANG_RU
//#define LANG_UA
//#define LANG_EN

///////////////////////////////////////////////////////////////////////////////////////////
//
//    Russian : �����������!
//
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef LANG_RU
#define LG_SELECT           "�����"
#define LG_BACK             "�����"
#define LG_OK               "OK"
#define LG_CLOSE            "�������"
#define LG_MENU             "����"
#define LG_CANCEL           "������"
#define LG_EXIT             "�����"
#define LG_HELP             "������"
//status_schange.c
#define LG_STATUSSEL        "����� �������"
#define LG_STONLINE         "������"
#define LG_STCHAT           "����� �������"
#define LG_STAWAY           "���������"
#define LG_STXA             "����������"
#define LG_STDND            "�����"
#define LG_STINVIS          "�����"
#define LG_STATUS           "������"
#define LG_ENTERTEXTSTATUS  "������� ����� �������:"
#define LG_PRIORITY         "���������:"
//MUC_Enter_UI.c
#define LG_NONAMECONF       "��� ����� �� ���������!"
#define LG_ENTERMUC         "���� � MUC"
#define LG_NAMEMUC          "��� �����������:"
#define LG_NICK             "���:"
#define LG_GETMESSAGECOUNT  "�������� ���������:"
//message_list.c
#define LG_NOSENDNULLMESS   "������ ������� ������ ���������!"
#define LG_NEW              "�����..."
//message_cmds.c
#define LG_SELCOMMAND       "����� �������..."
#define LG_SELTEMPLATE      "����� �������..."
#define LG_SELSMILE         "����� ������..."
#define LG_SELECT2          "�����..."
#define LG_COMMANDS         "�������"
#define LG_MSGTEMPLATE      "������� ���������"
#define LG_SMILE            "������"
#define LG_CLOSEDLG         "������� ������"
//mainmenu.c
#define LG_CONTACT          "�������"
#define LG_STATUS           "������"
#define LG_MUC              "�����������"
#define LG_BOOKMARK         "��������"
#define LG_MVIBRA           "����� �����"
#define LG_MSOUND           "����� �����"
#define LG_MOFFLINE         "���. ��������"
#define LG_SETTINGS         "���������"
#define LG_ABOUT            "�� �����..."
//main.c
#define LG_EXITSIEJC        "�������� SieJC?"
#define LG_ZLIBNOSASL       "ZLib �� �������� ��� SASL!"
#define LG_ENTERLOGPAS      "������� �����/������!"
#define LG_PLATFORMM        "��������� �� �������������!"
//jabber_util.c
#define LG_MUCEXITDONE      "����� �� MUC ��������!"
#define LG_VERINFO          "Version Info:\nName:%s\nVersion:%s\nOS:%s"
#define LG_TIMEINFO         "Time Info:\nUTC:%s\nTime Zone:%s\n:>%s"
//item_info.c
#define LG_ELROSTER         "������� �������"
#define LG_OFFLORCONTTR     "������� ��� ������� �� ����������"
#define LG_MUCPART          "�������� �����������"
#define LG_JTRANSP          "������ ������� �������� ����������� Jabber"
#define LG_GROUPROSTER      "������ �������"
#define LG_RESOURCE         "������:"
#define LG_REALJID          "�������� JID:"
#define LG_STATUS2          "������:"
#define LG_PRIVILEGES       "����������:"
#define LG_ROLE             "����:"
#define LG_POSIBLCLIENT     "����������� �������:"
//history.c
#define LG_ERRORWH          "������ I/O #%u ��� ������ �������!"
//cont_menu.c
#define LG_MENUCONTACT      "���� ��������"
#define LG_UNKACTION        "�������� ���������� ��� �� ��������������!"
#define LG_ABANDON          "��������"
#define LG_KIK              "���"
#define LG_BAN              "���"
#define LG_LVOISE           "������ �����"
#define LG_GVOISE           "���� �����"
#define LG_VERCLIENT        "������ �������"
#define LG_INFOFDISC        "���� �� Disco"
#define LG_ON               "��������"
#define LG_OFF              "���������"
#define LG_NOSUPACTION      "��� �������������� ��������"
#define LG_OHISTORY         "�������"
#define LG_QUERYTIME        "����� �������"
//clist_util.c
#define LG_AUTHORREM        "� ����������� ��������!"
#define LG_AUTHORGRANTED    "����������� ����!"
#define LG_MUCCROK          "����������� ������� �������"
//bookmarks.c
#define LG_MENUBOOKMARK     "���� ��������"
//config_data.c
#define LG_NO               "���"
#define LG_YES              "��"
#define LG_DISABLED         "���������"
#define LG_ENABLED          "��������"

#define LG_SETUPCONECT      "��������� �����������"
#define LG_LOGIN            "�����"
#define LG_PASSWORD         "������"
#define LG_SERVER           "������"
#define LG_HOST             "����"
#define LG_HOSTTYPE         "��� �����"
#define LG_HOSTNAME         "���"
#define LG_IPADRESS         "IP �����"
#define LG_PORT             "����"
#define LG_AUTHTYPE         "�����������"
#define LG_ZLIBUSE          "������������� ZLib"
#define LG_HISTORY          "�������"
#define LG_MUCHIST          "MUC �������"
#define LG_MUCDEF           "MUC �� ���������"
#define LG_MUCDEFNIK        "��� �����������"
#define LG_IDLEICON         "��������� ������"
#define LG_POPUPDIS         "���������� POPUP"
#define LG_COMPOSEV         "������� ���������"
#define LG_DELIVREP         "Delivery Report if required"

#define LG_SETUPSND         "��������� �����"
#define LG_SNDVOL           "���������"
#define LG_SNDMSGSND        "���� ��������"
#define LG_SNDMSGMUC        "���� ������ �� MUC"
#define LG_SNDMSGPM         "���� ������ �� PM"

#define LG_SETUPPATH        "��������� �����"
#define LG_PATHHIST         "�������"
#define LG_PATHPIC          "��������"
#define LG_PATHCMD          "�������"
#define LG_PATHMESG         "��������"
#define LG_PATHKNOWF        "��������� �����������"
#define LG_PATHSMILECFG     "������ �������"
#define LG_PATHSMILEDIR     "������� �������"
#define LG_DEFUALTDISK      "���� �� ���������"

#define LG_TEXTSTATUS       "����� ��������"
#define LG_DEFSTATES        "��������� �� ���������"
#endif //RU

///////////////////////////////////////////////////////////////////////////////////////////
//
//    Ukrainian : �����������!
//
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef LANG_UA
#define LG_SELECT           "����"
#define LG_BACK             "�����"
#define LG_OK               "OK"
#define LG_CLOSE            "�������"
#define LG_MENU             "����"
#define LG_CANCEL           "³������"
#define LG_EXIT             "�����"
#define LG_HELP             "��������"
//status_schange.c
#define LG_STATUSSEL        "���� �������"
#define LG_STONLINE         "������"
#define LG_STCHAT           "����� �������"
#define LG_STAWAY           "³�������"
#define LG_STXA             "������������"
#define LG_STDND            "������"
#define LG_STINVIS          "����"
#define LG_STATUS           "������"
#define LG_ENTERTEXTSTATUS  "������ ����� �������:"
#define LG_PRIORITY         "�������:"
//MUC_Enter_UI.c
#define LG_NONAMECONF       "��'� ����������� �� ���������!"
#define LG_ENTERMUC         "���� � MUC"
#define LG_NAMEMUC          "��'� �����������:"
#define LG_NICK             "ͳ�:"
#define LG_GETMESSAGECOUNT  "�������� ����������:"
//message_list.c
#define LG_NOSENDNULLMESS   "�� ����� ������� ������� �����������!"
#define LG_NEW              "����..."
//message_cmds.c
#define LG_SELCOMMAND       "���� �������..."
#define LG_SELTEMPLATE      "���� �������..."
#define LG_SELSMILE         "���� ������..."
#define LG_SELECT2          "����..."
#define LG_COMMANDS         "�������"
#define LG_MSGTEMPLATE      "������� ����������"
#define LG_SMILE            "������"
#define LG_CLOSEDLG         "������� �����"
//mainmenu.c
#define LG_CONTACT          "�������"
#define LG_STATUS           "������"
#define LG_MUC              "�����������"
#define LG_BOOKMARK         "��������"
#define LG_MVIBRA           "����� ����"
#define LG_MSOUND           "����� �����"
#define LG_MOFFLINE         "���. ��������"
#define LG_SETTINGS         "���������"
#define LG_ABOUT            "��� ����..."
//main.c
#define LG_EXITSIEJC        "�������� SieJC?"
#define LG_ZLIBNOSASL       "ZLib �� ������ ��� SASL!"
#define LG_ENTERLOGPAS      "������ ����/������!"
#define LG_PLATFORMM        "��������� �� �������!"
//jabber_util.c
#define LG_MUCEXITDONE      "����� �� MUC ��������!"
#define LG_VERINFO          "Version Info:\nName:%s\nVersion:%s\nOS:%s"
#define LG_TIMEINFO         "Time Info:\nUTC:%s\nTime Zone:%s\n:>%s"
//item_info.c
#define LG_ELROSTER         "������� �������"
#define LG_OFFLORCONTTR     "������� ��� ������� �� ����������"
#define LG_MUCPART          "������� �����������"
#define LG_JTRANSP          "����� ������� � ����������� Jabber"
#define LG_GROUPROSTER      "����� �������"
#define LG_RESOURCE         "������:"
#define LG_REALJID          "�������� JID:"
#define LG_STATUS2          "������:"
#define LG_PRIVILEGES       "������:"
#define LG_ROLE             "����:"
#define LG_POSIBLCLIENT     "��������� �������:"
//history.c
#define LG_ERRORWH          "������� I/O #%u ��� ������ �����!"
//cont_menu.c
#define LG_MENUCONTACT      "���� ��������"
#define LG_UNKACTION        "ĳ� ������� ��� �� �����������!"
#define LG_ABANDON          "��������"
#define LG_KIK              "ʳ�"
#define LG_BAN              "���"
#define LG_LVOISE           "³����� �����"
#define LG_GVOISE           "���� �����"
#define LG_VERCLIENT        "����� �������"
#define LG_INFOFDISC        "���� �� Disco"
#define LG_ON               "��������"
#define LG_OFF              "³��������"
#define LG_NOSUPACTION      "���� ������������ ��"
#define LG_OHISTORY         "������"
#define LG_QUERYTIME        "��� �������"
//clist_util.c
#define LG_AUTHORREM        "� ����������� ���������!"
#define LG_AUTHORGRANTED    "����������� ����!"
#define LG_MUCCROK          "����������� �������� ������"
//bookmarks.c
#define LG_MENUBOOKMARK     "���� ��������"
//config_data.c
#define LG_NO               "ͳ"
#define LG_YES              "���"
#define LG_DISABLED         "³��������"
#define LG_ENABLED          "��������"

#define LG_SETUPCONECT      "��������� �����������"
#define LG_LOGIN            "����"
#define LG_PASSWORD         "������"
#define LG_SERVER           "������"
#define LG_HOST             "����"
#define LG_HOSTTYPE         "��� �����"
#define LG_HOSTNAME         "��'�"
#define LG_IPADRESS         "IP ������"
#define LG_PORT             "����"
#define LG_AUTHTYPE         "�����������"
#define LG_ZLIBUSE          "������������ ZLib"
#define LG_HISTORY          "������"
#define LG_MUCHIST          "MUC ������"
#define LG_MUCDEF           "MUC �� ����������"
#define LG_MUCDEFNIK        "ͳ� �� ����������"
#define LG_IDLEICON         "��������� ������"
#define LG_POPUPDIS         "³����������� POPUP"
#define LG_COMPOSEV         "��䳿 ����������"
#define LG_DELIVREP         "Delivery Report if required"

#define LG_SETUPSND         "��������� �����"
#define LG_SNDVOL           "���������"
#define LG_SNDMSGSND        "���� ��������"
#define LG_SNDMSGMUC        "���� ������� �� MUC"
#define LG_SNDMSGPM         "���� ������� �� PM"

#define LG_SETUPPATH        "��������� ������"
#define LG_PATHHIST         "������"
#define LG_PATHPIC          "��������"
#define LG_PATHCMD          "�������"
#define LG_PATHMESG         "�����������"
#define LG_PATHKNOWF        "³��� ����������"
#define LG_PATHSMILECFG     "������ ������"
#define LG_PATHSMILEDIR     "������� ������"
#define LG_DEFUALTDISK      "���� �� ����������"

#define LG_TEXTSTATUS       "����� �������"
#define LG_DEFSTATES        "����� �� ����������"
#endif //UA

///////////////////////////////////////////////////////////////////////////////////////////
//
//    English : �����������!
//
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef LANG_EN
#define LG_SELECT           "Select"
#define LG_BACK             "Back"
#define LG_OK               "OK"
#define LG_CLOSE            "Close"
#define LG_MENU             "Menu"
#define LG_CANCEL           "Cancel"
#define LG_EXIT             "Exit"
#define LG_HELP             "Help"
//status_schange.c
#define LG_STATUSSEL        "Choice of status"
#define LG_STONLINE         "Online"
#define LG_STCHAT           "Chat"
#define LG_STAWAY           "Away"
#define LG_STXA             "Xa"
#define LG_STDND            "Dnd"
#define LG_STINVIS          "Invisible"
#define LG_STATUS           "Statuse"
#define LG_ENTERTEXTSTATUS  "Enter text status:"
#define LG_PRIORITY         "Priority:"
//MUC_Enter_UI.c
#define LG_NONAMECONF       "A conference name is not filled!"
#define LG_ENTERMUC         "Enter in MUC"
#define LG_NAMEMUC          "Name MUC:"
#define LG_NICK             "Nick:"
#define LG_GETMESSAGECOUNT  "To get messages:"
//message_list.c
#define LG_NOSENDNULLMESS   "It is impossible to send the empty message!"
#define LG_NEW              "New..."
//message_cmds.c
#define LG_SELCOMMAND       "Select commands..."
#define LG_SELTEMPLATE      "Select template..."
#define LG_SELSMILE         "Select smile..."
#define LG_SELECT2          "Select..."
#define LG_COMMANDS         "Commands"
#define LG_MSGTEMPLATE      "Templates messages"
#define LG_SMILE            "Smiles"
#define LG_CLOSEDLG         "Close a dialog"
//mainmenu.c
#define LG_CONTACT          "Contact"
#define LG_STATUS           "Statuse"
#define LG_MUC              "MUC"
#define LG_BOOKMARK         "Bookmark"
#define LG_MVIBRA           "Vibra mode"
#define LG_MSOUND           "Sound mode"
#define LG_MOFFLINE         "Show Offline"
#define LG_SETTINGS         "Settings"
#define LG_ABOUT            "About..."
//main.c
#define LG_EXITSIEJC        "Exit SieJC?"
#define LG_ZLIBNOSASL       "ZLib don't work without SASL!"
#define LG_ENTERLOGPAS      "Enter login/password!"
#define LG_PLATFORMM        "Target platform mismatch!"
//jabber_util.c
#define LG_MUCEXITDONE      "Exit from MUC execute!"
#define LG_VERINFO          "Version Info:\nName:%s\nVersion:%s\nOS:%s"
#define LG_TIMEINFO         "Time Info:\nUTC:%s\nTime Zone:%s\n:>%s"
//item_info.c
#define LG_ELROSTER         "Roster elements"
#define LG_OFFLORCONTTR     "Offline or contact from transport"
#define LG_MUCPART          "MUC partcipiant"
#define LG_JTRANSP          "This contact is Jabber transport"
#define LG_GROUPROSTER      "Roster group"
#define LG_RESOURCE         "Resource:"
#define LG_REALJID          "Real JID:"
#define LG_STATUS2          "Statuse:"
#define LG_PRIVILEGES       "Privileges:"
#define LG_ROLE             "Role:"
#define LG_POSIBLCLIENT     "Possibilities of client:"
//history.c
#define LG_ERRORWH          "Error I/O #%u at the history record!"
//cont_menu.c
#define LG_MENUCONTACT      "Contact menu"
#define LG_UNKACTION        "Unkcnow action or no support!"
#define LG_ABANDON          "Leave MUC"
#define LG_KIK              "Kik"
#define LG_BAN              "Ban"
#define LG_LVOISE           "Away voice"
#define LG_GVOISE           "Get voice"
#define LG_VERCLIENT        "Version"
#define LG_INFOFDISC        "Info from Disco"
#define LG_ON               "Connect"
#define LG_OFF              "Disconnect"
#define LG_NOSUPACTION      "No support action"
#define LG_OHISTORY         "History"
#define LG_QUERYTIME        "Time"
//clist_util.c
#define LG_AUTHORREM        "Authorization was removed!"
#define LG_AUTHORGRANTED    "Authorization was granted!"
#define LG_MUCCROK          "Conference created OK!"
//bookmarks.c
#define LG_MENUBOOKMARK     "Bookmark menu"
//config_data.c
#define LG_NO               "No"
#define LG_YES              "Yes"
#define LG_DISABLED         "Disabled"
#define LG_ENABLED          "Enabled"

#define LG_SETUPCONECT      "Connection setup"
#define LG_LOGIN            "Login"
#define LG_PASSWORD         "Password"
#define LG_SERVER           "Server"
#define LG_HOST             "Host"
#define LG_HOSTTYPE         "Host type"
#define LG_HOSTNAME         "Host name"
#define LG_IPADRESS         "IP address"
#define LG_PORT             "Port"
#define LG_AUTHTYPE         "Auth type"
#define LG_ZLIBUSE          "ZLib usage"
#define LG_HISTORY          "History"
#define LG_MUCHIST          "MUC history"
#define LG_MUCDEF           "Default MUC"
#define LG_MUCDEFNIK        "Default MUC nick"
#define LG_IDLEICON         "Idle icon position"
#define LG_POPUPDIS         "Display pop-ups"
#define LG_COMPOSEV         "Composing Events"
#define LG_DELIVREP         "Delivery Report if required"

#define LG_SETUPSND         "Sounds setup"
#define LG_SNDVOL           "sndVolume"
#define LG_SNDMSGSND        "Sound Msg Send"
#define LG_SNDMSGMUC        "Sound Msg Conf"
#define LG_SNDMSGPM         "Sound Msg PM"

#define LG_SETUPPATH        "Paths setup"
#define LG_PATHHIST         "History path"
#define LG_PATHPIC          "Pictures path"
#define LG_PATHCMD          "Commands path"
#define LG_PATHMESG         "Messages path"
#define LG_PATHKNOWF        "Known features"
#define LG_PATHSMILECFG     "Smiles config"
#define LG_PATHSMILEDIR     "Smiles .png path"
#define LG_DEFUALTDISK      "Default disc"

#define LG_TEXTSTATUS       "Statuses text"
#define LG_DEFSTATES        "Default states"
#endif //EN


#endif
