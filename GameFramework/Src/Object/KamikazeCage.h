// KamikazeCage.h

#pragma once
#include "Monster.h"
class KamikazeCage :
    public Monster
{
public:
    KamikazeCage();
    KamikazeCage(const KamikazeCage& _Other);
    virtual ~KamikazeCage();

    virtual KamikazeCage* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _dc);
    virtual void start();

    virtual float setDamage(float _fDamage) 
    { 
        Monster::setDamage(_fDamage); 
        return _fDamage;
    }

    void collisionBegin(Collider* _pSrc, Collider* _pDes);
    void collisionEnd(Collider* _pSrc, Collider* _pDes);

    void hit();
    void die();
    void explosion();

protected:

private:

};

