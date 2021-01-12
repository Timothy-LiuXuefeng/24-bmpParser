
#include "msgproc.h"




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE: 
        SetTimer(hWnd, ID_START_TIMER, 100, NULL); 
        break; 
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDM_FILE: 
            if (DialogBox(hInst, inputBmpDlgName, hWnd, iFDlgProc))
            {
                lBtnDown = false; 
                xMv = yMv = 0; 

                //��ȡλͼ�ļ�
                read: 
                switch (readBmp())
                {
                case READ_SUCCESS:      //��ȡ�ɹ�����ʼ����
                {
                    UINT32 width = *(UINT32*)bmpBuf, height = *(UINT32*)(bmpBuf + sizeof(UINT32) / sizeof(UCHAR)); 
                    RECT wndRect; 
                    GetWindowRect(hWnd, &wndRect); 
                    MoveWindow(hWnd, wndRect.left, wndRect.top, width, height, TRUE); 
                    paint: 
                    switch (paintBmpMem(width, height))
                    {
                    case PAINT_SUCCESS:
                        displayMode = displayModeType::display;
                        break;
                    case FAIL_TO_GET_DCMEM:
                        switch (MessageBox(hWnd, failToGetDCMem, error, MB_ICONERROR | MB_RETRYCANCEL))
                        {
                        case IDRETRY:
                            goto paint; 
                            break; 
                        case IDCANCEL:
                        default:
                            displayMode = displayModeType::start;
                            break;
                        }
                        break;
                    }
                    break; 
                }
                case READ_FAILURE:     //λͼ�ļ��򲻿�
                    switch (MessageBoxA(hWnd, (std::string(failToOpenBmpA) + std::string("\n�޷���/Cannot open ") + inputBmpName + std::string("!")).c_str(), errorA, MB_ICONERROR | MB_RETRYCANCEL))
                    {
                    case IDRETRY: 
                        goto read; 
                        break; 
                    case IDCANCEL: 
                    default: 
                        displayMode = displayModeType::start; 
                        InvalidateRect(hWnd, NULL, TRUE);
                        break; 
                    }
                    break; 
                case NOT_TWENTY_FOUR_BITMAP:    //��24λλͼ
                    MessageBox(hWnd, mustBeTwentyFourBmp, error, MB_OK | MB_ICONWARNING);
                    break;
                case BITMAP_DESTROYED:          //λͼ��
                    switch (MessageBox(hWnd, bmpDestroyed, error, MB_RETRYCANCEL | MB_ICONERROR))
                    {
                    case IDRETRY:
                        goto read; 
                        break;
                    case IDCANCEL:
                    default:
                        displayMode = displayModeType::start;
                        InvalidateRect(hWnd, NULL, TRUE); 
                        break;
                    }
                    break;
                case BITMAP_TOO_LARGE:      //λͼ�ļ��������뻺��ʧ��
                    switch (MessageBox(hWnd, bmpToolarge, error, MB_RETRYCANCEL | MB_ICONERROR))
                    {
                    case IDRETRY: 
                        goto read; 
                        break; 
                    case IDCANCEL: 
                    default: 
                        break; 
                    }
                    break; 
                }
            }
            break; 
        case IDM_PAUSE: 
            displayMode = displayModeType::start; 
            InvalidateRect(hWnd, NULL, TRUE); 
            break; 
        case IDM_HELP: 
            MessageBox(hWnd, help, helpTitle, MB_ICONQUESTION | MB_OK); 
            break; 
        case IDM_ABOUT: 
            MessageBox(hWnd, about, aboutTitle, MB_ICONINFORMATION | MB_OK); 
            break; 
        case IDM_EXIT: 
            SendMessage(hWnd, WM_DESTROY, 0, 0); 
            break; 
        }
        break; 
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        switch (displayMode)
        {
        case displayModeType::start:        //���ƿ�ʼ����
            paintMainInterface(hWnd, hdc); 
            break; 
        case displayModeType::display:      //����λͼ
            switch (paintBmp(hWnd, hdc, ps))
            {
            case PAINT_SUCCESS:             //�ɹ�����
                break; 
            case FAIL_TO_GET_DCMEM:        //��ȡMemDCʧ��
                switch (MessageBox(hWnd, failToGetDCMem, error, MB_ICONERROR | MB_RETRYCANCEL))
                {
                case IDRETRY: 
                    InvalidateRect(hWnd, NULL, TRUE); 
                    break; 
                case IDCANCEL: 
                default: 
                    displayMode = displayModeType::start; 
                    InvalidateRect(hWnd, NULL, TRUE); 
                    break; 
                }
                break; 
            }
            break; 
        default: 
            switch (MessageBox(hWnd, unknownError, error, MB_ICONERROR | MB_ABORTRETRYIGNORE))
            {
            case IDABORT: 
            default: 
                SendMessage(hWnd, WM_DESTROY, 0, 0); 
                break; 
            case IDRETRY: 
                InvalidateRect(hWnd, NULL, TRUE); 
                break; 
            case IDIGNORE: 
                break; 
            }
            break;
        }
        EndPaint(hWnd, &ps);
    }
    break; 
    case WM_LBUTTONDOWN: 
        if (displayMode == displayModeType::display)
        {
            lBtnDown = true; 
            lastCursorPos.x = LOWORD(lParam); 
            lastCursorPos.y = HIWORD(lParam); 
        }
        break; 
    case WM_LBUTTONUP: 
        lBtnDown = false; 
        break; 
    case WM_MOUSEMOVE: 
        if (lBtnDown && displayMode == displayModeType::display)
        {
            xMv += LOWORD(lParam) - lastCursorPos.x; 
            yMv += HIWORD(lParam) - lastCursorPos.y; 
            lastCursorPos.x = LOWORD(lParam); 
            lastCursorPos.y = HIWORD(lParam); 
            InvalidateRect(hWnd, NULL, TRUE); 
        }
        break; 
    case WM_TIMER: 
        switch (wParam)
        {
        case ID_START_TIMER: 
            KillTimer(hWnd, ID_START_TIMER); 
            InvalidateRect(hWnd, NULL, TRUE); 
            break; 
        }
        break; 
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



/*INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}*/

//�����ļ�·���Ի�����Ϣ������

BOOL CALLBACK iFDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND: 
        switch (LOWORD(wParam))
        {
        case IDB_OK: 
        {
            if (HIWORD(wParam) == BN_CLICKED)
            {
                LPSTR buf = new CHAR[500];
                GetDlgItemTextA(hDlg, IDC_INPUT, buf, 500);
                inputBmpName = buf;
                delete[] buf; 
                buf = NULL; 
                EndDialog(hDlg, 1);
            }
            break; 
        }
        }
        break; 
    case WM_CLOSE: 
        EndDialog(hDlg, 0); 
        break; 
    }
    return 0; 
}

