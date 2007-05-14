#ifndef _STRING_UTIL_H_
  #define _STRING_UTIL_H_

/*
  �������������� ������ ������ �� ��������� UTF-8 � ANSI
IN:
  - tmp_out: ���� �������� ���������. ����� ��� ������ ������������
             � � ��� ������ ���� ���������� �����
  - UTF8_str: ������ ����� ������ ��� ��������������
  - size: ������� ����� ������ ��� �������������� (UTF8_str)
  - fact - ���� �������� �������� ������ ������ � ������

OUT:  �������������� �����.
*/
void* convUTF8_to_ANSI(char* tmp_out, char *UTF8_str, unsigned int size, int* fact);

char* convUTF8_to_ANSI_STR(char *UTF8_str);

void ascii2ws(WSHDR *ws, const char *s);

// �������������� � ������ �������
char* str2lower(char *st);

// ������� �� ���������. UTF16->UTF8
char *utf16_to_utf8(char **s, size_t *len);

// ������� �� ���������. UTF8->UTF16
int utf8_to_utf16(char *utf8, int cc, char *unicode16);

// UTF8 ��� ��������
char* Correct_UTF8_String(char* utf8_jid);

// � ��� ������ ����� ���� ���� ������ (�) �������� �.�.
char* ANSI2UTF8(char* ansi_str, unsigned int maxlen);

// �������� �������� �� ��������� (��. �������� � ���� �����)
char *Get_Param_Value(char *ch, char *req, char cut_quotes);

char *Replace_Special_Syms(char *unrep_str);

char *Mask_Special_Syms(char *unrep_str);

// ������ strstr, �� ��� ���������������� � ��������
//char *stristr(char *haystack, char *needle);
char *stristr(const char *s, const char *find);

// ������ strcmp, �� ��� ���������������� � ��������
//int stricmp(char *str1, char *str2);
int stricmp(const char *s, const char *d);
#endif
