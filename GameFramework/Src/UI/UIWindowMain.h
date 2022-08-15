// UIWindowMain.h

#pragma once

#include "UIWindow.h"

class UIWindowMain :
    public UIWindow
{
public:
    UIWindowMain();
    virtual ~UIWindowMain();

    virtual bool init();

    void clickStartButton();
    void clickSettingButton();
    void clickEditButton();

private:

    friend class Scene;
};

