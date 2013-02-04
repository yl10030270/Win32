#include "main.h"

/*********************************************************************
Comp3770 Quiz#1 (Max 10 marks)

Submit your solution to the sharein Quiz folder. Your solution should
be placed in a folder with the .h and .cpp files then zipped. The folder
name should be "LastName FirstName Set" e.g. "Richards Dennis B"
NO OTHER FILES!!

Change the code to create 3 windows organized as shown in the demo.
Two windows are from the SAME class but have their text different
COLOURS. No globals are used to accomplish this. The THIRD window
uses a DIFFERENT class and proc to display a different message.
In addition, the 2 windows of the same type when the user closes one
of them it does NOT kill the program. The user must close BOTH of them
OR the different class window for the program to end.
You will need to keep track of the number of windows opened (and subtract
when they are closed). Since both windows must increment the count and
be able to refer to the count the count must be stored in a place all
windows of the same class type can see it.
A tricky bit is to initialize the count properly. The bad way is to
assume (and usually you will get away with it) that the place you store
the count will be cleared to 0 when created. The better way (and worth
a mark) is to use the last param of the CreateWindow() function. You
will need to do a bit of casting (several actually) to make it work.
Since you are only storing a single int for the count you don't need
to do any fancy malloc(). Of course the colour can be done the same
way or you can use a fancy malloc() if you prefer. Colours are 32-bits
in size (like an int).
NO GLOBALS ALLOWED. NO STATICS ALLOWED.
HINT: there are EXTRA spaces you can store stuff in. You will need to use
BOTH to accomplish this quiz.

Useful functions:

SetWindowLong()
GetWindowLong()
SetClassLong()
GetClassLong()
SetTextColor()
RGB() - macro that returns a 32-bit value used for colour 
COLORREF - type for colour returned by RBG() macro, needed for casting purposes etc

Marking Guide:

Neat windows											1
2 windows different colour msg from same wndclass		3
1 window from another class								1
main windows class keep track of number open/close		4
fancy way to initialize counter							1

The result should be like the "quiz1 main.exe". 

DO NOT DELETE ANY CODE PROVIDED!! ****DO NOT PUT ALL CODE INTO ONE FILE!! (loss of 1 mark if you do)*****

*********************************************************************/

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					PSTR szCMLine, int iCmdShow){
	static TCHAR szAppName[] = TEXT ("HelloApplication");
	static TCHAR szAppName2[] = TEXT ("HelloApplicationagain");
	HWND	hwnd;
	HWND    hwnd2;
	HWND    hwnd3;
	MSG		msg;
	WNDCLASS wndclass;
	WNDCLASS wndclass2;

	wndclass.style		= CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = HelloWndProc;
	wndclass.cbClsExtra	= sizeof(int);
	wndclass.cbWndExtra = sizeof(int);
	wndclass.hInstance	= hInstance;
	wndclass.hIcon		= LoadIcon (NULL, IDI_APPLICATION);
	wndclass.hCursor	= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	wndclass2.style		= CS_HREDRAW | CS_VREDRAW;
	wndclass2.lpfnWndProc = SecondwindowProc;
	wndclass2.cbClsExtra	= 0;
	wndclass2.cbWndExtra = 0;
	wndclass2.hInstance	= hInstance;
	wndclass2.hIcon		= LoadIcon (NULL, IDI_APPLICATION);
	wndclass2.hCursor	= LoadCursor (NULL, IDC_ARROW);
	wndclass2.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
	wndclass2.lpszMenuName = NULL;
	wndclass2.lpszClassName = szAppName2;

	if (!RegisterClass (&wndclass)){
		MessageBox (NULL, TEXT ("This program requires Windows 95/98/NT,from1"),
					szAppName, MB_ICONERROR);
		return 0;
	}

	if (!RegisterClass (&wndclass2)){
		MessageBox (NULL, TEXT ("This program requires Windows 95/98/NT,from2"),
					szAppName, MB_ICONERROR);
		return 0;
	}
	
	hwnd = CreateWindow(szAppName,		
						TEXT("Hello World in Color."), 
						WS_OVERLAPPEDWINDOW,	
						100,		
						150,		
						400,		
						300,		
						NULL,				
						NULL,			
						hInstance,			
						NULL);

	hwnd2 = CreateWindow(szAppName,		
						TEXT("Hello World in Color."), 
						WS_OVERLAPPEDWINDOW,	
					    100 + 400,		
						150,		
						400,		
						300,		
						NULL,				
						NULL,			
						hInstance,			
						NULL);	

	hwnd3 = CreateWindow(szAppName2,		
						TEXT("Another widow from different class."), 
						WS_OVERLAPPEDWINDOW,	
					    100,		
						150 + 300,		
						400,		
						300,		
						NULL,				
						NULL,			
						hInstance,			
						NULL);

	SetClassLong(hwnd,0,(LONG)2);
	SetClassLong(hwnd2,0,(LONG)2);
	SetWindowLongPtr(hwnd,0,(LONG_PTR)0);
	SetWindowLongPtr(hwnd2,0,(LONG_PTR)1);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	ShowWindow(hwnd2, iCmdShow);
	UpdateWindow(hwnd2);
	ShowWindow(hwnd3, iCmdShow);
	UpdateWindow(hwnd3);
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
	}

	return msg.wParam;
}