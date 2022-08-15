// UIWidgetText.h

#pragma once
#include "UIWidget.h"
#include "../Resource/Font.h"

class UIWidgetText :
    public UIWidget
{
public:
    UIWidgetText();
    UIWidgetText(const UIWidgetText& _Other);
    virtual ~UIWidgetText();

    virtual UIWidgetText* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);
    virtual void render(const Vec& _vPos, HDC _hDC);

    void setText(const TCHAR* _strText);
    void addText(const TCHAR* _strText);
    void popBack()
    {
        --m_nTextCount;
        m_strText[m_nTextCount] = 0;
    }
    void clear()
    {
        m_nTextCount = 0;
        memset(m_strText, 0, sizeof(TCHAR) * m_nTextCapacity);
    }
    
    int getTextCount() { return m_nTextCount; }

    void setTextColor(unsigned char _r, unsigned char _g, unsigned char _b) { m_eTextColor = RGB(_r, _g, _b); }

    void setFont(const wstring& _strName);

protected:
    TCHAR*          m_strText;
    int             m_nTextCount;
    int             m_nTextCapacity;
    COLORREF        m_eTextColor;
    SharedPtr<Font> m_pFont;

private:


};

