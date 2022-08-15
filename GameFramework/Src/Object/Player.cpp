// Player.cpp

#include "../GameInfo.h"
#include "Player.h"
#include "../Timer.h"
#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Input.h"
#include "Monster.h"
#include "../Collision/ColliderBox.h"
#include "../Collision/ColliderSphere.h"
#include "../UI/UIWindow.h"
#include "../UI/UIWidget.h"
#include "SpawnPlayer.h"
#include "../Scene/Camera.h"

Player::Player()
    : m_bTimeStop(false)
    , m_dAccTime(0.)
    , m_nDir(1)
    , m_bAniChangeRock(false)
    , m_dHitMotionTime(0.)
    , m_bDie(false)
    , m_bMoveUpLock(false)
    , m_bMoveDownLock(false)
    , m_bMoveLeftLock(false)
    , m_bMoveRightLock(false)
    , m_bCameraTargetOn(false)
{
    setObjSpeed(200.f);
    m_CharacterInfo.nMaxHP = 100;
    m_CharacterInfo.nHP = 100;

    m_CharacterInfo.nMaxMP = 100;
    m_CharacterInfo.nMP = 100;
    m_dAccTime = 0.;
    
}

Player::Player(Vec _vPos)
    : m_bTimeStop(false)
    , m_dAccTime(0.)
    , m_nDir(1)
    , m_bAniChangeRock(false)
    , m_dHitMotionTime(0.)
    , m_bDie(false)
    , m_bCameraTargetOn(false)
{
    setObjSpeed(200.f);
    m_CharacterInfo.nMaxHP = 100;
    m_CharacterInfo.nHP = 100;

    m_CharacterInfo.nMaxMP = 100;
    m_CharacterInfo.nMP = 100;
    m_dAccTime = 0.;

    setObjPos(_vPos);
}

Player::~Player()
{
}

Player::Player(const Player& _Other)
    : Character(_Other)
    , m_bCameraTargetOn(false)
{
    m_bTimeStop = false;
    m_nDir = 1;
    m_dAccTime = 0.;
    m_dHitMotionTime = 0.;
    m_bAniChangeRock = false;
    m_bDie = false;
}

Player* Player::Clone()
{
    return new Player(*this);
}

bool Player::init()
{
    if (!Character::init())
    {
        return false;
    }

    Vec vPos = m_pOwnerScene->findObject(L"PlayerSpawn")->getObjPos();
    setObjPos(vPos + Vec(0.f, 40.f));
    /*
    ColliderSphere* pPlayerHead = addCollider<ColliderSphere>(L"PlayerHead");
    pPlayerHead->setRadius(20.f);
    pPlayerHead->setOffset(Vec(0.f, -5.f));
    pPlayerHead->setProfile(L"Player");
    pPlayerHead->setCollisionBeginFunc<Player>(this, &Player::collisionBegin);
    */
    ColliderBox* pPlayerBody = addCollider<ColliderBox>(L"PlayerBody");
    pPlayerBody->setExtent(60.f, 80.f);
    pPlayerBody->setOffset(Vec(10.f, 10.f));
    pPlayerBody->setProfile(L"Player");
    pPlayerBody->setCollisionBeginFunc<Player>(this, &Player::collisionBegin);

    // setTexture(L"Jimmy", L"spr_jimmy_idle_0.bmp");
    // setTextureColorKey(255, 0, 255);

    createAnimation();
    addAnimation(L"spr_jimmy_right_idle");
    addAnimation(L"spr_jimmy_right_walk", true, 0.5f);
    addAnimation(L"spr_jimmy_right_holo", false, 0.5f);
    addAnimation(L"spr_jimmy_right_hit", false, 0.2f);
    addAnimation(L"spr_jimmy_right_die", false, 0.5f);
    addAnimation(L"spr_jimmy_right_respawn", false, 0.5f);
    
    addAnimation(L"spr_jimmy_left_idle");
    addAnimation(L"spr_jimmy_left_walk", true, 0.5f);
    addAnimation(L"spr_jimmy_left_holo", false, 0.5f);
    addAnimation(L"spr_jimmy_left_hit", false, 0.2f);
    addAnimation(L"spr_jimmy_left_die", false, 0.5f);

    wstring strAniName1 = L"spr_jimmy_right_hit";
    setAnimationEndNotify<Player>(strAniName1, this, &Player::hitRightEnd);

    wstring strAniName2 = L"spr_jimmy_left_hit";
    setAnimationEndNotify<Player>(strAniName2, this, &Player::hitLeftEnd);

    wstring str1 = L"spr_jimmy_right_die";
    setAnimationEndNotify<Player>(str1, this, &Player::dieEnd);

    wstring str2 = L"spr_jimmy_left_die";
    setAnimationEndNotify<Player>(str2, this, &Player::dieEnd);

    // wstring str2 = L"spr_jimmy_right_respwan";
    // setAnimationEndNotify<Player>(str2, this, &Player::dieEnd);

    m_pTextComponent = createUIComponent(L"TextComponent");
    
    return true;
}

