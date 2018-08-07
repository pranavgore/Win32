#include <windows.h>

#include "resource.h"



const TCHAR ClassName[] = TEXT("MainWindowClass");

HWND hWndListBox;



LRESULT CALLBACK WndProc(HWND    hWnd,

	UINT    Msg,

	WPARAM  wParam,

	LPARAM  lParam)

{

	switch (Msg)

	{

	case WM_CREATE:

	{

		hWndListBox = CreateWindow( TEXT("LISTBOX"), NULL, WS_VISIBLE | WS_CHILD | LBS_STANDARD | LBS_NOTIFY, 10, 10, 100, 50, hWnd, (HMENU)IDC_LISTBOX_TEXT, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);



		if (!hWnd)
			MessageBox(NULL, TEXT("ListBox Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);



		SendMessage(GetDlgItem(hWnd, IDC_LISTBOX_TEXT), LB_ADDSTRING, 0, (LPARAM)TEXT("List Item 1"));

		SendMessage(GetDlgItem(hWnd, IDC_LISTBOX_TEXT), LB_ADDSTRING, 0, (LPARAM)TEXT("List Item 2"));

		SendMessage(GetDlgItem(hWnd, IDC_LISTBOX_TEXT), LB_ADDSTRING, 0, (LPARAM)TEXT("List Item 3"));

	}

	break;



	case WM_COMMAND:

	{

		switch (LOWORD(wParam))

		{

		case IDC_LISTBOX_TEXT:

		{

			switch (HIWORD(wParam))

			{

			case LBN_SELCHANGE:

			{

				TCHAR Buffer[256];

				int index = SendMessage((HWND)lParam, LB_GETCARETINDEX, 0, 0);

				SendMessage((HWND)lParam, LB_GETTEXT, (LPARAM)index, (WPARAM)Buffer);

				SetWindowText(hWnd, Buffer);

			}

			}

		}

		break;

		}

		return 0;

	}

	break;



	case WM_CLOSE:

		DestroyWindow(hWnd);

		break;



	case WM_DESTROY:

		PostQuitMessage(0);

		break;



	default:

		return (DefWindowProc(hWnd, Msg, wParam, lParam));

	}



	return 0;

}



INT WINAPI WinMain(HINSTANCE  hInstance,

	HINSTANCE  hPrevInstance,

	LPSTR      lpCmdLine,

	INT        nCmdShow)

{

	WNDCLASSEX    wc;



	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = 0;

	wc.lpfnWndProc = (WNDPROC)WndProc;

	wc.cbClsExtra = 0;

	wc.cbWndExtra = 0;

	wc.hInstance = hInstance;

	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wc.lpszMenuName = NULL;

	wc.lpszClassName = ClassName;



	if (!RegisterClassEx(&wc))

	{

		MessageBox(NULL, TEXT("Failed To Register The Window Class."), TEXT("Error"), MB_OK | MB_ICONERROR);

		return 0;

	}



	HWND    hWnd;



	hWnd = CreateWindowEx(

		WS_EX_CLIENTEDGE,

		ClassName,

		TEXT("List Boxes"),

		WS_OVERLAPPEDWINDOW,

		CW_USEDEFAULT,

		CW_USEDEFAULT,

		240,

		120,

		NULL,

		NULL,

		hInstance,

		NULL);



	if (!hWnd)

	{

		MessageBox(NULL, TEXT("Window Creation Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);

		return 0;

	}



	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);



	MSG    Msg;



	while (GetMessage(&Msg, NULL, 0, 0))

	{

		TranslateMessage(&Msg);

		DispatchMessage(&Msg);

	}



	return Msg.wParam;

}