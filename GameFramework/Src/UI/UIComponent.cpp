// UIComponent.cpp

#include "../GameInfo.h"
#include "UIComponent.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"

UIComponent::UIComponent()
	: m_pOwnerObject(nullptr)
	, m_pOwnerScene(nullptr)
	, m_pWidget(nullptr)
	, m_vPos{}
	, m_bVisibility(true)
{
}

UIComponent::UIComponent(const UIComponent& _Other)
	: Ref(_Other)
	, m_pOwnerObject(nullptr)
	, m_pOwnerScene(nullptr)
	, m_pWidget(nullptr)
	, m_vPos{}
	, m_bVisibility(true)
{
	m_pWidget = _Other.m_pWidget->Clone();
	m_vPos = _Other.m_vPos;
	m_bVisibility = _Other.m_bVisibility;
}

UIComponent::~UIComponent()
{
}

UIComponent* UIComponent::Clone()
{
	return new UIComponent(*this);
}

bool UIComponent::init()
{
	return true;
}

void UIComponent::update()
{
	if (nullptr != m_pWidget)
	{
		m_pWidget->update();
	}
}

void UIComponent::postUpdate()
{
	if (nullptr != m_pWidget)
	{
		m_pWidget->postUpdate();
	}
}

void UIComponent::collision()
{
	if (nullptr != m_pWidget)
	{
		m_pWidget->collision();
	}
}

void UIComponent::render(HDC _hDC)
{
	if (nullptr != m_pWidget)
	{
		Vec vRenderPos = m_vPos + m_pOwnerScene->getCamera()->calculateRenderPos(m_pOwnerObject->getObjPos());
		m_pWidget->render(vRenderPos, _hDC);
	}
}
