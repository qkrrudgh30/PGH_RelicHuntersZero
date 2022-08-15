
#include "UIWindowESC.h"
#include "UIWidgetButton.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"
#include "../UI/UIWidgetImage.h"
#include "../Scene/SceneIntro.h"
#include "../Scene/SceneStage1.h"
#include "../Scene/SceneStage2.h"
#include "../Scene/SceneEditStage.h"

UIWindowESC::UIWindowESC()
{
}

UIWindowESC::~UIWindowESC()
{
}

bool UIWindowESC::init()
{
	Vec vRes;
	vRes.x = (float)GameManager::getInst()->getMainRes().x;
	vRes.y = (float)GameManager::getInst()->getMainRes().y;

	UIWidgetButton* pStartButton = createWidget<UIWidgetButton>(L"ExitButton");
	pStartButton->setButtonTexture(L"ExitButton", TEXT("spr_menu_bar_exit.bmp"), MENU_PATH);
	pStartButton->setButtonFrameData(EBUTTON_STATE::ENABLE, Vec(0.f, 0.f), Vec(320.f, 72.f));
	pStartButton->setButtonFrameData(EBUTTON_STATE::MOUSE_ON, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pStartButton->setButtonFrameData(EBUTTON_STATE::MOUSE_CLICK, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pStartButton->setButtonTextureColorKey(255, 0, 255, 0);
	pStartButton->setUIWidgetPos(Vec(vRes.x / 2.f - 160.f, vRes.y / 2.f + 14.f));
	pStartButton->setUIWidgetZOrder(2);
	pStartButton->setButtonClickCallback<UIWindowESC>(this, &UIWindowESC::clickExitButton);
	pStartButton->setButtonClickSound(L"ButtonClick");
	pStartButton->setButtonHoverSound(L"ButtonHover");

	UIWidgetButton* pSettingButton = createWidget<UIWidgetButton>(L"IntroButton");
	pSettingButton->setButtonTexture(L"IntroButton", TEXT("spr_menu_bar_gotostart.bmp"), MENU_PATH);
	pSettingButton->setButtonFrameData(EBUTTON_STATE::ENABLE, Vec(0.f, 0.f), Vec(320.f, 72.f));
	pSettingButton->setButtonFrameData(EBUTTON_STATE::MOUSE_ON, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pSettingButton->setButtonFrameData(EBUTTON_STATE::MOUSE_CLICK, Vec(320.f, 0.f), Vec(320.f, 72.f));
	pSettingButton->setButtonTextureColorKey(255, 0, 255, 0);
	pSettingButton->setUIWidgetPos(Vec(vRes.x / 2.f - 160.f, vRes.y / 2.f - 36.f + 132.f));
	pSettingButton->setUIWidgetZOrder(2);
	pSettingButton->setButtonClickCallback<UIWindowESC>(this, &UIWindowESC::clickIntroButton);
	pSettingButton->setButtonClickSound(L"ButtonClick");
	pSettingButton->setButtonHoverSound(L"ButtonHover");

	UIWidgetImage* pBGImage = createWidget<UIWidgetImage>(L"BGImage");
	pBGImage->setImageTexture(L"ESCBack", TEXT("spr_menu_back.bmp"), MENU_PATH);
	pBGImage->setUIWidgetPos(Vec(vRes.x / 2.f - 425.f, vRes.y / 2.f - 350.f));
	pBGImage->setImageTextureColorKey(255, 0, 255, 0);

	setUIWindowScale(Vec(pBGImage->getUIWidgetScale()));

	return true;
}

void UIWindowESC::clickExitButton()
{
}

void UIWindowESC::clickIntroButton()
{
}
