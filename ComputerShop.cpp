#include <Windows.h>
#include <string.h>
#include <iostream>
#include <CString>
#include <map>
#include <stdio.h>

#include "resource.h"
#include "ComponentData.h"

#define WIN_WIDTH	800
#define WIN_HEIGHT	600
#define NORMAL_ARRAY_SIZE	255
#define MEDIUM_ARRAY_SIZE	128

using namespace std;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL	CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL	CALLBACK DlgProcReceipt(HWND, UINT, WPARAM, LPARAM);
TCHAR *RemoveWhiteSpace(TCHAR *str);

HDC hDC;
HWND ghWnd;
PAINTSTRUCT ps;
RECT rc;
SIZE sz;

int iCPUModelSelect;

BOOL gbStartDrawing = FALSE;
BOOL gbName = FALSE;
BOOL gbGenerateReceipt = FALSE;

BOOL gbIntelCPUSelect = FALSE;
BOOL gbAMDCPUSelect = FALSE;

BOOL gbCorei3Select = FALSE;
BOOL gbCorei5Select = FALSE;
BOOL gbCorei7Select = FALSE;
BOOL gbCorei9Select = FALSE;
BOOL gbPentiumSelect = FALSE;
BOOL gbXeonSelect = FALSE;

BOOL gbRyzen3Select = FALSE;
BOOL gbRyzen5Select = FALSE;
BOOL gbRyzen7Select = FALSE;
BOOL gbRyzenThreadripperSelect = FALSE;
BOOL gbAPUSelect = FALSE;
BOOL gbFXSelect = FALSE;

BOOL gbNVidiaGPUSelect = FALSE;
BOOL gbAMDGPUSelect = FALSE;

BOOL gbGF700Select = FALSE;
BOOL gbGF900Select = FALSE;
BOOL gbGF10000Select = FALSE;

BOOL gbRX400Select = FALSE;
BOOL gbRX500Select = FALSE;
BOOL gbRXVegaSelect = FALSE;

BOOL gbAsusMotherboardSelect = FALSE;
BOOL gbGigabyteMotherboardSelect = FALSE;

BOOL gbCorsairRAMSelect = FALSE;
BOOL gbGSkillRAMSelect = FALSE;
BOOL gbKingstonRAMSelect = FALSE;

BOOL gb4GBSelect = FALSE;
BOOL gb8GBSelect = FALSE;
BOOL gb16GBSelect = FALSE;
BOOL gb32GBSelect = FALSE;

BOOL gbDDR3Select = FALSE;
BOOL gbDDR4Select = FALSE;

BOOL gbWDSelect = FALSE;
BOOL gbSeagateSelect = FALSE;

BOOL gbASUSMonitorSelect = FALSE;
BOOL gbSamsungMonitorSelect = FALSE;

BOOL gb21_5Inch = FALSE;
BOOL gb24Inch = FALSE;
BOOL gb27Inch = FALSE;
BOOL gb31_5Inch = FALSE;

BOOL gb1080pSelect = FALSE;
BOOL gb4KSelect = FALSE;

BOOL gbCMSMPSSelect = FALSE;
BOOL gbCorsairSMPSSelect = FALSE;

BOOL gbCorsairCabinetSelect = FALSE;
BOOL gbCMCabinetSelect = FALSE;

HWND hWndCPUVendor, hWndCPUSubType, hWndCPUModel;
HWND hWndMotherboardVendor, hWndMotherboardModel;
HWND hWndRAMVendor, hWndRAMType, hWndRAMCapacity;
HWND hWndGPUVendor, hWndGPUModel, hWndGPUSeries;
HWND hWndHDDVendor, hWndHDDCapacity, hWndHDDSpeed;
HWND hWndMonitorVendor, hWndMonitorScreensize, hWndMonitorResolution;
HWND hWndOpticalDriveVendor, hWndOpticalDriveSpeed;
HWND hWndSMPSVendor, hWndSMPSCapacity;
HWND hWndCabinetVendor, hWndCabinetFormFactor;
HWND hWndKeyboardVendor, hWndKeyboardType;
HWND hWndMouseVendor, hWndMouseType;
HWND hWndEditBox;

TCHAR tcCPUBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcCPUCostBuffer[NORMAL_ARRAY_SIZE];
int iCPUFinalCost = 0;

TCHAR tcMotherboardBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcMotherboardCostBuffer[NORMAL_ARRAY_SIZE];
int iMotherboardFinalCost = 0;

TCHAR tcRAMBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcRAMCostBuffer[NORMAL_ARRAY_SIZE];
int iRAMFinalCost = 0;

TCHAR tcGPUBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcGPUCostBuffer[NORMAL_ARRAY_SIZE];
int iGPUFinalCost = 0;

TCHAR tcHDDBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcHDDCostBuffer[NORMAL_ARRAY_SIZE];
int iHDDFinalCost = 0;

TCHAR tcMonitorBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcMonitorCostBuffer[NORMAL_ARRAY_SIZE];
int iMonitorFinalCost = 0;

TCHAR tcDVDBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcDVDCostBuffer[NORMAL_ARRAY_SIZE];
int iDVDROMFinalCost = 0;

TCHAR tcSMPSBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcSMPSCostBuffer[NORMAL_ARRAY_SIZE];
int iSMPSFinalCost = 0;

TCHAR tcCabinetBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcCabinetCostBuffer[NORMAL_ARRAY_SIZE];
int iCabinetFinalCost = 0;

TCHAR tcKeyboardBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcKeyboardCostBuffer[NORMAL_ARRAY_SIZE];
int iKeyboardFinalCost = 0;

TCHAR tcMouseBuff[MEDIUM_ARRAY_SIZE];
TCHAR tcMouseCostBuffer[NORMAL_ARRAY_SIZE];
int iMouseFinalCost = 0;

TCHAR tcTotalCost[NORMAL_ARRAY_SIZE];
int iTotalCost = 0;

TCHAR name[255];

TCHAR *ItemList[] = { TEXT("Processor"), TEXT("Motherboard"), TEXT("RAM"), TEXT("Graphics Processor"), TEXT("Hard Drive"), TEXT("Monitor"), TEXT("DVD-ROM Drive"), TEXT("Power Supply Unit"), TEXT("Cabinet"), TEXT("Keyboard"), TEXT("Mouse"), NULL };
TCHAR *Headings[] = { TEXT("Component"), TEXT("Selection"), TEXT("Cost"), TEXT("Total Cost"), TEXT("Welcome To Computer Shop"), TEXT("Press Spacebar To Continue."), TEXT("Press Enter to Generate the receipt."), TEXT("Want to Add the component? Press Spacebar") };

