// Input.cpp

#include "GameInfo.h"
#include "Input.h"
#include "GameManager.h"
#include "Resource/ResourceManager.h"

Input::Input()
    : m_vMouseCurPos{}
    , m_vMousePrePos{}
    , m_vMouseDisplacement{}
    , m_hWnd(0)
{
    m_vecKeyState.resize(KEYCOUNT_MAX);
    for (int i = 0; i < KEYCOUNT_MAX; ++i)
    {
        m_vecKeyState[i].key = i;
    }

    m_bCtrl = false;
    m_bAlt = false;
    m_bShift = false;

    m_bMouseNone = true;
    m_bMouseDown = false;
    m_bMouseHold = false;
    m_bMouseAway = false;
}

Input::~Input()
{
    auto iter = m_mapKeyInfo.begin();
    auto iterEnd = m_mapKeyInfo.end();

    for (; iter != iterEnd;)
    {
        SAFE_DELETE(iter->second);
        ++iter;
    }
}

bool Input::init()
{
    createKey(L"moveUp", 'W');
    createKey(L"moveDown", 'S');
    createKey(L"moveLeft", 'A');
    createKey(L"moveRight", 'D');
    createKey(L"fireBullet", VK_LBUTTON);
    // setCtrlKey(L"fireBullet", true); ctrl을 같이 눌러야 총알나가 짐.

    createKey(L"pause", 'P');
    setCtrlKey(L"pause", true);
    createKey(L"resume", 'R');
    setCtrlKey(L"resume", true);

    createKey(L"timeStop", '1');
    createKey(L"setSpawnPoint", '2');

    createKey(L"Editor", VK_F1);
    createKey(L"MouseLButton", VK_LBUTTON);
    createKey(L"MouseRButton", VK_RBUTTON);
    createKey(L"CameraTargetOn", VK_SPACE);


    return true;
}

void Input::update()
{
    /*
    RECT	rc;
    GetClientRect(m_hWnd, &rc);

    POINT	ptMouse;
    GetCursorPos(&ptMouse);
    ScreenToClient(m_hWnd, &ptMouse);

    if (rc.left <= ptMouse.x && ptMouse.x <= rc.right &&
        rc.top <= ptMouse.y && ptMouse.y <= rc.bottom)
    {
        if (isShowCursor())
        {
            setShowCursor(false);
            ShowCursor(FALSE);
        }
    }

    else
    {
        if (!isShowCursor())
        {
            setShowCursor(true);
            ShowCursor(TRUE);
        }
    }
    */

    HWND hMainWnd = GameManager::getInst()->getMainWnd();
    HWND hWnd = GetFocus();

    if (nullptr != hWnd)
    {
        updateKeyState();

        updateMouse();

        updateKeyInfo();
    }
    

}

void Input::updateKeyState()
{
    size_t uSize = m_vecAddKey.size();
    for (size_t i = 0; i < uSize; ++i)
    {
        int nKey = m_vecAddKey[i];
        if (GetAsyncKeyState(nKey) & 0x8000)
        {
            if (!m_vecKeyState[nKey].state[KeyState_Down] &&
                !m_vecKeyState[nKey].state[KeyState_Hold])
            {
                // 지금 눌렀고, 이전은 안누름.
                m_vecKeyState[nKey].state[KeyState_Down] = true;
                m_vecKeyState[nKey].state[KeyState_Hold] = true;
            }
            else
            {
                // 지금 눌렀고, 이전도 누름
                m_vecKeyState[nKey].state[KeyState_Down] = false;
                m_vecKeyState[nKey].state[KeyState_Hold] = true;
            }

        }
        else if (m_vecKeyState[nKey].state[KeyState_Hold])
        {
            // 지금 안눌렀고, 이전에 누름
            m_vecKeyState[nKey].state[KeyState_Down] = false;
            m_vecKeyState[nKey].state[KeyState_Hold] = false;
            m_vecKeyState[nKey].state[KeyState_Away] = true;
        }
        else if (m_vecKeyState[nKey].state[KeyState_Away])
        {
            // 지금 안눌렀고, 이전에도 안누름
            m_vecKeyState[nKey].state[KeyState_Down] = false;
            m_vecKeyState[nKey].state[KeyState_Hold] = false;
            m_vecKeyState[nKey].state[KeyState_Away] = false;
        }
    }

    if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
    {
        m_bCtrl = true;
    }
    else
    {
        m_bCtrl = false;
    }

    if (GetAsyncKeyState(VK_MENU) & 0x8000)
    {
        m_bAlt = true;
    }
    else
    {
        m_bAlt = false;
    }

    if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
    {
        m_bShift = true;
    }
    else
    {
        m_bShift = false;
    }
}

