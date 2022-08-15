// Gun.cpp

#include "../GameInfo.h"
#include "Gun.h"
#include "../GameManager.h"
#include "../Timer.h"
#include "../Scene/Scene.h"
#include "Player.h"
#include "../Input.h"
#include "Bullet.h"
#include "../Scene/Camera.h"

Gun::Gun()
    : m_vDir{ 1.f, 0.f }
    , m_bFire(false)
    , m_arrPoint{}
    , m_arrDir{}
    , m_arrDistance{}
    , m_arrRotatedPoint{}
    , m_dAccTime(0.01)
{
    m_eObjectType = EOBJECT_TYPE::GUN;
}

Gun::~Gun()
{
}

Gun::Gun(const Gun& _Other)
    : Object(_Other)
{
    m_vDir = _Other.m_vDir;
    m_dAccTime = 0.01;
}

Gun* Gun::Clone()
{
    return new Gun(*this);
}

bool Gun::init()
{
    if (!Object::init())
    {
        return false;
    }

    Input::getInst()->setCallback<Gun>(L"fireBullet", KeyState_Down, this, &Gun::fireBullet);
    // Input::getInst()->setCallback<Gun>(L"MouseRButton", KeyState_Down, this, &Gun::fireSpeedBullet);
    Input::getInst()->setCallback<Gun>(L"MouseRButton", KeyState_Hold, this, &Gun::cameraShakeOn);
    Input::getInst()->setCallback<Gun>(L"MouseRButton", KeyState_Away, this, &Gun::cameraShakeOff);

    // setTexture(L"GunIdle", L"spr_shotgun_heavy_idle.bmp");
    // setTextureColorKey(255, 0, 255);

    createAnimation();
    addAnimation(L"spr_shotgun_heavy_right_idle", true, 0.001f);
    Vec vOffset = Vec(-30.f, 0.f);
    addAnimation(L"spr_shotgun_heavy_left_idle", true, 0.001f, 1.f, false, vOffset);
    addAnimation(L"spr_shotgun_heavy_right_fire", false, 0.2f);
    addAnimation(L"spr_shotgun_heavy_left_fire", false, 0.2f, 1.f, false, vOffset);

    wstring strAniName = L"spr_shotgun_heavy_right_fire";
    addAnimationNotify<Gun>(strAniName, 2, this, &Gun::fire);
    setAnimationEndNotify<Gun>(strAniName, this, &Gun::fireEnd);

    wstring strAniName2 = L"spr_shotgun_heavy_left_fire";
    addAnimationNotify<Gun>(strAniName2, 2, this, &Gun::fire);
    setAnimationEndNotify<Gun>(strAniName2, this, &Gun::fireEnd);

    return true;
}

void Gun::update()
{
    Object::update();
    /*
    m_arrPoint[0].x = getObjRenderPos().x - getObjScale().x / 2.f; // Left Top
    m_arrPoint[0].y = getObjRenderPos().y - getObjScale().y / 2.f; 
    m_arrPoint[1].x = getObjRenderPos().x + getObjScale().x / 2.f; // Right Top
    m_arrPoint[1].y = getObjRenderPos().y - getObjScale().y / 2.f;
    m_arrPoint[2].x = getObjRenderPos().x - getObjScale().x / 2.f; // Left Bottom
    m_arrPoint[2].y = getObjRenderPos().y + getObjScale().y / 2.f;

    for (size_t i = 0; i < 3; ++i)
    {
        m_arrDir[i] = (m_arrPoint[i] - getObjRenderPos());
        m_arrDistance[i] = m_arrDir[i].length();
        m_arrDir[i].normalize();        
    }

    for (size_t i = 0; i < 3; ++i)
    {
        m_arrRotatedPoint[i].x = m_arrDir[i].x * 
    }
    */
    
    Vec vMouseRenderPos = Input::getInst()->getMouseCurPos();
    //Vec vGunRenderPos = getOwnerScene()->findObject(L"Gun")->getObjPos();
    
    
    //Vec vMouseRenderPos = m_pOwnerScene->getCamera()->calculateRenderPos(Input::getInst()->getMouseCurPos());
    Vec vGunRenderPos = m_pOwnerScene->getCamera()->calculateRenderPos(getObjPos());
    
    m_vDir = vMouseRenderPos - vGunRenderPos;
    
    if (m_vDir.x < 0 && !m_bFire)
    {
        changeAnimation(L"spr_shotgun_heavy_left_idle");
    }
    if (m_vDir.x > 0 && !m_bFire)
    {
        changeAnimation(L"spr_shotgun_heavy_right_idle");
    }
    m_dAccTime -= DT;
    /*
    m_dAccTime += fDT;
    if (m_dAccTime > 1.f)
    {
#ifdef _DEBUG
        wchar_t buff[101];
        swprintf_s(buff, L"vMouseRenderPos: (%.0f, %.0f), vGunRenderPos: (%.0f, %.0f), vDir: (%.0f, %0.f)", 
            vMouseRenderPos.x, vMouseRenderPos.y,
            vGunRenderPos.x, vGunRenderPos.y,
            m_vDir.x, m_vDir.y);
        SetWindowText(GameManager::getInst()->getMainWnd(), buff);
#endif // _DEBUG

    }
    */
    // 추후에 사방향 구현 예정.
}

