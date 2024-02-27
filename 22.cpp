#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

HWND textfield, buttonPlus, buttonMinus, buttonMultiply, buttonDivide, TextBoxOne, TextBoxTwo;
char textOne[20], textTwo[20], answerStr[20];
double valueOne, valueTwo, numOne, numTwo, answer;

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch(Message) {

        case WM_CREATE:
            textfield = CreateWindow("STATIC",
                                     "Please input two numbers",
                                     WS_VISIBLE|WS_CHILD,
                                     20,20,195,20,
                                     hwnd,NULL,NULL,NULL);
            buttonPlus = CreateWindow("BUTTON",
                                      "+",
                                      WS_VISIBLE|WS_CHILD,
                                      70,115,25,25,
                                      hwnd,(HMENU) 1,NULL,NULL);
            buttonMinus = CreateWindow("BUTTON",
                                       "-",
                                       WS_VISIBLE|WS_CHILD,
                                       100,115,25,25,
                                       hwnd,(HMENU) 2,NULL,NULL);
            buttonMultiply = CreateWindow("BUTTON",
                                          "*",
                                          WS_VISIBLE|WS_CHILD,
                                          130,115,25,25,
                                          hwnd,(HMENU) 3,NULL,NULL);
            buttonDivide = CreateWindow("BUTTON",
                                        "/",
                                        WS_VISIBLE|WS_CHILD,
                                        160,115,25,25,
                                        hwnd,(HMENU) 4,NULL,NULL);
            TextBoxOne = CreateWindow("EDIT",
                                      "",
                                      WS_VISIBLE|WS_CHILD,
                                      50,50,150,20,
                                      hwnd,NULL,NULL,NULL);
            TextBoxTwo = CreateWindow("EDIT",
                                      "",
                                      WS_VISIBLE|WS_CHILD,
                                      50,75,150,20,
                                      hwnd,NULL,NULL,NULL);
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case 1:
                    valueOne = GetWindowText(TextBoxOne, &textOne[0], 20);
                    valueTwo = GetWindowText(TextBoxTwo, &textTwo[0], 20);
                    if(valueOne >= 0 && valueTwo >= 0){
                        numOne = atof(textOne);
                        numTwo = atof(textTwo);
                        answer = numOne + numTwo;
                    }
                    sprintf(answerStr, "%f", answer);
                    ::MessageBox(hwnd,answerStr,"Result",MB_OK);
                    break;
                case 2:
                    valueOne = GetWindowText(TextBoxOne, &textOne[0], 20);
                    valueTwo = GetWindowText(TextBoxTwo, &textTwo[0], 20);
                    if(valueOne >= 0 && valueTwo >= 0){
                        numOne = atof(textOne);
                        numTwo = atof(textTwo);
                        answer = numOne - numTwo;
                    }
                    sprintf(answerStr, "%f", answer);
                    ::MessageBox(hwnd,answerStr,"Result",MB_OK);
                    break;
                case 3:
                    valueOne = GetWindowText(TextBoxOne, &textOne[0], 20);
                    valueTwo = GetWindowText(TextBoxTwo, &textTwo[0], 20);
                    if(valueOne >= 0 && valueTwo >= 0){
                        numOne = atof(textOne);
                        numTwo = atof(textTwo);
                        answer = numOne * numTwo;
                    }
                    sprintf(answerStr, "%f", answer);
                    ::MessageBox(hwnd,answerStr,"Result",MB_OK);
                    break;
                case 4:
                    valueOne = GetWindowText(TextBoxOne, &textOne[0], 20);
                    valueTwo = GetWindowText(TextBoxTwo, &textTwo[0], 20);
                    if(valueOne >= 0 && valueTwo >= 0){
                        numOne = atof(textOne);
                        numTwo = atof(textTwo);
                        if(numTwo == 0){
                            ::MessageBox(hwnd,"Cannot divide by zero.","Result",MB_ICONEXCLAMATION|MB_OK);
                            break;
                        }
                        else answer = numOne / numTwo;
                    }
                    sprintf(answerStr, "%f", answer);
                    ::MessageBox(hwnd,answerStr,"Result",MB_OK);
                    break;
            }
            break;

        /* Upon destruction, tell the main thread to stop */
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }

        /* All other messages (a lot of them) are processed using default procedures */
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc; /* A properties struct of our window */
    HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
    MSG msg; /* A temporary location for all messages */

    /* zero out the struct and set the stuff we want to modify */
    memset(&wc,0,sizeof(wc));
    wc.cbSize    = sizeof(WNDCLASSEX);
    wc.lpfnWndProc   = WndProc; /* This is where we will send messages to */
    wc.hInstance     = hInstance;
    wc.hCursor   = LoadCursor(NULL, IDC_ARROW);

    /* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 50);
    wc.lpszClassName = "WindowClass";
    wc.hIcon     = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
    wc.hIconSm   = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
        CW_USEDEFAULT, /* x */
        CW_USEDEFAULT, /* y */
        250, /* width */
        200, /* height */
        NULL,NULL,hInstance,NULL);

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
        return 0;
    }

    /*
        This is the heart of our program where all input is processed and
        sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
        this loop will not produce unreasonably high CPU usage
    */
    while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
        TranslateMessage(&msg); /* Translate key codes to chars if present */
        DispatchMessage(&msg); /* Send it to WndProc */
    }
    return msg.wParam;
}