#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#define _WIN32_IE 0x0600
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

WCHAR		szWindowClass[] = L"mygui_0";
WCHAR		szTitle[] = L"�ҵĴ���Ӵ";
HINSTANCE	hInstance;
DWORD		dwErr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	// ȷ�� CommonControls ����ȷ��ʼ��
	INITCOMMONCONTROLSEX initcc = { 0 };
	initcc.dwSize = sizeof(initcc);
	initcc.dwICC = 0;
	
	if (!InitCommonControlsEx(&initcc))
	{
		MessageBoxW(NULL, L"��ʼ�� CommonControls ʧ��", L"������", MB_OK);
		return -1;
	}

	MessageBoxW(NULL, L"��ʼ�� CommonControls�ɹ� ^_^", L"��ϲ", MB_OK);

	// ����������Լ��Ĵ�����
	
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;

	if (0 == RegisterClassExW(&wcex))
	{
		MessageBoxW(NULL, L"ע�ᴰ����ʧ��", L"������", MB_OK);
		return -1;
	}

	MessageBoxW(NULL, L"ע�ᴰ����ɹ� ^_^", L"��ϲ", MB_OK);

	// ��������

	HWND hWnd = CreateWindowExW(0L, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (NULL == hWnd)
	{
		dwErr = GetLastError();
		MessageBoxW(NULL, L"��������ʧ��", L"������", MB_OK);
		return -1;
	}

	MessageBoxW(NULL, L"��������ɹ� ^_^", L"��ϲ", MB_OK);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ������Ϣѭ������������

	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_CREATE)
	{
		// �����ؼ�

		HWND hButton = CreateWindowEx(0L, L"BUTTON", L"����ѽ", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10, 10, 100, 32, hWnd, NULL, hInstance, NULL);

		// ��������

		HFONT hFont = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, GB2312_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, L"΢���ź�");
		if (hFont == NULL)
		{
			MessageBoxW(NULL, L"��������ʧ��", L"������", MB_OK);
		}
		else
		{
			SendMessageW(hWnd, WM_SETFONT, (WPARAM)hFont, TRUE);
			SendMessageW(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
		}
	}
	else if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	else if (message == WM_COMMAND)
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		if (wmId == BN_CLICKED)
		{
			MessageBoxW(hWnd, L"��⵽�û����", L"�¼�", MB_OK);
		}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}