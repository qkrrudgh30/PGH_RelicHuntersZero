// UIWidget.cpp

#include "../GameInfo.h"
#include "UIWidget.h"

UIWidget::UIWidget()
    : m_vPos{}
    , m_vScale{}
    , m_pOwnerScene(nullptr)
    , m_pOwnerWindow(nullptr)
    , m_nZOrder(0)
    , m_bVisibility(true)
    , m_bMouseHovered(false)
{
}

UIWidget::UIWidget(const UIWidget& _Other)
    : Ref(_Other)
{
    *this = _Other;
}

UIWidget::~UIWidget()
{
}

UIWidget* UIWidget::Clone()
{
    return new UIWidget(*this);
}

bool UIWidget::init()
{
    return true;
}

void UIWidget::update()
{
}

void UIWidget::postUpdate()
{
}

void UIWidget::collision()
{
}

void UIWidget::render(HDC _hDC)
{
}

void UIWidget::render(const Vec& _vPos, HDC _hDC)
{
}

void UIWidget::collisionMouseHoveredCallback()
{
    m_bMouseHovered = true;
}

void UIWidget::collisionMouseReleasedCallback()
{
    m_bMouseHovered = false;
}

bool UIWidget::collisionMouse(const Vec& _vMousePos)
{
    if (m_vPos.x <= _vMousePos.x && _vMousePos.x <= m_vPos.x + m_vScale.x &&
        m_vPos.y <= _vMousePos.y && _vMousePos.y <= m_vPos.y + m_vScale.y)
    {
        if (false == m_bMouseHovered)
        {
            collisionMouseHoveredCallback();
        }
        return true;
    }
    return false;
}