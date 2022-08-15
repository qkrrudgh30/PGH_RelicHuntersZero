#pragma once
#include "Object.h"
class Potal :
    public Object
{
public:
    Potal();
    Potal(const Potal& _Other);
    virtual ~Potal();

    Potal* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);
    virtual void start();

    void collisionBegin(Collider* _pSrc, Collider* _pDes);
    void collisionEnd(Collider* _pSrc, Collider* _pDes);

private:
    Collider* m_pCollider;
    bool m_bTeleport;

    void createPotal();

};

