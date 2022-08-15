// GameManager.cpp

#include "GameInfo.h"
#include "GameManager.h"
#include "Timer.h"
#include "Scene/SceneManager.h"
#include "Scene/MainScene.h"
#include "Input.h"
#include "PathManager.h"
#include "Resource/ResourceManager.h"
#include "Collision/CollisionManager.h"
#include "Scene/SceneIntro.h"

GameManager::GameManager()
    : m_hMainInst(0)
    , m_hMainWnd(0)
    , m_ptMainRes{}
    , m_hDC(0)
    , m_hBackDC(0)
    , m_hBackBmp(0)
    , m_hPreBackBmp(0)
    , m_hDefaultBrush(0)
    , m_hGreenBrush(0)
    , m_hRedBrush(0)
    , m_hGreenPen(0)
    , m_hRedPen(0)
    , m_bEditorMode(false)
{
}

GameManager::~GameManager()
{
    SelectObject(m_hBackDC, m_hPreBackBmp);
    DeleteObject(m_hBackBmp);
    SelectObject(m_hBackDC, m_hDefaultBrush);
    DeleteDC(m_hBackDC);
    DeleteObject(m_hDefaultBrush);

    ReleaseDC(m_hMainWnd, m_hDC);

    DeleteObject(m_hGreenBrush);
    DeleteObject(m_hRedBrush);
    DeleteObject(m_hYellowBrush);
    DeleteObject(m_hGreenPen);
    DeleteObject(m_hRedPen);
}

bool GameManager::init(HINSTANCE _hInst, HWND _hWnd, POINT _ptMainRes)
{
    m_hMainInst = _hInst;
    m_hMainWnd = _hWnd;
    m_ptMainRes = _ptMainRes;
    m_hDC = GetDC(m_hMainWnd);

    Timer::getInst()->init();

    if (!PathManager::getInst()->init())
    {
        return false;
    }

    if (!ResourceManager::getInst()->init())
    {
        return false;
    }

    if (!CollisionManager::getInst()->init())
    {
        return false;
    }

    if (!Input::getInst()->init())
    {
        return false;
    }

    if (!SceneManager::getInst()->init())
    {
        return false;
    }

    SceneManager::getInst()->createScene<SceneIntro>();

    m_hBackDC = CreateCompatibleDC(m_hDC);
    m_hBackBmp = CreateCompatibleBitmap(m_hDC, m_ptMainRes.x, m_ptMainRes.y);
    m_hPreBackBmp = (HBITMAP)SelectObject(m_hBackDC, m_hBackBmp);
    
    HBRUSH hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
    m_hDefaultBrush = (HBRUSH)SelectObject(m_hBackDC, hBlackBrush);
    
    m_hGreenBrush = CreateSolidBrush(RGB(0, 255, 0));
    m_hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
    m_hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
    m_hGreenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
    m_hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

    return true;
}

void GameManager::logic()
{
    if (true == update())
    {
        return;
    }

    if (true == postUpdate())
    {
        return;
    }

    if (true == collision())
    {
        return;
    }

    if (true == render(m_hDC))
    {
        return;
    }
    
}

bool GameManager::update()
{
    bool bRes = SceneManager::getInst()->update();
    if (true == bRes)
    {
        return true;
    }
    Timer::getInst()->update();
    Input::getInst()->update();
    return bRes;
}

bool GameManager::postUpdate()
{
    return SceneManager::getInst()->postUpdate();
}

bool GameManager::collision()
{
    return SceneManager::getInst()->collision();
}

bool GameManager::render(HDC _dc)
{
    Rectangle(m_hBackDC, -1, -1, m_ptMainRes.x + 1, m_ptMainRes.y + 1);

    bool res = SceneManager::getInst()->render(m_hBackDC);

    BitBlt(m_hDC, 0, 0, (int)m_ptMainRes.x, (int)m_ptMainRes.y, m_hBackDC, 0, 0, SRCCOPY);

    return res;
}
