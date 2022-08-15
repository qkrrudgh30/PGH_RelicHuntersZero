// UIWidget.h

#pragma once

#include "../Ref.h"

class Scene;
class UIWindow;

class UIWidget :
    public Ref
{
public:
    UIWidget();
    UIWidget(const UIWidget& _Other);
    virtual ~UIWidget();

    UIWidget* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);
    virtual void render(const Vec& _vPos, HDC _hDC);

    virtual void collisionMouseHoveredCallback();
    virtual void collisionMouseReleasedCallback();
    bool collisionMouse(const Vec& _vMousePos);

    Vec getUIWidgetPos() { return m_vPos; }
    void setUIWidgetPos(Vec _vPos) { m_vPos = _vPos; }

    Vec getUIWidgetScale() { return m_vScale; }
    void setUIWidgetScale(Vec _vScale) { m_vScale = _vScale; }

    Scene* getUIWidgetOwnerScene() { return m_pOwnerScene; }
    void setOwnerScene(Scene* _pOwnerScene) { m_pOwnerScene = _pOwnerScene; }

    UIWindow* getUIWidgetOwnerUIWindow() { return m_pOwnerWindow; }
    void setUIWidgetOwnerUIWindow(UIWindow* _pOwnerWindow) { m_pOwnerWindow = _pOwnerWindow; }

    int getUIWidgetZOrder() { return m_nZOrder; }
    void setUIWidgetZOrder(int _nZOrder) { m_nZOrder = _nZOrder; }

    bool isUIWidgetVisible() { return m_bVisibility; }
    void setUIWidgetVisible(bool _bVisibility) { m_bVisibility = _bVisibility; }

    bool isUIWidgetMouseHovered() { return m_bVisibility; }

protected:
    Vec         m_vPos;
    Vec         m_vScale;
    Scene*      m_pOwnerScene;
    UIWindow*   m_pOwnerWindow;
    int         m_nZOrder;
    bool        m_bVisibility;
    bool        m_bMouseHovered;

private:

};