// Boss.cpp

#include "../GameInfo.h"
#include "KamikazeBoss.h"
#include "../Timer.h"
#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../UI/UIWidgetProgressBar.h"
#include "../UI/UIWidgetImage.h"
#include "../Object/Object.h"
#include "../Object/EffectHit.h"
#include "../Scene/MainScene.h"
#include "../Scene/SceneResource.h"
#include "../Scene/Camera.h"
#include "../Resource/ResourceManager.h"

KamikazeBoss::KamikazeBoss()
	: m_dAccTime(0.)
	, m_bAttackState(false)
	, m_bAttack(false)
	, m_bSkill(false)
	, m_bToggle(false)
{
	setObjSpeed(100.f);
	m_CharacterInfo.nHP = 200;
	m_CharacterInfo.nMaxHP = 200;
	m_CharacterInfo.nAttack = 50;
}

KamikazeBoss::KamikazeBoss(const KamikazeBoss& _Other)
	: Monster(_Other)
	, m_dAccTime(0.)
	, m_bAttackState(false)
	, m_bToggle(false)
{
}

KamikazeBoss::~KamikazeBoss()
{
}

KamikazeBoss* KamikazeBoss::Clone()
{
	return new KamikazeBoss(*this);
}

bool KamikazeBoss::init()
{
	if (false == Monster::init())
	{
		return false;
	}

	ColliderBox* pMonsterBody = addCollider<ColliderBox>(L"MonsterBody");
	pMonsterBody->setExtent(74.f, 82.f);
	pMonsterBody->setOffset(Vec(0.f, 10.f));
	pMonsterBody->setProfile(L"Monster");
	pMonsterBody->setCollisionBeginFunc<KamikazeBoss>(this, &KamikazeBoss::collisionBegin);
	pMonsterBody->setCollisionEndFunc<KamikazeBoss>(this, &KamikazeBoss::collisionEnd);
	
	m_pHPBar->setComponentPos(Vec(-15.f, -50.f));

	createAnimation();
	addAnimation(L"spr_kamikazeboss_right_egg", true, 1.f);
	addAnimation(L"spr_kamikazeboss_right_crack", false, 3.f);
	addAnimation(L"spr_kamikazeboss_right_spawn", false, 1.f);
	addAnimation(L"spr_kamikazeboss_right_idle", true, 2.5f);
	addAnimation(L"spr_kamikazeboss_right_hit", false, 0.2f);
	addAnimation(L"spr_kamikazeboss_right_die", false, 1.f);
	addAnimation(L"spr_kamikazeboss_right_attack", false, 0.3f);
	addAnimation(L"spr_kamikazeboss_right_bomb", false, 1.f);
	addAnimation(L"spr_kamikazeboss_left_idle", true, 2.5f);
	addAnimation(L"spr_kamikazeboss_left_hit", false, 0.2f);
	addAnimation(L"spr_kamikazeboss_left_die", false, 1.f);
	addAnimation(L"spr_kamikazeboss_left_attack", false, 0.3f);
	addAnimation(L"spr_kamikazeboss_left_bomb", false, 1.f);

	wstring strAniName = L"spr_kamikazeboss_right_hit";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::hit);

	strAniName = L"spr_kamikazeboss_left_hit";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::hit);

	strAniName = L"spr_kamikazeboss_right_egg";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::egg);

	strAniName = L"spr_kamikazeboss_right_spawn";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::spawn);

	strAniName = L"spr_kamikazeboss_right_crack";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::crack);
	addAnimationNotify<KamikazeBoss>(strAniName, 2, this, &KamikazeBoss::beginCrack);

	strAniName = L"spr_kamikazeboss_right_die";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::die);

	strAniName = L"spr_kamikazeboss_left_die";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::die);

	strAniName = L"spr_kamikazeboss_right_idle";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::walk);

	strAniName = L"spr_kamikazeboss_left_idle";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::walk);

	strAniName = L"spr_kamikazeboss_right_attack";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::attack);
	addAnimationNotify<KamikazeBoss>(strAniName, 2, this, &KamikazeBoss::attackBegin);

	strAniName = L"spr_kamikazeboss_left_attack";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::attack);
	addAnimationNotify<KamikazeBoss>(strAniName, 2, this, &KamikazeBoss::attackBegin);

	strAniName = L"spr_kamikazeboss_right_bomb";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::bomb);
	addAnimationNotify<KamikazeBoss>(strAniName, 7, this, &KamikazeBoss::bombBegin);

	strAniName = L"spr_kamikazeboss_left_bomb";
	setAnimationEndNotify<KamikazeBoss>(strAniName, this, &KamikazeBoss::bomb);
	addAnimationNotify<KamikazeBoss>(strAniName, 7, this, &KamikazeBoss::bombBegin);

	setCurAnimation(L"spr_kamikazeboss_right_egg");

	return true;
}

