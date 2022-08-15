// UIWindow.h

#pragma once

#include "../GameInfo.h"
#include "../Ref.h"
#include "UIWidget.h"

class Scene;

class UIWindow :
    public Ref
{
public:
    UIWindow();
    UIWindow(const UIWindow& _Other);
    virtual ~UIWindow();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);

    static int sortZorder(const void* _pSrc, const void* _pDes);

    template <typename T>
    T* findWidget(const wstring& _strName);
    template <typename T>
    T* createWidget(const wstring& _strName);

    Vec getUIWindowPos() { return m_vPos; }
    void setUIWindowPos(Vec _vPos) { m_vPos = _vPos; }

    Vec getUIWindowScale() { return m_vScale; }
    void setUIWindowScale(Vec _vScale) { m_vScale = _vScale; }

    Scene* getUIWindowOwnerScene() { return m_pOwnerScene; }
    void setUIWindowOwnerScene(Scene* _pOwnerScene) { m_pOwnerScene = _pOwnerScene; }

    UIWidget* getUIWidget(size_t _uIdx) { return m_dpWidgetArray[_uIdx]; }
    void setUIWidget(size_t _uIdx, UIWidget* _pWidget) { m_dpWidgetArray[_uIdx] = _pWidget; }

    int getUIWindowZOrder() { return m_nZOrder; }
    void setUIWindowZOrder(int _nZOrder) { m_nZOrder = _nZOrder; }

    int getUIWindowWidgetCount() { return m_nWidgetCount; }
    void setUIWindowWidgetCount(int _nWidgetCount) { m_nWidgetCount = _nWidgetCount; }

    int getUIWindowWidgetCapacity() { return m_nWidgetCapacity; }
    void setUIWindowWidgetCapacity(int _nWidgetCapacity) { m_nWidgetCapacity = _nWidgetCapacity; }

    bool isUIWindowVisible() { return m_bVisibility; }
    void setUIWindowVisible(bool _bVisibility) { m_bVisibility = _bVisibility; }

protected:
    Vec         m_vPos;
    Vec         m_vScale;
    Scene*      m_pOwnerScene;
    UIWidget**  m_dpWidgetArray;
    int         m_nZOrder;
    int         m_nWidgetCount;
    int         m_nWidgetCapacity;
    bool        m_bVisibility;

private:


};

template<typename T>
inline T* UIWindow::findWidget(const wstring& _strName)
{
    for (int i = 0; i < m_nWidgetCount; ++i)
    {
        if (m_dpWidgetArray[i]->getObjName() == _strName)
        {
            return (T*)m_dpWidgetArray[i];
        }
    }

    return nullptr;
}

template<typename T>
inline T* UIWindow::createWidget(const wstring& _strName)
{
    T* pWidget = new T;

    pWidget->setObjName(_strName);
    pWidget->setOwnerScene(getUIWindowOwnerScene());
    pWidget->setUIWidgetOwnerUIWindow(this);

    if (false == pWidget->init())
    {
        SAFE_DELETE(pWidget);
        return nullptr;
    }

    if (m_nWidgetCount == m_nWidgetCapacity)
    {
        m_nWidgetCapacity *= 2;
        UIWidget** dpWidgetArray = new UIWidget * [m_nWidgetCapacity];
        memcpy(dpWidgetArray, m_dpWidgetArray, sizeof(UIWidget*) * m_nWidgetCount);
        SAFE_DELETE_ARRAY(m_dpWidgetArray);
        m_dpWidgetArray = dpWidgetArray;
    }

    pWidget->addRefCount();
    m_dpWidgetArray[m_nWidgetCount] = pWidget;
    ++m_nWidgetCount;

    return (T*)pWidget;
}