void Input::updateKeyInfo()
{
    auto iter = m_mapKeyInfo.begin();
    auto iterEnd = m_mapKeyInfo.end();

    for (; iter != iterEnd;)
    {
        int nKey = iter->second->m_keyState.key;
        if (m_vecKeyState[nKey].state[KeyState_Down] &&
            iter->second->m_bCtrl == m_bCtrl &&
            iter->second->m_bAlt == m_bAlt &&
            iter->second->m_bShift == m_bShift)
        {
            if (iter->second->m_fpCallback[KeyState_Down])
            {
                iter->second->m_fpCallback[KeyState_Down]();
            }
        }

        if (m_vecKeyState[nKey].state[KeyState_Hold] &&
            iter->second->m_bCtrl == m_bCtrl &&
            iter->second->m_bAlt == m_bAlt &&
            iter->second->m_bShift == m_bShift)
        {
            if (iter->second->m_fpCallback[KeyState_Hold])
            {
                iter->second->m_fpCallback[KeyState_Hold]();
            }
        }

        if (m_vecKeyState[nKey].state[KeyState_Away] &&
            iter->second->m_bCtrl == m_bCtrl &&
            iter->second->m_bAlt == m_bAlt &&
            iter->second->m_bShift == m_bShift)
        {
            if (iter->second->m_fpCallback[KeyState_Away])
            {
                iter->second->m_fpCallback[KeyState_Away]();
            }
        }

        ++iter;
    }
}

void Input::updateMouse()
{
    POINT ptMousePos;
    GetCursorPos(&ptMousePos);
    ScreenToClient(GameManager::getInst()->getMainWnd(), &ptMousePos);

    Vec vCurMousePos;
    vCurMousePos.x = (float)ptMousePos.x;
    vCurMousePos.y = (float)ptMousePos.y;

    m_vMouseCurPos = vCurMousePos;

    m_vMouseDisplacement = m_vMouseCurPos - m_vMousePrePos;

    m_vMousePrePos = m_vMouseCurPos;

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
    {
        if (false == m_bMouseDown && false == m_bMouseHold)
        {
            m_bMouseNone = false;
            m_bMouseDown = true;
            m_bMouseHold = false;
            m_bMouseAway = false;
        }
        else if (true == m_bMouseDown && false == m_bMouseHold)
        {
            m_bMouseNone = false;
            m_bMouseDown = false;
            m_bMouseHold = true;
            m_bMouseAway = false;
        }
    }
    else
    {
        if (false == m_bMouseDown && false == m_bMouseHold)
        {
            m_bMouseNone = true;
            m_bMouseDown = false;
            m_bMouseHold = false;
            m_bMouseAway = false;
        }
        else if (true == m_bMouseDown || true == m_bMouseHold)
        {
            m_bMouseNone = false;
            m_bMouseDown = false;
            m_bMouseHold = false;
            m_bMouseAway = true;
        }
    }
}

bool Input::createKey(const wstring& _strName, int _nKey)
{
    KeyInfo* info = findKeyInfo(_strName);

    if (info)
    {
        return false;
    }

    info = new KeyInfo;
    info->m_strKeyName = _strName;
    info->m_keyState.key = _nKey;

    m_mapKeyInfo.insert(make_pair(_strName, info));

    bool res = false;
    size_t uSize = m_vecAddKey.size();
    for (size_t i = 0; i < uSize; ++i)
    {
        if (m_vecAddKey[i] == _nKey)
        {
            res = true;
            break;
        }
    }

    if (!res)
    {
        m_vecAddKey.push_back(_nKey);
    }

    return true;
}

void Input::clearCallback()
{
    auto iter = m_mapKeyInfo.begin();
    auto endIter = m_mapKeyInfo.begin();
    for (; iter != endIter;)
    {
        for (int i = 0; i < KeyState_Max; ++i)
        {
            iter->second->m_fpCallback[i] = nullptr;
        }
        ++iter;
    }
}

bool Input::setCtrlKey(const wstring& _strName, bool _bState)
{
    KeyInfo* info = findKeyInfo(_strName);

    if (!info)
    {
        return false;
    }

    info->m_bCtrl = _bState;

    return true;
}

bool Input::setAltKey(const wstring& _strName, bool _bState)
{
    KeyInfo* info = findKeyInfo(_strName);

    if (!info)
    {
        return false;
    }

    info->m_bAlt = _bState;

    return true;
}

bool Input::setShiftKey(const wstring& _strName, bool _bState)
{
    KeyInfo* info = findKeyInfo(_strName);

    if (!info)
    {
        return false;
    }

    info->m_bShift = _bState;

    return true;
}

KeyInfo* Input::findKeyInfo(const wstring& _strName)
{
    unordered_map<wstring, KeyInfo*>::iterator iter;
    iter = m_mapKeyInfo.find(_strName);

    if (iter == m_mapKeyInfo.end())
    {
        return nullptr;
    }

    return iter->second;
}