void KamikazeBoss::update()
{
	Monster::update();

	m_dAccTime += DT;

	bool bEgg = checkCurAnimation(L"spr_kamikazeboss_right_egg");
	bool bCrack = checkCurAnimation(L"spr_kamikazeboss_right_crack");
	bool bSpawn = checkCurAnimation(L"spr_kamikazeboss_right_spawn");
	
	if (!bEgg && !bCrack && !bSpawn)
	{
		Vec vMonPos = getObjPos();
		Vec vDir;
		m_vDir = getOwnerScene()->findObject(L"Player")->getObjPos() - vMonPos;
		float fDistance = m_vDir.length();
		vDir = m_vDir;
		vDir.normalize();
		m_bAttackState = false;

		if (fDistance <= 500.f)
		{
			if (fDistance <= 300.f)
			{
				m_bAttackState = true;
				setObjSpeed(0.f);
				
			}
			else
			{
				
				if (m_vDir.x <= 0)
				{
					changeAnimation(L"spr_kamikazeboss_left_idle");
				}
				else
				{
					changeAnimation(L"spr_kamikazeboss_right_idle");
				}
				setObjSpeed(100.f);
				move(vDir);
			}
		}

		

		if (m_bAttackState && 3. <= m_dAccTime)
		{
			if (m_vDir.x <= 0)
			{
				if (60 <= m_CharacterInfo.nHP)
				{
					changeAnimation(L"spr_kamikazeboss_left_attack");
				}
				else
				{
					if (m_bToggle == false)
					{
						changeAnimation(L"spr_kamikazeboss_left_attack");
					}
					else
					{
						changeAnimation(L"spr_kamikazeboss_left_bomb");
					}
					m_bToggle = !m_bToggle;
				}
			}
			else
			{
				if (60 <= m_CharacterInfo.nHP)
				{
					changeAnimation(L"spr_kamikazeboss_right_attack");
				}
				else
				{
					if (m_bToggle == false)
					{
						changeAnimation(L"spr_kamikazeboss_right_attack");
					}
					else
					{
						changeAnimation(L"spr_kamikazeboss_right_bomb");
					}
					m_bToggle = !m_bToggle;
				}
			}
			m_dAccTime = 0.;
		}

		/*
		if (m_pCurAnimation->checkCurAnimation(L"spr_kamikazeboss_right_idle") || m_pCurAnimation->checkCurAnimation(L"spr_kamikazeboss_left_idle"))
		{
			if (m_vDir.x <= 0)
			{
				changeAnimation(L"spr_kamikazeboss_left_idle");
			}
			else
			{
				changeAnimation(L"spr_kamikazeboss_right_idle");
			}
		}
		*/
	}
	
}

void KamikazeBoss::postUpdate()
{
	Monster::postUpdate();
}

void KamikazeBoss::collision()
{
	Monster::collision();
}

void KamikazeBoss::render(HDC _dc)
{
	Monster::render(_dc);
}

void KamikazeBoss::start()
{
	Monster::start();
}

void KamikazeBoss::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
	if (_pDes->getOwnerObject()->getObjName() == L"PlayerBullet")
	{
		if (m_vDir.x <= 0)
		{
			changeAnimation(L"spr_kamikazeboss_left_hit");
		}
		else
		{
			changeAnimation(L"spr_kamikazeboss_right_hit");
		}
	}
}