FILE *receipt;
errno_t error;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	void CleanBuffers(void);

	WNDCLASSEX WndClass;
	HWND hWnd;
	MSG msg;
	TCHAR AppName[] = TEXT("SDKProject");

	WndClass.cbClsExtra = 0;
	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	//WndClass.hbrBackground = CreatePatternBrush(LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP)));
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
	//hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, AppName, TEXT("Main Window"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	hWnd = CreateWindowEx(WS_EX_CLIENTEDGE, AppName, TEXT("Computer Shop"), WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, 0, 0, iWidth, iHeight, NULL, NULL, hInstance, NULL);

	if (hWnd == NULL)
	{
		MessageBox(NULL, TEXT("Failed to create window."), TEXT("Error"), MB_OK);
		exit(1);
	}

	ghWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	CleanBuffers();

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void DisplayData(HDC hdc);
	void CleanBuffers(void);
	static HINSTANCE hInstance;

	static HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP));

	switch (iMsg)
	{
	case WM_CREATE:
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
		//return 0;
		break;

	case WM_SETFOCUS:
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
			HDC hdcInst, hdcBitmap;
			PAINTSTRUCT ps;
			BITMAP bmp;
			RECT rc;

			hdcInst = BeginPaint(ghWnd, &ps);

			hdcBitmap = CreateCompatibleDC(hdcInst);

			SelectObject(hdcBitmap, hBitmap);

			GetObject(hBitmap, sizeof(bmp), &bmp);

			GetClientRect(hWnd, &rc);

			StretchBlt(hdcInst, 0, 0, rc.right - rc.left, rc.bottom - rc.top, hdcBitmap, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

			SetTextColor(hdcInst, RGB(255, 255, 0));
			SetBkMode(hdcInst, TRANSPARENT);
			


			if (gbStartDrawing == TRUE)
			{
				DisplayData(hdcInst);
			}
			else
			{
				TextOut(hdcInst, 500, 50, Headings[4], wcslen(Headings[4]));
				TextOut(hdcInst, 500, 80, Headings[5], wcslen(Headings[5]));
			}
			
			DeleteDC(hdcBitmap);
			EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;


		case VK_SPACE:
			CleanBuffers();
			DialogBox(hInstance, TEXT("MAINDIALOG"), hWnd, DlgProc);
			break;

		case VK_RETURN:
			if (gbGenerateReceipt == TRUE && iTotalCost != 0)
				DialogBox(hInstance, TEXT("RECEIPTDIALOG"), hWnd, DlgProcReceipt);
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

BOOL CALLBACK DlgProcReceipt(HWND hWndDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR buff1[255], name1[255];
	hWndEditBox = GetDlgItem(hWndDlg, ID_EDITBOX_NAME);

	const char *buff = NULL;

	switch (iMsg)
	{
	case WM_INITDIALOG:
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		/*case ID_EDITBOX_NAME:
			switch (HIWORD(wParam))
			{

			default:
				break;
			}
			break;*/

		case IDOK:
			GetDlgItemText(hWndDlg, ID_EDITBOX_NAME, name, sizeof(name));

			if (name[0] == TEXT('\0'))
			{
				MessageBox(NULL, TEXT("Empty array"), TEXT("Msg"), MB_OK);
			}
			else
			{
				wcscpy_s(name1, name);
				wcscat_s(name, TEXT(".txt"));
				wsprintf(buff1, TEXT("%s"), (const char *)name);
				error = _wfopen_s(&receipt, name, TEXT("w"));

				if (error != 0)
				{
					MessageBox(NULL, TEXT("Failed to generate receipt"), TEXT("File error."), MB_OK | MB_ICONEXCLAMATION);
				}

				fwprintf_s(receipt, TEXT("\t\t\t\t\tAstromedicomp\nName: %s\n"), name1);
				fwprintf_s(receipt, TEXT("****************************************************************\n"));
				fwprintf_s(receipt, TEXT("\t%0.20s\t\t\t%0.50s\t\t\t%s\n"), Headings[0], Headings[1], Headings[2]);
				
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[0], tcCPUBuff, iCPUFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[1], tcMotherboardBuff, iMotherboardFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[2], tcRAMBuff, iRAMFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[3], tcGPUBuff, iGPUFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[4], tcHDDBuff, iHDDFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[5], tcMonitorBuff, iMonitorFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[6], tcDVDBuff, iDVDROMFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[7], tcSMPSBuff, iSMPSFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[8], tcCabinetBuff, iCabinetFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[9], tcKeyboardBuff, iKeyboardFinalCost);
				fwprintf_s(receipt, TEXT("\t%0.20s:\t\t\t%0.50s\t\t\tRs.%d\n\n"), ItemList[10], tcMouseBuff, iMouseFinalCost);
				
				fwprintf_s(receipt, TEXT("****************************************************************\n"));
				fwprintf_s(receipt, TEXT("Total Cost: %d"), iTotalCost);

				fclose(receipt);
			}

			EndDialog(hWndDlg, 0);
			break;

		case IDCANCEL:
			EndDialog(hWndDlg, 0);
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return(FALSE);
}

BOOL CALLBACK DlgProc(HWND hWndDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void InitializeComboBoxes(void);
	void SelectionCheck(HWND hWndDlg, HWND hCBox);
	void CPUVendorSelectionCheck(HWND hDlg, HWND hCBox);
	void CPUSubTypeSelectionCheck(HWND hDlg, HWND hCBox);
	void CPUModelSelectionCheck(HWND hDlg, HWND hCBox);
	void MotherboardVendorSelect(HWND hDlg, HWND hCBox);
	void MotherboardModelSelect(HWND hDlg, HWND hCBox);
	void RAMVendorSelect(HWND hDlg, HWND hCBox);
	void RAMTypeSelect(HWND hDlg, HWND hCBox);
	void RAMCapacitySelect(HWND hDlg, HWND hCBox);
	void GPUVendorSelect(HWND hDlg, HWND hCBox);
	void GPUSeriesSelect(HWND hDlg, HWND hCBox);
	void GPUModelSelect(HWND hDlg, HWND hCBox);
	void HDDVendorSelect(HWND hDlg, HWND hCBox);
	void HDDCapacitySelect(HWND hDlg, HWND hCBox);
	void HDDSpeedSelect(HWND hDlg, HWND hCBox);
	void MonitorVendorSelect(HWND hDlg, HWND hCBox);
	void MonitorSizeSelect(HWND hDlg, HWND hCBox);
	void MonitorResolutionSelect(HWND hDlg, HWND hCBox);
	void DVDVendorSelect(HWND hDlg, HWND hCBox);
	void DVDSpeedSelect(HWND hDlg, HWND hCBox);
	void SMPSVendorSelect(HWND hDlg, HWND hCBox);
	void SMPSCapacitySelect(HWND hDlg, HWND hCBox);
	void CabinetVendorSelect(HWND hDlg, HWND hCBox);
	void CabinetFormFactorSelect(HWND hDlg, HWND hCBox);
	void KeyboardSelect(HWND hDlg, HWND hCBox);
	void MouseSelect(HWND hDlg, HWND hCBox);

	void DisplayData(void);
	void CheckSelection(HWND hDlg);

	hWndCabinetFormFactor	= GetDlgItem(hWndDlg, ID_CBOX_CABINET_FORMFACTOR);
	hWndCabinetVendor		= GetDlgItem(hWndDlg, ID_CBOX_CABINET_VENDOR);
	hWndCPUVendor			= GetDlgItem(hWndDlg, ID_PROCESSOR_VENDOR_COMBOBOX);
	hWndCPUSubType			= GetDlgItem(hWndDlg, ID_PROCESSOR_SUBTYPE_COMBOBOX);
	hWndCPUModel			= GetDlgItem(hWndDlg, ID_PROCESSOR_MODEL_COMBOBOX);
	hWndGPUModel			= GetDlgItem(hWndDlg, ID_CBOX_GPU_MODEL);
	hWndGPUSeries			= GetDlgItem(hWndDlg, ID_CBOX_GPU_SERIES);
	hWndGPUVendor			= GetDlgItem(hWndDlg, ID_CBOX_GPU_VENDOR);
	hWndHDDCapacity			= GetDlgItem(hWndDlg, ID_CBOX_STORAGE_CAPACITY);
	hWndHDDSpeed			= GetDlgItem(hWndDlg, ID_CBOX_STORAGE_SPEED);
	hWndHDDVendor			= GetDlgItem(hWndDlg, ID_CBOX_STORAGE_VENDOR);
	hWndKeyboardType		= GetDlgItem(hWndDlg, ID_CBOX_KEYBOARD_INTERFACE);
	hWndKeyboardVendor		= GetDlgItem(hWndDlg, ID_CBOX_KEYBOARD_VENDOR);
	hWndMonitorResolution	= GetDlgItem(hWndDlg, ID_CBOX_MONITOR_RESOLUTION);
	hWndMonitorScreensize	= GetDlgItem(hWndDlg, ID_CBOX_MONITOR_SCREENSIZE);
	hWndMonitorVendor		= GetDlgItem(hWndDlg, ID_CBOX_MONITOR_VENDOR);
	hWndMotherboardModel	= GetDlgItem(hWndDlg, ID_CBOX_MOTHERBOARD_MODEL);
	hWndMotherboardVendor	= GetDlgItem(hWndDlg, ID_CBOX_MOTHERBOARD_VENDOR);
	hWndMouseType			= GetDlgItem(hWndDlg, ID_CBOX_MOUSE_TYPE);
	hWndMouseVendor			= GetDlgItem(hWndDlg, ID_CBOX_MOUSE_VENDOR);
	hWndOpticalDriveSpeed	= GetDlgItem(hWndDlg, ID_CBOX_OPTICAL_DRIVE_SPEED);
	hWndOpticalDriveVendor	= GetDlgItem(hWndDlg, ID_CBOX_OPTICAL_DRIVE_VENDOR);
	hWndRAMCapacity			= GetDlgItem(hWndDlg, ID_CBOX_RAM_CAPACITY);
	hWndRAMType				= GetDlgItem(hWndDlg, ID_CBOX_RAM_TYPE);
	hWndRAMVendor			= GetDlgItem(hWndDlg, ID_CBOX_RAM_VENDOR);
	hWndSMPSCapacity		= GetDlgItem(hWndDlg, ID_CBOX_POWERSUPPLY_CAPACITY);
	hWndSMPSVendor			= GetDlgItem(hWndDlg, ID_CBOX_POWERSUPPLY_VENDOR);
	
	
	//TCHAR msg[255];

	switch (iMsg)
	{
	case WM_INITDIALOG:
		InitializeComboBoxes();
		break;
		//return TRUE;

	case WM_LBUTTONDOWN:
		//SendMessage(GetDlgItem(hWndDlg, ID_PROCESSOR_VENDOR_COMBOBOX), CB_SHOWDROPDOWN, TRUE, 0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_PROCESSOR_VENDOR_COMBOBOX:
			switch (HIWORD(wParam))
			{
			case CBN_CLOSEUP:
				//iVendorSelect = (int)SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
				/*if (iVendorSelect == 1 || iVendorSelect == 2)
					MessageBox(NULL, TEXT("Selection"), TEXT("Message"), MB_OK);
				else
					MessageBox(NULL, TEXT("No Selection"), TEXT("Message"), MB_OK);*/
				break;

			case CBN_SELCHANGE:
				//SelectionCheck(hWndDlg, hWndCPUVendor);
				CPUVendorSelectionCheck(hWndDlg, hWndCPUVendor);
				break;

			case CBN_DROPDOWN:
				ShowWindow(hWndCPUSubType, SW_HIDE);
				ShowWindow(hWndCPUModel, SW_HIDE);
				break;
			
			default:
				break;
			}
			break;


		case ID_PROCESSOR_SUBTYPE_COMBOBOX:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				CPUSubTypeSelectionCheck(hWndDlg, hWndCPUSubType);
				break;
		
			default:
				break;
			}
			break;

		case ID_PROCESSOR_MODEL_COMBOBOX:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				//CPUModelSelectionCheck(hWndDlg, hWndCPUModel);
				break;

			case CBN_CLOSEUP:
				CPUModelSelectionCheck(hWndDlg, hWndCPUModel);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_MOTHERBOARD_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				MotherboardVendorSelect(hWndDlg, hWndMotherboardVendor);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_MOTHERBOARD_MODEL:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				MotherboardModelSelect(hWndDlg, hWndMotherboardModel);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_RAM_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				RAMVendorSelect(hWndDlg, hWndRAMVendor);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_RAM_TYPE:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				RAMTypeSelect(hWndDlg, hWndRAMType);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_RAM_CAPACITY:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				RAMCapacitySelect(hWndDlg, hWndRAMCapacity);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_GPU_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				GPUVendorSelect(hWndDlg, hWndGPUVendor);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_GPU_SERIES:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				GPUSeriesSelect(hWndDlg, hWndGPUSeries);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_GPU_MODEL:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				GPUModelSelect(hWndDlg, hWndGPUModel);
				break;

			case CBN_DROPDOWN:
				SendMessage(hWndGPUModel, CB_SETDROPPEDWIDTH, 300, 0);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_STORAGE_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				HDDVendorSelect(hWndDlg, hWndHDDVendor);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_STORAGE_CAPACITY:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				HDDCapacitySelect(hWndDlg, hWndHDDCapacity);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_STORAGE_SPEED:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				HDDSpeedSelect(hWndDlg, hWndHDDSpeed);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_MONITOR_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				MonitorVendorSelect(hWndDlg, hWndMonitorVendor);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_MONITOR_SCREENSIZE:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				MonitorSizeSelect(hWndDlg, hWndMonitorScreensize);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_MONITOR_RESOLUTION:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				MonitorResolutionSelect(hWndDlg, hWndMonitorResolution);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_OPTICAL_DRIVE_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				DVDVendorSelect(hWndDlg, hWndOpticalDriveVendor);
				break;

			default:
				break;
			}
			break;
			
		case ID_CBOX_OPTICAL_DRIVE_SPEED:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				DVDSpeedSelect(hWndDlg, hWndOpticalDriveSpeed);
				break;

			case CBN_DROPDOWN:
				SendMessage(hWndOpticalDriveSpeed, CB_SETDROPPEDWIDTH, 250, 0);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_POWERSUPPLY_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				SMPSVendorSelect(hWndDlg, hWndSMPSVendor);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_POWERSUPPLY_CAPACITY:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				SMPSCapacitySelect(hWndDlg, hWndSMPSCapacity);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_CABINET_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				CabinetVendorSelect(hWndDlg, hWndCabinetVendor);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_CABINET_FORMFACTOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				CabinetFormFactorSelect(hWndDlg, hWndCabinetFormFactor);
				break;

			case CBN_DROPDOWN:
				SendMessage(hWndCabinetFormFactor, CB_SETDROPPEDWIDTH, 300, 0);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_KEYBOARD_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				KeyboardSelect(hWndDlg, hWndKeyboardVendor);
				break;

			case CBN_DROPDOWN:
				SendMessage(hWndKeyboardVendor, CB_SETDROPPEDWIDTH, 450, 0);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_KEYBOARD_INTERFACE:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				// to do
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_MOUSE_VENDOR:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				MouseSelect(hWndDlg, hWndMouseVendor);
				break;

			default:
				break;
			}
			break;

		case ID_CBOX_MOUSE_TYPE:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				// to do
				break;

			default:
				break;
			}
			break;

		case IDOK:
		case IDCANCEL:
			CheckSelection(hWndDlg);
			gbStartDrawing = TRUE;
			gbGenerateReceipt = TRUE;
			InvalidateRect(ghWnd, NULL, TRUE);
			EndDialog(hWndDlg, 0);
			break;
			//return TRUE;

		default:
			break;
		}
		break;
	}
	return(FALSE);
}

