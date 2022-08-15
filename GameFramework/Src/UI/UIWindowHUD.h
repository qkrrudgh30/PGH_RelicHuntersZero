// UIWindowHUD.h

#pragma once

#include "UIWindow.h"
#include "UIWidgetProgressBar.h"
#include "UIWidgetButton.h"
#include "UIWidgetImage.h"

class UIWindowHUD :
    public UIWindow
{
public:
    UIWindowHUD();
    virtual ~UIWindowHUD();

    virtual bool init();

    void setHPBar(float _fPercent) { m_pHPBar->setPercent(_fPercent); }

    void setMPBar(float _fPercent) { m_pMPBar->setPercent(_fPercent); }

private:
    SharedPtr<UIWidgetProgressBar> m_pHPBar;
    SharedPtr<UIWidgetProgressBar> m_pMPBar;


    friend class Scene;
};

