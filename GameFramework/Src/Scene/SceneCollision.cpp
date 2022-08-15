// SceneCollider.cpp

#include "../GameInfo.h"
#include "SceneCollision.h"
#include "../Collision/Collider.h"
#include "../Input.h"
#include "Scene.h"
#include "../UI/UIWindow.h"
#include "../UI/UIWidget.h"
#include "Camera.h"

SceneCollision::SceneCollision()
	: m_pOwnerScene(nullptr)
	, m_pMouseHoveredWidget(nullptr)
	, m_pMouseCollision(nullptr)
	, m_pSelectedWidget(nullptr)
{
	m_vecCollider.reserve(500);
	m_vecUIWindow.reserve(10);
}

SceneCollision::~SceneCollision()
{
}

int SceneCollision::sortY(const void* _pSrc, const void* _pDes)
{
	Collider* pSrcCollider = *(Collider**)_pSrc;
	Collider* pDesCollider = *(Collider**)_pDes;

	// Bottom 값을 구한다.
	float	SrcY = pSrcCollider->getBottom();
	float	DesY = pDesCollider->getBottom();

	if (SrcY < DesY)
	{
		return -1;
	}
	else if (SrcY > DesY)
	{
		return 1;
	}
	return 0;
}

void SceneCollision::collision()
{
	size_t uSize = m_vecCollider.size();
	if (uSize <= 1)
	{
		m_vecCollider.clear();
		return;
	}

	for (size_t i = 0; i < uSize - 1; ++i)
	{
		Collider* pSrc = m_vecCollider[i];
		for (size_t j = i + 1; j < uSize; ++j)
		{
			Collider* pDes = m_vecCollider[j];
			if (pSrc->getOwnerObject() == pDes->getOwnerObject())
			{
				continue;
			}

			CollisionProfile* pSrcProfile = pSrc->getProfile();
			CollisionProfile* pDesProfile = pDes->getProfile();

			ECOLLISION_STATE eSrcState = pSrcProfile->vecState[pDesProfile->eChannel];
			ECOLLISION_STATE eDesState = pDesProfile->vecState[pSrcProfile->eChannel];

			if (eSrcState == ECOLLISION_STATE::NONCOLLISION ||
				eDesState == ECOLLISION_STATE::NONCOLLISION)
			{
				continue;
			}

			if (pSrc->collision(pDes))
			{
				if (!pSrc->checkCollisionList(pDes))
				{
					pSrc->addCollisionList(pDes);
					pDes->addCollisionList(pSrc);

					pSrc->callCollisionBeginFunc(pDes);
					pDes->callCollisionBeginFunc(pSrc);
				}
			}
			else if (pSrc->checkCollisionList(pDes))
			{
				pSrc->deleteCollisionList(pDes);
				pDes->deleteCollisionList(pSrc);

				pSrc->callCollisionEndFunc(pDes);
				pDes->callCollisionEndFunc(pSrc);
			}

		}
	}

	m_vecCollider.clear();
	m_vecUIWindow.clear();
}

void SceneCollision::collisionMouse()
{
	Vec vMousePos = Input::getInst()->getMouseCurPos();
	Vec vMouseWorldPos = vMousePos + m_pOwnerScene->getCamera()->getCameraLT();

	int nWidgetCount = 0;
	size_t uWindowCount = m_vecUIWindow.size();
	for (size_t i = 0; i < uWindowCount; ++i)
	{
		nWidgetCount += m_vecUIWindow[i]->getUIWindowWidgetCount();
	}

	vector<UIWidget*> vecWidget;
	vecWidget.resize(nWidgetCount);
	int nWidgetOffset = 0;
	
	if (nullptr != m_pSelectedWidget)
	{
		vecWidget[nWidgetOffset] = m_pSelectedWidget;
		++nWidgetOffset;
	}

	for (size_t i = 0; i < uWindowCount; ++i)
	{
		int nCount = m_vecUIWindow[i]->getUIWindowWidgetCount();
		for (int j = 0; j < nCount; ++j)
		{
			UIWidget* pWidget = m_vecUIWindow[i]->getUIWidget(j);
			if (pWidget != m_pSelectedWidget)
			{
				vecWidget[nWidgetOffset] = pWidget;
				++nWidgetOffset;
			}
		}
	}

	bool bEnableCollision = false;
	for (int i = 0; i < nWidgetCount; ++i)
	{
		if (true == vecWidget[i]->collisionMouse(vMousePos))
		{
			if (nullptr != m_pMouseHoveredWidget && vecWidget[i] != m_pMouseHoveredWidget)
			{
				m_pMouseHoveredWidget->collisionMouseReleasedCallback();
			}

			if (nullptr != m_pMouseCollision)
			{
				m_pMouseCollision->setMouseCollision(false);
				m_pMouseCollision = nullptr;
			}

			m_pMouseHoveredWidget = vecWidget[i];
			bEnableCollision = true;
			break;
		}
	}


	if (false == bEnableCollision)
	{
		if (nullptr != m_pMouseHoveredWidget)
		{
			m_pMouseHoveredWidget->collisionMouseReleasedCallback();
			m_pMouseHoveredWidget = nullptr;
		}
		if (nullptr != m_pSelectedWidget)
		{
			m_pSelectedWidget = nullptr;
		}

		size_t uSize = m_vecCollider.size();
		if (uSize > 1)
		{
			qsort(&m_vecCollider[0], (size_t)uSize, sizeof(Collider*), SceneCollision::sortY);

			bool bMouseCollision = false;
			for (size_t i = 0; i < uSize; ++i)
			{
				if (m_vecCollider[i]->collisionMouse(vMouseWorldPos))
				{
					if (nullptr != m_pMouseCollision)
					{
						m_pMouseCollision->setMouseCollision(false);
					}
					m_pMouseCollision = m_vecCollider[i];
					m_pMouseCollision->setMouseCollision(true);

					bMouseCollision = true;
				}
			}

			if (false == bMouseCollision)
			{
				if (nullptr != m_pMouseCollision)
				{
					m_pMouseCollision->setMouseCollision(false);
					m_pMouseCollision = nullptr;
				}
			}
		}
	}

}

void SceneCollision::addCollider(Collider* _pCollider)
{
	m_vecCollider.push_back(_pCollider);
}

void SceneCollision::addUIWindow(UIWindow* _pWindow)
{
	m_vecUIWindow.push_back(_pWindow);
}
