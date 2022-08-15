// UIWindowIntro.h

#pragma once

#include "UIWindow.h"

class UIWindowIntro :
    public UIWindow
{
public:
    UIWindowIntro();
    virtual ~UIWindowIntro();

    virtual bool init();

    void clickStartButton();
    void clickSettingButton();
    void clickEditButton();

private:

    friend class Scene;
};

