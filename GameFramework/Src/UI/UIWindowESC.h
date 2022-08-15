// UIWindowESC.h

#pragma once

#include "UIWindow.h"

class UIWindowESC :
    public UIWindow
{
public:
    UIWindowESC();
    virtual ~UIWindowESC();

    virtual bool init();

    void clickExitButton();
    void clickIntroButton();

private:

    friend class Scene;
};

