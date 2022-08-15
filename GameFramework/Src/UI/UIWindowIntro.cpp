// UIWindowIntro.cpp

#include "UIWindowIntro.h"
#include "UIWidgetButton.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include  "../GameManager.h"
#include "../UI/UIWidgetImage.h"
#include "../Scene/SceneStage1.h"
#include "../Scene/SceneEditStage.h"

UIWindowIntro::UIWindowIntro()
{
}

UIWindowIntro::~UIWindowIntro()
{
}

bool UIWindowIntro::init()
{
	Vec vRes;
	vRes.x = (float)GameManager::getInst()->getMainRes().x;
	vRes.y = (float)GameManager::getInst()->getMainRes().y;
	UIWidgetButton* pStartButton = createWidget<UIWidgetButton>(L"StartButton");
	pStartButton->setButtonTexture(L"StartButton", TEXT("spr_button_startgame.bmp"), L"ButtonPath");
	pStartButton->setButtonFrameData(EBUTTON_STATE::ENABLE, Vec(0.f, 0.f), Vec(320.f, 72.f));
	pStartButton->setButtonFrameData(EBUTTON_STATE::MOUSE_ON, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pStartButton->setButtonFrameData(EBUTTON_STATE::MOUSE_CLICK, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pStartButton->setButtonTextureColorKey(255, 0, 255, 0);
	pStartButton->setUIWidgetPos(Vec(vRes.x/2.f - 160.f, vRes.y/2.f + 14.f));
	pStartButton->setUIWidgetZOrder(1);
	pStartButton->setButtonClickCallback<UIWindowIntro>(this, &UIWindowIntro::clickStartButton);
	pStartButton->setButtonClickSound(L"ButtonClick");
	pStartButton->setButtonHoverSound(L"ButtonHover");

	UIWidgetButton* pMapEditButton = createWidget<UIWidgetButton>(L"MapEditButton");
	pMapEditButton->setButtonTexture(L"MapEditButton", TEXT("spr_button_mapedit.bmp"), L"ButtonPath");
	pMapEditButton->setButtonFrameData(EBUTTON_STATE::ENABLE, Vec(0.f, 0.f), Vec(320.f, 72.f));
	pMapEditButton->setButtonFrameData(EBUTTON_STATE::MOUSE_ON, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pMapEditButton->setButtonFrameData(EBUTTON_STATE::MOUSE_CLICK, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pMapEditButton->setButtonTextureColorKey(255, 0, 255, 0);
	pMapEditButton->setUIWidgetPos(Vec(vRes.x / 2.f - 160.f, vRes.y / 2.f - 36.f + 132.f));
	pMapEditButton->setUIWidgetZOrder(1);
	pMapEditButton->setButtonClickCallback<UIWindowIntro>(this, &UIWindowIntro::clickEditButton);
	pMapEditButton->setButtonClickSound(L"ButtonClick");
	pMapEditButton->setButtonHoverSound(L"ButtonHover");
	/*
	UIWidgetButton* pSettingButton = createWidget<UIWidgetButton>(L"SettingButton"); 
	pSettingButton->setButtonTexture(L"SettingButton", TEXT("spr_button_setting.bmp"), L"ButtonPath");
	pSettingButton->setButtonFrameData(EBUTTON_STATE::ENABLE, Vec(0.f, 0.f), Vec(320.f, 72.f));
	pSettingButton->setButtonFrameData(EBUTTON_STATE::MOUSE_ON, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pSettingButton->setButtonFrameData(EBUTTON_STATE::MOUSE_CLICK, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pSettingButton->setButtonTextureColorKey(255, 0, 255, 0);
	pSettingButton->setUIWidgetPos(Vec(vRes.x / 2.f - 160.f, vRes.y / 2.f - 36.f + 214.f));
	pSettingButton->setUIWidgetZOrder(1);
	pSettingButton->setButtonClickCallback<UIWindowIntro>(this, &UIWindowIntro::clickSettingButton);
	pSettingButton->setButtonClickSound(L"ButtonClick");
	pSettingButton->setButtonHoverSound(L"ButtonHover");
	*/


	UIWidgetImage* pBGImage = createWidget<UIWidgetImage>(L"BGImage");
	pBGImage->setImageTexture(L"IntroBack", TEXT("SceneIntro2.bmp"), TEXTURE_PATH);
	pBGImage->setUIWidgetPos(Vec(vRes.x / 2.f - 425.f, vRes.y/2.f - 350.f));
	pBGImage->setImageTextureColorKey(255, 0, 255, 0);

	ShowCursor(FALSE);
	UIWidgetImage* pMouseImage = createWidget<UIWidgetImage>(L"Mouse");
	pMouseImage->setImageTexture(L"Mouse", L"spr_crosshair_0.bmp", TEXTURE_PATH);
	pMouseImage->setImageTextureColorKey(255, 0, 255, 0);
	pMouseImage->setUIWidgetZOrder(2);

	return true;
}

void UIWindowIntro::clickStartButton()
{
	SceneManager::getInst()->createScene<SceneStage1>();
	// SceneManager::getInst()->createScene<MainScene>();
}

void UIWindowIntro::clickSettingButton()
{
	MessageBox(0, TEXT("Setting"), TEXT("Setting"), MB_OK);
}

void UIWindowIntro::clickEditButton()
{
	// MessageBox(0, TEXT("Edit"), TEXT("Edit"), MB_OK);
	SceneManager::getInst()->createScene<SceneEditStage>();
}