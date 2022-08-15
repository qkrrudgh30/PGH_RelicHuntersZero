// Kamikaze.cpp

#include "../GameInfo.h"
#include "Kamikaze.h"
#include "../Timer.h"
#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../UI/UIWidgetProgressBar.h"
#include "../UI/UIWidgetImage.h"

Kamikaze::Kamikaze()
	: m_bBite(false)
	, m_dAccTime(0.)
{
	setObjSpeed(80.f);
	m_CharacterInfo.nHP = 100;
	m_CharacterInfo.nMaxHP = 100;
	m_CharacterInfo.nAttack = 30;
}

Kamikaze::Kamikaze(const Kamikaze& _Other)
	: Monster(_Other)
	, m_bBite(false)
	, m_dAccTime(0.)
{
}

Kamikaze::~Kamikaze()
{
}

Kamikaze* Kamikaze::Clone()
{
	return new Kamikaze(*this);
}

bool Kamikaze::init()
{
	if (false == Monster::init())
	{
		return false;
	}

	ColliderBox* pMonsterBody = addCollider<ColliderBox>(L"MonsterBody");
	pMonsterBody->setExtent(40.f, 30.f);
	pMonsterBody->setOffset(Vec(0.f, 30.f));
	pMonsterBody->setProfile(L"Monster");
	pMonsterBody->setCollisionBeginFunc<Kamikaze>(this, &Kamikaze::collisionBegin);
	pMonsterBody->setCollisionEndFunc<Kamikaze>(this, &Kamikaze::collisionEnd);
	// setObjPos(getOwnerScene()->findObject(L"KamikazeSpawn")->getObjPos() + Vec(0.f, 40.f));

	createAnimation();
	addAnimation(L"spr_Kamikaze_left_idle");
	addAnimation(L"spr_Kamikaze_left_hit", false, 0.2f);
	addAnimation(L"spr_Kamikaze_left_die", false, 0.8f);
	addAnimation(L"spr_Kamikaze_right_idle");
	addAnimation(L"spr_Kamikaze_right_hit", false, 0.2f);
	addAnimation(L"spr_Kamikaze_right_die", false, 0.8f);
	addAnimation(L"spr_Kamikaze_explosion", false);

	wstring strAniName = L"spr_Kamikaze_left_hit";
	setAnimationEndNotify<Kamikaze>(strAniName, this, &Kamikaze::hit);

	strAniName = L"spr_Kamikaze_right_hit";
	setAnimationEndNotify<Kamikaze>(strAniName, this, &Kamikaze::hit);

	strAniName = L"spr_Kamikaze_left_die";
	setAnimationEndNotify<Kamikaze>(strAniName, this, &Kamikaze::die);

	strAniName = L"spr_Kamikaze_right_die";
	setAnimationEndNotify<Kamikaze>(strAniName, this, &Kamikaze::die);

	strAniName = L"spr_Kamikaze_right_idle";
	setAnimationEndNotify<Kamikaze>(strAniName, this, &Kamikaze::walk);

	strAniName = L"spr_Kamikaze_right_idle";
	setAnimationEndNotify<Kamikaze>(strAniName, this, &Kamikaze::walk);

	strAniName = L"spr_Kamikaze_explosion";
	setAnimationEndNotify<Kamikaze>(strAniName, this, &Kamikaze::explosion);

	return true;
}

void Kamikaze::update()
{
	Monster::update();

	Vec vMonPos = getObjPos();
	Vec vDir;
	m_vDir = getOwnerScene()->findObject(L"Player")->getObjPos() - vMonPos;
	vDir = m_vDir;
	vDir.normalize();
	move(vDir);

	if (true == m_bBite)
	{
		m_dAccTime += DT;
	}

	if (m_pCurAnimation->checkCurAnimation(L"spr_Kamikaze_left_idle") || m_pCurAnimation->checkCurAnimation(L"spr_Kamikaze_right_idle"))
	{
		if (m_vDir.x <= 0)
		{
			changeAnimation(L"spr_Kamikaze_left_idle");
		}
		else
		{
			changeAnimation(L"spr_Kamikaze_right_idle");
		}
	}
}

void Kamikaze::postUpdate()
{
	Monster::postUpdate();
}

void Kamikaze::collision()
{
	Monster::collision();
}

void Kamikaze::render(HDC _dc)
{
	Monster::render(_dc);
}

void Kamikaze::start()
{
	Monster::start();
}

void Kamikaze::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
	if (_pDes->getOwnerObject()->getObjName() == L"PlayerBullet")
	{
		if (m_vDir.x <= 0)
		{
			changeAnimation(L"spr_Kamikaze_left_hit");
		}
		else
		{
			changeAnimation(L"spr_Kamikaze_right_hit");
		}
	}
	else if (_pDes->getOwnerObject()->getObjName() == L"Player")
	{
		if (m_bBite == false)
		{
			_pDes->getOwnerObject()->setDamage((float)m_CharacterInfo.nAttack);
			m_bBite = true;
		}
		changeAnimation(L"spr_Kamikaze_explosion");
		setObjSpeed(0.f);
	}
	else if (_pDes->getOwnerObject()->getObjName() == L"WallTile")
	{
		changeAnimation(L"spr_Kamikaze_explosion");
		setObjSpeed(0.f);
	}
}

void Kamikaze::collisionEnd(Collider* _pSrc, Collider* _pDes)
{
}

void Kamikaze::hit()
{
	if (0 < m_CharacterInfo.nHP)
	{
		if (m_vDir.x <= 0)
		{
			changeAnimation(L"spr_Kamikaze_left_idle");
		}
		else
		{
			changeAnimation(L"spr_Kamikaze_right_idle");
		}
	}
	else
	{
		if (m_vDir.x < 0)
		{
			setObjSpeed(0.f);
			changeAnimation(L"spr_Kamikaze_left_die");
		}
		else
		{
			setObjSpeed(0.f);
			changeAnimation(L"spr_Kamikaze_right_die");
		}
	}
}

void Kamikaze::die()
{
	destroy();
}

void Kamikaze::explosion()
{
	destroy();
}

void Kamikaze::walk()
{
	if (m_vDir.x <= 0)
	{
		changeAnimation(L"spr_Kamikaze_left_idle");
	}
	else
	{
		changeAnimation(L"spr_Kamikaze_right_idle");
	}
}
