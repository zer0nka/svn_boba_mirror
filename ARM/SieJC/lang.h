/*
    SieNatJabber Project
 Language
*/
#include "setlang.h"
#ifndef _LANG_H_
#define _LANG_H_

#define LG_COPYRIGHT "Siemens natJabber Client\n(c)Kibab, Ad, Borman99\n%s r%i\nCompiled %s"

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
#define LG_UPDATE           "��������"
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
#define LG_LASTACTIVMSG     "IDLE: %d d. %d hr. %d min. %d sec." //�������� �������� �������� Bad UTF encoding..
//item_info.c
#define LG_ELROSTER         "������� �������"
#define LG_OFFLORCONTTR     "������� ��� ������� �� ����������"
#define LG_MUCPART          "�������� �����������"
#define LG_JTRANSP          "������ ������� �������� ����������� Jabber"
#define LG_GROUPROSTER      "������ �������"
#define LG_RESOURCE         "������:"
#define LG_PRIORITY         "���������:"
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
#define LG_MUC_ADMIN        "muc#admin"
#define LG_KIK              "���"
#define LG_BAN              "���"
#define LG_LVOISE           "������ �����"
#define LG_GVOISE           "���� �����"
#define LG_PARTICIPANT      "Participant"
#define LG_MEMBER           "Member"
#define LG_MODERATOR        "Moderator"
#define LG_ADMIN            "Admin"
#define LG_OWNER            "Owner"
#define LG_VERCLIENT        "������ �������"
#define LG_INFOFDISC        "���� �� Disco"
#define LG_ON               "��������"
#define LG_OFF              "���������"
#define LG_NOSUPACTION      "��� �������������� ��������"
#define LG_OHISTORY         "�������"
#define LG_QUERYTIME        "����� �������"
#define LG_QUERYVCARD       "vCard"
#define LG_QUERYLAST        "��������� ����������"
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
#define LG_RES              "������"
#define LG_HISTORY          "�������"
#define LG_MUCHIST          "MUC �������"
#define LG_MUCDEF           "MUC �� ���������"
#define LG_MUCDEFNIK        "��� �����������"
#define LG_IDLEICON         "��������� ������"
#define LG_POPUPDIS         "���������� POPUP"
#define LG_COMPOSEV         "������� ���������"
#define LG_DELIVREP         "����� � �������, ���� ���������"

#define LG_SETUPSND         "��������� �����"
#define LG_SNDVOL           "���������"
#define LG_SNDMSGSND        "���� ��������"
#define LG_SNDMSGMUC        "���� ������ �� MUC"
#define LG_SNDMSGPM         "���� ������ �� PM"

#define LG_SETUPPATH        "��������� �����"
#define LG_PATHHIST         "�������"
#define LG_PATHPIC          "��������"
#define LG_PATHAVATARS      "�������"
#define LG_PATHCMD          "�������"
#define LG_PATHMESG         "���������"
#define LG_PATHKNOWF        "��������� �����������"
#define LG_PATHSMILECFG     "������ �������"
#define LG_PATHSMILEDIR     "������� �������"
#define LG_DEFAULTDISK      "���� �� ���������"

#define LG_TEXTSTATUS       "����� ��������"
#define LG_DEFSTATES        "��������� �� ���������"

//vCard.c

#define LG_SHOW_AVATAR      "�������� �������"

#define LG_VCARD_JABBERID   "JID"
#define LG_VCARD_FN         "������ ���"
#define LG_VCARD_NICKNAME   "���"
#define LG_VCARD_BDAY       "���� ��������"
#define LG_VCARD_GENDER     "���"
#define LG_VCARD_ORGNAME    "�������� �����������"
#define LG_VCARD_ORGUNIT    "��������� �����������"
#define LG_VCARD_TITLE      "�������� ���������"
#define LG_VCARD_ROLE       "���������"
#define LG_VCARD_EMAIL      "E-Mail"
#define LG_VCARD_URL        "�������� ��������"
#define LG_VCARD_DESC       "� ����"
#define LG_VCARD_AVATAR     "�������"

#endif //RU

