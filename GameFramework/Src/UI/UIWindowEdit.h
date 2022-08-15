#pragma once
#include "UIWindow.h"

class UIWidgetImage;

class UIWindowEdit :
    public UIWindow
{
public:
    UIWindowEdit();
    virtual ~UIWindowEdit();

    virtual bool init();

    void setMousePlayerImage();
    void setMouseKamikazeLiteSpawnImage();
    void setMouseKamikazeSpawnImage();
    void setMouseKamikazeBossSpawnImage();
    void setMouseStage1PotalImage();
    void setMouseStage2PotalImage();

    UIWidgetImage* getMouseImage() { return m_pMouseImage; }

private:
    UIWidgetImage* m_pMouseImage;

    friend class Scene;
};

