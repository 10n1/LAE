/*
 *  winmain.c
 *  lae
 *
 *  Created by Kyle C Weicht on 6/6/12.
 *  Copyright (c) 2012 Kyle C Weicht. All rights reserved.
 */
 #include "lae_config.h"

/*----------------------------------------------------------------------------*/
/* C headers */
#include <Windows.h>
/* External headers */
/* Internal headers */
#include "lae_defines.h"
#include "lae_graphics.h"
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*\
Internal
\*----------------------------------------------------------------------------*/
static const char   PROGRAM_NAME[] = "Lae Win32 Test";
static const int    WINDOW_WIDTH = 1280;
static const int    WINDOW_HEIGHT = 720;

static HWND             hwnd = NULL;
static lae_graphics_t*  graphics = NULL;

static LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    switch(message)
    {
    case WM_KEYDOWN:
        if(wParam == VK_ESCAPE)
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
    case WM_CLOSE:
        {
            PostQuitMessage(0);
            return 0;
        }
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

/*----------------------------------------------------------------------------*\
External
\*----------------------------------------------------------------------------*/
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    /*
     * Create Application
     */
    {
        WNDCLASSEX wcex;
        wcex.cbSize         = sizeof(WNDCLASSEX); 
        wcex.style          = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc    = WndProc;
        wcex.cbClsExtra     = 0;
        wcex.cbWndExtra     = 0;
        wcex.hInstance      = hInstance;
        wcex.hIcon          = NULL;
        wcex.hCursor        = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground  = NULL;
        wcex.lpszMenuName   = NULL;
        wcex.lpszClassName  = PROGRAM_NAME;
        wcex.hIconSm        = NULL;
        if(!RegisterClassEx(&wcex))
        {
            MessageBox(NULL, "Could not register class", "Error", MB_OK);
            return 0;
        }
    }
    /*
     * Create Window
     */
    {
        UINT uiStyle = WS_OVERLAPPEDWINDOW;
        RECT rect;

        rect.left = 0;
        rect.top = 0;
        rect.right = WINDOW_WIDTH;
        rect.bottom = WINDOW_HEIGHT;

        AdjustWindowRect(&rect, uiStyle, FALSE);
        hwnd = CreateWindow(PROGRAM_NAME, 
                            "Main Window", 
                            uiStyle, 
                            CW_USEDEFAULT, CW_USEDEFAULT,
                            rect.right-rect.left, 
                            rect.bottom-rect.top, 
                            NULL, NULL, 
                            hInstance, NULL);
        if(hwnd == NULL)
        {
            MessageBox(NULL, "Could not create window", "Error", MB_OK);
            return 0;
        }

        ShowWindow(hwnd, SW_SHOWNORMAL);
    }

    /*
     * Initialization
     */
    graphics = lae_graphics_create(hwnd);
    lae_graphics_clear_color(graphics, 0.4f, 0.2f, 0.8f, 1.0f, 1.0f);

    /*
     * Main loop
     */
    {
        MSG msg = {0};

        do
        {
            while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
            {
                if(!GetMessage(&msg, NULL, 0, 0))
                {
                    break;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            /*
             * Main frame
             */
            {
                lae_graphics_present(graphics);
                lae_graphics_clear(graphics);
            }
        } while(msg.message != WM_QUIT);
    }
    
    /*
     * Shutdown
     */
    lae_graphics_destroy(graphics);

    return 0;
    UNUSED_PARAMETER(hInstance);
    UNUSED_PARAMETER(hPrevInstance);
    UNUSED_PARAMETER(lpCmdLine);
    UNUSED_PARAMETER(nCmdShow);
}