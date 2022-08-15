// GameManager.h

#pragma once
class GameManager
{
    SINGLETON(GameManager);

public:
    bool init(HINSTANCE _hInst, HWND _hWnd, POINT _ptMainRes);

    void logic();
    bool update();
    bool postUpdate();
    bool collision();
    bool render(HDC _dc);

    HINSTANCE getMainInst() { return m_hMainInst; }

    HWND getMainWnd() { return m_hMainWnd; }

    POINT getMainRes() { return m_ptMainRes; }

    HDC getMainDC() { return m_hDC; }

    HBRUSH getGreenBrush() const { return m_hGreenBrush; }
    
    HBRUSH getRedBrush() const { return m_hRedBrush; }

    HBRUSH getYellowBrush() const { return m_hYellowBrush; }

    HPEN getGreenPen() const { return m_hGreenPen; }
     
    HPEN getRedPen() const { return m_hRedPen; }

    void setEditorMode(bool _bEditorMode) { m_bEditorMode = _bEditorMode; }
    bool isEditorMode() { return m_bEditorMode; }

private:
    HINSTANCE           m_hMainInst;
    HWND                m_hMainWnd;
    POINT               m_ptMainRes;
    HDC                 m_hDC;

    HDC                 m_hBackDC;
    HBITMAP             m_hBackBmp;
    HBITMAP             m_hPreBackBmp;
    HBRUSH              m_hDefaultBrush;

    HBRUSH              m_hGreenBrush;
    HBRUSH              m_hRedBrush;
    HBRUSH              m_hYellowBrush;
    HPEN                m_hGreenPen;
    HPEN                m_hRedPen;

    bool                m_bEditorMode;
};
