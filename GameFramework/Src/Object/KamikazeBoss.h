// KamikazeBoss.h

#pragma once
#include "Monster.h"
class KamikazeBoss :
    public Monster
{
public:
    KamikazeBoss();
    KamikazeBoss(const KamikazeBoss& _Other);
    virtual ~KamikazeBoss();

    virtual KamikazeBoss* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _dc);
    virtual void start();

    virtual float setDamage(float _fDamage) { Monster::setDamage(_fDamage); return _fDamage; }

    void collisionBegin(Collider* _pSrc, Collider* _pDes);
    void collisionEnd(Collider* _pSrc, Collider* _pDes);

    void egg();
    void crack();
    void beginCrack();
    void spawn();
    void hit();
    void die();
    void walk();
    void attack();
    void attackBegin();
    void bomb();
    void bombBegin();

private:
    bool m_bAttackState;
    double m_dAccTime;
    bool m_bAttack;
    bool m_bSkill;
    bool m_bToggle;
    


};

