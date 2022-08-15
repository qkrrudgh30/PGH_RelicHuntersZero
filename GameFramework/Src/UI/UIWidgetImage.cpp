// UIWidgetImage.cpp

#include "../GameInfo.h"
#include "UIWidgetImage.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "UIWindow.h"
#include "../Input.h"

UIWidgetImage::UIWidgetImage()
	: m_nFrameIndex(0)
	, m_fPlaytime(0.f)
	, m_fAniTime(0.f)
	, m_vOffset{}
{
}

UIWidgetImage::UIWidgetImage(const UIWidgetImage& _Other)
	: UIWidget(_Other)
{
	m_pTexture = _Other.m_pTexture;
	m_vecFrameData = _Other.m_vecFrameData;
	m_nFrameIndex = 0;
	m_fPlaytime = _Other.m_fPlaytime;
	m_fAniTime = 0.f;
}

UIWidgetImage::~UIWidgetImage()
{
}

bool UIWidgetImage::init()
{
	return true;
}

void UIWidgetImage::update()
{
}

void UIWidgetImage::postUpdate()
{
}

void UIWidgetImage::collision()
{
}

void UIWidgetImage::render(HDC _hDC)
{
	if (nullptr != m_pTexture)
	{
		Vec vPos = m_vPos + m_pOwnerWindow->getUIWindowPos();
		if (getObjName() == L"Mouse")
		{
			Vec vMousePos = Input::getInst()->getMouseCurPos();
			Vec vScale;
			vScale.x = (float)m_pTexture->getTextureWidth();
			vScale.y = (float)m_pTexture->getTextureHeight();
			vPos.x = vMousePos.x - vScale.x / 2.f;
			vPos.y = vMousePos.y - vScale.y / 2.f;
		}
		m_pTexture->render(_hDC, vPos, Vec(0.f, 0.f), m_vScale);
	}
}

void UIWidgetImage::render(const Vec& _vPos, HDC _hDC)
{
	if (nullptr != m_pTexture)
	{
		m_pTexture->render(_hDC, _vPos, Vec(0.f, 0.f), m_vScale);
	}
}


void UIWidgetImage::setImageTexture(const wstring& _strName)
{
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();
	}
}

void UIWidgetImage::setImageTexture(const wstring& _strName, const TCHAR* _strFileName, const wstring& _strPath)
{
	m_pOwnerScene->getSceneResource()->loadTexture(_strName, _strFileName, _strPath);
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();
	}
	int a = 100;
}

void UIWidgetImage::setImageTexture(const wstring& _strName, const TCHAR* _strFullPath)
{
	m_pOwnerScene->getSceneResource()->loadTexture(_strName, _strFullPath);
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();
	}
}

void UIWidgetImage::setImageTextureColorKey(unsigned char _r, unsigned char _g, unsigned char _b, size_t _uIdx)
{
	if (nullptr != m_pTexture)
	{
		m_pTexture->setTextureColorKey(_r, _g, _b, _uIdx);
	}
}

void UIWidgetImage::changeTexture(const wstring& _strName, const TCHAR* _strFileName, const wstring& _strPath)
{
	if (m_pTexture->getTextureFileName() == _strFileName)
	{
		return;
	}
	else
	{
		m_pTexture->loadTexture(_strName, _strFileName, _strPath);
	}
}