void InitializeComboBoxes(void)
{
	//for (int Count = 0; Count < (sizeof(CPUVendor) / sizeof(TCHAR *)); Count++)
	for (int Count = 0; CPUVendor[Count] != NULL; Count++)
	{
		SendMessage(hWndCPUVendor, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)CPUVendor[Count]));
		//SendMessage(hWndCPUVendor, CB_ADDSTRING, 0, (LPARAM)CPUVendor[Count]);
		//SendMessage(hWndCPUVendor, CB_SETCURSEL, 2, 0);
		SendMessage(hWndCPUVendor, WM_SETTEXT, 0, (LPARAM)CPUVendor[0]);
	}

	for (int Count = 0; MotherboardVendor[Count] != NULL; Count++)
	{
		SendMessage(hWndMotherboardVendor, CB_ADDSTRING, 0, (LPARAM)MotherboardVendor[Count]);
		SendMessage(hWndMotherboardVendor, WM_SETTEXT, 0, (LPARAM)MotherboardVendor[0]);
	}

	for (int Count = 0; RAMVendor[Count] != NULL; Count++)
	{
		SendMessage(hWndRAMVendor, CB_ADDSTRING, 0, (LPARAM)RAMVendor[Count]);
		SendMessage(hWndRAMVendor, WM_SETTEXT, 0, (LPARAM)RAMVendor[0]);
	}

	for (int Count = 0; GPUVendor[Count] != NULL; Count++)
	{
		SendMessage(hWndGPUVendor, CB_ADDSTRING, 0, (LPARAM)GPUVendor[Count]);
		SendMessage(hWndGPUVendor, WM_SETTEXT, 0, (LPARAM)GPUVendor[0]);
	}

	for (int Count = 0; HDDVendor[Count] != NULL; Count++)
	{
		SendMessage(hWndHDDVendor, CB_ADDSTRING, 0, (LPARAM)HDDVendor[Count]);
		SendMessage(hWndHDDVendor, WM_SETTEXT, 0, (LPARAM)HDDVendor[0]);
	}

	for (int Count = 0; MonitorVendor[Count] != NULL; Count++)
	{
		SendMessage(hWndMonitorVendor, CB_ADDSTRING, 0, (LPARAM)MonitorVendor[Count]);
		SendMessage(hWndMonitorVendor, WM_SETTEXT, 0, (LPARAM)MonitorVendor[0]);
	}

	for (int Count = 0; DVDSpeed[Count] != NULL; Count++)
	{
		SendMessage(hWndOpticalDriveSpeed, CB_ADDSTRING, 0, (LPARAM)DVDSpeed[Count]);
		SendMessage(hWndOpticalDriveSpeed, WM_SETTEXT, 0, (LPARAM)DVDSpeed[0]);
	}

	for (int Count = 0; SMPSVendor[Count] != NULL; Count++)
	{
		SendMessage(hWndSMPSVendor, CB_ADDSTRING, 0, (LPARAM)SMPSVendor[Count]);
		SendMessage(hWndSMPSVendor, WM_SETTEXT, 0, (LPARAM)SMPSVendor[0]);
	}

	for (int Count = 0; CabinetVendor[Count] != NULL; Count++)
	{
		SendMessage(hWndCabinetVendor, CB_ADDSTRING, 0, (LPARAM)CabinetVendor[Count]);
		SendMessage(hWndCabinetVendor, WM_SETTEXT, 0, (LPARAM)CabinetVendor[0]);
	}

	for (int Count = 0; Keyboard[Count] != NULL; Count++)
	{
		SendMessage(hWndKeyboardVendor, CB_ADDSTRING, 0, (LPARAM)Keyboard[Count]);
		SendMessage(hWndKeyboardVendor, WM_SETTEXT, 0, (LPARAM)Keyboard[0]);
	}

	for (int Count = 0; Mouse[Count] != NULL; Count++)
	{
		SendMessage(hWndMouseVendor, CB_ADDSTRING, 0, (LPARAM)Mouse[Count]);
		SendMessage(hWndMouseVendor, WM_SETTEXT, 0, (LPARAM)Mouse[0]);
	}

	ShowWindow(hWndCPUSubType, SW_HIDE);
	ShowWindow(hWndCPUModel, SW_HIDE);
	ShowWindow(hWndCabinetFormFactor, SW_HIDE);
	ShowWindow(hWndGPUModel, SW_HIDE);
	ShowWindow(hWndGPUSeries, SW_HIDE);
	ShowWindow(hWndHDDCapacity, SW_HIDE);
	ShowWindow(hWndHDDSpeed, SW_HIDE);
	ShowWindow(hWndKeyboardType, SW_HIDE);
	ShowWindow(hWndMonitorResolution, SW_HIDE);
	ShowWindow(hWndMonitorScreensize, SW_HIDE);
	ShowWindow(hWndMotherboardModel, SW_HIDE);
	ShowWindow(hWndMouseType, SW_HIDE);
	ShowWindow(hWndRAMCapacity, SW_HIDE);
	ShowWindow(hWndRAMType, SW_HIDE);
	ShowWindow(hWndSMPSCapacity, SW_HIDE);
}

void CPUVendorSelectionCheck(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iVendorSelect;
	TCHAR str[255];

	iVendorSelect = SendDlgItemMessage(hWndDlg, ID_PROCESSOR_VENDOR_COMBOBOX, CB_GETCURSEL, 0, 0);
	if (iVendorSelect != CB_ERR && iVendorSelect != 0)
	{
		ShowWindow(hWndCPUSubType, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);
		//MessageBox(NULL, str, TEXT("Information"), MB_OK | MB_SYSTEMMODAL);

		//wcscat_s(tcCPUBuff, str);
		//wcscat_s(tcCPUBuff, TEXT(" "));

		if (wcscmp(str, TEXT("Intel")) == 0)
		{
			gbIntelCPUSelect = TRUE;
			gbAMDCPUSelect = FALSE;
			SendMessage(hWndCPUSubType, CB_RESETCONTENT, 0, 0);
			//for (int Count = 0; Count < (sizeof(IntelSubType) / sizeof(TCHAR *)); Count++)
			for (int Count = 0; IntelSubType[Count] != NULL; Count++)
			{
				SendMessage(hWndCPUSubType, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)IntelSubType[Count]));
				//SendMessage(hWndCPUVendor, CB_ADDSTRING, 0, (LPARAM)CPUVendor[Count]);
				//SendMessage(hWndCPUVendor, CB_SETCURSEL, 2, 0);
				SendMessage(hWndCPUSubType, WM_SETTEXT, 0, (LPARAM)IntelSubType[0]);
			}
		}
		else if (wcscmp(str, TEXT("AMD")) == 0)
		{
			gbIntelCPUSelect = FALSE;
			gbAMDCPUSelect = TRUE;
			SendMessage(hWndCPUSubType, CB_RESETCONTENT, 0, 0);
			//for (int Count = 0; Count < (sizeof(AMDSubType) / sizeof(TCHAR *)); Count++)
			for (int Count = 0; AMDSubType[Count] != NULL; Count++)
			{
				SendMessage(hWndCPUSubType, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)AMDSubType[Count]));
				//SendMessage(hWndCPUVendor, CB_ADDSTRING, 0, (LPARAM)CPUVendor[Count]);
				//SendMessage(hWndCPUVendor, CB_SETCURSEL, 2, 0);
				SendMessage(hWndCPUSubType, WM_SETTEXT, 0, (LPARAM)AMDSubType[0]);
			}
		}
	}
	else
	{
		ShowWindow(hWndCPUSubType, SW_HIDE);
		ShowWindow(hWndCPUModel, SW_HIDE);
	}
}