///////////////////////////////////////////////////////////////////////////////////////////
//
//    Ukrainian : �����������!
//
///////////////////////////////////////////////////////////////////////////////////////////
#ifdef LANG_UA
#define LG_SELECT           "����"
#define LG_BACK             "�����"
#define LG_OK               "�����"
#define LG_CLOSE            "�������"
#define LG_MENU             "����"
#define LG_CANCEL           "³������"
#define LG_EXIT             "�����"
#define LG_HELP             "��������"
#define LG_UPDATE           "�������"
//status_schange.c
#define LG_STATUSSEL        "���� �������"
#define LG_STONLINE         "� �����"
#define LG_STCHAT           "������� �� �������"
#define LG_STAWAY           "³�������"
#define LG_STXA             "�����������"
#define LG_STDND            "��������"
#define LG_STINVIS          "���������"
#define LG_STATUS           "������"
#define LG_ENTERTEXTSTATUS  "������ ����� �������:"
#define LG_PRIORITY         "���������:"
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
#define LG_SETTINGS         "������������"
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
#define LG_LASTACTIVMSG     "IDLE: %d d. %d hr. %d min. %d sec." //�������� �������� �������� Bad UTF encoding..
//item_info.c
#define LG_ELROSTER         "������� �������"
#define LG_OFFLORCONTTR     "������� ��� ������� �� ����������"
#define LG_MUCPART          "������� �����������"
#define LG_JTRANSP          "������ ������� � ����������� Jabber"
#define LG_GROUPROSTER      "����� �������"
#define LG_RESOURCE         "������:"
#define LG_PRIORITY         "���������:"
#define LG_REALJID          "�������� JID:"
#define LG_STATUS2          "������:"
#define LG_PRIVILEGES       "������:"
#define LG_ROLE             "����:"
#define LG_POSIBLCLIENT     "��������� �볺���:"
//history.c
#define LG_ERRORWH          "������� I/O #%u ��� ������ �����!"
//cont_menu.c
#define LG_MENUCONTACT      "���� ��������"
#define LG_UNKACTION        "ĳ� ������� ��� �� �����������!"
#define LG_ABANDON          "��������"
#define LG_MUC_ADMIN        "muc#admin"
#define LG_KIK              "ʳ�"
#define LG_BAN              "���"
#define LG_LVOISE           "³����� �����"
#define LG_GVOISE           "���� �����"
#define LG_PARTICIPANT      "Participant"
#define LG_MEMBER           "Member"
#define LG_MODERATOR        "Moderator"
#define LG_ADMIN            "Admin"
#define LG_OWNER            "Owner"
#define LG_VERCLIENT        "����� �볺���"
#define LG_INFOFDISC        "���� �� Disco"
#define LG_ON               "��������"
#define LG_OFF              "³��������"
#define LG_NOSUPACTION      "���� ������������ ��"
#define LG_OHISTORY         "������"
#define LG_QUERYTIME        "���"
#define LG_QUERYVCARD       "vCard"
#define LG_QUERYLAST        "Last Activity"
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

#define LG_SETUPCONECT      "������������ ����������"
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
#define LG_RES              "������"  // ���� �� ���, ������ �� �����
#define LG_HISTORY          "������"
#define LG_MUCHIST          "MUC ������"
#define LG_MUCDEF           "MUC �� ����������"
#define LG_MUCDEFNIK        "ͳ� �� ����������"
#define LG_IDLEICON         "������������ ������"
#define LG_POPUPDIS         "³��������� POPUP"
#define LG_COMPOSEV         "��䳿 ����������"
#define LG_DELIVREP         "Delivery Report if required"

#define LG_SETUPSND         "������������ �����"
#define LG_SNDVOL           "��������"
#define LG_SNDMSGSND        "���� ��������"
#define LG_SNDMSGMUC        "���� ������� �� MUC"
#define LG_SNDMSGPM         "���� ������� �� PM"

#define LG_SETUPPATH        "������������ ������"
#define LG_PATHHIST         "������"
#define LG_PATHPIC          "��������"
#define LG_PATHAVATARS      "�������"
#define LG_PATHCMD          "�������"
#define LG_PATHMESG         "�����������"
#define LG_PATHKNOWF        "³��� ����������"
#define LG_PATHSMILECFG     "������ ������"
#define LG_PATHSMILEDIR     "������� ������"
#define LG_DEFAULTDISK      "���� �� ����������"

#define LG_TEXTSTATUS       "����� �������"
#define LG_DEFSTATES        "����� �� ����������"

//vCard.c

#define LG_SHOW_AVATAR      "�������� �������"

