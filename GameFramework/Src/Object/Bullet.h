// Bullet.h

#pragma once
#include "Object.h"

class Collider;

class Bullet :
    public Object
{
public:
    Bullet();
    virtual ~Bullet();

    Bullet(const Bullet& _Other);

    virtual Bullet* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _dc);
    virtual void start();

    Vec getDir() { return m_vDir; }
    void setDir(Vec _vDir) { m_vDir = _vDir; }
    void setDir(float _fAngle)
    {
        m_vDir.x = cosf(degreeToRadian(_fAngle));
        m_vDir.y = sinf(degreeToRadian(_fAngle));
    }

    float getDistance() { return m_fDistance; }
    void setDistance(float _fDistance) { m_fDistance = _fDistance; }

    void collisionBegin(Collider* _pSrc, Collider* _pDes);
    void collisionEnd(Collider* _pSrc, Collider* _pDes);

    Collider* getBulletCollider() { return m_pCollider; };

    float getBulletDamage() { return m_fDamage; }
    void setBulletDamage(float _fDamage) { m_fDamage = _fDamage; }

private:
    Vec         m_vDir;
    float       m_fDistance;
    Collider*   m_pCollider;
    float       m_fDamage;

};