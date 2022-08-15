// Monster.h

#pragma once

#include "Character.h"
#include "../UI/UIWindowHUD.h"
#include "../UI/UIComponent.h"

class Monster :
    public Character
{
public:
    Monster();
    virtual ~Monster();

    Monster(const Monster& _Other);

    virtual Monster* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _dc);
    virtual void start();

    float getFireTime() { return m_fFireTime; }
    void setFireTime(float _fFireTime) { m_fFireTime = _fFireTime; }

    bool isFire() { return m_bFire; }
    void setFire(bool _bFire) { m_bFire = _bFire; }
    virtual float setDamage(float _fDamage)
    {
        _fDamage = Character::setDamage(_fDamage);

        UIWidgetProgressBar* pMonsetHPProgressBar = (UIWidgetProgressBar*)m_pHPBar->getWidget();
        float fPercent = m_CharacterInfo.nHP / (float)m_CharacterInfo.nMaxHP;
        pMonsetHPProgressBar->setPercent(fPercent);

        return _fDamage;
    }

    Vec getMonsterDir() { return m_vDir; }

protected:
    Vec                     m_vDir;
    float                   m_fFireTime;
    bool                    m_bFire;
    int                     m_nCount;
    SharedPtr<UIComponent>  m_pHPBar;
    EMONSTER_STATE          m_eState;
    float                   m_fDetectDist;
    float                   m_fAttackDist;
    bool                    m_bAttack;
    bool                    m_bSkill;

    virtual void idle();
    virtual void trace();
    virtual void attack();
    virtual void skill();
    virtual void death();

};