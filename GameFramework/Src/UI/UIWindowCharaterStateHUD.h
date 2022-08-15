// UIWindowCharacterStateHUD.h

#pragma once

#include "UIWindow.h"

class UIWindowCharacterStateHUD :
    public UIWindow
{
public:
    UIWindowCharacterStateHUD();
    virtual ~UIWindowCharacterStateHUD();

    virtual bool init();

    void clickStartButton();
    void clickSettingButton();
    void clickEditButton();

private:

    friend class Scene;
};

