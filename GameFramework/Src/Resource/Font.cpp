// Font.cpp

#include "../GameInfo.h"
#include "Font.h"

Font::Font()
	: m_FontInfo{}
	, m_hFont(0)
	, m_hDefaultFont(0)
{
}

Font::~Font()
{
	if (0 != m_hFont)
	{
		DeleteObject(m_hFont);
	}
}

bool Font::loadFont(const wstring& _strName, const TCHAR* _strFontName, int _nWidth, int _nHeight)
{
	m_FontInfo.lfHeight = (LONG)_nHeight;
	m_FontInfo.lfWidth = (LONG)_nWidth;
	m_FontInfo.lfCharSet = HANGEUL_CHARSET;
	m_FontInfo.lfWeight = FW_NORMAL;
	m_FontInfo.lfItalic = 0;
	// m_FontInfo.lfEscapement = 1;
	m_FontInfo.lfUnderline = 0;
	m_FontInfo.lfStrikeOut = 0;
	m_FontInfo.lfPitchAndFamily = 2;

	lstrcpy(m_FontInfo.lfFaceName, _strFontName);
	m_hFont = CreateFontIndirect(&m_FontInfo);
	return m_hFont ? true : false;
}

void Font::setFont(HDC _hDC)
{
	m_hDefaultFont = (HFONT)SelectObject(_hDC, m_hFont);
}

void Font::resetFont(HDC _hDC)
{
	SelectObject(_hDC, m_hDefaultFont);
}
