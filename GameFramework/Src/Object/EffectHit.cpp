// EffectHit.cpp

#include "../GameInfo.h"
#include "EffectHit.h"
#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"

EffectHit::EffectHit()
{
    m_eObjectType = EOBJECT_TYPE::EFFECT;
}

EffectHit::~EffectHit()
{
}

EffectHit::EffectHit(const EffectHit& _Other)
    : Object(_Other)
{
}

EffectHit* EffectHit::Clone()
{
    return new EffectHit(*this);
}

bool EffectHit::init()
{
    if (!Object::init())
    {
        return false;
    }
    
    createAnimation();
    addAnimation(L"BodyHit", false, 0.2f);
    addAnimation(L"spr_hit_fire", false, 0.2f);
    addAnimation(L"spr_hit_bomb", false, 1.5f);
    Vec vOffset = Vec(0.f, -400.f);
    addAnimation(L"spr_shovel", false, 4.f, 1.f, false, vOffset);
    
    return true;
}

void EffectHit::update()
{
    Object::update();
}

void EffectHit::postUpdate()
{
    Object::postUpdate();
}

void EffectHit::collision()
{
    Object::collision();
}

void EffectHit::render(HDC _dc)
{
    Object::render(_dc);
}

void EffectHit::start()
{
    Object::start();

    createAnimation();
    
    wstring strTemp = L"BodyHit";
    setAnimationEndNotify<EffectHit>(strTemp, this, &EffectHit::animationFinish);
    strTemp = L"spr_shovel";
    setAnimationEndNotify<EffectHit>(strTemp, this, &EffectHit::animationFinish);
    strTemp = L"spr_hit_fire";
    setAnimationEndNotify<EffectHit>(strTemp, this, &EffectHit::animationFinish);
    strTemp = L"spr_hit_bomb";
    setAnimationEndNotify<EffectHit>(strTemp, this, &EffectHit::animationFinish);
    addAnimationNotify<EffectHit>(strTemp, 5, this, &EffectHit::bomb);
}

void EffectHit::animationFinish()
{
    destroy();
}

void EffectHit::bomb()
{
    // 266 250
    Vec vPlayerPos = m_pOwnerScene->findObject(L"Player")->getObjPos();
    Vec vExplosionPos = getObjPos();

    if (vExplosionPos.x <= vPlayerPos.x && vPlayerPos.x <= (vExplosionPos.x + 133.f) &&
        vExplosionPos.y <= vPlayerPos.y && vPlayerPos.y <= (vExplosionPos.y + 125.f))
    {
        m_pOwnerScene->findObject(L"Player")->setDamage(9999.f);
    }
}
