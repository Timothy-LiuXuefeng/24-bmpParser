#pragma once

#include "framework.h"

//��ȡλͼ�ļ�״̬

#define READ_SUCCESS  0					//��ȡ�ɹ�
#define NOT_TWENTY_FOUR_BITMAP 1		//��24ɫλͼ
#define BITMAP_DESTROYED 2				//λͼ��
#define READ_FAILURE 3					//��ȡλͼ�ļ�ʧ��
#define BITMAP_TOO_LARGE 4

#define PAINT_SUCCESS 0					//��ͼ�ɹ�
#define FAIL_TO_GET_DCMEM 1				//��ȡ�ڴ�ʧ��
#define FAIL_TO_GET_CLIENT 2			//��ȡ�û���ʧ��

#define MAIN_WIN_WIDTH 864
#define MAIN_WIN_HEIGHT 486

#define ID_START_TIMER 9999

enum class displayModeType
{
	start, 
	display
}; 

//ȫ�ֱ�����Ŵ�

extern HINSTANCE hInst;                             //��ǰʵ��
extern HWND hWndMain;								//�����ھ��

extern bool lBtnDown;								//�������Ƿ���
extern int xMv;									//x����λ����
extern int yMv;									//y����λ����
extern POINT lastCursorPos;							//֮ǰ����λ��

extern std::string inputBmpName;					//λͼ�ļ���			
extern displayModeType displayMode;					//Ŀǰ״̬
extern UCHAR* bmpBuf;								//��ʱ�洢λͼ�ļ��Ļ�����ָ��
extern HBITMAP hBmMem;								//�洢��ǰλͼ
extern HBITMAP hBmMain;								//�洢������λͼ

