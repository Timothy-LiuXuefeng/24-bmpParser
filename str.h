#pragma once

#include "framework.h"


//����������
static LPCTSTR wndClassName = TEXT("bmpParserMainWnd"); 
static LPCTSTR wndTitleName = TEXT("24λλͼ������"); 
static LPCTSTR MAINMENUNAME = TEXT("MAINMENU"); 
static LPCTSTR iconName = TEXT("MAINICON"); 

//�����ļ�·���Ի�������
static LPCTSTR inputBmpDlgName = TEXT("INPUTBMP"); 

//���ڽ����Ի�������
static LPCTSTR loadingDlgName = TEXT("LOADING"); 

//�쳣
static LPCTSTR mustBeTwentyFourBmp = TEXT("ͼƬ�ļ�������24ɫλͼ\nThe file must be a 24-color bitmap!"); 
static LPCTSTR bmpDestroyed = TEXT("λͼ�ļ�����\nThe bitmap has been destroyed!"); 
static LPCTSTR unknownError = TEXT("δ֪����\nUnknown error!"); 
static LPCTSTR failToOpenBmp = TEXT("��λͼ�ļ�ʧ��\nFail to open the bitmap file!"); 
static LPCSTR failToOpenBmpA = "��λͼ�ļ�ʧ��\nFail to open the bitmap file!";
static LPCTSTR failToGetClient = TEXT("��ȡ�û���ʧ�ܣ�\nFail to get client!"); 
static LPCTSTR failToGetDCMem = TEXT("��ȡ�ڴ�ʧ�ܣ�\nFail to get Mem!");
static LPCTSTR bmpToolarge = TEXT("λͼ�ļ�����\nThe bitmap is too large!"); 
static LPCTSTR error = TEXT("Error"); 
static LPCSTR errorA = "Error";

//����
static LPCTSTR welcome = TEXT("��ӭ������"); 

//�˵�
static LPCTSTR help = TEXT(
"1.�����ʼ->�ļ������ļ���·��������\n\
2.�ļ���������ѹ��24λλͼ\n\
3.��������϶�ͼƬ"); 
static LPCTSTR helpTitle = TEXT("Help"); 
static LPCTSTR about = TEXT(
"���ƣ�\t24λλͼ������/24-bmp Parser\n\
��;��\t��24λλͼ�ļ����н�������ʾ����Ļ��\n\
�汾��\tv1.0\n\
���ߣ�\tTimothy Liu\n\
Copyright(C): Timothy Liu\tAll rights reserved"); 
static LPCTSTR aboutTitle = TEXT("About"); 
