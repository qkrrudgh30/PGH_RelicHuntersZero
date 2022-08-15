// Monster.cpp

#include "../GameInfo.h"
#include "Monster.h"
#include "../Timer.h"
#include "Bullet.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../UI/UIWidgetProgressBar.h"
#include "../UI/UIWidgetImage.h"
#include "../Object/Object.h"
#include "../Object/Character.h"
#include "../Object/Player.h"

Monster::Monster()
    : m_vDir{ 0.f, 1.f }
    , m_fFireTime(1.f)
    , m_bFire(true)
    , m_nCount(0)
    , m_eState(EMONSTER_STATE::IDLE)
    , m_fDetectDist(500.f)
    , m_fAttackDist(300.f)
    , m_bAttack(false)
    , m_bSkill(false)
{
}

Monster::~Monster()
{
}

Monster::Monster(const Monster& _Other)
    : Character(_Other)
{
    m_fFireTime = _Other.m_fFireTime;
    m_vDir = Vec(0.f, 1.f);
    m_bFire = true;
    m_nCount = 0;
}

Monster* Monster::Clone()
{
    return new Monster(*this);
}

bool Monster::init()
{
    if (!Character::init())
    {
        return false;
    }

    m_pHPBar = createUIComponent(L"MonsterHPWidget");
    UIWidgetProgressBar* pHP = m_pHPBar->createWidget<UIWidgetProgressBar>(L"HPBar");
    pHP->setImageTexture(L"MonsetHPBar", TEXT("MiniHP.bmp"), TEXTURE_PATH);
    m_pHPBar->setComponentPos(Vec(-15.f, -10.f));

    return true;
}

void Monster::update()
{
    Character::update();

    if (m_pOwnerScene->findObject(L"Player"))
    {
        Object* pPlayer = m_pOwnerScene->findObject(L"Player");
        Vec vPlayerPos = pPlayer->getObjPos();
        Vec vDist = vPlayerPos - (this->getObjPos());
        float fDist = vDist.length();

        if (fDist <= m_fDetectDist)
        {
            if (fDist <= m_fAttackDist)
            {
                if (m_CharacterInfo.nHP <= 60)
                {
                    m_eState = EMONSTER_STATE::SKILL;
                    m_bAttack = false;
                    m_bSkill = true;
                }
                else
                {
                    m_eState = EMONSTER_STATE::ATTACK;
                    m_bAttack = true;
                    m_bSkill = false;
                }
            }
            else
            {
                m_eState = EMONSTER_STATE::TRACE;

                m_bAttack = false;
                m_bSkill = false;
            }
        }
        else
        {
            m_eState = EMONSTER_STATE::IDLE;
            m_bAttack = false;
            m_bSkill = false;
        }
    }
    

    

    if (m_CharacterInfo.nHP <= 0)
    {
        m_eState = EMONSTER_STATE::DEATH;
    }

    switch (m_eState)
    {
    case EMONSTER_STATE::IDLE:
        idle();
        break;
    case EMONSTER_STATE::TRACE:
        trace();
        break;
    case EMONSTER_STATE::ATTACK:
        attack();
        break;
    case EMONSTER_STATE::SKILL:
        skill();
        break;
    case EMONSTER_STATE::DEATH:
        death();
        break;

    default:
        break;
    }
    
}

void Monster::postUpdate()
{
    Character::postUpdate();
}

void Monster::collision()
{
     Character::collision();
}

void Monster::render(HDC _dc)
{
    Character::render(_dc);
}

void Monster::start()
{
    Character::start();
}

void Monster::idle()
{
}

void Monster::trace()
{
}

void Monster::attack()
{
}

void Monster::skill()
{
}

void Monster::death()
{
}
