// Gun.h

#pragma once
#include "Object.h"

class Gun :
    public Object
{
public:
    Gun();
    virtual ~Gun();

    Gun(const Gun& _Other);

    virtual Gun* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _dc);
    virtual void start();

    void fireBullet();
    void fire();
    void fireEnd();

    Vec getDir() { return m_vDir; }
    void setDir(Vec _vDir) { m_vDir = _vDir; }

    void cameraShakeOn();
    void cameraShakeOff();
    void fireSpeedBullet();

private:
    Vec m_vDir;
    bool m_bFire;
    Vec m_arrPoint[3];
    Vec m_arrDir[3];
    float m_arrDistance[3];
    Vec m_arrRotatedPoint[3];
    double m_dAccTime;

};