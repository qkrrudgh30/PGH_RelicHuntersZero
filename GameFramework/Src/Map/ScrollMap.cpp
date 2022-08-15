
#include "../GameInfo.h"
#include "ScrollMap.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"

ScrollMap::ScrollMap()
	: m_vScrollRatio(1.f, 1.f)
	, m_bLoop(false)
{
}

ScrollMap::~ScrollMap()
{
}

bool ScrollMap::init()
{
	MapBase::init();
	return true;
}

void ScrollMap::update()
{
	MapBase::update();
}

void ScrollMap::postUpdate()
{
	MapBase::postUpdate();
}

void ScrollMap::preRender()
{
	MapBase::preRender();
}

void ScrollMap::render(HDC _hDC)
{
	MapBase::render(_hDC);


	if (m_pScollTexture)
	{
		Camera* pCamera = m_pOwnerScene->getCamera();

		Vec Resolution = pCamera->getCameraResolution();

		if (!m_bLoop)
		{

			Vec ImagePos = pCamera->getCameraPos() * m_vScrollRatio;

			unsigned int	Width = m_pScollTexture->getTextureWidth();
			unsigned int	Height = m_pScollTexture->getTextureHeight();

			ImagePos.x = ImagePos.x < 0.f ? 0.f : ImagePos.x;
			ImagePos.x = ImagePos.x + Resolution.x > Width ? Width - Resolution.x : ImagePos.x;

			ImagePos.y = ImagePos.y < 0.f ? 0.f : ImagePos.y;
			ImagePos.y = ImagePos.y + Resolution.y > Height ? Height - Resolution.y : ImagePos.y;

			m_pScollTexture->render(_hDC, m_vPos, ImagePos, m_vScale);
		}

		else
		{
			Vec	CameraPos = pCamera->getCameraPos();

			Vec	ImagePos;

			int	XRatio = (int)(CameraPos.x / Resolution.x);
			int	YRatio = (int)(CameraPos.y / Resolution.y);

			// 화요일에 잘라서 이어붙이기.

			// 왼쪽 출력
			m_pScollTexture->render(_hDC, m_vPos, ImagePos, m_vScale);
		}
	}
}

void ScrollMap::start()
{
	MapBase::start();
}

void ScrollMap::save(FILE* _pFile)
{
}

void ScrollMap::load(FILE* _pFile)
{
}

void ScrollMap::setTexture(const wstring& Name, const TCHAR* FileName, const wstring& PathName)
{
	m_pOwnerScene->getSceneResource()->loadTexture(Name, FileName, PathName);

	setTexture(Name);
}

void ScrollMap::setTextureFullPath(const wstring& Name, const TCHAR* FullPath)
{
	m_pOwnerScene->getSceneResource()->loadTextureFullPath(Name, FullPath);

	setTexture(Name);
}

void ScrollMap::setTexture(const wstring& Name, const std::vector<wstring>& vecFileName, const wstring& PathName)
{
	m_pOwnerScene->getSceneResource()->loadTexture(Name, vecFileName, PathName);

	setTexture(Name);
}

void ScrollMap::setTexture(const wstring& Name)
{
	m_pScollTexture = m_pOwnerScene->getSceneResource()->findTexture(Name);
}

void ScrollMap::setTextureColorKey(const unsigned char r, const unsigned char g, const unsigned char b)
{
	if (m_pScollTexture)
	{
		m_pScollTexture->setTextureColorKey(r, g, b);
	}
}
