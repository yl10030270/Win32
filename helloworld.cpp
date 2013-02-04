/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
                 (c) Charles Petzold, 1998
  ------------------------------------------------------------*/


/*--------------------------------------------------------------
Q3.
"The BeginPaint function prepares the specified window for painting 
and fills a PAINTSTRUCT structure with information about the painting."

If we only have code "return 0", the wiondow will display with nothing 
filled in. Because you didn't specify which window you want to paint on
all also there are no the required structure and information be specifed 
for the painting.

Q4.
Because the we don't want to worried too much about handling the message
and also it's too much work for us. It's hard for us to figure out where is 
this message from , what kind of message this is. so we just send it back to 
the system, the system will help us automaticly deal with it.
----------------------------------------------------------------*/



#include <windows.h>

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
     static TCHAR szAppName[] = TEXT ("HelloWin") ;
     HWND         hwnd1;
	 HWND		  hwnd2;
     MSG          msg ;
     WNDCLASS     wndclass;
	 LPCWSTR a = TEXT("first window");
	 LPCWSTR b = TEXT("second window");
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
	 wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = sizeof(LONG_PTR);
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;

     if (!RegisterClass (&wndclass))
     {
          MessageBox (NULL, TEXT ("This program requires Windows NT!"), 
                      szAppName, MB_ICONERROR) ;
          return 0 ;
     }
     
     hwnd1 = CreateWindow (szAppName,                  // window class name
                          TEXT ("The Hello Program"), // window caption
                          WS_OVERLAPPEDWINDOW,        // window style
                          100,              // initial x position
                          150,              // initial y position
                          500,              // initial x size
                          500,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters
	 hwnd2 = CreateWindow (szAppName,                  // window class name
                          TEXT ("The Hello Program"), // window caption
                          WS_OVERLAPPEDWINDOW,        // window style
                          100+500,              // initial x position
                          150,              // initial y position
                          500,              // initial x size
                          500,              // initial y size
                          NULL,                       // parent window handle
                          NULL,                       // window menu handle
                          hInstance,                  // program instance handle
                          NULL) ;                     // creation parameters

     SetWindowLongPtr(hwnd1,0,(LONG_PTR)a);
	 SetWindowLongPtr(hwnd2,0,(LONG_PTR)b);
     ShowWindow (hwnd1, iCmdShow) ;
     UpdateWindow (hwnd1) ;
	 ShowWindow (hwnd2, iCmdShow) ;
     UpdateWindow (hwnd2) ;
     while (GetMessage (&msg, NULL, 0, 0))
     {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
     }
     return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect ;
	 LPCWSTR sp = (LPCWSTR)GetWindowLongPtr(hwnd,0);
     
     switch (message)
     {
     case WM_CREATE:
          PlaySound (TEXT ("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC) ;
          return 0 ;
          
     case WM_PAINT:

          hdc = BeginPaint (hwnd, &ps) ;
          
          GetClientRect (hwnd, &rect) ;
          
		  DrawText (hdc, sp, -1, &rect,
                    DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;

          EndPaint (hwnd, &ps) ;
          return 0 ;
          
     case WM_DESTROY:
          PostQuitMessage (0) ;
          return 0 ;
     }
     return DefWindowProc (hwnd, message, wParam, lParam) ;
}