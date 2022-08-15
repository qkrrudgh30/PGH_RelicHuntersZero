// UIWidgetProgressBar.cpp

#include "../GameInfo.h"
#include "UIWidgetProgressBar.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "UIWindow.h"

UIWidgetProgressBar::UIWidgetProgressBar()
	: m_fPercent(1.f)
{
}

UIWidgetProgressBar::UIWidgetProgressBar(const UIWidgetProgressBar& _Other)
	: UIWidget(_Other)
{
	m_fPercent = _Other.m_fPercent;
	m_pTexture = _Other.m_pTexture;
}

UIWidgetProgressBar::~UIWidgetProgressBar()
{
}

bool UIWidgetProgressBar::init()
{
	return true;
}

void UIWidgetProgressBar::update()
{
}

void UIWidgetProgressBar::postUpdate()
{
}

void UIWidgetProgressBar::collision()
{
}

void UIWidgetProgressBar::render(HDC _hDC)
{
	if (nullptr != m_pTexture)
	{
		Vec vPos = m_vPos + m_pOwnerWindow->getUIWindowPos();
		m_pTexture->render(_hDC, vPos, Vec(0.f, 0.f), m_vScale * Vec(m_fPercent, 1.f));
	}
}

void UIWidgetProgressBar::render(const Vec& _vPos, HDC _hDC)
{
	if (nullptr != m_pTexture)
	{
		m_pTexture->render(_hDC, _vPos, Vec(0.f, 0.f), m_vScale * Vec(m_fPercent, 1.f));
	}
}


void UIWidgetProgressBar::setImageTexture(const wstring& _strName)
{
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();
	}
}

void UIWidgetProgressBar::setImageTexture(const wstring& _strName, const TCHAR* _strFileName, const wstring& _strPath)
{
	m_pOwnerScene->getSceneResource()->loadTexture(_strName, _strFileName, _strPath);
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();
	}
}

void UIWidgetProgressBar::setImageTexture(const wstring& _strName, const TCHAR* _strFullPath)
{
	m_pOwnerScene->getSceneResource()->loadTexture(_strName, _strFullPath);
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();
	}
}

void UIWidgetProgressBar::setImageTextureColorKey(unsigned char _r, unsigned char _g, unsigned char _b, size_t _uIdx)
{
	if (nullptr != m_pTexture)
	{
		m_pTexture->setTextureColorKey(_r, _g, _b, _uIdx);
	}
}