void Player::update()
{
    Character::update();

    if (GetAsyncKeyState('Q') & 0x8000)
    {
        setAttackSpeed(0.0001f);
    }

    m_dAccTime += DT;
    if (1. < m_dAccTime && m_pText != nullptr)
    {
        if (m_pText->getTextCount() != 0)
        {
            m_pText->clear();
        }
        
        m_dAccTime = 0.;
    }

    m_dHitMotionTime -= DT;
    if (m_dHitMotionTime <= 0.)
    {
        m_bAniChangeRock = false;
    }

    if (true == m_bDie)
    {
        setObjPos(getOwnerScene()->findObject(L"PlayerSpawn")->getObjPos() + Vec(0.f, 40.f));
        changeAnimation(L"spr_jimmy_right_respawn");
        m_CharacterInfo.nHP = 100;
        setDamage(0);
        // getOwnerScene()->getCamera()->moveSmoothlyCamera(getObjPos(), 5.);
        getOwnerScene()->getCamera()->moveAccelateCamera(getObjPos(), Vec(600.f, 600.f));
        m_bDie = false;
    }
}

void Player::postUpdate()
{
    Character::postUpdate();

    if (checkCurAnimation(L"spr_jimmy_left_walk") && 0.f == getObjVelocity().length())
    {
        changeAnimation(L"spr_jimmy_left_idle");
    }
    else if (checkCurAnimation(L"spr_jimmy_right_walk") && 0.f == getObjVelocity().length())
    {
        changeAnimation(L"spr_jimmy_right_idle");
    }
}

void Player::collision()
{
    Character::collision();
}

void Player::render(HDC _dc)
{
    Character::render(_dc);
}

void Player::start()
{
    Character::start(); 

    Input::getInst()->setCallback<Player>(L"moveUp", KeyState_Hold, this, &Player::moveUp);
    Input::getInst()->setCallback<Player>(L"moveDown", KeyState_Hold, this, &Player::moveDown);
    Input::getInst()->setCallback<Player>(L"moveLeft", KeyState_Hold, this, &Player::moveLeft);
    Input::getInst()->setCallback<Player>(L"moveRight", KeyState_Hold, this, &Player::moveRight);
    Input::getInst()->setCallback<Player>(L"fireBullet", KeyState_Hold, this, &Player::fireBullet);
    Input::getInst()->setCallback<Player>(L"pause", KeyState_Down, this, &Player::pause);
    Input::getInst()->setCallback<Player>(L"resume", KeyState_Down, this, &Player::resume);
    Input::getInst()->setCallback<Player>(L"timeStop", KeyState_Down, this, &Player::timeStop);
    Input::getInst()->setCallback<Player>(L"CameraTargetOn", KeyState_Down, this, &Player::cameraTargetOn);
    
}


void Player::cameraTargetOn()
{
    m_bCameraTargetOn = !m_bCameraTargetOn;
    if (m_bCameraTargetOn)
    {
        m_pOwnerScene->getCamera()->setTargetObject(this);
    }
    else
    {
        m_pOwnerScene->getCamera()->setTargetObject(nullptr);
    }
}
void Player::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
    if (-1 == m_nDir)
    {
        changeAnimation(L"spr_jimmy_left_hit");
        m_bAniChangeRock = true;
        m_dHitMotionTime = 0.2;
    }
    else if (1 == m_nDir)
    {
        changeAnimation(L"spr_jimmy_right_hit");
        m_bAniChangeRock = true;
        m_dHitMotionTime = 0.2;
    }

    if (_pDes->getOwnerObject()->getObjName() == L"WallTile")
    {

        Vec vSrcColliderPos = _pSrc->getOwnerObject()->getObjPos() + _pSrc->getOffset();
        Vec vDesColliderPos = _pDes->getOwnerObject()->getObjPos() + _pDes->getOffset();
        Vec vDir = vSrcColliderPos - vDesColliderPos;
        // m_pPlayer = (Player*)(_pDes->getOwnerObject());

        if (vDir.x <= -49.f)
        {
            // аб -> ©Л
            setMoveUpLock(false);
            setMoveDownLock(false);
            setMoveLeftLock(false);
            setMoveRightLock(true);

        }
        else if (vDir.x >= 49.f)
        {
            // ©Л -> аб
            setMoveUpLock(false);
            setMoveDownLock(false);
            setMoveLeftLock(true);
            setMoveRightLock(false);

        }
        else if (vDir.y <= -49.f)
        {
            // ╩С -> го
            setMoveUpLock(false);
            setMoveDownLock(true);
            setMoveLeftLock(false);
            setMoveRightLock(false);
        }
        else if (vDir.y >= 49.f)
        {
            // го -> ╩С
            setMoveUpLock(true);
            setMoveDownLock(false);
            setMoveLeftLock(false);
            setMoveRightLock(false);
        }
    }
}

