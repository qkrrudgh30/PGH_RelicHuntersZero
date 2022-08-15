// UIWindowMain.cpp

#include "UIWindowMain.h"
#include "UIWidgetButton.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include  "../GameManager.h"
#include "../UI/UIWidgetImage.h"
#include "../GameManager.h"
#include "UIWidgetProgressBar.h"
#include "UIWidgetText.h"
#include "../Scene/SceneStage1.h"

UIWindowMain::UIWindowMain()
{
}

UIWindowMain::~UIWindowMain()
{
}

bool UIWindowMain::init()
{
	/*
	UIWidgetImage* pBack = createWidget<UIWidgetImage>(L"BarBack");
	pBack->setImageTexture(L"BarBack", TEXT("Bar.bmp"), TEXTURE_PATH);
	pBack->setUIWidgetPos(Vec(30.f, 20.f));
	pBack->setImageTextureColorKey(255, 0, 255, 0);
	*/

	ShowCursor(FALSE);
	UIWidgetImage* pMouseImage = createWidget<UIWidgetImage>(L"Mouse");
	pMouseImage->setImageTexture(L"Mouse", L"spr_crosshair_0.bmp", TEXTURE_PATH);
	pMouseImage->setImageTextureColorKey(255, 0, 255, 0);

	return true;
}

void UIWindowMain::clickStartButton()
{
	SceneManager::getInst()->createScene<MainScene>();
	// SceneManager::getInst()->createScene<SceneStage1>();
}

void UIWindowMain::clickSettingButton()
{
	MessageBox(0, TEXT("Setting"), TEXT("Setting"), MB_OK);
}

void UIWindowMain::clickEditButton()
{
	MessageBox(0, TEXT("Edit"), TEXT("Edit"), MB_OK);
}