void Gun::postUpdate()
{
    Object::postUpdate();
    
    Scene* pOwnerScene = getObjOwnerScene();
    auto iter = pOwnerScene->getObjectList()->begin();
    auto iterEnd = pOwnerScene->getObjectList()->end();
    Vec vPlayerPos;
    for (; iter != iterEnd;)
    {
        Object* pTempObj = *iter;
        const wstring name = pTempObj->getObjName();
        if (name == L"Player")
        {
            vPlayerPos = pTempObj->getObjPos();
            break;
        }
        ++iter;
    }
    
    vPlayerPos.x += 20.f;
    vPlayerPos.y += 20.f;
    
    setObjPos(vPlayerPos);
}

void Gun::collision()
{
    Object::collision();
}

void Gun::render(HDC _dc)
{
    Object::render(_dc);
}

void Gun::start()
{
    Object::start();
}

void Gun::fireBullet()
{
    m_bFire = true;
    if (m_vDir.x < 0)
    {
        changeAnimation(L"spr_shotgun_heavy_left_fire");
    }
    if (m_vDir.x > 0)
    {
        changeAnimation(L"spr_shotgun_heavy_right_fire");
    }
}

void Gun::fire()
{
    Vec vPos = getObjPos();
    Vec vScale = getObjScale();
    SharedPtr<Bullet> pBullet;

    if (m_vDir.x < 0)
    {
        pBullet = getOwnerScene()->createObject<Bullet>(L"PlayerBullet", L"PlayerBullet",
            Vec(vPos - Vec(vScale.x / 2.f + 10.f, vScale.y / 2.f - 10.f)), Vec(50.f, 50.f));
        pBullet->setDir(Vec(-1.f, 0.f));
    }
    else
    {
        pBullet = getOwnerScene()->createObject<Bullet>(L"PlayerBullet", L"PlayerBullet",
            Vec(vPos + Vec(vScale.x / 2.f + 10.f, vScale.y / 2.f - 10.f)), Vec(50.f, 50.f));
        pBullet->setDir(Vec(1.f, 0.f));
    }

    pBullet->getBulletCollider()->setProfile(L"PlayerBullet");
    pBullet->setBulletDamage(20.f);

    setObjPos(vPos);
}

void Gun::fireEnd()
{
    if (m_vDir.x < 0 && !m_bFire)
    {
        changeAnimation(L"spr_shotgun_heavy_left_idle");
    }
    if (m_vDir.x > 0 && !m_bFire)
    {
        changeAnimation(L"spr_shotgun_heavy_right_idle");
    }
    m_bFire = false;
}

void Gun::cameraShakeOn()
{
    m_pOwnerScene->getCamera()->shakeCamera();
    if (m_dAccTime <= 0.)
    {
        fire();
        m_dAccTime = 0.01;
    }
}

void Gun::cameraShakeOff()
{
    m_pOwnerScene->getCamera()->shakeOffCamera();
}
