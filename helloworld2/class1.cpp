#include "main.h"

LRESULT CALLBACK HelloWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC		hdc;
	PAINTSTRUCT ps;
	RECT	rect;
	int color;
	int counter;

	switch (message){
		case WM_CREATE:			
			
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			hdc = GetDC(hwnd);			
			color = (int)GetWindowLong(hwnd,0);
			GetClientRect(hwnd, &rect);
			if(color == 0){
				SetTextColor(hdc,COLORREF RGB(255,0,0));				
			}
			else if(color == 1){
				SetTextColor(hdc,COLORREF RGB(0,0,255));
			}
			DrawText(hdc, TEXT("Hello World in COLOR"), -1, &rect,
						DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			return 0;

		case WM_DESTROY:
			counter = (int)GetClassLong(hwnd,0);
			if(counter == 1){
				PostQuitMessage(0);
			}
			counter--;
			SetClassLong(hwnd,0,(LONG)counter);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}

LRESULT CALLBACK SecondwindowProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam){
	HDC		hdc;
	PAINTSTRUCT ps;
	RECT	rect;

	switch (message){
		case WM_CREATE:			
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			GetClientRect(hwnd, &rect);				
			DrawText(hdc, TEXT("Hello World in Another Window"), -1, &rect,
						DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			EndPaint(hwnd, &ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);

}