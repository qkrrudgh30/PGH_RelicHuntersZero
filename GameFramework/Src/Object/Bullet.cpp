// Bullet.cpp

#include "../GameInfo.h"
#include "Bullet.h"
#include "../Timer.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"
#include "../Object/EffectHit.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Object/Monster.h"

Bullet::Bullet()
    : m_vDir{1.f, 0.f}
    , m_fDistance(1000.f)
    , m_pCollider(nullptr)
    , m_fDamage(10.f)
{    
    setObjSpeed(600.f);
    m_eObjectType = EOBJECT_TYPE::BULLET;
}

Bullet::~Bullet()
{
}

Bullet::Bullet(const Bullet& _Other)
    : Object(_Other)
{
    m_vDir = _Other.m_vDir;
    m_fDistance = _Other.m_fDistance;
    m_pCollider = _Other.m_pCollider;
    m_fDamage = _Other.m_fDamage;
}

Bullet* Bullet::Clone()
{
    return new Bullet(*this);
}

bool Bullet::init()
{
    if (!Object::init())
    {
        return false;
    }

    // setTexture(L"BulletBlueIdle", L"spr_bullet_blue_idle.bmp");
    // setTextureColorKey(255, 0, 255);

    createAnimation();
    addAnimation(L"spr_bullet_right_blue", false, 0.2f);
    addAnimation(L"spr_bullet_left_blue", false, 0.2f);
    addAnimation(L"spr_bullet_fire", true, 0.5f);

    return true;
}

void Bullet::update()
{
    Object::update();

    Vec vDir = getDir();
    vDir.normalize();
    move(vDir);

    m_fDistance -= getObjSpeed() * getObjTimeScale() * fDT;
    if (m_fDistance <= 0)
    {
        destroy();
    }

    if (getObjName() == L"MonsterBullet")
    {
        changeAnimation(L"spr_bullet_fire");
    }
    else
    {
        if (m_vDir.x < 0.f)
        {
            changeAnimation(L"spr_bullet_left_blue");
        }
        else
        {
            changeAnimation(L"spr_bullet_right_blue");
        }
    }
    
}


void Bullet::postUpdate()
{
    Object::postUpdate();
}

void Bullet::collision()
{
    Object::collision();
}

void Bullet::render(HDC _dc)
{
    Object::render(_dc);
}

void Bullet::start()
{
    Object::start();

    ColliderSphere* pBulletBody = addCollider<ColliderSphere>(L"BulletBody");
    m_pCollider = (Collider*)pBulletBody;
    pBulletBody->setRadius(20.f);
    pBulletBody->setOffset(Vec(2.f, 0.f));
    pBulletBody->setCollisionBeginFunc<Bullet>(this, &Bullet::collisionBegin);
    pBulletBody->setCollisionEndFunc<Bullet>(this, &Bullet::collisionEnd);
}

void Bullet::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
    destroy();

    _pDes->getOwnerObject()->setDamage(m_fDamage);
    if (_pDes->getOwnerObject()->getObjName() == L"KamikazeLite")
    {
        Monster* temp = (Monster*)_pDes->getOwnerObject();
        if (temp->getMonsterDir().x <= 0)
        {
            _pDes->getOwnerObject()->changeAnimation(L"spr_kamikazelite_left_hit");
        }
        else
        {
            _pDes->getOwnerObject()->changeAnimation(L"spr_kamikazelite_right_hit");
        }
    }

    if (_pDes->getOwnerObject()->getObjName() == L"KamikazeCage")
    {
        _pDes->getOwnerObject()->changeAnimation(L"spr_kamikazecage_hit");
    }

    if (_pDes->getOwnerObject()->getObjName() == L"Kamikaze")
    {
        Monster* temp = (Monster*)_pDes->getOwnerObject();
        if (temp->getMonsterDir().x <= 0)
        {
            _pDes->getOwnerObject()->changeAnimation(L"spr_Kamikaze_left_hit");
        }
        else
        {
            _pDes->getOwnerObject()->changeAnimation(L"spr_Kamikaze_right_hit");
        }
    }

    if (_pDes->getOwnerObject()->getObjName() == L"KamikazeBoss")
    {
        Monster* temp = (Monster*)_pDes->getOwnerObject();
        if (temp->getMonsterDir().x <= 0)
        {
            _pDes->getOwnerObject()->changeAnimation(L"spr_kamikazeboss_left_hit");
        }
        else
        {
            _pDes->getOwnerObject()->changeAnimation(L"spr_kamikazeboss_right_hit");
        }
    }

    EffectHit* pHit = getOwnerScene()->createObject<EffectHit>(L"BodyHit", L"BodyHit",
        getObjPos(), Vec(92.f, 92.f));

    if (_pSrc->getOwnerObject()->getObjName() == L"MonsterBullet")
    {
        pHit->setCurAnimation(L"spr_hit_fire");
    }


    getOwnerScene()->getSceneResource()->playSound(L"EffectHit");
}

void Bullet::collisionEnd(Collider* _pSrc, Collider* _pDes)
{
}
