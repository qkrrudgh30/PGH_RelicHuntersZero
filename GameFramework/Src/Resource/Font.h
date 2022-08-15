// Font.h

#pragma once

#include "../Ref.h"

class Font :
    public Ref
{
public:
    Font();
    virtual ~Font();

    bool loadFont(const wstring& _strName, const TCHAR* _strFontName,
        int _nWidth = 10, int _nHeight = 10);
    void setFont(HDC _hDC);
    void resetFont(HDC _hDC);

private:
    LOGFONT m_FontInfo;
    HFONT   m_hFont;
    HFONT   m_hDefaultFont;

};

