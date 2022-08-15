// ColliderBox.h

#pragma once
#include "Collider.h"

class ColliderBox :
    public Collider
{
public:
    ColliderBox();
    virtual ~ColliderBox();

    ColliderBox(const ColliderBox& _Other);

    virtual Collider* Clone();

    virtual bool init();
    virtual void update();
 
    virtual void postUpdate();
    virtual void render(HDC _dc);
    virtual bool collision(Collider* _pDesCollider);
    virtual bool collisionMouse(const Vec& _vMousePos);

    void setExtent(float _fWidth, float _fHeight)
    {
        m_fWidth = _fWidth;
        m_fHeight = _fHeight;
    }

    RectInfo getInfo() const { return m_rtInfo; }

    virtual float getBottom() const { return m_rtInfo.Bottom; }

    Vec getScale() { return Vec(m_fWidth, m_fHeight); }
    Vec getCenterPos() { return m_vCenterPos; }

protected:
    float      m_fWidth;
    float      m_fHeight;
    RectInfo   m_rtInfo;
    Vec        m_vCenterPos;

private:

    friend class Object;
};

