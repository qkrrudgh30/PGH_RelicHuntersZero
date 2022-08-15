// KamikazeLite.cpp

#include "../GameInfo.h"
#include "KamikazeLite.h"
#include "../Timer.h"
#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../UI/UIWidgetProgressBar.h"
#include "../UI/UIWidgetImage.h"

KamikazeLite::KamikazeLite()
    : m_bBite(false)
    , m_dAccTime(0.)
{
	setObjSpeed(50.f);
	m_CharacterInfo.nHP = 60;
	m_CharacterInfo.nMaxHP = 60;
    m_CharacterInfo.nAttack = 20;
}

KamikazeLite::KamikazeLite(const KamikazeLite& _Other)
	: Monster(_Other)
{
    m_bBite = false;
    m_dAccTime = 0.;
}

KamikazeLite::~KamikazeLite()
{
}

KamikazeLite* KamikazeLite::Clone()
{
	return new KamikazeLite(*this);
}

bool KamikazeLite::init()
{
    if (false == Monster::init())
    {
        return false;
    }

    ColliderBox* pMonsterBody = addCollider<ColliderBox>(L"MonsterBody");
    pMonsterBody->setExtent(40.f, 30.f);
    pMonsterBody->setOffset(Vec(0.f, 30.f));
    pMonsterBody->setProfile(L"Monster");
    pMonsterBody->setCollisionBeginFunc<KamikazeLite>(this, &KamikazeLite::collisionBegin);
    pMonsterBody->setCollisionEndFunc<KamikazeLite>(this, &KamikazeLite::collisionEnd);

	createAnimation();
	addAnimation(L"spr_kamikazelite_left_idle");
	addAnimation(L"spr_kamikazelite_left_hit", false, 0.2f);
	addAnimation(L"spr_kamikazelite_left_die", false, 0.8f);
	addAnimation(L"spr_kamikazelite_right_idle");
	addAnimation(L"spr_kamikazelite_right_hit", false, 0.2f);
	addAnimation(L"spr_kamikazelite_right_die", false, 0.8f);
	addAnimation(L"spr_kamikazelite_explosion", false);

    wstring strAniName = L"spr_kamikazelite_left_hit";
    setAnimationEndNotify<KamikazeLite>(strAniName, this, &KamikazeLite::hit);

    strAniName = L"spr_kamikazelite_right_hit";
    setAnimationEndNotify<KamikazeLite>(strAniName, this, &KamikazeLite::hit);

    strAniName = L"spr_kamikazelite_left_die";
    setAnimationEndNotify<KamikazeLite>(strAniName, this, &KamikazeLite::die);

    strAniName = L"spr_kamikazelite_right_die";
    setAnimationEndNotify<KamikazeLite>(strAniName, this, &KamikazeLite::die);

    strAniName = L"spr_kamikazelite_explosion";
    setAnimationEndNotify<KamikazeLite>(strAniName, this, &KamikazeLite::explosion);

	return true;
}

void KamikazeLite::update()
{
    Monster::update();

    Vec vMonPos = getObjPos();
    m_vDir = getOwnerScene()->findObject(L"Player")->getObjPos() - vMonPos;
    m_vDir.normalize();
    move(m_vDir);

    if (m_pCurAnimation->checkCurAnimation(L"spr_kamikazelite_left_idle") || m_pCurAnimation->checkCurAnimation(L"spr_kamikazelite_right_idle"))
    {
        if (m_vDir.x <= 0)
        {
            changeAnimation(L"spr_kamikazelite_left_idle");
        }
        else
        {
            changeAnimation(L"spr_kamikazelite_right_idle");
        }
    }
    

    if (true == m_bBite)
    {
        m_dAccTime += DT;
    }

    /*
    vPos += m_vDir * getObjSpeed() * getObjTimeScale() * fDT;
    if (720.f <= (vPos.y + vScale.y / 2))
    {
        vPos.y = 720.f - vScale.y / 2;
        m_vDir.y *= -1;
    }
    else if ((vPos.y - vScale.y / 2) <= 0.f)
    {
        vPos.y = 0.f + vScale.y / 2;
        m_vDir *= -1;
    }
    setObjPos(vPos);

    m_fFireTime -= fDT;
    if (m_fFireTime <= 0.f && m_bFire)
    {
        ++m_nCount;

        SharedPtr<Bullet> pBullet = getOwnerScene()->createObject<Bullet>(L"MonsterBullet", L"MonsterBullet",
            Vec(vPos + Vec(100.f, 25.f)), Vec(50.f, 50.f));
        pBullet->getBulletCollider()->setProfile(L"MonsterBullet");
        pBullet->setBulletDamage(15.f);

        if (m_nCount % 3 != 0)
        {
            pBullet->setDir(Vec(-1.f, 0.f));
        }
        else
        {
            Object* pPlayer = getOwnerScene()->findObject(L"Player");
            float fAngle = getAngle(pBullet->getObjPos(), pPlayer->getObjPos());
            pBullet->setDir(fAngle);
        }

        m_fFireTime = 1.f;

    }
    */
}

void KamikazeLite::postUpdate()
{
    Monster::postUpdate();
}

void KamikazeLite::collision()
{
    Monster::collision();
}

void KamikazeLite::render(HDC _dc)
{
    Monster::render(_dc);
}

void KamikazeLite::start()
{
    Monster::start();
}

void KamikazeLite::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
    if (_pDes->getOwnerObject()->getObjName() == L"PlayerBullet")
    {
        if (m_vDir.x <= 0)
        {
            changeAnimation(L"spr_kamikazelite_left_hit");
        }
        else
        {
            changeAnimation(L"spr_kamikazelite_right_hit");
        }
    }
    else if (_pDes->getOwnerObject()->getObjName() == L"Player")
    {
        if (m_bBite == false)
        {
            _pDes->getOwnerObject()->setDamage((float)m_CharacterInfo.nAttack);
            m_bBite = true;
        }
        changeAnimation(L"spr_kamikazelite_explosion");
        setObjSpeed(0.f);
    }
    else if (_pDes->getOwnerObject()->getObjName() == L"WallTile")
    {
        changeAnimation(L"spr_kamikazelite_explosion");
        setObjSpeed(0.f);
    }

    /*
    m_bBite = true;
    m_dAccTime = 0.;
    */
}

void KamikazeLite::collisionEnd(Collider* _pSrc, Collider* _pDes)
{
    /*
    int nDamage = (int)m_dAccTime * m_CharacterInfo.nAttack;
    _pDes->getOwnerObject()->setDamage((float)nDamage);
    m_bBite = false;
    m_dAccTime = 0.;
    */
}

void KamikazeLite::hit()
{
    if (0 < m_CharacterInfo.nHP)
    {
        if (m_vDir.x <= 0)
        {
            changeAnimation(L"spr_kamikazelite_left_idle");
        }
        else
        {
            changeAnimation(L"spr_kamikazelite_right_idle");
        }
    }
    else
    {
        if (m_vDir.x < 0)
        {
            setObjSpeed(0.f);
            changeAnimation(L"spr_kamikazelite_left_die");
        }
        else
        {
            setObjSpeed(0.f);
            changeAnimation(L"spr_kamikazelite_right_die");
        }
    }
}

void KamikazeLite::die()
{
    destroy();
}

void KamikazeLite::explosion()
{
    destroy();
}
