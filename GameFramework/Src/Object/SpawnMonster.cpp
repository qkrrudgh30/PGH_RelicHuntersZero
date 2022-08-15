// SpawnMonster.cpp

#include "../GameInfo.h"
#include "SpawnMonster.h"
#include "../Timer.h"
#include "../Scene/Scene.h"
#include "KamikazeLite.h"
#include "../Collision/Collider.h"
#include "../Collision/ColliderSphere.h"
#include "EffectHit.h"

SpawnMonster::SpawnMonster()
	: m_dAccTime(0.)
	, m_dAccDiggingTime(0.)
	, m_pCollider(nullptr)
	, m_bDigging(false)
{
}

SpawnMonster::SpawnMonster(const SpawnMonster& _Other)
	: Object(_Other)
	, m_dAccTime(0.)
	, m_dAccDiggingTime(0.)
	, m_pCollider(nullptr)
	, m_bDigging(false)
{

}

SpawnMonster::~SpawnMonster()
{
}

SpawnMonster* SpawnMonster::Clone()
{
	return new SpawnMonster(*this);
}

bool SpawnMonster::init()
{
	if (false == Object::init())
	{
		return false;
	}

	ColliderSphere* pSpawnMonster = addCollider<ColliderSphere>(L"SpawnMonster");
	m_pCollider = (Collider*)pSpawnMonster;
	pSpawnMonster->setRadius(30.f);
	pSpawnMonster->setOffset(Vec(2.f, 0.f));
	pSpawnMonster->setProfile(L"Monster");
	pSpawnMonster->setCollisionBeginFunc<SpawnMonster>(this, &SpawnMonster::collisionBegin);
	pSpawnMonster->setCollisionEndFunc<SpawnMonster>(this, &SpawnMonster::collisionEnd);

	createAnimation();
	addAnimation(L"spr_monster_spawn_idle");
	return true;
}

void SpawnMonster::update()
{
	Object::update();

	m_dAccTime += DT;

	if (m_bDigging)
	{
		m_dAccDiggingTime += DT;
		if (5. <= m_dAccDiggingTime)
		{
			destroy();
		}
	}
	Vec vPlayerPos;
	float fDist = 1000.f;
	if (m_pOwnerScene->findObject(L"Player"))
	{
		vPlayerPos = m_pOwnerScene->findObject(L"Player")->getObjPos();
		fDist = (vPlayerPos - getObjPos()).length();
	}
	


	if (3. <= m_dAccTime && fDist < 300.f)
	{
		KamikazeLite* pKamikazeLite = m_pOwnerScene->createObject<KamikazeLite>(L"KamikazeLite");
		pKamikazeLite->setObjPos(getObjPos() + Vec(0.f, 35.f));
		m_dAccTime = 0.;
	}
}

void SpawnMonster::postUpdate()
{
	Object::postUpdate();
}

void SpawnMonster::collision()
{
	Object::collision();
}

void SpawnMonster::render(HDC _hDC)
{
	Object::render(_hDC);
}

void SpawnMonster::start()
{
	Object::start();
	changeAnimation(L"spr_monster_spawn_idle");	
}

void SpawnMonster::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
	if (_pDes->getOwnerObject()->getObjName() == L"Player" && 0.2 <= m_dAccTime)
	{
		m_bDigging = true;
		EffectHit* pHit = getOwnerScene()->createObject<EffectHit>(L"spr_shovel", L"spr_shovel",
			getObjPos(), Vec(114.f, 94.f));
		pHit->changeAnimation(L"spr_shovel");
	}
}

void SpawnMonster::collisionEnd(Collider* _pSrc, Collider* _pDes)
{
	m_bDigging = false;
}
