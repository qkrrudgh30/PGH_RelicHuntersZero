#include "../GameInfo.h"
#include "Potal.h"
#include "../Timer.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneStage2.h"
#include "KamikazeLite.h"
#include "../Collision/Collider.h"
#include "../Collision/ColliderSphere.h"
#include "../Collision/ColliderBox.h"
#include "EffectHit.h"
#include "../Scene/Camera.h"

Potal::Potal()
	: m_bTeleport(false)
{
}

Potal::Potal(const Potal& _Other)
{
}

Potal::~Potal()
{
}

Potal* Potal::Clone()
{
	return new Potal(*this);
}

bool Potal::init()
{
	if (false == Object::init())
	{
		return false;
	}

	ColliderBox* pSpawnMonster = addCollider<ColliderBox>(L"Potal");
	m_pCollider = (Collider*)pSpawnMonster;
	pSpawnMonster->setExtent(60.f, 60.f);
	pSpawnMonster->setOffset(Vec(0.f, 10.f));
	pSpawnMonster->setProfile(L"Monster");
	pSpawnMonster->setCollisionBeginFunc<Potal>(this, &Potal::collisionBegin);
	pSpawnMonster->setCollisionEndFunc<Potal>(this, &Potal::collisionEnd);

	createAnimation();
	addAnimation(L"spr_effect_potal_create");
	addAnimation(L"spr_effect_potal_idle");

	wstring strAniName = L"spr_effect_potal_create";
	setAnimationEndNotify<Potal>(strAniName, this, &Potal::createPotal);
	
	return true;
}

void Potal::update()
{
	Object::update();

	if (m_bTeleport)
	{
		m_pOwnerScene->getCamera()->fadeOut(3.f);
		SceneManager::getInst()->createScene<SceneStage2>();
		m_bTeleport = false;
	}
}

void Potal::postUpdate()
{
	Object::postUpdate();
}

void Potal::collision()
{
	Object::collision();
}

void Potal::render(HDC _hDC)
{
	Object::render(_hDC);
}

void Potal::start()
{
	Object::start();
}

void Potal::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
}

void Potal::collisionEnd(Collider* _pSrc, Collider* _pDes)
{
	if (_pDes->getOwnerObject()->getObjName() == L"Player")
	{
		m_bTeleport = true;
	}
}

void Potal::createPotal()
{
	changeAnimation(L"spr_effect_potal_idle");
}
