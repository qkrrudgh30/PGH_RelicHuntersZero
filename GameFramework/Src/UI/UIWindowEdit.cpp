
#include "../GameInfo.h"
#include "../GameManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneEditStage.h"
#include "UIWidget.h"
#include "UIWindowEdit.h"
#include "UIWidgetText.h"
#include "UIWidgetImage.h"

UIWindowEdit::UIWindowEdit()
	: m_pMouseImage(nullptr)
{
}

UIWindowEdit::~UIWindowEdit()
{
}

bool UIWindowEdit::init()
{
	ShowCursor(TRUE);
	m_pMouseImage = createWidget<UIWidgetImage>(L"Mouse");

	return true;
}

void UIWindowEdit::setMousePlayerImage()
{
	// m_pMouseImage->changeTexture(L"Mouse1", L"spr_set_jimmy.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTexture(L"PlayerSpawn", L"spr_set_jimmy.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTextureColorKey(255, 0, 255);
}

void UIWindowEdit::setMouseKamikazeLiteSpawnImage()
{
	// m_pMouseImage->changeTexture(L"Mouse2", L"spr_set_spawn1.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTexture(L"KamikazeLiteSpawn", L"spr_set_spawn1.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTextureColorKey(255, 0, 255);
}

void UIWindowEdit::setMouseKamikazeSpawnImage()
{
	// m_pMouseImage->changeTexture(L"Mouse3", L"spr_set_spawn2.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTexture(L"KamikazeSpawn", L"spr_set_spawn2.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTextureColorKey(255, 0, 255);
}

void UIWindowEdit::setMouseKamikazeBossSpawnImage()
{
	// m_pMouseImage->changeTexture(L"Mouse4", L"spr_set_egg.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTexture(L"KamikazeBossSpawn", L"spr_set_egg.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTextureColorKey(255, 0, 255);
}

void UIWindowEdit::setMouseStage1PotalImage()
{
	// m_pMouseImage->changeTexture(L"Mouse5", L"spr_set_pota1.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTexture(L"Stage1Potal", L"spr_set_pota1.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTextureColorKey(255, 0, 255);
}

void UIWindowEdit::setMouseStage2PotalImage()
{
	// m_pMouseImage->changeTexture(L"Mouse6", L"spr_set_pota2.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTexture(L"Stage2Potal", L"spr_set_pota2.bmp", MOUSE_PATH);
	m_pMouseImage->setImageTextureColorKey(255, 0, 255);
}
