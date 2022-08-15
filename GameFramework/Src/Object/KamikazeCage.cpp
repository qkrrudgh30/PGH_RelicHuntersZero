// KamikazeCage.h

#include "../GameInfo.h"
#include "KamikazeCage.h"
#include "../Timer.h"
#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../UI/UIWidgetProgressBar.h"
#include "../UI/UIWidgetImage.h"
#include "Kamikaze.h"

KamikazeCage::KamikazeCage()
{
	setObjSpeed(0.f);
	m_CharacterInfo.nHP = 120;
	m_CharacterInfo.nMaxHP = 120;
}

KamikazeCage::KamikazeCage(const KamikazeCage& _Other)
	: Monster(_Other)
{
}

KamikazeCage::~KamikazeCage()
{
}

KamikazeCage* KamikazeCage::Clone()
{
	return new KamikazeCage(*this);
}

bool KamikazeCage::init()
{
	if (false == Monster::init())
	{
		return false;
	}

	ColliderBox* pKamikazeCage = addCollider<ColliderBox>(L"KamikazeCage");
	pKamikazeCage->setExtent(130.f, 120.f);
	pKamikazeCage->setOffset(Vec(0.f, -10.f));
	pKamikazeCage->setProfile(L"Monster");
	pKamikazeCage->setCollisionBeginFunc<KamikazeCage>(this, &KamikazeCage::collisionBegin);
	pKamikazeCage->setCollisionEndFunc<KamikazeCage>(this, &KamikazeCage::collisionEnd);
	
	m_pHPBar->setComponentPos(Vec(-15.f, -70.f));

	createAnimation();
	addAnimation(L"spr_kamikazecage_idle");
	addAnimation(L"spr_kamikazecage_hit");
	addAnimation(L"spr_kamikazecage_die");

	wstring strAniName = L"spr_kamikazecage_hit";
	setAnimationEndNotify<KamikazeCage>(strAniName, this, &KamikazeCage::hit);

	strAniName = L"spr_kamikazecage_die";
	setAnimationEndNotify<KamikazeCage>(strAniName, this, &KamikazeCage::die);

	return true;
}

void KamikazeCage::update()
{
	Monster::update();
}

void KamikazeCage::postUpdate()
{
	Monster::postUpdate();
}

void KamikazeCage::collision()
{
	Monster::collision();
}

void KamikazeCage::render(HDC _dc)
{
	Monster::render(_dc);
}

void KamikazeCage::start()
{
	Monster::start();
}

void KamikazeCage::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
	changeAnimation(L"spr_kamikazecage_hit");
}

void KamikazeCage::collisionEnd(Collider* _pSrc, Collider* _pDes)
{
}

void KamikazeCage::hit()
{
	if (0 < m_CharacterInfo.nHP)
	{
		changeAnimation(L"spr_kamikazecage_idle");
	}
	else
	{
		changeAnimation(L"spr_kamikazecage_die");
	}
}

void KamikazeCage::die()
{
	/*
	size_t uKamikazeCount = 6;
	for (size_t i = 0; i < uKamikazeCount; ++i)
	{

	}
	*/

	Kamikaze* pKamikaze = getOwnerScene()->createObject<Kamikaze>(L"Kamikaze", getObjPos());

	destroy();
}

void KamikazeCage::explosion()
{
}
