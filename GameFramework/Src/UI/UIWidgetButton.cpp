// UIWidgetButton.cpp

#include "../GameInfo.h"
#include "UIWidgetButton.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Input.h"
#include "UIWindow.h"

UIWidgetButton::UIWidgetButton()
	: m_pTexture(nullptr)
	, m_eCurButtonState(EBUTTON_STATE::ENABLE)
	, m_fpButtonMouseOnCallback(nullptr)
	, m_fpButtonClickCallback(nullptr)
{
}

UIWidgetButton::UIWidgetButton(const UIWidgetButton& _Other)
	: UIWidget(_Other)
{
	*this = _Other;
}

UIWidgetButton::~UIWidgetButton()
{
}

bool UIWidgetButton::init()
{
	return true;
}

void UIWidgetButton::update()
{
	if (EBUTTON_STATE::DISABLE != m_eCurButtonState)
	{
		
		if (true == m_bMouseHovered)
		{
			if (true == Input::getInst()->isMouseHold())
			{
				m_eCurButtonState = EBUTTON_STATE::MOUSE_CLICK;
			}
			else if (EBUTTON_STATE::MOUSE_CLICK == m_eCurButtonState &&
				Input::getInst()->isMouseAway())
			{
				if (nullptr != m_fpButtonClickCallback)
				{
					if (m_arrButtonSound[1])
					{
						m_arrButtonSound[1]->play();
					}
					m_fpButtonClickCallback();
				}
				
				m_eCurButtonState = EBUTTON_STATE::MOUSE_ON;
			}
			else if (EBUTTON_STATE::MOUSE_CLICK == m_eCurButtonState &&
				Input::getInst()->isMouseDown())
			{
				m_eCurButtonState = EBUTTON_STATE::MOUSE_CLICK;
			}
			else
			{
				m_eCurButtonState = EBUTTON_STATE::MOUSE_ON;
				if (nullptr != m_fpButtonMouseOnCallback)
				{
					m_fpButtonMouseOnCallback();
				}
			}
			
		}
		else
		{
			m_eCurButtonState = EBUTTON_STATE::ENABLE;
		}
		
	}

	m_vScale = m_FrameData[(int)m_eCurButtonState].vScale;
}

void UIWidgetButton::postUpdate()
{
}

void UIWidgetButton::collision()
{
}

void UIWidgetButton::render(HDC _hDC)
{
	if (nullptr != m_pTexture)
	{
		Vec vPos = m_vPos + m_pOwnerWindow->getUIWindowPos();
		if (m_pTexture->getTextureType() == ETEXTURETYPE::ETEXTURETYPE_ATLAS)
		{
			m_pTexture->render(_hDC, vPos,
				m_FrameData[(int)m_eCurButtonState].vStartPos,
				m_FrameData[(int)m_eCurButtonState].vScale);
		}
		else
		{
			m_pTexture->render(_hDC, vPos,
				Vec(0.f, 0.f),
				m_vScale,
				(int)m_eCurButtonState);
		}
	}
}

void UIWidgetButton::render(const Vec& _vPos, HDC _hDC)
{
	if (nullptr != m_pTexture)
	{
		Vec vPos = _vPos + m_pOwnerWindow->getUIWindowPos();
		m_pTexture->render(_hDC, vPos, Vec(0.f, 0.f), m_vScale);
	}
}

void UIWidgetButton::setButtonTexture(const wstring& _strName)
{
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();
		for (int i = 0; i < (int)EBUTTON_STATE::END; ++i)
		{
			m_FrameData[i].vScale = m_vScale;
		}
	}
}

void UIWidgetButton::setButtonTexture(const wstring& _strName, const TCHAR* _strFileName, const wstring& _strPath)
{
	m_pOwnerScene->getSceneResource()->loadTexture(_strName, _strFileName, _strPath);
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();

		for (int i = 0; i < (int)EBUTTON_STATE::END; ++i)
		{
			m_FrameData[i].vScale = m_vScale;
		}
	}
}

void UIWidgetButton::setButtonTexture(const wstring& _strName, const TCHAR* _strFullPath)
{
	m_pOwnerScene->getSceneResource()->loadTexture(_strName, _strFullPath);
	m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
	if (nullptr != m_pTexture)
	{
		m_vScale.x = (float)m_pTexture->getTextureWidth();
		m_vScale.y = (float)m_pTexture->getTextureHeight();

		for (int i = 0; i < (int)EBUTTON_STATE::END; ++i)
		{
			m_FrameData[i].vScale = m_vScale;
		}
	}
}

void UIWidgetButton::setButtonTextureColorKey(unsigned char _r, unsigned char _g, unsigned char _b, size_t _uIdx)
{
	if (nullptr != m_pTexture)
	{
		m_pTexture->setTextureColorKey(_r, _g, _b, _uIdx);
	}
}

void UIWidgetButton::setButtonFrameData(EBUTTON_STATE _eState, const Vec& _vStart, const Vec& _vScale)
{
	m_FrameData[(int)_eState].vStartPos = _vStart;
	m_FrameData[(int)_eState].vScale = _vScale;
	m_vScale = _vScale;
}

void UIWidgetButton::setButtonHoverSound(const wstring& _strName)
{
	m_arrButtonSound[0] = m_pOwnerScene->getSceneResource()->findSound(_strName);
}

void UIWidgetButton::setButtonClickSound(const wstring& _strName)
{
	m_arrButtonSound[1] = m_pOwnerScene->getSceneResource()->findSound(_strName);
}

void UIWidgetButton::collisionMouseHoveredCallback()
{
	UIWidget::collisionMouseHoveredCallback();
	m_eCurButtonState = EBUTTON_STATE::ENABLE;
	if (m_arrButtonSound[0])
	{
		m_arrButtonSound[0]->play();
	}
}

void UIWidgetButton::collisionMouseReleasedCallback()
{
	UIWidget::collisionMouseReleasedCallback();
	m_eCurButtonState = EBUTTON_STATE::MOUSE_ON;
}
