// SpawnPoint.cpp

#include "../GameInfo.h"
#include "SpawnPoint.h"

SpawnPoint::SpawnPoint()
{
}

SpawnPoint::SpawnPoint(const SpawnPoint& _Other)
	: Object(_Other)
{
}

SpawnPoint::~SpawnPoint()
{
}

SpawnPoint* SpawnPoint::Clone()
{
	return new SpawnPoint(*this);
}

bool SpawnPoint::init()
{
	if (false == Object::init())
	{
		return false;
	}

	createAnimation();
	addAnimation(L"spr_player_spawn_idle");
	addAnimation(L"spr_monster_spawn_idle");
	addAnimation(L"spr_player_spawn_setup", false, 1.f);
	addAnimation(L"spr_player_spawn_unset", false, 1.f);

	wstring str2 = L"spr_player_spawn_setup";
	setAnimationEndNotify<SpawnPoint>(str2, this, &SpawnPoint::playerSpawnSetupEnd);
	
	return true;
}

void SpawnPoint::update()
{
	Object::update();
}

void SpawnPoint::postUpdate()
{
	Object::postUpdate();
}

void SpawnPoint::collision()
{
	Object::collision();
}

void SpawnPoint::render(HDC _hDC)
{
	Object::render(_hDC);
}

void SpawnPoint::start()
{
	Object::start();
	if (this->getObjName() == L"MonsterSpawnPoint")
	{
		changeAnimation(L"spr_monster_spawn_idle");
	}
	else
	{
		changeAnimation(L"spr_player_spawn_setup");
	}
}

void SpawnPoint::playerSpawnSetupEnd()
{
	changeAnimation(L"spr_player_spawn_idle");
}
