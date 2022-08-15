// UIWindowHUD.cpp

#include "UIWindowHUD.h"
#include "../GameManager.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneManager.h"

UIWindowHUD::UIWindowHUD()
{
}

UIWindowHUD::~UIWindowHUD()
{
}

bool UIWindowHUD::init()
{
	setUIWindowPos(Vec(100.f, 620.f));
	UIWidgetImage* pPlayerPortrait = createWidget<UIWidgetImage>(L"PlayerPortrait");
	pPlayerPortrait->setImageTexture(L"PlayerPortrait", TEXT("spr_hud_face_jimmy_0.bmp"), TEXTURE_PATH);
	pPlayerPortrait->setImageTextureColorKey(255, 0, 255);
	pPlayerPortrait->setUIWidgetPos(Vec(-90.f, 0.f));

	UIWidgetImage* pPlayerHPBackBar = createWidget<UIWidgetImage>(L"PlayerHPBackBar");
	pPlayerHPBackBar->setImageTexture(L"PlayerHPBackBar", TEXT("Bar.bmp"), TEXTURE_PATH);
	pPlayerHPBackBar->setImageTextureColorKey(255, 0, 255);
	pPlayerHPBackBar->setUIWidgetZOrder(1);
	m_pHPBar = createWidget<UIWidgetProgressBar>(L"PlayerHPBar");
	m_pHPBar->setImageTexture(L"PlayerHPBar", TEXT("HP.bmp"), TEXTURE_PATH);
	m_pHPBar->setUIWidgetZOrder(0);

	UIWidgetImage* pPlayerMPBackBar = createWidget<UIWidgetImage>(L"PlayerMPBackBar");
	pPlayerMPBackBar->setImageTexture(L"PlayerMPBackBar", TEXT("Bar.bmp"), TEXTURE_PATH);
	pPlayerMPBackBar->setImageTextureColorKey(255, 0, 255);
	pPlayerMPBackBar->setUIWidgetPos(Vec(0.f, 50.f));
	pPlayerMPBackBar->setUIWidgetZOrder(1);
	m_pMPBar = createWidget<UIWidgetProgressBar>(L"PlayerMPBar");
	m_pMPBar->setImageTexture(L"PlayerMPBar", TEXT("MP.bmp"), TEXTURE_PATH);
	m_pMPBar->setUIWidgetPos(Vec(0.f, 50.f));
	m_pMPBar->setUIWidgetZOrder(0);

	return true;
}