void CPUSubTypeSelectionCheck(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iCPUSubTypeSelect;
	TCHAR str[255];
	TCHAR *buffer = NULL;
	TCHAR *CPUModelAppend = TEXT("Models");
	TCHAR *CPUPriceAppend = TEXT("Prices");

	iCPUSubTypeSelect = SendDlgItemMessage(hWndDlg, ID_PROCESSOR_SUBTYPE_COMBOBOX, CB_GETCURSEL, 0, 0);
	if (iCPUSubTypeSelect != CB_ERR && iCPUSubTypeSelect != 0)
	{
		ShowWindow(hWndCPUModel, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);
		//MessageBox(NULL, str, TEXT("Information"), MB_OK | MB_SYSTEMMODAL);

		//wcscat_s(tcCPUBuff, str);
		//wcscat_s(tcCPUBuff, TEXT(" "));

		if (gbIntelCPUSelect == TRUE)
		{
			if (wcscmp(str, TEXT("Core i3")) == 0)
			{
				gbCorei3Select = TRUE;
				gbCorei5Select = FALSE;
				gbCorei7Select = FALSE;
				gbCorei9Select = FALSE;
				gbPentiumSelect = FALSE;
				gbXeonSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; Corei3Models[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)Corei3Models[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)Corei3Models[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)Corei3Models[0]);
				}
			}

			if (wcscmp(str, TEXT("Core i5")) == 0)
			{
				gbCorei3Select = FALSE;
				gbCorei5Select = TRUE;
				gbCorei7Select = FALSE;
				gbCorei9Select = FALSE;
				gbPentiumSelect = FALSE;
				gbXeonSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; Corei5Models[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)Corei5Models[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)Corei5Models[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)Corei5Models[0]);
				}
			}

			if (wcscmp(str, TEXT("Core i7")) == 0)
			{
				gbCorei3Select = FALSE;
				gbCorei5Select = FALSE;
				gbCorei7Select = TRUE;
				gbCorei9Select = FALSE;
				gbPentiumSelect = FALSE;
				gbXeonSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; Corei7Models[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)Corei7Models[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)Corei7Models[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)Corei7Models[0]);
				}
			}

			if (wcscmp(str, TEXT("Core i9")) == 0)
			{
				gbCorei3Select = FALSE;
				gbCorei5Select = FALSE;
				gbCorei7Select = FALSE;
				gbCorei9Select = TRUE;
				gbPentiumSelect = FALSE;
				gbXeonSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; Corei9Models[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)Corei9Models[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)Corei9Models[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)Corei9Models[0]);
				}
			}

			if (wcscmp(str, TEXT("Xeon")) == 0)
			{
				gbCorei3Select = FALSE;
				gbCorei5Select = FALSE;
				gbCorei7Select = FALSE;
				gbCorei9Select = FALSE;
				gbPentiumSelect = FALSE;
				gbXeonSelect = TRUE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; XeonModels[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)XeonModels[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)XeonModels[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)XeonModels[0]);
				}
			}

			if (wcscmp(str, TEXT("Pentium")) == 0)
			{
				gbCorei3Select = FALSE;
				gbCorei5Select = FALSE;
				gbCorei7Select = FALSE;
				gbCorei9Select = FALSE;
				gbPentiumSelect = TRUE;
				gbXeonSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; PentiumModels[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)PentiumModels[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)PentiumModels[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)PentiumModels[0]);
				}
			}
		}
		else if (gbAMDCPUSelect == TRUE)
		{
			if (wcscmp(str, TEXT("Ryzen 3")) == 0)
			{
				gbRyzen3Select = TRUE;
				gbRyzen5Select = FALSE;
				gbRyzen7Select = FALSE;
				gbRyzenThreadripperSelect = FALSE;
				gbAPUSelect = FALSE;
				gbFXSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; Ryzen3Models[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)Ryzen3Models[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)Ryzen3Models[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)Ryzen3Models[0]);
				}
			}

			if (wcscmp(str, TEXT("Ryzen 5")) == 0)
			{
				gbRyzen3Select = FALSE;
				gbRyzen5Select = TRUE;
				gbRyzen7Select = FALSE;
				gbRyzenThreadripperSelect = FALSE;
				gbAPUSelect = FALSE;
				gbFXSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; Ryzen5Models[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)Ryzen5Models[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)Ryzen5Models[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)Ryzen5Models[0]);
				}
			}

			if (wcscmp(str, TEXT("Ryzen 7")) == 0)
			{
				gbRyzen3Select = FALSE;
				gbRyzen5Select = FALSE;
				gbRyzen7Select = TRUE;
				gbRyzenThreadripperSelect = FALSE;
				gbAPUSelect = FALSE;
				gbFXSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; Ryzen7Models[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)Ryzen7Models[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)Ryzen7Models[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)Ryzen7Models[0]);
				}
			}

			if (wcscmp(str, TEXT("Ryzen Threadripper")) == 0)
			{
				gbRyzen3Select = FALSE;
				gbRyzen5Select = FALSE;
				gbRyzen7Select = FALSE;
				gbRyzenThreadripperSelect = TRUE;
				gbAPUSelect = FALSE;
				gbFXSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; RyzenThreadripperModels[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)RyzenThreadripperModels[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)RyzenThreadripperModels[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)RyzenThreadripperModels[0]);
				}
			}

			if (wcscmp(str, TEXT("A Series APU")) == 0)
			{
				gbRyzen3Select = FALSE;
				gbRyzen5Select = FALSE;
				gbRyzen7Select = FALSE;
				gbRyzenThreadripperSelect = FALSE;
				gbAPUSelect = TRUE;
				gbFXSelect = FALSE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; ASeriesAPUModels[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)ASeriesAPUModels[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)ASeriesAPUModels[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)ASeriesAPUModels[0]);
				}
			}

			if (wcscmp(str, TEXT("FX Series")) == 0)
			{
				gbRyzen3Select = FALSE;
				gbRyzen5Select = FALSE;
				gbRyzen7Select = FALSE;
				gbRyzenThreadripperSelect = FALSE;
				gbAPUSelect = FALSE;
				gbFXSelect = TRUE;

				SendMessage(hWndCPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; FXSeriesModels[Count] != NULL; Count++)
				{
					SendMessage(hWndCPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)FXSeriesModels[Count]));
					//SendMessage(hWndCPUModel, CB_ADDSTRING, 0, (LPARAM)FXSeriesModels[Count]);
					//SendMessage(hWndCPUModel, CB_SETCURSEL, 2, 0);
					SendMessage(hWndCPUModel, WM_SETTEXT, 0, (LPARAM)FXSeriesModels[0]);
				}
			}
		}

		//if (gbIntelSelect == TRUE)
		//{
		//	for (int Count = 1; IntelSubType[Count] != NULL; Count++)
		//	{
		//		if (wcscmp(str, IntelSubType[Count]) == 0)
		//		{
		//			buffer = RemoveWhiteSpace((TCHAR *)IntelSubType[Count]);
		//			wcscat(buffer, CPUModelAppend);
		//			wsprintf(str, TEXT("%s"), buffer);
		//			//MessageBox(NULL, str, TEXT("Msg"), MB_OK);

		//			//map<TCHAR *, int>varname;
		//			//varname[buffer] = Count;

		//		}
		//		else
		//		{
		//			// To do
		//		}
		//	}
		//}
		//else if (gbAMDSelect == TRUE)
		//{
		//	for (int Count = 1; AMDSubType[Count] != NULL; Count++)
		//	{
		//		if (wcscmp(str, AMDSubType[Count]) == 0)
		//		{
		//			buffer = RemoveWhiteSpace((TCHAR *)AMDSubType[Count]);
		//			wcscat(buffer, CPUModelAppend);
		//			wsprintf(str, TEXT("%s"), buffer);
		//			MessageBox(NULL, str, TEXT("Msg"), MB_OK);
		//		}
		//		else
		//		{
		//			// To do
		//		}
		//	}
		//}	
	}
	else
	{
		ShowWindow(hWndCPUModel, SW_HIDE);
	}
}

void CPUModelSelectionCheck(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iCPUModelSelect;
	TCHAR str[255];

	iCPUModelSelect = SendDlgItemMessage(hWndDlg, ID_PROCESSOR_MODEL_COMBOBOX, CB_GETCURSEL, 0, 0);
	
	iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
	SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);


	//wcscat_s(tcCPUBuff, str);
	//wcscat_s(tcCPUBuff, TEXT(" "));

	if (gbIntelCPUSelect == TRUE)
	{
		if (gbCorei3Select == TRUE)
		{
			iCPUFinalCost = Corei3Prices[iIndex];
		}
		else if (gbCorei5Select == TRUE)
		{
			iCPUFinalCost = Corei5Prices[iIndex];
		}
		else if (gbCorei7Select == TRUE)
		{
			iCPUFinalCost = Corei7Prices[iIndex];
		}
		else if (gbCorei9Select == TRUE)
		{
			iCPUFinalCost = Corei9Prices[iIndex];
		}
		else if (gbXeonSelect == TRUE)
		{
			iCPUFinalCost = XeonPrices[iIndex];
		}
		else if (gbPentiumSelect == TRUE)
		{
			iCPUFinalCost = PentiumPrices[iIndex];
		}
	}
	else if (gbAMDCPUSelect == TRUE)
	{
		if (gbRyzen3Select == TRUE)
		{
			iCPUFinalCost = Ryzen3Prices[iIndex];
		}
		else if (gbRyzen5Select == TRUE)
		{
			iCPUFinalCost = Ryzen5Prices[iIndex];
		}
		else if (gbRyzen7Select == TRUE)
		{
			iCPUFinalCost = Ryzen7Prices[iIndex];
		}
		else if (gbRyzenThreadripperSelect == TRUE)
		{
			iCPUFinalCost = RyzenThreadripperPrices[iIndex];
		}
		else if (gbAPUSelect == TRUE)
		{
			iCPUFinalCost = APUPrices[iIndex];
		}
		else if (gbFXSelect == TRUE)
		{
			iCPUFinalCost = FXPrices[iIndex];
		}
	}
}

void MotherboardVendorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iVendorSelect;
	TCHAR str[255];

	iVendorSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_MOTHERBOARD_VENDOR, CB_GETCURSEL, 0, 0);
	if (iVendorSelect != CB_ERR && iVendorSelect != 0)
	{
		ShowWindow(hWndMotherboardModel, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcMotherboardBuff, str);
		//wcscat_s(tcMotherboardBuff, TEXT(" "));

		if (wcscmp(str, TEXT("Asus")) == 0)
		{
			gbAsusMotherboardSelect = TRUE;
			gbGigabyteMotherboardSelect = FALSE;

			SendMessage(hWndMotherboardModel, CB_RESETCONTENT, 0, 0);
			for (int Count = 0; AsusMotherboards[Count] != NULL; Count++)
			{
				SendMessage(hWndMotherboardModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)AsusMotherboards[Count]));
				//SendMessage(hWndCPUVendor, CB_ADDSTRING, 0, (LPARAM)CPUVendor[Count]);
				//SendMessage(hWndCPUVendor, CB_SETCURSEL, 2, 0);
				SendMessage(hWndMotherboardModel, WM_SETTEXT, 0, (LPARAM)AsusMotherboards[0]);
			}
		}
		else if (wcscmp(str, TEXT("Gigabyte")) == 0)
		{
			gbAsusMotherboardSelect = FALSE;
			gbGigabyteMotherboardSelect = TRUE;

			SendMessage(hWndMotherboardModel, CB_RESETCONTENT, 0, 0);
			for (int Count = 0; GigabyteMotherboard[Count] != NULL; Count++)
			{
				SendMessage(hWndMotherboardModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)GigabyteMotherboard[Count]));
				//SendMessage(hWndCPUVendor, CB_ADDSTRING, 0, (LPARAM)CPUVendor[Count]);
				//SendMessage(hWndCPUVendor, CB_SETCURSEL, 2, 0);
				SendMessage(hWndMotherboardModel, WM_SETTEXT, 0, (LPARAM)GigabyteMotherboard[0]);
			}
		}
	}
	else
	{
		ShowWindow(hWndMotherboardModel, SW_HIDE);
	}
}

void MotherboardModelSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iMotherboardModelSelect;
	TCHAR str[255];

	iMotherboardModelSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_MOTHERBOARD_MODEL, CB_GETCURSEL, 0, 0);

	iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
	SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

	//wcscat_s(tcMotherboardBuff, str);

	if (gbAsusMotherboardSelect == TRUE)
	{
		iMotherboardFinalCost = AsusMotherboardsPrices[iIndex];
	}
	else if (gbGigabyteMotherboardSelect == TRUE)
	{
		iMotherboardFinalCost = GigabyteMotherboardPrices[iIndex];
	}

}

void RAMVendorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iVendorSelect;
	TCHAR str[255];

	iVendorSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_RAM_VENDOR, CB_GETCURSEL, 0, 0);
	if (iVendorSelect != CB_ERR && iVendorSelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcRAMBuff, str);
		//wcscat_s(tcRAMBuff, TEXT(" "));

		ShowWindow(hWndRAMType, SW_SHOWNORMAL);
		SendMessage(hWndRAMType, CB_RESETCONTENT, 0, 0);
		for (int Count = 0; RAMType[Count] != NULL; Count++)
		{
			SendMessage(hWndRAMType, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)RAMType[Count]));
			SendMessage(hWndRAMType, WM_SETTEXT, 0, (LPARAM)RAMType[0]);
		}

		if (wcscmp(str, TEXT("Corsair")) == 0)
		{
			gbCorsairRAMSelect = TRUE;
			gbGSkillRAMSelect = FALSE;
			gbKingstonRAMSelect = FALSE;
		}
		else if (wcscmp(str, TEXT("G Skill")) == 0)
		{
			gbCorsairRAMSelect = FALSE;
			gbGSkillRAMSelect = TRUE;
			gbKingstonRAMSelect = FALSE;
		}
		else if (wcscmp(str, TEXT("Kingston")) == 0)
		{
			gbCorsairRAMSelect = FALSE;
			gbGSkillRAMSelect = FALSE;
			gbKingstonRAMSelect = TRUE;
		}
	}
	else
	{
		ShowWindow(hWndRAMType, SW_HIDE);
		ShowWindow(hWndRAMCapacity, SW_HIDE);
	}
}

void RAMTypeSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iTypeSelect;
	TCHAR str[255];

	iTypeSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_RAM_TYPE, CB_GETCURSEL, 0, 0);
	if (iTypeSelect != CB_ERR && iTypeSelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcRAMBuff, str);
		//wcscat_s(tcRAMBuff, TEXT(" "));

		if (wcscmp(str, TEXT("DDR3")) == 0)
		{
			gbDDR3Select = TRUE;
			gbDDR4Select = FALSE;
		}
		else if (wcscmp(str, TEXT("DDR4")) == 0)
		{
			gbDDR3Select = FALSE;
			gbDDR4Select = TRUE;
		}
		
		ShowWindow(hWndRAMCapacity, SW_SHOWNORMAL);
		SendMessage(hWndRAMCapacity, CB_RESETCONTENT, 0, 0);
		for (int Count = 0; RAMCapacity[Count] != NULL; Count++)
		{
			SendMessage(hWndRAMCapacity, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)RAMCapacity[Count]));
			SendMessage(hWndRAMCapacity, WM_SETTEXT, 0, (LPARAM)RAMCapacity[0]);
		}
	}
	else
	{
		ShowWindow(hWndRAMCapacity, SW_HIDE);
	}
}

void RAMCapacitySelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iCapacitySelect;
	TCHAR str[255];

	iCapacitySelect = SendDlgItemMessage(hWndDlg, ID_CBOX_RAM_CAPACITY, CB_GETCURSEL, 0, 0);
	if (iCapacitySelect != CB_ERR && iCapacitySelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcRAMBuff, str);
		//wcscat_s(tcRAMBuff, TEXT(" "));

		if (gbCorsairRAMSelect == TRUE)
		{
			if (gbDDR3Select == TRUE)
			{
				if (wcscmp(str, TEXT("4 GB")) == 0)
				{
					iRAMFinalCost = Corsair4GBDDR3;
				}
				else if (wcscmp(str, TEXT("8 GB")) == 0)
				{
					iRAMFinalCost = Corsair8GBDDR3;
				}
				else if (wcscmp(str, TEXT("16 GB")) == 0)
				{
					iRAMFinalCost = Corsair16GBDDR3;
				}
				else if (wcscmp(str, TEXT("32 GB")) == 0)
				{
					iRAMFinalCost = Corsair32GBDDR3;
				}
			}
			else if (gbDDR4Select == TRUE)
			{
				if (wcscmp(str, TEXT("4 GB")) == 0)
				{
					iRAMFinalCost = Corsair4GBDDR4;
				}
				else if (wcscmp(str, TEXT("8 GB")) == 0)
				{
					iRAMFinalCost = Corsair8GBDDR4;
				}
				else if (wcscmp(str, TEXT("16 GB")) == 0)
				{
					iRAMFinalCost = Corsair16GBDDR4;
				}
				else if (wcscmp(str, TEXT("32 GB")) == 0)
				{
					iRAMFinalCost = Corsair32GBDDR4;
				}
			}
		}
		else if (gbGSkillRAMSelect == TRUE)
		{
			if (gbDDR3Select == TRUE)
			{
				if (wcscmp(str, TEXT("4 GB")) == 0)
				{
					iRAMFinalCost = GSkill4GBDDR3;
				}
				else if (wcscmp(str, TEXT("8 GB")) == 0)
				{
					iRAMFinalCost = GSkill8GBDDR3;
				}
				else if (wcscmp(str, TEXT("16 GB")) == 0)
				{
					iRAMFinalCost = GSkill16GBDDR3;
				}
				else if (wcscmp(str, TEXT("32 GB")) == 0)
				{
					iRAMFinalCost = GSkill32GBDDR3;
				}
			}
			else if (gbDDR4Select == TRUE)
			{
				if (wcscmp(str, TEXT("4 GB")) == 0)
				{
					iRAMFinalCost = GSkill4GBDDR4;
				}
				else if (wcscmp(str, TEXT("8 GB")) == 0)
				{
					iRAMFinalCost = GSkill8GBDDR4;
				}
				else if (wcscmp(str, TEXT("16 GB")) == 0)
				{
					iRAMFinalCost = GSkill16GBDDR4;
				}
				else if (wcscmp(str, TEXT("32 GB")) == 0)
				{
					iRAMFinalCost = GSkill16GBDDR4;
				}
			}
		}
		else if (gbKingstonRAMSelect == TRUE)
		{
			if (gbDDR3Select == TRUE)
			{
				if (wcscmp(str, TEXT("4 GB")) == 0)
				{
					iRAMFinalCost = Kingston4GBDDR3;
				}
				else if (wcscmp(str, TEXT("8 GB")) == 0)
				{
					iRAMFinalCost = Kingston8GBDDR3;
				}
				else if (wcscmp(str, TEXT("16 GB")) == 0)
				{
					iRAMFinalCost = Kingston16GBDDR3;
				}
				else if (wcscmp(str, TEXT("32 GB")) == 0)
				{
					iRAMFinalCost = Kingston32GBDDR3;
				}
			}
			else if (gbDDR4Select == TRUE)
			{
				if (wcscmp(str, TEXT("4 GB")) == 0)
				{
					iRAMFinalCost = Kingston4GBDDR4;
				}
				else if (wcscmp(str, TEXT("8 GB")) == 0)
				{
					iRAMFinalCost = Kingston8GBDDR4;
				}
				else if (wcscmp(str, TEXT("16 GB")) == 0)
				{
					iRAMFinalCost = Kingston16GBDDR4;
				}
				else if (wcscmp(str, TEXT("32 GB")) == 0)
				{
					iRAMFinalCost = Kingston32GBDDR4;
				}
			}
		}


	}
}

void GPUVendorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iVendorSelect;
	TCHAR str[255];

	iVendorSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_GPU_VENDOR, CB_GETCURSEL, 0, 0);
	if (iVendorSelect != CB_ERR && iVendorSelect != 0)
	{
		ShowWindow(hWndGPUSeries, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcGPUBuff, str);
		//wcscat_s(tcGPUBuff, TEXT(" "));

		if (wcscmp(str, TEXT("Nvidia GeForce")) == 0)
		{
			gbNVidiaGPUSelect = TRUE;
			gbAMDGPUSelect = FALSE;

			SendMessage(hWndGPUSeries, CB_RESETCONTENT, 0, 0);
			for (int Count = 0; NvidiaSeries[Count] != NULL; Count++)
			{
				SendMessage(hWndGPUSeries, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)NvidiaSeries[Count]));
				SendMessage(hWndGPUSeries, WM_SETTEXT, 0, (LPARAM)NvidiaSeries[0]);
			}
		}
		else if (wcscmp(str, TEXT("AMD Radeon")) == 0)
		{
			gbNVidiaGPUSelect = FALSE;
			gbAMDGPUSelect = TRUE;

			SendMessage(hWndGPUSeries, CB_RESETCONTENT, 0, 0);
			for (int Count = 0; AMDSeries[Count] != NULL; Count++)
			{
				SendMessage(hWndGPUSeries, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)AMDSeries[Count]));
				SendMessage(hWndGPUSeries, WM_SETTEXT, 0, (LPARAM)AMDSeries[0]);
			}
		}
	}
	else
	{
		ShowWindow(hWndGPUSeries, SW_HIDE);
		ShowWindow(hWndGPUModel, SW_HIDE);
	}
}

void GPUSeriesSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iSeriesSelect;
	TCHAR str[255];

	iSeriesSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_GPU_SERIES, CB_GETCURSEL, 0, 0);
	if (iSeriesSelect != CB_ERR && iSeriesSelect != 0)
	{
		ShowWindow(hWndGPUModel, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcGPUBuff, str);
		//wcscat_s(tcGPUBuff, TEXT(" "));

		if (gbNVidiaGPUSelect == TRUE)
		{
			if (wcscmp(str, TEXT("GeForce 700")) == 0)
			{
				gbGF700Select = TRUE;
				gbGF900Select = FALSE;
				gbGF10000Select = FALSE;

				SendMessage(hWndGPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; GeForce700Models[Count] != NULL; Count++)
				{
					SendMessage(hWndGPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)GeForce700Models[Count]));
					SendMessage(hWndGPUModel, WM_SETTEXT, 0, (LPARAM)GeForce700Models[0]);
				}
			}
			else if (wcscmp(str, TEXT("GeForce 900")) == 0)
			{
				gbGF700Select = FALSE;
				gbGF900Select = TRUE;
				gbGF10000Select = FALSE;

				SendMessage(hWndGPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; GeForce900Models[Count] != NULL; Count++)
				{
					SendMessage(hWndGPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)GeForce900Models[Count]));
					SendMessage(hWndGPUModel, WM_SETTEXT, 0, (LPARAM)GeForce900Models[0]);
				}
			}
			else if (wcscmp(str, TEXT("GeForce 1000")) == 0)
			{
				gbGF700Select = FALSE;
				gbGF900Select = FALSE;
				gbGF10000Select = TRUE;

				SendMessage(hWndGPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; GeForce1000Models[Count] != NULL; Count++)
				{
					SendMessage(hWndGPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)GeForce1000Models[Count]));
					SendMessage(hWndGPUModel, WM_SETTEXT, 0, (LPARAM)GeForce1000Models[0]);
				}
			}
		}
		else if (gbAMDGPUSelect == TRUE)
		{
			if (wcscmp(str, TEXT("RX 400")) == 0)
			{
				gbRX400Select = TRUE;
				gbRX500Select = FALSE;
				gbRXVegaSelect = FALSE;

				SendMessage(hWndGPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; RX400Models[Count] != NULL; Count++)
				{
					SendMessage(hWndGPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)RX400Models[Count]));
					SendMessage(hWndGPUModel, WM_SETTEXT, 0, (LPARAM)RX400Models[0]);
				}
			}
			else if (wcscmp(str, TEXT("RX 500")) == 0)
			{
				gbRX400Select = FALSE;
				gbRX500Select = TRUE;
				gbRXVegaSelect = FALSE;

				SendMessage(hWndGPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; RX500Models[Count] != NULL; Count++)
				{
					SendMessage(hWndGPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)RX500Models[Count]));
					SendMessage(hWndGPUModel, WM_SETTEXT, 0, (LPARAM)RX500Models[0]);
				}
			}
			else if (wcscmp(str, TEXT("RX Vega")) == 0)
			{
				gbRX400Select = FALSE;
				gbRX500Select = FALSE;
				gbRXVegaSelect = TRUE;

				SendMessage(hWndGPUModel, CB_RESETCONTENT, 0, 0);
				for (int Count = 0; RXVegaModels[Count] != NULL; Count++)
				{
					SendMessage(hWndGPUModel, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)RXVegaModels[Count]));
					SendMessage(hWndGPUModel, WM_SETTEXT, 0, (LPARAM)RXVegaModels[0]);
				}
			}
		}
	}
	else
	{
		ShowWindow(hWndGPUModel, SW_HIDE);
	}
}

void GPUModelSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iGPUModelSelect;
	TCHAR str[255];

	iGPUModelSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_GPU_MODEL, CB_GETCURSEL, 0, 0);

	iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
	SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

	//wcscat_s(tcGPUBuff, str);
	//wcscat_s(tcGPUBuff, TEXT(" "));

	if (gbNVidiaGPUSelect == TRUE)
	{
		if (gbGF700Select == TRUE)
		{
			iGPUFinalCost = GeForce700Prices[iIndex];
		}
		else if (gbGF900Select == TRUE)
		{
			iGPUFinalCost = GeForce900Prices[iIndex];
		}
		else if (gbGF10000Select == TRUE)
		{
			iGPUFinalCost = GeForce1000Prices[iIndex];
		}
	}
	else if (gbAMDGPUSelect == TRUE)
	{
		if (gbRX400Select == TRUE)
		{
			iGPUFinalCost = RX400Prices[iIndex];
		}
		else if (gbRX500Select == TRUE)
		{
			iGPUFinalCost = RX500Prices[iIndex];
		}
		else if (gbRXVegaSelect == TRUE)
		{
			iGPUFinalCost = RXVegaPrices[iIndex];
		}
	}
}

void HDDVendorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iVendorSelect;
	TCHAR str[255];

	iVendorSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_STORAGE_VENDOR, CB_GETCURSEL, 0, 0);
	if (iVendorSelect != CB_ERR && iVendorSelect != 0)
	{
		ShowWindow(hWndHDDCapacity, SW_SHOWNORMAL);
		SendMessage(hWndHDDCapacity, CB_RESETCONTENT, 0, 0);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcHDDBuff, str);
		//wcscat_s(tcHDDBuff, TEXT(" "));

		if (wcscmp(str, TEXT("Western Digital")) == 0)
		{
			gbWDSelect = TRUE;
			gbSeagateSelect = FALSE;
		}
		else if (wcscmp(str, TEXT("Seagate")) == 0)
		{
			gbWDSelect = FALSE;
			gbSeagateSelect = TRUE;
		}

		for (int Count = 0; HDDCapacity[Count] != NULL; Count++)
		{
			SendMessage(hWndHDDCapacity, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)HDDCapacity[Count]));
			SendMessage(hWndHDDCapacity, WM_SETTEXT, 0, (LPARAM)HDDCapacity[0]);
		}
	}
	else
	{
		ShowWindow(hWndHDDCapacity, SW_HIDE);
	}
}

void HDDCapacitySelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iCapacitySelect;
	TCHAR str[255];

	iCapacitySelect = SendDlgItemMessage(hWndDlg, ID_CBOX_STORAGE_CAPACITY, CB_GETCURSEL, 0, 0);
	if (iCapacitySelect != CB_ERR && iCapacitySelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcHDDBuff, str);
		//wcscat_s(tcHDDBuff, TEXT(" "));

		if (gbWDSelect == TRUE)
		{
			if (wcscmp(str, TEXT("1TB")) == 0)
			{
				iHDDFinalCost = WD1TBPrice[iIndex];
			}
			else if (wcscmp(str, TEXT("2TB")) == 0)
			{
				iHDDFinalCost = WD2TBPrice[iIndex];
			}
			else if (wcscmp(str, TEXT("4TB")) == 0)
			{
				iHDDFinalCost = WD4TBPrice[iIndex];
			}
			else if (wcscmp(str, TEXT("8TB")) == 0)
			{
				iHDDFinalCost = WD8TBPrice[iIndex];
			}
		}
		else if (gbSeagateSelect == TRUE)
		{
			if (wcscmp(str, TEXT("1TB")) == 0)
			{
				iHDDFinalCost = Seagate1TBPrice[iIndex];
			}
			else if (wcscmp(str, TEXT("2TB")) == 0)
			{
				iHDDFinalCost = Seagate2TBPrice[iIndex];
			}
			else if (wcscmp(str, TEXT("4TB")) == 0)
			{
				iHDDFinalCost = Seagate4TBPrice[iIndex];
			}
			else if (wcscmp(str, TEXT("8TB")) == 0)
			{
				iHDDFinalCost = Seagate8TBPrice[iIndex];
			}
		}
	}
}

void HDDSpeedSelect(HWND hWndDlg, HWND hWndComboBox)
{
	// To do
}

void MonitorVendorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iVendorSelect;
	TCHAR str[255];

	iVendorSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_MONITOR_VENDOR, CB_GETCURSEL, 0, 0);
	if (iVendorSelect != CB_ERR && iVendorSelect != 0)
	{
		ShowWindow(hWndMonitorScreensize, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcMonitorBuff, str);
		//wcscat_s(tcMonitorBuff, TEXT(" "));

		if (wcscmp(str, TEXT("Asus")) == 0)
		{
			gbASUSMonitorSelect = TRUE;
			gbSamsungMonitorSelect = FALSE;
		}
		if (wcscmp(str, TEXT("SAMSUNG")) == 0)
		{
			gbASUSMonitorSelect = FALSE;
			gbSamsungMonitorSelect = TRUE;
		}

		SendMessage(hWndMonitorScreensize, CB_RESETCONTENT, 0, 0);
		for (int Count = 0; MonitorScreenSize[Count] != NULL; Count++)
		{
			SendMessage(hWndMonitorScreensize, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)MonitorScreenSize[Count]));
			SendMessage(hWndMonitorScreensize, WM_SETTEXT, 0, (LPARAM)MonitorScreenSize[0]);
		}
	}
	else
	{
		ShowWindow(hWndMonitorScreensize, SW_HIDE);
		ShowWindow(hWndMonitorResolution, SW_HIDE);
	}
}

void MonitorSizeSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iSizeSelect;
	TCHAR str[255];

	iSizeSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_MONITOR_SCREENSIZE, CB_GETCURSEL, 0, 0);
	if (iSizeSelect != CB_ERR && iSizeSelect != 0)
	{
		ShowWindow(hWndMonitorResolution, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcMonitorBuff, str);
		//wcscat_s(tcMonitorBuff, TEXT(" "));

		if (wcscmp(str, MonitorScreenSize[1]) == 0)
		{
			gb21_5Inch = TRUE;
			gb24Inch = FALSE;
			gb27Inch = FALSE;
			gb31_5Inch = FALSE;
		}
		else if (wcscmp(str, MonitorScreenSize[2]) == 0)
		{
			gb21_5Inch = FALSE;
			gb24Inch = TRUE;
			gb27Inch = FALSE;
			gb31_5Inch = FALSE;
		}
		else if (wcscmp(str, MonitorScreenSize[3]) == 0)
		{
			gb21_5Inch = FALSE;
			gb24Inch = FALSE;
			gb27Inch = TRUE;
			gb31_5Inch = FALSE;
		}
		else if (wcscmp(str, MonitorScreenSize[4]) == 0)
		{
			gb21_5Inch = FALSE;
			gb24Inch = FALSE;
			gb27Inch = FALSE;
			gb31_5Inch = TRUE;
		}

		SendMessage(hWndMonitorResolution, CB_RESETCONTENT, 0, 0);
		for (int Count = 0; MonitorResolution[Count] != NULL; Count++)
		{
			SendMessage(hWndMonitorResolution, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)MonitorResolution[Count]));
			SendMessage(hWndMonitorResolution, WM_SETTEXT, 0, (LPARAM)MonitorResolution[0]);
		}
	}
	else
	{
		ShowWindow(hWndMonitorResolution, SW_HIDE);
	}
}

void MonitorResolutionSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iSizeSelect;
	TCHAR str[255];

	iSizeSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_MONITOR_RESOLUTION, CB_GETCURSEL, 0, 0);
	if (iSizeSelect != CB_ERR && iSizeSelect != 0)
	{
		ShowWindow(hWndMonitorResolution, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcMonitorBuff, str);
		//wcscat_s(tcMonitorBuff, TEXT(" "));

		if (gbASUSMonitorSelect == TRUE)
		{
			if (gb21_5Inch == TRUE)
			{
				iMonitorFinalCost = ASUS1080_21_5;
			}
			else if (gb24Inch == TRUE)
			{
				iMonitorFinalCost = ASUS1080_24;
			}
			else if (gb27Inch == TRUE)
			{
				iMonitorFinalCost = ASUS1080_27;
			}
			else if (gb31_5Inch == TRUE)
			{
				iMonitorFinalCost = ASUS1080_31_5;
			}
		}
		else if (gbSamsungMonitorSelect = TRUE)
		{
			if (gb21_5Inch == TRUE)
			{
				iMonitorFinalCost = SAMSUNG1080_21_5;
			}
			else if (gb24Inch == TRUE)
			{
				iMonitorFinalCost = SAMSUNG1080_24;
			}
			else if (gb27Inch == TRUE)
			{
				iMonitorFinalCost = SAMSUNG1080_27;
			}
			else if (gb31_5Inch == TRUE)
			{
				iMonitorFinalCost = SAMSUNG1080_31_5;
			}
		}
	}
	else
	{
		ShowWindow(hWndMonitorResolution, SW_HIDE);
	}
}

void DVDVendorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	// To do
}

void DVDSpeedSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iDVDSelect;
	TCHAR str[255];

	iDVDSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_OPTICAL_DRIVE_SPEED, CB_GETCURSEL, 0, 0);
	if (iDVDSelect != CB_ERR && iDVDSelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcDVDBuff, str);

		iDVDROMFinalCost = DVDPrice[iIndex];
	}
}

void SMPSVendorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iVendorSelect;
	TCHAR str[255];

	iVendorSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_POWERSUPPLY_VENDOR, CB_GETCURSEL, 0, 0);
	if (iVendorSelect != CB_ERR && iVendorSelect != 0)
	{
		ShowWindow(hWndSMPSCapacity, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcSMPSBuff, str);
		//wcscat_s(tcSMPSBuff, TEXT(" "));

		if (wcscmp(str, TEXT("Corsair")) == 0)
		{
			gbCorsairSMPSSelect = TRUE;
			gbCMSMPSSelect = FALSE;
		}
		else if (wcscmp(str, TEXT("Cooler Master")) == 0)
		{
			gbCorsairSMPSSelect = FALSE;
			gbCMSMPSSelect = TRUE;
		}

		SendMessage(hWndSMPSCapacity, CB_RESETCONTENT, 0, 0);
		for (int Count = 0; SMPSCapacity[Count] != NULL; Count++)
		{
			SendMessage(hWndSMPSCapacity, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)SMPSCapacity[Count]));
			SendMessage(hWndSMPSCapacity, WM_SETTEXT, 0, (LPARAM)SMPSCapacity[0]);
		}
	}
	else
	{
		ShowWindow(hWndSMPSCapacity, SW_HIDE);
	}
}

void SMPSCapacitySelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iCapacitySelect;
	TCHAR str[255];

	iCapacitySelect = SendDlgItemMessage(hWndDlg, ID_CBOX_POWERSUPPLY_CAPACITY, CB_GETCURSEL, 0, 0);
	if (iCapacitySelect != CB_ERR && iCapacitySelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscat_s(tcSMPSBuff, str);

		if (gbCMSMPSSelect == TRUE)
		{
			if (wcscmp(str, TEXT("650W")) == 0)
			{
				iSMPSFinalCost = CM650;
			}
			else if (wcscmp(str, TEXT("750W")) == 0)
			{
				iSMPSFinalCost = CM750;
			}
			else if (wcscmp(str, TEXT("850W")) == 0)
			{
				iSMPSFinalCost = CM850;
			}
			else if (wcscmp(str, TEXT("1000W")) == 0)
			{
				iSMPSFinalCost = CM1000;
			}
			else if (wcscmp(str, TEXT("1200W")) == 0)
			{
				iSMPSFinalCost = CM1200;
			}
		}
		else if (gbCorsairSMPSSelect == TRUE)
		{
			if (wcscmp(str, TEXT("650W")) == 0)
			{
				iSMPSFinalCost = Corsair650;
			}
			else if (wcscmp(str, TEXT("750W")) == 0)
			{
				iSMPSFinalCost = Corsair750;
			}
			else if (wcscmp(str, TEXT("850W")) == 0)
			{
				iSMPSFinalCost = Corsair850;
			}
			else if (wcscmp(str, TEXT("1000W")) == 0)
			{
				iSMPSFinalCost = Corsair1000;
			}
			else if (wcscmp(str, TEXT("1200W")) == 0)
			{
				iSMPSFinalCost = Corsair1200;
			}
		}
	}
}

void CabinetVendorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iVendorSelect;
	TCHAR str[255];

	iVendorSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_CABINET_VENDOR, CB_GETCURSEL, 0, 0);
	if (iVendorSelect != CB_ERR && iVendorSelect != 0)
	{
		ShowWindow(hWndCabinetFormFactor, SW_SHOWNORMAL);

		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);
		//MessageBox(NULL, str, TEXT("Information"), MB_OK | MB_SYSTEMMODAL);

		//wcscat_s(tcCabinetBuff, str);
		//wcscat_s(tcCabinetBuff, TEXT(" "));

		if (wcscmp(str, TEXT("Corsair")) == 0)
		{
			gbCorsairCabinetSelect = TRUE;
			gbCMCabinetSelect = FALSE;

			SendMessage(hWndCabinetFormFactor, CB_RESETCONTENT, 0, 0);
			//for (int Count = 0; Count < (sizeof(IntelSubType) / sizeof(TCHAR *)); Count++)
			for (int Count = 0; CorsairCabinet[Count] != NULL; Count++)
			{
				SendMessage(hWndCabinetFormFactor, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)CorsairCabinet[Count]));
				SendMessage(hWndCabinetFormFactor, WM_SETTEXT, 0, (LPARAM)CorsairCabinet[0]);
			}
		}
		else if (wcscmp(str, TEXT("Cooler Master")) == 0)
		{
			gbCorsairCabinetSelect = FALSE;
			gbCMCabinetSelect = TRUE;

			SendMessage(hWndCabinetFormFactor, CB_RESETCONTENT, 0, 0);
			//for (int Count = 0; Count < (sizeof(AMDSubType) / sizeof(TCHAR *)); Count++)
			for (int Count = 0; CMCabinets[Count] != NULL; Count++)
			{
				SendMessage(hWndCabinetFormFactor, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>((LPCTSTR)CMCabinets[Count]));
				SendMessage(hWndCabinetFormFactor, WM_SETTEXT, 0, (LPARAM)CMCabinets[0]);
			}
		}
	}
	else
	{
		ShowWindow(hWndCabinetFormFactor, SW_HIDE);
	}
}

void CabinetFormFactorSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iFormFactorSelect;
	TCHAR str[255];

	iFormFactorSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_CABINET_FORMFACTOR, CB_GETCURSEL, 0, 0);
	if (iFormFactorSelect != CB_ERR && iFormFactorSelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);
		//MessageBox(NULL, str, TEXT("Information"), MB_OK | MB_SYSTEMMODAL);

		//wcscat_s(tcCabinetBuff, str);

		if (gbCorsairCabinetSelect == TRUE)
		{
			iCabinetFinalCost = CorsairCabinetCost[iIndex];
		}
		else if (gbCMCabinetSelect == TRUE)
		{
			iCabinetFinalCost = CMCabinetCost[iIndex];
		}
	}

}

void KeyboardSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iKeyboardSelect;
	TCHAR str[255];

	iKeyboardSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_KEYBOARD_VENDOR, CB_GETCURSEL, 0, 0);
	if (iKeyboardSelect != CB_ERR && iKeyboardSelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);
	
		//wcscpy_s(tcKeyboardBuff, str);

		iKeyboardFinalCost = KeyboardCost[iIndex];
	}
}

void MouseSelect(HWND hWndDlg, HWND hWndComboBox)
{
	int iIndex, iMouseSelect;
	TCHAR str[255];

	iMouseSelect = SendDlgItemMessage(hWndDlg, ID_CBOX_MOUSE_VENDOR, CB_GETCURSEL, 0, 0);
	if (iMouseSelect != CB_ERR && iMouseSelect != 0)
	{
		iIndex = SendMessage(hWndComboBox, CB_GETCURSEL, 0, 0);
		SendMessage(hWndComboBox, CB_GETLBTEXT, iIndex, (LPARAM)str);

		//wcscpy_s(tcMouseBuff, str);

		iMouseFinalCost = MouseCost[iIndex];
	}
}

//TCHAR *RemoveWhiteSpace(TCHAR *string)
//{
//	TCHAR cleanstring[NORMAL_ARRAY_SIZE], append[NORMAL_ARRAY_SIZE];
//
//	memset((void *)&cleanstring, '\0', sizeof(TCHAR) * NORMAL_ARRAY_SIZE);
//	memset((void *)&append, '\0', sizeof(TCHAR) * NORMAL_ARRAY_SIZE);
//
//	int len = 0;
//	len = wcslen(string);
//
//	for (int i = 0; i < len; i++)
//	{
//		if (string[i] != (wchar_t)' ')
//		{
//			append[0] = string[i];
//			wcscat_s(cleanstring, append);
//		}
//	}
//	return cleanstring;
//}

void DisplayData(HDC hDC)
{
	int x = 20;
	int y = 40;

	int len = 0;
	GetClientRect(ghWnd, &rc);
	//hDC = BeginPaint(ghWnd, &ps);
	


	int Count = 0;
	for (int i = 60; i < 500; i += 40)
	{
		TextOut(hDC, 20, i, ItemList[Count], wcslen(ItemList[Count]));
		Count += 1;
	}

	TextOut(hDC, 20, 20, Headings[0], wcslen(Headings[0]));
	TextOut(hDC, 320, 20, Headings[1], wcslen(Headings[1]));
	TextOut(hDC, 920, 20, Headings[2], wcslen(Headings[2]));
	TextOut(hDC, 820, 520, Headings[3], wcslen(Headings[3]));

	TextOut(hDC, 320, 60, tcCPUBuff, wcslen(tcCPUBuff));
	TextOut(hDC, 320, 100, tcMotherboardBuff, wcslen(tcMotherboardBuff));
	TextOut(hDC, 320, 140, tcRAMBuff, wcslen(tcRAMBuff));
	TextOut(hDC, 320, 180, tcGPUBuff, wcslen(tcGPUBuff));
	TextOut(hDC, 320, 220, tcHDDBuff, wcslen(tcHDDBuff));
	TextOut(hDC, 320, 260, tcMonitorBuff, wcslen(tcMonitorBuff));
	TextOut(hDC, 320, 300, tcCabinetBuff, wcslen(tcCabinetBuff));
	TextOut(hDC, 320, 340, tcSMPSBuff, wcslen(tcSMPSBuff));
	TextOut(hDC, 320, 380, tcDVDBuff, wcslen(tcDVDBuff));
	TextOut(hDC, 320, 420, tcKeyboardBuff, wcslen(tcKeyboardBuff));
	TextOut(hDC, 320, 460, tcMouseBuff, wcslen(tcMouseBuff));

	TextOut(hDC, 920, 60, tcCPUCostBuffer, wcslen(tcCPUCostBuffer));
	TextOut(hDC, 920, 100, tcMotherboardCostBuffer, wcslen(tcMotherboardCostBuffer));
	TextOut(hDC, 920, 140, tcRAMCostBuffer, wcslen(tcRAMCostBuffer));
	TextOut(hDC, 920, 180, tcGPUCostBuffer, wcslen(tcGPUCostBuffer));
	TextOut(hDC, 920, 220, tcHDDCostBuffer, wcslen(tcHDDCostBuffer));
	TextOut(hDC, 920, 260, tcMonitorCostBuffer, wcslen(tcMonitorCostBuffer));
	TextOut(hDC, 920, 300, tcCabinetCostBuffer, wcslen(tcCabinetCostBuffer));
	TextOut(hDC, 920, 340, tcSMPSCostBuffer, wcslen(tcSMPSCostBuffer));
	TextOut(hDC, 920, 380, tcDVDCostBuffer, wcslen(tcDVDCostBuffer));
	TextOut(hDC, 920, 420, tcKeyboardCostBuffer, wcslen(tcKeyboardCostBuffer));
	TextOut(hDC, 920, 460, tcMouseCostBuffer, wcslen(tcMouseCostBuffer));
	
	TextOut(hDC, 920, 520, tcTotalCost, wcslen(tcTotalCost));

	if (iTotalCost != 0)
		TextOut(hDC, 600, 600, Headings[6], wcslen(Headings[6]));
	else
		TextOut(hDC, 600, 600, Headings[7], wcslen(Headings[7]));

	SelectObject(hDC, GetStockObject(DC_PEN));

	//    Set the Pen to Blue
	SetDCPenColor(hDC, RGB(255, 255, 0));

	// Horizontal Lines
	MoveToEx(hDC, 10, 10, (LPPOINT)NULL);
	LineTo(hDC, 1200, 10);
	
	MoveToEx(hDC, 10, 50, (LPPOINT)NULL);
	LineTo(hDC, 1200, 50);

	MoveToEx(hDC, 10, 500, (LPPOINT)NULL);
	LineTo(hDC, 1200, 500);

	MoveToEx(hDC, 10, 550, (LPPOINT)NULL);
	LineTo(hDC, 1200, 550);

	// Vertical Lines
	MoveToEx(hDC, 10, 10, (LPPOINT)NULL);
	LineTo(hDC, 10, 550);

	MoveToEx(hDC, 300, 10, (LPPOINT)NULL);
	LineTo(hDC, 300, 550);

	MoveToEx(hDC, 900, 10, (LPPOINT)NULL);
	LineTo(hDC, 900, 550);

	MoveToEx(hDC, 1200, 10, (LPPOINT)NULL);
	LineTo(hDC, 1200, 550);

	//EndPaint(ghWnd, &ps);
}

