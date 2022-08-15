#pragma once
#include "Collider.h"
class ColliderSphere :
    public Collider
{
public:
    ColliderSphere();
    virtual ~ColliderSphere();

    ColliderSphere(const ColliderSphere& _Other);

    virtual Collider* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void render(HDC _dc);
    virtual bool collision(Collider* _pDesCollider);
    virtual bool collisionMouse(const Vec& _vMousePos);

    void setRadius(float _fRadius)
    {
        m_spInfo.fRadius = _fRadius;
    }

    SphereInfo getInfo() const { return m_spInfo; }

    virtual float getBottom() const { return m_spInfo.vCenter.y + m_spInfo.fRadius; }

protected:
    SphereInfo   m_spInfo;

private:

    friend class Object;
};

