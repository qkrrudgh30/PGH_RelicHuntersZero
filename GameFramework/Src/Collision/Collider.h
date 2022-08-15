// Collider.h

#pragma once
#include "../Ref.h"
#include "CollisionManager.h"

class Scene;
class Object;

class Collider :
    public Ref
{
public:
    Collider();
    virtual ~Collider() = 0;

    Collider(const Collider& _Other);

    virtual Collider* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void render(HDC _dc);
    virtual bool collision(Collider* _pDestCollider) = 0;
    virtual bool collisionMouse(const Vec& _vMousePos) = 0;

    Scene* getOwnerScene() { return m_pOwnerScene; }
    void setOwnerScene(Scene* _pOwnerScene) { m_pOwnerScene = _pOwnerScene; }

    Object* getOwnerObject() { return m_pOwnerObject; }
    void setOwnerObject(Object* _pOwnerObject) { m_pOwnerObject = _pOwnerObject; }

    ECOLLIDER_TYPE getColliderType() { return m_eColliderType; }
    void setColliderType(ECOLLIDER_TYPE _eColliderType) { m_eColliderType = _eColliderType; }

    Vec getOffset() { return m_vOffset; }
    void setOffset(Vec _vOffset) { m_vOffset = _vOffset; }

    bool isEnable() { return m_bEnable; }
    void setEnable(bool _bEnable) { m_bEnable = _bEnable; }

    CollisionProfile* getProfile() { return m_pProfile; }
    void setProfile(const wstring& _strName) { m_pProfile = CollisionManager::getInst()->findProfile(_strName); }


    template <typename T>
    void setCollisionBeginFunc(T* _Obj, void(T::* _pFunc)(Collider*, Collider*))
    {
        m_pCollisionBeginFunc = bind(_pFunc, _Obj, placeholders::_1, placeholders::_2);
    }

    template <typename T>
    void setCollisionEndFunc(T* _Obj, void(T::* _pFunc)(Collider*, Collider*))
    {
        m_pCollisionEndFunc = bind(_pFunc, _Obj, placeholders::_1, placeholders::_2);
    }

    void callCollisionBeginFunc(Collider* _pDes);
    void callCollisionEndFunc(Collider* _pDes);

    void addCollisionList(Collider* _pCollider);
    bool checkCollisionList(Collider* _pCollider);
    void deleteCollisionList(Collider* _pCollider);
    void clearCollisionList();

    template <typename T>
    void setMouseCollisionBeginFunc(T* _Obj, void(T::* _pFunc)(Collider*, const Vec&))
    {
        m_fpMouseBeginFunc = bind(_pFunc, _Obj, placeholders::_1, placeholders::_2);
    }

    template <typename T>
    void setMouseCollisionEndFunc(T* _Obj, void(T::* _pFunc)(Collider*, const Vec&))
    {
        m_fpMouseEndFunc = bind(_pFunc, _Obj, placeholders::_1, placeholders::_2);
    }

    void callMouseCollisionBeginFunc(const Vec& _vMousePos);
    void callMouseCollisionEndFunc(const Vec& _vMousePos);

    bool getMouseCollision() { return m_bMouseCollision; }
    void setMouseCollision(bool _bMouseCollision) { m_bMouseCollision = _bMouseCollision; }

    virtual float getBottom() const { return 0.f; }



protected:
    Scene*                                  m_pOwnerScene;
    Object*                                 m_pOwnerObject;
    ECOLLIDER_TYPE                          m_eColliderType;
    Vec                                     m_vOffset;
    bool                                    m_bEnable;
    CollisionProfile*                       m_pProfile;
    function<void(Collider*, Collider*)>    m_pCollisionBeginFunc;
    function<void(Collider*, Collider*)>    m_pCollisionEndFunc;
    list<SharedPtr<Collider>>               m_lsPreCollision;

    function<void(Collider*, const Vec&)>   m_fpMouseBeginFunc;
    function<void(Collider*, const Vec&)>   m_fpMouseEndFunc;
    bool                                    m_bMouseCollision;
    float                                   m_fColliderBottom;

    Vec                                     m_vPos;

private:

    friend class Object;
};

