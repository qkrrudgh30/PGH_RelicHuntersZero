// CollisionManager.cpp

#include "../GameInfo.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
	auto iter = m_mapProfiles.begin();
	auto iterEnd = m_mapProfiles.end();
	for (; iter != iterEnd;)
	{
		SAFE_DELETE(iter->second);
		++iter;
	}
	m_mapProfiles.clear();

}

bool CollisionManager::init()
{
	createProfile(L"Object", CHANNEL_OBJECT, true);
	createProfile(L"Player", CHANNEL_PLAYER, true);
	createProfile(L"Monster", CHANNEL_MONSTER, true);
	createProfile(L"PlayerBullet", CHANNEL_PLAYER_BULLET, true);
	createProfile(L"MonsterBullet", CHANNEL_MONSTER_BULLET, true);
	createProfile(L"Wall", CHANNEL_WALL, true);

	setCollisionState(L"Player", CHANNEL_PLAYER, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"Player", CHANNEL_PLAYER_BULLET, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"Player", CHANNEL_MONSTER, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"Player", CHANNEL_MONSTER_BULLET, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"Player", CHANNEL_WALL, ECOLLISION_STATE::COLLISION);

	setCollisionState(L"PlayerBullet", CHANNEL_PLAYER, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"PlayerBullet", CHANNEL_PLAYER_BULLET, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"PlayerBullet", CHANNEL_MONSTER, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"PlayerBullet", CHANNEL_MONSTER_BULLET, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"PlayerBullet", CHANNEL_WALL, ECOLLISION_STATE::COLLISION);
	
	setCollisionState(L"Monster", CHANNEL_MONSTER, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"Monster", CHANNEL_MONSTER_BULLET, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"Monster", CHANNEL_PLAYER, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"Monster", CHANNEL_PLAYER_BULLET, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"Monster", CHANNEL_WALL, ECOLLISION_STATE::COLLISION);
	
	setCollisionState(L"MonsterBullet", CHANNEL_MONSTER, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"MonsterBullet", CHANNEL_MONSTER_BULLET, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"MonsterBullet", CHANNEL_PLAYER, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"MonsterBullet", CHANNEL_PLAYER_BULLET, ECOLLISION_STATE::NONCOLLISION);
	setCollisionState(L"MonsterBullet", CHANNEL_WALL, ECOLLISION_STATE::COLLISION);

	setCollisionState(L"Wall", CHANNEL_MONSTER, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"Wall", CHANNEL_MONSTER_BULLET, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"Wall", CHANNEL_PLAYER, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"Wall", CHANNEL_PLAYER_BULLET, ECOLLISION_STATE::COLLISION);
	setCollisionState(L"Wall", CHANNEL_WALL, ECOLLISION_STATE::NONCOLLISION);

	return true;
}

CollisionProfile* CollisionManager::findProfile(const wstring& _strName)
{
	auto iter = m_mapProfiles.find(_strName);
	if (m_mapProfiles.end() == iter)
	{
		return nullptr;
	}
	return iter->second;
}

bool CollisionManager::createProfile(const wstring& _strName, ECOLLISION_CHANNEL _eChannel, bool _bEnable, ECOLLISION_STATE _eState)
{
	CollisionProfile* pProfile = findProfile(_strName);
	if (pProfile)
	{
		return false;
	}

	pProfile = new CollisionProfile;
	pProfile->strName = _strName;
	pProfile->eChannel = _eChannel;
	pProfile->bCollisionEnable = _bEnable;
	pProfile->vecState.resize(CHANNEL_END);

	for (size_t i = 0; i < CHANNEL_END; ++i)
	{
		pProfile->vecState[i] = _eState;
	}

	m_mapProfiles.insert(make_pair(_strName, pProfile));

	return true;
}

bool CollisionManager::setCollisionState(const wstring& _strName, ECOLLISION_CHANNEL _eChannel, ECOLLISION_STATE _eState)
{
	CollisionProfile* pProfile = findProfile(_strName);

	if (!pProfile)
	{
		return false;
	}

	pProfile->vecState[_eChannel] = _eState;

	return true;
}