#define LG_VCARD_JABBERID   "JID"
#define LG_VCARD_FN         "����� ��'�"
#define LG_VCARD_NICKNAME   "ͳ�"
#define LG_VCARD_BDAY       "���� ����������"
#define LG_VCARD_GENDER     "�����"
#define LG_VCARD_ORGNAME    "����� �����������"
#define LG_VCARD_ORGUNIT    "³��� �����������"
#define LG_VCARD_TITLE      "����� ������"
#define LG_VCARD_ROLE       "������"
#define LG_VCARD_EMAIL      "E-Mail"
#define LG_VCARD_URL        "������� �������"
#define LG_VCARD_DESC       "��� ����"
#define LG_VCARD_AVATAR     "�������"
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
#define LG_UPDATE           "Update"
//status_schange.c
#define LG_STATUSSEL        "Status choice"
#define LG_STONLINE         "online"
#define LG_STCHAT           "chat"
#define LG_STAWAY           "away"
#define LG_STXA             "xa"
#define LG_STDND            "dnd"
#define LG_STINVIS          "invisible"
#define LG_STATUS           "Status"
#define LG_ENTERTEXTSTATUS  "Enter status text:"
#define LG_PRIORITY         "Priority:"
//MUC_Enter_UI.c
#define LG_NONAMECONF       "A conference name is empty!"
#define LG_ENTERMUC         "Join MUC"
#define LG_NAMEMUC          "MUC name:"
#define LG_NICK             "Nickname:"
#define LG_GETMESSAGECOUNT  "Number of messages:"
//message_list.c
#define LG_NOSENDNULLMESS   "It is impossible to send an empty message!"
#define LG_NEW              "New..."
//message_cmds.c
#define LG_SELCOMMAND       "Select command..."
#define LG_SELTEMPLATE      "Select template..."
#define LG_SELSMILE         "Select smile..."
#define LG_SELECT2          "Select..."
#define LG_COMMANDS         "Commands"
#define LG_MSGTEMPLATE      "Templates"
#define LG_SMILE            "Smiles"
#define LG_CLOSEDLG         "Close"
//mainmenu.c
#define LG_CONTACT          "Contact"
#define LG_STATUS           "Status"
#define LG_MUC              "MUC"
#define LG_BOOKMARK         "Bookmarks"
#define LG_MVIBRA           "Vibra mode"
#define LG_MSOUND           "Sound mode"
#define LG_MOFFLINE         "Show Offline"
#define LG_SETTINGS         "Settings"
#define LG_ABOUT            "About..."
//main.c
#define LG_EXITSIEJC        "Exit SieJC?"
#define LG_ZLIBNOSASL       "ZLib doesn't work without SASL!"
#define LG_ENTERLOGPAS      "Enter login/password!"
#define LG_PLATFORMM        "Target platform mismatch!"
//jabber_util.c
#define LG_MUCEXITDONE      "Leave MUC ok"
#define LG_VERINFO          "Version Info:\nName:%s\nVersion:%s\nOS:%s"
#define LG_TIMEINFO         "Time Info:\nUTC:%s\nTime Zone:%s\n:>%s"
#define LG_LASTACTIVMSG     "IDLE: %d d. %d hr. %d min. %d sec."
//item_info.c
#define LG_ELROSTER         "Roster elements"
#define LG_OFFLORCONTTR     "Offline or transport contact"
#define LG_MUCPART          "MUC partcipiant"
#define LG_JTRANSP          "This contact is a transport"
#define LG_GROUPROSTER      "Roster group"
#define LG_RESOURCE         "Resource:"
#define LG_PRIORITY         "Priority:"
#define LG_REALJID          "Real JID:"
#define LG_STATUS2          "Status:"
#define LG_PRIVILEGES       "Affiliation:"
#define LG_ROLE             "Role:"
#define LG_POSIBLCLIENT     "Client features:"
//history.c
#define LG_ERRORWH          "I/O Error #%u while trying to write the history"
//cont_menu.c
#define LG_MENUCONTACT      "Contact menu"
#define LG_UNKACTION        "Unknown or unsupported action!"
#define LG_ABANDON          "Leave MUC"
#define LG_MUC_ADMIN        "muc#admin"
#define LG_KIK              "Kick"
#define LG_BAN              "Ban"
#define LG_LVOISE           "Devoice"
#define LG_GVOISE           "Grant voice"
#define LG_PARTICIPANT      "Participant"
#define LG_MEMBER           "Member"
#define LG_MODERATOR        "Moderator"
#define LG_ADMIN            "Admin"
#define LG_OWNER            "Owner"
#define LG_VERCLIENT        "Version"
#define LG_INFOFDISC        "Disco info"
#define LG_ON               "Connect"
#define LG_OFF              "Disconnect"
#define LG_NOSUPACTION      "No supported action"
#define LG_OHISTORY         "History"
#define LG_QUERYTIME        "Time"
#define LG_QUERYVCARD       "vCard"
#define LG_QUERYLAST        "Last Activity"
//clist_util.c
#define LG_AUTHORREM        "Authorization was removed!"
#define LG_AUTHORGRANTED    "Authorization was granted!"
#define LG_MUCCROK          "MUC created OK!"
//bookmarks.c
#define LG_MENUBOOKMARK     "Bookmarks menu"
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
#define LG_RES              "Resource"
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
#define LG_PATHAVATARS      "Avatars path"
#define LG_PATHCMD          "Commands path"
#define LG_PATHMESG         "Messages path"
#define LG_PATHKNOWF        "Known features"
#define LG_PATHSMILECFG     "Smiles config"
#define LG_PATHSMILEDIR     "Smiles .png path"
#define LG_DEFAULTDISK      "Default disc"

#define LG_TEXTSTATUS       "Statuses text"
#define LG_DEFSTATES        "Default states"

//vCard.c

#define LG_SHOW_AVATAR      "Show avatar"

#define LG_VCARD_JABBERID   "JID"
#define LG_VCARD_FN         "Full name"
#define LG_VCARD_NICKNAME   "Nickname"
#define LG_VCARD_BDAY       "Birthday"
#define LG_VCARD_GENDER     "Gender"
#define LG_VCARD_ORGNAME    "Org. name"
#define LG_VCARD_ORGUNIT    "Org. unit"
#define LG_VCARD_TITLE      "Title"
#define LG_VCARD_ROLE       "Role"
#define LG_VCARD_EMAIL      "E-Mail"
#define LG_VCARD_URL        "Homepage"
#define LG_VCARD_DESC       "Description"
#define LG_VCARD_AVATAR     "Avatar"
#endif //EN


#endif
