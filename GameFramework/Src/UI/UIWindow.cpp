// UIWindow.cpp

#include "../GameInfo.h"
#include "UIWindow.h"
#include "UIWidget.h"

UIWindow::UIWindow()
    : m_vPos{}
    , m_vScale{}
    , m_pOwnerScene(nullptr)
    , m_dpWidgetArray(nullptr)
    , m_nWidgetCapacity(2)
    , m_nWidgetCount(0)
    , m_nZOrder(0)
    , m_bVisibility(true)
{
    m_dpWidgetArray = new UIWidget * [m_nWidgetCapacity];
}

UIWindow::UIWindow(const UIWindow& _Other)
    : Ref(_Other)
{
    *this = _Other;
}

UIWindow::~UIWindow()
{
    for (int i = 0; i < m_nWidgetCount; ++i)
    {
        SAFE_RELEASE(m_dpWidgetArray[i]);
    }

    SAFE_DELETE_ARRAY(m_dpWidgetArray);
}

bool UIWindow::init()
{
    return true;
}

void UIWindow::update()
{
    for (int i = 0; i < m_nWidgetCount;)
    {
        if (false == m_dpWidgetArray[i]->isAlive())
        {
            SAFE_RELEASE(m_dpWidgetArray[i]);
            for (int j = i; j < m_nWidgetCount - 1; ++j)
            {
                m_dpWidgetArray[j] = m_dpWidgetArray[j + 1];
            }
            --m_nWidgetCount;

            continue;
        }
        else if (false == m_dpWidgetArray[i]->isUIWidgetVisible())
        {
            ++i;
            continue;
        }
        m_dpWidgetArray[i]->update();
        ++i;
    }
}

void UIWindow::postUpdate()
{
    for (int i = 0; i < m_nWidgetCount;)
    {
        if (false == m_dpWidgetArray[i]->isAlive())
        {
            SAFE_RELEASE(m_dpWidgetArray[i]);
            for (int j = i; j < m_nWidgetCount - 1; ++j)
            {
                m_dpWidgetArray[j] = m_dpWidgetArray[j + 1];
            }
            --m_nWidgetCount;

            continue;
        }
        else if (false == m_dpWidgetArray[i]->isUIWidgetVisible())
        {
            ++i;
            continue;
        }
        m_dpWidgetArray[i]->postUpdate();
        ++i;
    }
}

void UIWindow::collision()
{
    if (m_nWidgetCount >= 2)
    {
        qsort(m_dpWidgetArray, (size_t)m_nWidgetCount, sizeof(UIWidget*),
            UIWindow::sortZorder);
    }
}

void UIWindow::render(HDC _hDC)
{
    for (int i = 0; i < m_nWidgetCount;)
    {
        if (false == m_dpWidgetArray[i]->isAlive())
        {
            SAFE_RELEASE(m_dpWidgetArray[i]);
            for (int j = i; j < m_nWidgetCount - 1; ++j)
            {
                m_dpWidgetArray[j] = m_dpWidgetArray[j + 1];
            }
            --m_nWidgetCount;

            continue;
        }
        
        ++i;
    }
    for (int i = m_nWidgetCount - 1; i >= 0; --i)
    {
        if (false == m_dpWidgetArray[i]->isUIWidgetVisible())
        {
            continue;
        }
        m_dpWidgetArray[i]->render(_hDC);
    }
}

int UIWindow::sortZorder(const void* _pSrc, const void* _pDes)
{
    UIWidget* pSrc = *(UIWidget**)_pSrc;
    UIWidget* pDes = *(UIWidget**)_pDes;

    int nSrcZ = pSrc->getUIWidgetZOrder();
    int nDesZ = pDes->getUIWidgetZOrder();

    if (nSrcZ > nDesZ)
    {
        return -1;
    }
    else if (nSrcZ < nDesZ)
    {
        return 1;
    }
    return 0;
}