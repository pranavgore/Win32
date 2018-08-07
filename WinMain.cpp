#include <Windows.h>

#include "resource.h"

#define WIN_WIDTH	800
#define WIN_HEIGHT	600

#define ID_LIST	1
#define ID_TEXT 2

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void FillListBox(HWND hwndList);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HDC hDC;
PAINTSTRUCT ps;
RECT rc;
SIZE sz;

HWND hWndComboBox;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX WndClass;
	HWND hWnd;
	MSG msg;
	TCHAR AppName[] = TEXT("SDK Project");

	WndClass.cbClsExtra = 0;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, TEXT("IDI_ICON1"));
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = AppName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&WndClass))
	{
		MessageBox(NULL, TEXT("Window class registration failed."), AppName, MB_ICONERROR);
	}

	int iWidth = GetSystemMetrics(SM_CXSCREEN);
	int iHeight = GetSystemMetrics(SM_CYSCREEN);

	//hWnd = CreateWindow(AppName, TEXT("Main Window"), WS_OVERLAPPEDWINDOW, (iWidth / 2) - (WIN_WIDTH / 2), (iHeight / 2) - (WIN_HEIGHT / 2), WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, AppName, TEXT("Main Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		MessageBox(NULL, TEXT("Failed to create window."), TEXT("Error"), MB_OK);
		exit(1);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndList, hwndText;
	int iIndex, iLength, cxChar, cyChar;
	TCHAR *pVariableName, *pVariableValue;
	HINSTANCE hInst;

	switch (iMsg)
	{
	case WM_CREATE:
		hWndComboBox = CreateWindow(TEXT("ComboBox"), NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWN, 10, 10, 100, 800, hWnd, (HMENU)IDC_COMBOBOX_TEXT, (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), NULL);
		if (!hWndComboBox)
			MessageBox(NULL, TEXT("Combo Box Failed"), TEXT("Error"), MB_OK | MB_ICONERROR);

		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)TEXT("Item 1"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)TEXT("Item 2"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_ADDSTRING, 0, (LPARAM)TEXT("Item 3"));
		SendMessage(GetDlgItem(hWnd, IDC_COMBOBOX_TEXT), CB_SETCURSEL, 0, 0);

		hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);
		DialogBox(hInst, TEXT("Sample"), hWnd, DlgProc);
		break;

	case WM_SETFOCUS:
		break;

	case WM_COMMAND:
		if (LOWORD(wParam) == ID_LIST && HIWORD(wParam) == LBN_SELCHANGE)
		{
			iIndex = SendMessage(hwndList, LB_GETCURSEL, 0, 0);
			iLength = SendMessage(hwndList, LB_GETTEXTLEN, iIndex, 0) + 1;
			pVariableName = (TCHAR *)calloc(iLength, sizeof(TCHAR));
			SendMessage(hwndList, LB_GETTEXT, iIndex, (LPARAM)pVariableName);

			iLength = GetEnvironmentVariable(pVariableName, NULL, 0);
			pVariableValue = (TCHAR *)calloc(iLength, sizeof(TCHAR));
			GetEnvironmentVariable(pVariableName, pVariableValue, iLength);

			SetWindowText(hwndText, pVariableValue);
			free(pVariableName);
			free(pVariableValue);
		}

		switch (LOWORD(wParam))
		{
		case IDC_COMBOBOX_TEXT:
			switch (HIWORD(wParam))
			{
				// Handle notification code
			}
		}
		break;

	case WM_MOVE:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_VSCROLL:
		break;

	case WM_HSCROLL:
		break;

	case WM_PAINT:
		break;

	case WM_SIZE:
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;

		default:
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		break;
	}
	return(DefWindowProc(hWnd, iMsg, wParam, lParam));
}

BOOL CALLBACK DlgProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		default:
			break;
		}
		break;

	default:
		break;
	}
	return(FALSE);
}

void FillListBox(HWND hwndList)
{
	MessageBox(NULL, TEXT("In FillListBox()"), TEXT("MESSAGE"), MB_OK);
	int iLength;
	TCHAR *pVariableBlock, *pVariableBegin, *pVariableEnd, *pVariableName;

	pVariableBlock = GetEnvironmentStrings();

	while (*pVariableBlock)
	{
		if (*pVariableBlock != '=')
		{
			pVariableBegin = pVariableBlock;
			while (*pVariableBlock++ != '=');
			pVariableEnd = pVariableBlock - 1;
			iLength = pVariableEnd - pVariableBegin;

			pVariableName = (TCHAR *)calloc(iLength + 1, sizeof(TCHAR));
			CopyMemory(pVariableName, pVariableBegin, iLength * sizeof(TCHAR));
			pVariableName[iLength] = '\0';

			SendMessage(hwndList, LB_ADDSTRING, 0, (LPARAM)pVariableName);
			free(pVariableName);
		}
		while (*pVariableBlock++ != '\0');
	}
	FreeEnvironmentStrings(pVariableBlock);
	MessageBox(NULL, TEXT("Leaving FillListBox()"), TEXT("MESSAGE"), MB_OK);
}
