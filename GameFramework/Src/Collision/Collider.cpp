// Collider.cpp

#include "../GameInfo.h"
#include "Collider.h"

Collider::Collider()
    : m_pOwnerScene(nullptr)
    , m_pOwnerObject(nullptr)
    , m_eColliderType(ECOLLIDER_TYPE::ECOLLISION_TYPE_END)
    , m_vOffset{ 0.f, 0.f }
    , m_bEnable(true)
    , m_pProfile(nullptr)
    , m_bMouseCollision(false)
    , m_fpMouseBeginFunc(nullptr)
    , m_fpMouseEndFunc(nullptr)
    , m_pCollisionBeginFunc(nullptr)
    , m_pCollisionEndFunc(nullptr)
{
}

Collider::~Collider()
{
    auto iter = m_lsPreCollision.begin();
    auto iterEnd = m_lsPreCollision.end();

    for (; iter != iterEnd;)
    {
        (*iter)->deleteCollisionList(this);
        ++iter;
    }
}

Collider::Collider(const Collider& _Other)
    : Ref(_Other)
    , m_pOwnerScene(nullptr)
    , m_pOwnerObject(nullptr)
    , m_eColliderType(_Other.m_eColliderType)
    , m_vOffset(_Other.m_vOffset)
    , m_bEnable(true)
    , m_pProfile(_Other.m_pProfile)
{
}

Collider* Collider::Clone()
{
    return nullptr;
}

bool Collider::init()
{
    m_pProfile = CollisionManager::getInst()->findProfile(L"Object");

    return true;
}

void Collider::update()
{
}

void Collider::postUpdate()
{
}

void Collider::render(HDC _dc)
{
}

void Collider::callCollisionBeginFunc(Collider* _pDes)
{
    if (nullptr != m_pCollisionBeginFunc)
    {
        m_pCollisionBeginFunc(this, _pDes);
    }
}

void Collider::callCollisionEndFunc(Collider* _pDes)
{
    if (nullptr != m_pCollisionEndFunc)
    {
        m_pCollisionEndFunc(this, _pDes);
    }
}

void Collider::addCollisionList(Collider* _pCollider)
{
    m_lsPreCollision.push_back(_pCollider);
}

bool Collider::checkCollisionList(Collider* _pCollider)
{
    auto iter = m_lsPreCollision.begin();
    auto iterEnd = m_lsPreCollision.end();

    for (; iter != iterEnd;)
    {
        if (*iter == _pCollider)
        {
            return true;
        }
        ++iter;
    }

    return false;
}

void Collider::deleteCollisionList(Collider* _pCollider)
{
    auto iter = m_lsPreCollision.begin();
    auto iterEnd = m_lsPreCollision.end();

    for (; iter != iterEnd;)
    {
        if (_pCollider == *iter)
        {
            m_lsPreCollision.erase(iter);
            return;
        }
        ++iter;
    }

}

void Collider::clearCollisionList()
{
    auto iter = m_lsPreCollision.begin();
    auto iterEnd = m_lsPreCollision.end();

    for (; iter != iterEnd;)
    {
        (*iter)->deleteCollisionList(this);
        ++iter;
    }
    m_lsPreCollision.clear();
}

void Collider::callMouseCollisionBeginFunc(const Vec& _vMousePos)
{
    if (nullptr != m_fpMouseBeginFunc)
    {
        m_fpMouseBeginFunc(this, _vMousePos);
    }
}

void Collider::callMouseCollisionEndFunc(const Vec& _vMousePos)
{
    if (nullptr != m_fpMouseEndFunc)
    {
        m_fpMouseEndFunc(this, _vMousePos);
    }
}
