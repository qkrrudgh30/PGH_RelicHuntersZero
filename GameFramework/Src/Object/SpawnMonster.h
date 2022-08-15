#pragma once
#include "Object.h"
class SpawnMonster :
    public Object
{
public:
    SpawnMonster();
    SpawnMonster(const SpawnMonster& _Other);
    virtual ~SpawnMonster();

    SpawnMonster* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);
    virtual void start();

    void collisionBegin(Collider* _pSrc, Collider* _pDes);
    void collisionEnd(Collider* _pSrc, Collider* _pDes);

private:
    double m_dAccTime;
    double m_dAccDiggingTime;
    bool   m_bDigging;
    Collider* m_pCollider;

};
