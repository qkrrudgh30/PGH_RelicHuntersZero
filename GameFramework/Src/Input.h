// Input.h

#pragma once

#include "UI/UIWidgetImage.h"

enum EMOUSETYPE
{
    MOUSETYPE_DEFAULT,
    MOUSETYPE_BATTLE,
    MOUSETYPE_END
};

struct KeyState
{
    int     key;
    bool    state[KeyState_Max];

    KeyState()
        : key(0)
        , state{}
    {}
};

struct KeyInfo
{
    wstring          m_strKeyName;
    KeyState         m_keyState;
    // return type: void
    // parameter type: void
    function<void()> m_fpCallback[KeyState_Max];
    bool             m_bCtrl;
    bool             m_bAlt;
    bool             m_bShift;

    KeyInfo()
        : m_bCtrl(false)
        , m_bAlt(false)
        , m_bShift(false)
    {}
};

class Input
{
    SINGLETON(Input);

public:
    bool init();
    void update();
    void updateKeyState();
    void updateKeyInfo();
    void updateMouse();

    bool createKey(const wstring& _strName, int _nKey);
    
    template <typename T>
    void setCallback(const wstring& _strName, EKeyState _state, T* _Obj, void(T::* _mFunc)());
    void clearCallback();

    bool isCtrlDown() { return m_bCtrl; }
    bool setCtrlKey(const wstring& _strName, bool _bState);

    bool isAltDown() { return m_bAlt; }
    bool setAltKey(const wstring& _strName, bool _bState);

    bool isShiftDown() { return m_bShift; }
    bool setShiftKey(const wstring& _strName, bool _bState);

    Vec getMouseCurPos() { return m_vMouseCurPos; }
    Vec getMousePrePos() { return m_vMousePrePos; }
    Vec getMouseDisplacement() { return m_vMouseDisplacement; }

    bool isMouseNone() { return m_bMouseNone; }
    bool isMouseDown() { return m_bMouseDown; }
    bool isMouseHold() { return m_bMouseHold; }
    bool isMouseAway() { return m_bMouseAway; }

    void setShowCursor(bool _bShowCursor) { m_bShowCursor = _bShowCursor; }
    bool isShowCursor() { return m_bShowCursor; }

private:
    unordered_map<wstring, KeyInfo*>    m_mapKeyInfo;
    vector<KeyState>                    m_vecKeyState;
    vector<int>                         m_vecAddKey;

    bool                                m_bCtrl;
    bool                                m_bAlt;
    bool                                m_bShift;

    Vec                                 m_vMouseCurPos;
    Vec                                 m_vMousePrePos;
    Vec                                 m_vMouseDisplacement;

    HWND                                m_hWnd;
    bool                                m_bMouseNone;
    bool                                m_bMouseDown;
    bool                                m_bMouseHold;
    bool                                m_bMouseAway;
    bool                                m_bShowCursor;
     
    SharedPtr<UIWidgetImage>            m_pMouseImage;
    EMOUSETYPE                          m_eMouseType;

    KeyInfo* findKeyInfo(const wstring& _strName);

};

template<typename T>
inline void Input::setCallback(const wstring& _strName, EKeyState _state, T* _Obj, void(T::* _mFunc)())
{
    KeyInfo* info = findKeyInfo(_strName);
    info->m_fpCallback[_state] = bind(_mFunc, _Obj);
    // info->m_fpCallback[_state] = bind(_mFunc, _Obj, placeholders::_1);
    // 만약 등록할 함수 포인터가 인자 하나를 강제로 받게끔 하려면, placeholder 사용.
}