void Player::hitRightEnd()
{
    if (0 < m_CharacterInfo.nHP)
    {
        changeAnimation(L"spr_jimmy_right_idle");
    }
    else
    {
        changeAnimation(L"spr_jimmy_right_die");
    }
    
}

void Player::hitLeftEnd()
{
    if (0 < m_CharacterInfo.nHP)
    {
        // m_bDie = true;
        changeAnimation(L"spr_jimmy_left_idle");
    }
    else
    {
        changeAnimation(L"spr_jimmy_left_die");
    }
    
}

void Player::dieEnd()
{
    m_bDie = true;
}

void Player::moveUp()
{
    if (m_bMoveUpLock)
    {
        return;
    }

    if (getObjPos().y <= 30.f)
    {
        return;
    }


    move(Vec(0.f, -1.f));

    if (-1 == m_nDir)
    {
        changeAnimation(L"spr_jimmy_left_walk");
    }
    else if (1 == m_nDir)
    {
        changeAnimation(L"spr_jimmy_right_walk");
    }
}

void Player::moveDown()
{
    if (m_bMoveDownLock)
    {
        return;
    }

    if (m_pOwnerScene->getCamera()->getWorldResolution().y - 50.f <= getObjPos().y)
    {
        return;
    }

    move(Vec(0.f, 1.f));

    if (-1 == m_nDir)
    {
        changeAnimation(L"spr_jimmy_left_walk");
    }
    else if (1 == m_nDir)
    {
        changeAnimation(L"spr_jimmy_right_walk");
    }
}

void Player::moveLeft()
{
    if (m_bMoveLeftLock)
    {
        return;
    }

    if (getObjPos().x <= 20.f)
    {
        return;
    }

    move(Vec(-1.f, 0.f));
    m_nDir = -1;
    changeAnimation(L"spr_jimmy_left_walk");
}

void Player::moveRight()
{
    if (m_bMoveRightLock)
    {
        return;
    }

    if (m_pOwnerScene->getCamera()->getWorldResolution().x - 40.f <= getObjPos().x)
    {
        return;
    }

    move(Vec(1.f, 0.f));
    m_nDir = 1;
    changeAnimation(L"spr_jimmy_right_walk");
}

void Player::fireBullet()
{
}

void Player::pause()
{
    Timer::getInst()->setGameTimeScale(0.f);
}

void Player::resume()
{
    Timer::getInst()->setGameTimeScale(1.f);
}

void Player::timeStop()
{
    auto iter = getOwnerScene()->getObjectList()->begin();
    auto iterEnd = getOwnerScene()->getObjectList()->end();

    setDamage(!getDamage());

    m_bTimeStop = !m_bTimeStop;

    if (m_bTimeStop && 0 < m_CharacterInfo.nMP)
    {
        setMana(20.f);
        if (checkCurAnimation(L"spr_jimmy_left_idle") || checkCurAnimation(L"spr_jimmy_left_walk"))
        {
            changeAnimation(L"spr_jimmy_left_holo");
        }
        else if (checkCurAnimation(L"spr_jimmy_right_idle") || checkCurAnimation(L"spr_jimmy_right_walk"))
        {
            changeAnimation(L"spr_jimmy_right_holo");
        }
        for (; iter != iterEnd;)
        {
            Object* tempPtr = *iter;
            wstring name = tempPtr->getObjName();
            if (name == L"Monster")
            {
                tempPtr->setObjTimeScale(0.f);
                ((Monster*)tempPtr)->setFire(false);
            }
            ++iter;
        }
    }
    else
    {
        if (m_CharacterInfo.nMP == 0)
        {
            m_pText = m_pTextComponent->createWidget<UIWidgetText>(L"PlayerStateText");
            m_pText->setText(TEXT("Not enough mana."));
            m_pText->setTextColor(0, 0, 255);
            m_pTextComponent->setComponentPos(Vec(-60.f, -50.f));
        }
        if (checkCurAnimation(L"spr_jimmy_left_holo") || checkCurAnimation(L"spr_jimmy_left_walk"))
        {
            changeAnimation(L"spr_jimmy_left_idle");
        }
        else if (checkCurAnimation(L"spr_jimmy_right_holo") || checkCurAnimation(L"spr_jimmy_right_walk"))
        {
            changeAnimation(L"spr_jimmy_right_idle");
        }
        for (; iter != iterEnd;)
        {
            Object* tempPtr = *iter;
            wstring name = tempPtr->getObjName();
            if (name == L"Monster")
            {
                tempPtr->setObjTimeScale(1.f);
                ((Monster*)tempPtr)->setFire(true);
            }
            ++iter;
        }
    }
}

void Player::showText(const wstring& _strText)
{
    
    
}
