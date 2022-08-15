// UIWidgetText.cpp

#include "../GameInfo.h"
#include "UIWidgetText.h"
#include "../Resource/ResourceManager.h"

UIWidgetText::UIWidgetText()
	: m_strText{}
	, m_nTextCount(0)
	, m_nTextCapacity(32)
	, m_eTextColor(RGB(0, 0, 0))
{
	m_strText = new TCHAR[m_nTextCapacity];
	memset(m_strText, 0, sizeof(TCHAR) * m_nTextCapacity);
}

UIWidgetText::UIWidgetText(const UIWidgetText& _Other)
	: UIWidget(_Other)
{
	m_nTextCount = _Other.m_nTextCount;
	m_nTextCapacity = _Other.m_nTextCapacity;
	m_eTextColor = _Other.m_eTextColor;
	m_pFont = _Other.m_pFont;

	m_strText = new TCHAR[m_nTextCapacity];
	memset(m_strText, 0, sizeof(TCHAR) * m_nTextCapacity);
	memcpy(m_strText, _Other.m_strText, sizeof(TCHAR) * m_nTextCount);
}

UIWidgetText::~UIWidgetText()
{
	SAFE_DELETE_ARRAY(m_strText);
}

UIWidgetText* UIWidgetText::Clone()
{
	return new UIWidgetText(*this);
}

bool UIWidgetText::init()
{
	m_pFont = ResourceManager::getInst()->findFont(L"DefaultFont");

	return true;
}

void UIWidgetText::update()
{
}

void UIWidgetText::postUpdate()
{
}

void UIWidgetText::collision()
{
}

void UIWidgetText::render(HDC _hDC)
{
	m_pFont->setFont(_hDC);
	SetBkMode(_hDC, TRANSPARENT);
	::SetTextColor(_hDC, m_eTextColor);
	TextOut(_hDC, (int)m_vPos.x, (int)m_vPos.y, m_strText, m_nTextCount);
	m_pFont->resetFont(_hDC);
}

void UIWidgetText::render(const Vec& _vPos, HDC _hDC)
{
	m_pFont->setFont(_hDC);
	SetBkMode(_hDC, TRANSPARENT);
	::SetTextColor(_hDC, m_eTextColor);
	TextOut(_hDC, (int)_vPos.x, (int)_vPos.y, m_strText, m_nTextCount);
	m_pFont->resetFont(_hDC);
}

void UIWidgetText::setText(const TCHAR* _strText)
{
	int nLength = lstrlen(_strText);

	if (m_nTextCapacity < nLength + 1)
	{
		m_nTextCapacity = nLength + 1;
		SAFE_DELETE_ARRAY(m_strText);
		m_strText = new TCHAR[m_nTextCapacity];
		memset(m_strText, 0, sizeof(TCHAR) * m_nTextCapacity);
	}
	lstrcpy(m_strText, _strText);
	m_nTextCount = lstrlen(_strText);
}

void UIWidgetText::addText(const TCHAR* _strText)
{
	int nLength = m_nTextCount + lstrlen(_strText);
	if (m_nTextCapacity < nLength + 1)
	{
		m_nTextCapacity = nLength + 1;
		SAFE_DELETE_ARRAY(m_strText);
		m_strText = new TCHAR[m_nTextCapacity];
		memset(m_strText, 0, sizeof(TCHAR) * m_nTextCapacity);
	}
	lstrcat(m_strText, _strText);
	m_nTextCount = lstrlen(_strText);
}

void UIWidgetText::setFont(const wstring& _strName)
{
	m_pFont = ResourceManager::getInst()->findFont(_strName);
}