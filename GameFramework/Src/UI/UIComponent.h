// UIComponent.h

#pragma once

#include "../Ref.h"
#include "UIWidget.h"

class Object;
class Scene;

class UIComponent :
    public Ref
{
public:
    UIComponent();
    UIComponent(const UIComponent& _Other);
    virtual ~UIComponent();

    UIComponent* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);

    Object* getOwnerObject() { return m_pOwnerObject; }
    void setOwnerObject(Object* _pOwnerObject) { m_pOwnerObject = _pOwnerObject; }

    Scene* getOwnerScene() { return m_pOwnerScene; }
    void setOwnerScene(Scene* _pOwnerScene) { m_pOwnerScene = _pOwnerScene; }

    UIWidget* getWidget() const { return m_pWidget; }
    // void setWidget(UIWidget* _pWidget) const { m_pWidget = _pWidget; }

    Vec getComponentPos() { return m_vPos; }
    void setComponentPos(Vec _vPos) { m_vPos = _vPos; }

    bool isVisible() { return m_bVisibility; }
    void setVisible(bool _bVisible) { m_bVisibility = _bVisible; }

    template <typename T>
    T* createWidget(const wstring& _strName);

private:
    Object*             m_pOwnerObject;
    Scene*              m_pOwnerScene;
    SharedPtr<UIWidget> m_pWidget;
    Vec                 m_vPos;
    bool                m_bVisibility;

};

template<typename T>
inline T* UIComponent::createWidget(const wstring& _strName)
{
    T* pWidget = new T;
    pWidget->setObjName(_strName);
    pWidget->setOwnerScene(m_pOwnerScene);

    if (false == pWidget->init())
    {
        SAFE_DELETE(pWidget);
        return nullptr;
    }

    m_pWidget = pWidget;

    return pWidget;
}