void KamikazeBoss::collisionEnd(Collider* _pSrc, Collider* _pDes)
{
}

void KamikazeBoss::egg()
{
}

void KamikazeBoss::crack()
{
	changeAnimation(L"spr_kamikazeboss_right_spawn");
}

void KamikazeBoss::beginCrack()
{
	getOwnerScene()->getCamera()->moveAccelateCamera(getObjPos(), Vec(500.f, 500.f));
}

void KamikazeBoss::spawn()
{
	changeAnimation(L"spr_kamikazeboss_right_idle");
	getOwnerScene()->getCamera()->moveAccelateCamera(m_pOwnerScene->findObject(L"Player")->getObjPos(), Vec(500.f, 500.f));
}

void KamikazeBoss::hit()
{
	if (0 < m_CharacterInfo.nHP)
	{
		if (m_vDir.x <= 0)
		{
			changeAnimation(L"spr_kamikazeboss_left_idle");
		}
		else
		{
			changeAnimation(L"spr_kamikazeboss_right_idle");
		}
	}
	else
	{
		if (m_vDir.x < 0)
		{
			setObjSpeed(0.f);
			changeAnimation(L"spr_kamikazeboss_left_die");
		}
		else
		{
			setObjSpeed(0.f);
			changeAnimation(L"spr_kamikazeboss_right_die");
		}
	}
}

void KamikazeBoss::die()
{
	destroy();

	m_pOwnerScene->getCamera()->changeEndingVeil();
	m_pOwnerScene->getCamera()->setEndingOn();
	m_pOwnerScene->getCamera()->fadeOut(2.f);
}

void KamikazeBoss::walk()
{
}

void KamikazeBoss::attack()
{
	if (m_vDir.x <= 0)
	{
		//changeAnimation(L"spr_kamikazeboss_left_idle");
	}
	else
	{
		//changeAnimation(L"spr_kamikazeboss_right_idle");
	}
}

void KamikazeBoss::attackBegin()
{
	Vec vPos = getObjPos();
	Vec vScale = getObjScale();
	SharedPtr<Bullet> pBullet;

	if (m_vDir.x < 0)
	{
		pBullet = getOwnerScene()->createObject<Bullet>(L"MonsterBullet", L"MonsterBullet",
			Vec(vPos + Vec(-40.f, +40.f)), Vec(50.f, 50.f));

		Object* pPlayer = m_pOwnerScene->findObject(L"Player");
		Vec vPlayer = pPlayer->getObjPos();
		Vec vDir = vPlayer - getObjPos();
		vDir.normalize();
		pBullet->setDir(vDir);
		pBullet->setCurAnimation(L"spr_bullet_fire");
		changeAnimation(L"spr_kamikazeboss_left_idle");
	}
	else
	{
		pBullet = getOwnerScene()->createObject<Bullet>(L"MonsterBullet", L"MonsterBullet",
			Vec(vPos + Vec(-40.f, +40.f)), Vec(50.f, 50.f));
		Object* pPlayer = m_pOwnerScene->findObject(L"Player");
		Vec vPlayer = pPlayer->getObjPos();
		Vec vDir = vPlayer - getObjPos();
		vDir.normalize();
		pBullet->setDir(vDir);
		pBullet->setCurAnimation(L"spr_bullet_fire");
		changeAnimation(L"spr_kamikazeboss_right_idle");
	}

	pBullet->getBulletCollider()->setProfile(L"MonsterBullet");
	pBullet->setBulletDamage(30.f);
}

void KamikazeBoss::bomb()
{
	if (m_vDir.x <= 0)
	{
		changeAnimation(L"spr_kamikazeboss_left_idle");
	}
	else
	{
		changeAnimation(L"spr_kamikazeboss_right_idle");
	}
}

void KamikazeBoss::bombBegin()
{
	Vec vPlayerPos = m_pOwnerScene->findObject(L"Player")->getObjPos();
	EffectHit* pHit = getOwnerScene()->createObject<EffectHit>(L"spr_hit_bomb", L"BodyHit",
		vPlayerPos, Vec(266.f, 255.f));
	pHit->setCurAnimation(L"spr_hit_bomb");
}
