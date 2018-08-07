#include <windows.h>

#include "resource.h"

const TCHAR ClassName[] = TEXT("MainWindowClass");

HWND hWndComboBox;

LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CREATE:
		hWndComboBox = CreateWindow(TEXT("COMBOBOX"), NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN | CBS_DROPDOWNLIST, 10, 10, 100, 800, hWnd, (HMENU)IDC_COMBOBOX_TEXT, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
		if (!hWndComboBox)
			MessageBox(NULL, TEXT("ComboBox Failed."), TEXT("Error"), MB_OK | MB_ICONERROR);

		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)TEXT("Item 1"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)TEXT("Item 2"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)TEXT("Item 3"));
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDC_COMBOBOX_TEXT:
			switch (HIWORD(wParam))
			{
				// Handle notification code
			}
		}
		break;
		return 0;
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



INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow)
{

	WNDCLASSEX wc;

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

		TEXT("Combo Boxes"),

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
