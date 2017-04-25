#include <windows.h>
#include <gl/gl.h>
#include <iostream>
#include <map>
#include <math.h>
#include <complex>
#include "imageloading.h"
#include "text.h"
#include "maincharactertexture.h"
#include "units.h"

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

bool sKeyDown = FALSE;
bool wKeyDown = FALSE;
bool aKeyDown = FALSE;
bool dKeyDown = FALSE;
bool returnKeyDown = FALSE;
const unsigned int timerLength = 70;

struct coords{
unsigned int x;
unsigned int y;
};

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow){
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;

    //Register window class
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "If you see this something has gone wrong";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    unsigned int counter=0;
    double theta=0;
    const char * p = (const char *)0x28ff44;
    //Preloading textures. Delete this as soon as we have a clean workaround
    std::map<char,const unsigned char *> letters={{'a',aLetter},{'b',bLetter},{'c',cLetter},{'d',dLetter},{'e',eLetter},{'f',fLetter}
    ,{'g',gLetter},{'h',hLetter},{'i',iLetter},{'j',jLetter},{'k',kLetter},{'l',lLetter},{'m',mLetter},{'n',nLetter},{'o',oLetter}
    ,{'p',pLetter},{'q',qLetter},{'r',rLetter},{'s',sLetter},{'t',tLetter},{'u',uLetter},{'v',vLetter},{'w',wLetter},{'x',xLetter}
    ,{'y',yLetter},{'z',zLetter},{'1',charOne},{'2',charTwo},{'3',charThree},{'4',charFour},{'5',charFive},{'6',charSix},{'7',charSeven}
    ,{'8',charEight},{'9',charNine},{'!',charExclamation},{'?',charQuestion},{'+',charPlus},{'-',charMinus},{'>',charArrow},{':',charColon}
    ,{' ',charSpace}};
    std::vector<unit> unitsList;
    int cursorPos=30;
    enum class MenuState {MASTERMENU, NEWGAME, CREDITS, BONUS, QUIT};
    MenuState menuState=MenuState::MASTERMENU;
                    unitsList.push_back(unit("john john", 0, 0, 0, {&mainCharacterDown[0],&mainCharacterDownLeft[0],&mainCharacterDownRight[0],
                                                                &mainCharacterLeftRest[0],&mainCharacterLeftActive[0],&mainCharacterUp[0],
                                                                &mainCharacterUpLeft[0],&mainCharacterUpRight[0],&mainCharacterRightRest[0],
                                                                &mainCharacterRightActive[0]}));
    if (!RegisterClassEx(&wcex))
        return 0;

    //Create main window
    hwnd = CreateWindowEx(0,
                          "If you see this something has gone wrong",
                          "Don't close this window or my universe will end",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          160,
                          144,//Why is this so crappy
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    //Enable OpenGL for the window
    EnableOpenGL(hwnd, &hDC, &hRC);

    //Program main loop
    while (!bQuit){
        //Check for messages
        if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
            //Handle or dispatch messages
            if (msg.message == WM_QUIT){
                bQuit = TRUE;
            }
            else{
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else{

            ///=============================================================///
            //OpenGL animation code goes here
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            //glPixelZoom()
            glDisable(GL_LIGHTING);
            glEnable(GL_STENCIL_TEST);
            glRasterPos2d(-1,-1);

            if(menuState==MenuState::MASTERMENU){
                if(sKeyDown == TRUE && counter%timerLength==0){
                    cursorPos-=10;
                    if(cursorPos==-10){cursorPos=30;}
                }
                else if(wKeyDown == TRUE && counter%timerLength==0){
                    cursorPos+=10;
                    if(cursorPos==40){cursorPos=0;}
                }
                else if(returnKeyDown == TRUE && cursorPos==20){
                    menuState=MenuState::CREDITS;
                }
                else if(returnKeyDown == TRUE && cursorPos==0){
                    PostQuitMessage(0);
                }
                else if (returnKeyDown == TRUE && cursorPos==30){
                    menuState=MenuState::NEWGAME;
                }
                else if (returnKeyDown == TRUE && cursorPos==10){
                    menuState=MenuState::BONUS;
                }
                writeText("the slime master", letters, -45, 60);
                writeText("new game", letters,-45,30);
                writeText("credits", letters,-45,20);
                writeText("bonus", letters,-45,10);
                writeText("quit", letters,-45,0);
                writeText(">", letters,-50,cursorPos);
            }
            else if(menuState==MenuState::CREDITS){
                writeText("this game has no author", letters,-75,80);
                writeText("strange isnt it?", letters,-75,70);
                if(returnKeyDown == TRUE/* && counter%timerLength*2==0*/){menuState=MenuState::MASTERMENU;}
            }
            else if(menuState==MenuState::BONUS){
                writeText("avdokvmbpdggvphzhzdgcvx",letters,-75,80);
                if(returnKeyDown == TRUE/* && counter%timerLength*2==0*/){menuState=MenuState::MASTERMENU;}
            }

            else if(menuState==MenuState::NEWGAME){
                //0 Down, 1 Down Left, 2 Down Right, 3 Left Rest, 4 Left Active, 5 Up, 6 Up Left, 7 Up Right, 8 Right Rest, 9 Right Active

                unitsList[0].draw();
                if(wKeyDown==TRUE){unitsList[0].state=5;}
                else if(dKeyDown==TRUE){unitsList[0].state=3;}
                else if(sKeyDown==TRUE){unitsList[0].state=0;}
                else if(aKeyDown==TRUE){unitsList[0].state=8;}
            }

            glRasterPos2d(-1,-1);

            SwapBuffers(hDC);
            theta+=0.01;
            counter++;
            Sleep(1);
        }
    }

    //Shutdown OpenGL
    DisableOpenGL(hwnd, hDC, hRC);

    //Destroy the window explicitly
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    if (uMsg == 16){PostQuitMessage(0);}
    else if(uMsg == 2){return 0;}
    else if(uMsg == 256){
        if(wParam == 0x53){sKeyDown = TRUE;}//S Key
        else if(wParam == 0x57){wKeyDown = TRUE;}//W Key
        else if(wParam == 0x41){aKeyDown = TRUE;}//A Key
        else if(wParam == 0x44){dKeyDown = TRUE;}//D key
        else if(wParam == 0x0D){returnKeyDown = TRUE;}//Enter Key
        else if(wParam == VK_ESCAPE){PostQuitMessage(0);}
    }
    else if(uMsg == WM_KEYUP){
        if(wParam == 0x53){sKeyDown = FALSE;}
        else if(wParam == 0x57){wKeyDown = FALSE;}//W Key
        else if(wParam == 0x41){aKeyDown = FALSE;}//A Key
        else if(wParam == 0x44){dKeyDown = FALSE;}//D key
        else if(wParam == 0x0D){returnKeyDown = FALSE;}//Enter Key
    }
    else{return DefWindowProc(hwnd, uMsg, wParam, lParam);}
    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC){
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    //Get the device context (DC)
    *hDC = GetDC(hwnd);

    //Set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    //Create and enable the render context (RC)
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC){
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}
