// SceneIntro.cpp

#include "../GameInfo.h"
#include "SceneIntro.h"
#include "../GameManager.h"
#include "../Object/Player.h"
#include "../Object/Bullet.h"
#include "../Object/Monster.h"
#include "../Object/Gun.h"
#include "../Scene/SceneResource.h"
#include "../Object/EffectHit.h"
#include "Camera.h"
#include "../UI/UIWindow.h"
#include "../UI/UIWidget.h"
#include "../UI/UIWidgetImage.h"
#include "../UI/UIWindowIntro.h"
#include "../UI/UIWidgetButton.h"
#include "../Map/ScrollMap.h"
#include "../UI/UIWindowESC.h"


SceneIntro::SceneIntro()
{
}

SceneIntro::~SceneIntro()
{
}

bool SceneIntro::init()
{
    if (!Scene::init())
    {
        return false;
    }

    loadAnimationSequence();


    getSceneResource()->loadSound(L"BGM", true, L"IntroBGM", "bgm_intro_remix.ogg");

    getSceneResource()->playSound(L"IntroBGM");

    getSceneResource()->loadSound(L"UI", false, L"ButtonHover", "button_hover.mp3");
    getSceneResource()->loadSound(L"UI", false, L"ButtonClick", "button_click.mp3");

    UIWindowIntro* pUIWindowIntro = createUIWindow<UIWindowIntro>(L"UIWindowIntro");
    /*
    UIWidgetImage* pTestImage = pTestWindow->createWidget<UIWidgetImage>(L"TestImage");
    pTestImage->setImageTexture(L"TestImage", TEXT("StartGame.bmp"), TEXTURE_PATH);
    pTestImage->setUIWidgetPos(Vec(100.f, 100.f));
    pTestImage->setImageTextureColorKey(255, 0, 255);
    pTestImage->setUIWidgetZOrder(1);
    */

    getCamera()->setWorldResolution(Vec(1920.f, 1080.f));
    getCamera()->setCameraPos(Vec(1920.f / 2.f, 1080.f / 2.f));

    ScrollMap* pMap = createMap<ScrollMap>(L"ScollMap");
    pMap->setScale(Vec(1280.f, 720.f));
    pMap->setTexture(L"ScrollBack", L"spr_intro_scrollmap.bmp");
    pMap->setScrollRatio(0.2f, 0.2f);
    /*
    UIWindowESC* pESCWindow = createUIWindow<UIWindowESC>(L"ESCWindow");
    Vec vRes;
    vRes.x = (float)GameManager::getInst()->getMainRes().x;
    vRes.y = (float)GameManager::getInst()->getMainRes().y;
    Vec vScale = pESCWindow->getUIWindowScale();
    pESCWindow->setUIWindowPos(vRes / 2.f - vScale + Vec(-100.f, 400.f));
    pESCWindow->setUIWindowZOrder(1);
    */
    return true;
}

void SceneIntro::loadAnimationSequence()
{
}

void SceneIntro::load(const wstring& _strName, const wstring& _strPath, int _nFrameCount, float _fSizeX, float _fSizeY)
{
    const TCHAR* temp = _strPath.c_str();
    getSceneResource()->createAnimationSequence(_strName, _strName, temp);
    getSceneResource()->setTextureColorKey(_strName, 255, 0, 255);
    for (int i = 0; i < _nFrameCount; ++i)
    {
        getSceneResource()->addAnimationFrameData(_strName,
            i * _fSizeX, 0.f, _fSizeX, _fSizeY);
    }
}
