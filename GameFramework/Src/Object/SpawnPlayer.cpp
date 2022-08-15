// SpawnPlayer.cpp

#include "../GameInfo.h"
#include "SpawnPlayer.h"
#include "../Input.h"
#include "../Scene/Scene.h"
#include "Player.h"
#include "Gun.h"

SpawnPlayer::SpawnPlayer()
	: m_pPlayer(nullptr)
{
}

SpawnPlayer::SpawnPlayer(const SpawnPlayer& _Other)
	: Object(_Other)
{
}

SpawnPlayer::~SpawnPlayer()
{
}

SpawnPlayer* SpawnPlayer::Clone()
{
	return new SpawnPlayer(*this);
}

bool SpawnPlayer::init()
{
	if (false == Object::init())
	{
		return false;
	}

	createAnimation();
	addAnimation(L"spr_player_spawn_idle");
	addAnimation(L"spr_player_spawn_setup", false, 1.f);
	addAnimation(L"spr_player_spawn_unset", false, 1.f);

	wstring str2 = L"spr_player_spawn_setup";
	setAnimationEndNotify<SpawnPlayer>(str2, this, &SpawnPlayer::playerSpawnSetupEnd);

	wstring str3 = L"spr_player_spawn_unset";
	setAnimationEndNotify<SpawnPlayer>(str3, this, &SpawnPlayer::playerSpawnUnsetEnd);

	// Player* pPlayer = createObject<Player>(L"Player", Vec(100.f, 100.f));
	// Gun* pGun = 


	return true;
}

void SpawnPlayer::update()
{
	Object::update();

	if (!m_pPlayer)
	{
		m_pPlayer = m_pOwnerScene->createObject<Player>(L"Player", getObjPos() + Vec(0.f, 40.f));
		m_pOwnerScene->createObject<Gun>(L"Gun", m_pPlayer->getObjPos() + Vec(10.f, 0.f), Vec(30.f, 30.f));
	}
}

void SpawnPlayer::postUpdate()
{
	Object::postUpdate();
}

void SpawnPlayer::collision()
{
	Object::collision();
}

void SpawnPlayer::render(HDC _hDC)
{
	Object::render(_hDC);
}

void SpawnPlayer::start()
{
	Object::start();
	changeAnimation(L"spr_player_spawn_setup");
	Input::getInst()->setCallback<SpawnPlayer>(L"setSpawnPoint", KeyState_Down, this, &SpawnPlayer::playerSpawnSetup);
}

void SpawnPlayer::playerSpawnSetupEnd()
{
	changeAnimation(L"spr_player_spawn_idle");
}

void SpawnPlayer::playerSpawnUnsetEnd()
{
	setObjPos(getOwnerScene()->findObject(L"Player")->getObjPos() - Vec(0.f, 40.f));
	changeAnimation(L"spr_player_spawn_setup");
}

void SpawnPlayer::playerSpawnSetup()
{
	changeAnimation(L"spr_player_spawn_unset");
}