void CleanBuffers(void)
{
	iCPUFinalCost = 0;
	iGPUFinalCost = 0;
	iMotherboardFinalCost = 0;
	iCabinetFinalCost = 0;
	iHDDFinalCost = 0;
	iRAMFinalCost = 0;
	iMonitorFinalCost = 0;
	iSMPSFinalCost = 0;
	iDVDROMFinalCost = 0;
	iKeyboardFinalCost = 0;
	iMouseFinalCost = 0;
	iTotalCost = 0;

	ZeroMemory(tcCPUBuff, sizeof(TCHAR));
	ZeroMemory(tcMotherboardBuff, sizeof(TCHAR));
	ZeroMemory(tcRAMBuff, sizeof(TCHAR));
	ZeroMemory(tcGPUBuff, sizeof(TCHAR));
	ZeroMemory(tcHDDBuff, sizeof(TCHAR));
	ZeroMemory(tcMonitorBuff, sizeof(TCHAR));
	ZeroMemory(tcCabinetBuff, sizeof(TCHAR));
	ZeroMemory(tcDVDBuff, sizeof(TCHAR));
	ZeroMemory(tcKeyboardBuff, sizeof(TCHAR));
	ZeroMemory(tcSMPSBuff, sizeof(TCHAR));
	ZeroMemory(tcMouseBuff, sizeof(TCHAR));

	ZeroMemory(tcCPUCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcMotherboardCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcRAMCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcGPUCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcHDDCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcMonitorCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcCabinetCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcDVDCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcKeyboardCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcSMPSCostBuffer, sizeof(TCHAR));
	ZeroMemory(tcMouseCostBuffer, sizeof(TCHAR));
}

void CheckSelection(HWND hWndDlg)
{
	TCHAR Buffer[NORMAL_ARRAY_SIZE];

	GetDlgItemText(hWndDlg, ID_PROCESSOR_VENDOR_COMBOBOX, Buffer, sizeof(Buffer));

	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcCPUBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcCPUBuff, Buffer);
		wcscat_s(tcCPUBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_PROCESSOR_SUBTYPE_COMBOBOX, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcCPUBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcCPUBuff, Buffer);
			wcscat_s(tcCPUBuff, TEXT(" "));

			GetDlgItemText(hWndDlg, ID_PROCESSOR_MODEL_COMBOBOX, Buffer, sizeof(Buffer));
			if (wcscmp(Buffer, TEXT("Select the component")) == 0)
			{
				wcscpy_s(tcCPUBuff, TEXT(" - "));
			}
			else
			{
				wcscat_s(tcCPUBuff, Buffer);
				wcscat_s(tcCPUBuff, TEXT(" "));
				wsprintf(tcCPUCostBuffer, TEXT("Rs. %d"), iCPUFinalCost);
			}
		}

	}
	
	GetDlgItemText(hWndDlg, ID_CBOX_MOTHERBOARD_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcMotherboardBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcMotherboardBuff, Buffer);
		wcscat_s(tcMotherboardBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_CBOX_MOTHERBOARD_MODEL, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcMotherboardBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcMotherboardBuff, Buffer);
			wcscat_s(tcMotherboardBuff, TEXT(" "));
			wsprintf(tcMotherboardCostBuffer, TEXT("Rs. %d"), iMotherboardFinalCost);
		}
	}

	GetDlgItemText(hWndDlg, ID_CBOX_RAM_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcRAMBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcRAMBuff, Buffer);
		wcscat_s(tcRAMBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_CBOX_RAM_TYPE, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcRAMBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcRAMBuff, Buffer);
			wcscat_s(tcRAMBuff, TEXT(" "));

			GetDlgItemText(hWndDlg, ID_CBOX_RAM_CAPACITY, Buffer, sizeof(Buffer));
			if (wcscmp(Buffer, TEXT("Select the component")) == 0)
			{
				wcscpy_s(tcRAMBuff, TEXT(" - "));
			}
			else
			{
				wcscat_s(tcRAMBuff, Buffer);
				wcscat_s(tcRAMBuff, TEXT(" "));
				wsprintf(tcRAMCostBuffer, TEXT("Rs. %d"), iRAMFinalCost);
			}
		}
	}
	
	
	GetDlgItemText(hWndDlg, ID_CBOX_GPU_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcGPUBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcGPUBuff, Buffer);
		wcscat_s(tcGPUBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_CBOX_GPU_SERIES, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcGPUBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcGPUBuff, Buffer);
			wcscat_s(tcGPUBuff, TEXT(" "));

			GetDlgItemText(hWndDlg, ID_CBOX_GPU_MODEL, Buffer, sizeof(Buffer));
			if (wcscmp(Buffer, TEXT("Select the component")) == 0)
			{
				wcscpy_s(tcGPUBuff, TEXT(" - "));
			}
			else
			{
				wcscat_s(tcGPUBuff, Buffer);
				wcscat_s(tcGPUBuff, TEXT(" "));
				wsprintf(tcGPUCostBuffer, TEXT("Rs. %d"), iGPUFinalCost);
			}
		}
	}

	
	GetDlgItemText(hWndDlg, ID_CBOX_STORAGE_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcHDDBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcHDDBuff, Buffer);
		wcscat_s(tcHDDBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_CBOX_STORAGE_CAPACITY, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcHDDBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcHDDBuff, Buffer);
			wcscat_s(tcHDDBuff, TEXT(" "));

			GetDlgItemText(hWndDlg, ID_CBOX_STORAGE_SPEED, Buffer, sizeof(Buffer));
			if (wcscmp(Buffer, TEXT("Select the component")) == 0)
			{
				wcscpy_s(tcHDDBuff, TEXT(" - "));
			}
			else
			{
				wcscat_s(tcHDDBuff, Buffer);
				wcscat_s(tcHDDBuff, TEXT(" "));
				wsprintf(tcHDDCostBuffer, TEXT("Rs. %d"), iHDDFinalCost);
			}
		}
	}
	
	GetDlgItemText(hWndDlg, ID_CBOX_MONITOR_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcMonitorBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcMonitorBuff, Buffer);
		wcscat_s(tcMonitorBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_CBOX_MONITOR_SCREENSIZE, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcMonitorBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcMonitorBuff, Buffer);
			wcscat_s(tcMonitorBuff, TEXT(" "));

			GetDlgItemText(hWndDlg, ID_CBOX_MONITOR_RESOLUTION, Buffer, sizeof(Buffer));
			if (wcscmp(Buffer, TEXT("Select the component")) == 0)
			{
				wcscpy_s(tcMonitorBuff, TEXT(" - "));
			}
			else
			{
				wcscat_s(tcMonitorBuff, Buffer);
				wcscat_s(tcMonitorBuff, TEXT(" "));
				wsprintf(tcMonitorCostBuffer, TEXT("Rs. %d"), iMonitorFinalCost);
			}
		}
	}

	
	GetDlgItemText(hWndDlg, ID_CBOX_OPTICAL_DRIVE_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcDVDBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcDVDBuff, Buffer);
		wcscat_s(tcDVDBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_CBOX_OPTICAL_DRIVE_SPEED, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcDVDBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcDVDBuff, Buffer);
			wcscat_s(tcDVDBuff, TEXT(" "));
			wsprintf(tcDVDCostBuffer, TEXT("Rs. %d"), iDVDROMFinalCost);
		}
	}

	

	GetDlgItemText(hWndDlg, ID_CBOX_POWERSUPPLY_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcSMPSBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcSMPSBuff, Buffer);
		wcscat_s(tcSMPSBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_CBOX_POWERSUPPLY_CAPACITY, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcSMPSBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcSMPSBuff, Buffer);
			wcscat_s(tcSMPSBuff, TEXT(" "));
			wsprintf(tcSMPSCostBuffer, TEXT("Rs. %d"), iSMPSFinalCost);
		}
	}
	

	GetDlgItemText(hWndDlg, ID_CBOX_CABINET_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscpy_s(tcCabinetBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcCabinetBuff, Buffer);
		wcscat_s(tcCabinetBuff, TEXT(" "));

		GetDlgItemText(hWndDlg, ID_CBOX_CABINET_FORMFACTOR, Buffer, sizeof(Buffer));
		if (wcscmp(Buffer, TEXT("Select the component")) == 0)
		{
			wcscpy_s(tcCabinetBuff, TEXT(" - "));
		}
		else
		{
			wcscat_s(tcCabinetBuff, Buffer);
			wcscat_s(tcCabinetBuff, TEXT(" "));
			wsprintf(tcCabinetCostBuffer, TEXT("Rs. %d"), iCabinetFinalCost);
		}
	}

	

	GetDlgItemText(hWndDlg, ID_CBOX_KEYBOARD_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscat_s(tcKeyboardBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcKeyboardBuff, Buffer);
		wcscat_s(tcKeyboardBuff, TEXT(" "));
		wsprintf(tcKeyboardCostBuffer, TEXT("Rs. %d"), iKeyboardFinalCost);
	}

	/*GetDlgItemText(hWndDlg, ID_CBOX_KEYBOARD_INTERFACE, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscat_s(tcKeyboardBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcKeyboardBuff, Buffer);
		wcscat_s(tcKeyboardBuff, TEXT(" "));
	}*/

	GetDlgItemText(hWndDlg, ID_CBOX_MOUSE_VENDOR, Buffer, sizeof(Buffer));
	if (wcscmp(Buffer, TEXT("Select the component")) == 0)
	{
		wcscat_s(tcMouseBuff, TEXT(" - "));
	}
	else
	{
		wcscat_s(tcMouseBuff, Buffer);
		wcscat_s(tcMouseBuff, TEXT(" "));
		wsprintf(tcMouseCostBuffer, TEXT("Rs. %d"), iMouseFinalCost);
	}

	iTotalCost = iCPUFinalCost + iMotherboardFinalCost + iGPUFinalCost + iRAMFinalCost + iCabinetFinalCost + iHDDFinalCost + iDVDROMFinalCost + iSMPSFinalCost + iKeyboardFinalCost + iMonitorFinalCost + iMouseFinalCost;
	wsprintf(tcTotalCost, TEXT("Rs. %d"), iTotalCost);
	//GetDlgItemText(hWndDlg, ID_CBOX_MOUSE_TYPE, Buffer, sizeof(Buffer));
}

