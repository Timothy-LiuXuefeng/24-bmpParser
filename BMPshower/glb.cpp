#include "glb.h"

HINSTANCE hInst;                                // ��ǰʵ��
HWND hWndMain;								//�����ھ��

int xMv = 0;	
int yMv = 0;	
bool lBtnDown = false; 
POINT lastCursorPos = { 0, 0 }; 

std::string inputBmpName; 
displayModeType displayMode = displayModeType::start; 
UCHAR* bmpBuf = NULL; 
HBITMAP hBmMem = NULL; 
HBITMAP hBmMain = NULL; 
