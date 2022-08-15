// main.cpp

#include "GameInfo.h"
#include "GameManager.h"

static bool s_bLoop = true;

HWND  g_hMainWnd;
POINT g_ptMainRes = { 1280, 720 };

ATOM                       MyRegisterClass(HINSTANCE _hInst);
BOOL                       InitInstance(HINSTANCE _hInst, int _nCmdShow);
static LRESULT CALLBACK    WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);


int APIENTRY wWinMain(_In_ HINSTANCE _hInst,
    _In_opt_ HINSTANCE _hPrevInst,
    _In_ LPWSTR _lpCmdLine,
    _In_ int _nCmdShow)
{
    MyRegisterClass(_hInst);
    InitInstance(_hInst, SW_SHOW);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(9688);

    GameManager::getInst()->init(_hInst, g_hMainWnd, g_ptMainRes);

    MSG msg;
    while (s_bLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            GameManager::getInst()->logic();
        }
    }

    return 0;
}

ATOM MyRegisterClass(HINSTANCE _hInst)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; 
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = LoadIcon(_hInst, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"GameFramework";
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE _hInst, int _nCmdShow)
{
    g_hMainWnd = CreateWindowW(L"GameFramework", L"GameFramework", WS_OVERLAPPEDWINDOW,
        0, 0, g_ptMainRes.x, g_ptMainRes.y, nullptr, nullptr, _hInst, nullptr);

    if (!g_hMainWnd)
    {
        return FALSE;
    }

    RECT rc = { 0, 0, g_ptMainRes.x, g_ptMainRes.y };

    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
    SetWindowPos(g_hMainWnd, nullptr, 0, 0, rc.right - rc.left, rc.bottom - rc.top, 0);

    ShowWindow(g_hMainWnd, _nCmdShow);
    UpdateWindow(g_hMainWnd);

    return true;
}

LRESULT WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_DESTROY:
        s_bLoop = false; 
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return LRESULT();
}
