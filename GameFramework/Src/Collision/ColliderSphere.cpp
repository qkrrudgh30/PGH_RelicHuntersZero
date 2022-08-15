// ColliderSphere.cpp

#include "../GameInfo.h"
#include "ColliderSphere.h"
#include "../Object/Object.h"
#include "../GameManager.h"
#include "Collision.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"


ColliderSphere::ColliderSphere()
{
	m_spInfo.fRadius = 50.f;
	m_eColliderType = ECOLLIDER_TYPE::ECOLLISION_TYPE_SPHERE;
}

ColliderSphere::~ColliderSphere()
{
}

ColliderSphere::ColliderSphere(const ColliderSphere& _Other)
	: Collider(_Other)
{
	m_spInfo = _Other.m_spInfo;
}

Collider* ColliderSphere::Clone()
{
	return new ColliderSphere(*this);
}

bool ColliderSphere::init()
{
	if (!Collider::init())
	{
		return false;
	}

	return true;
}

void ColliderSphere::update()
{
	Collider::update();
}

void ColliderSphere::postUpdate()
{
	Collider::postUpdate();
	
	// m_spInfo.vCenter = m_pOwnerObject->getObjRenderPos() + m_vOffset;
	m_spInfo.vCenter = m_pOwnerObject->getObjPos() + m_vOffset;
}

void ColliderSphere::render(HDC _dc)
{
	Collider::render(_dc);

#ifdef _DEBUG
	HPEN hPen = GameManager::getInst()->getGreenPen();

	if (!m_lsPreCollision.empty())
	{
		hPen = GameManager::getInst()->getRedPen();
	}

	HGDIOBJ hPrePen = (HGDIOBJ)SelectObject(_dc, hPen);

	Vec vPos = m_pOwnerScene->getCamera()->calculateRenderPos(m_spInfo.vCenter);

	// MoveToEx(_dc, (int)(m_spInfo.vCenter.x + m_spInfo.fRadius), (int)m_spInfo.vCenter.y, nullptr);
	MoveToEx(_dc, (int)(vPos.x + m_spInfo.fRadius), (int)vPos.y, nullptr);

	for (size_t i = 0; i < 12; ++i)
	{
		float fRadian = degreeToRadian((i + 1) * (360.f / 12.f));
		/*
		float x = m_spInfo.vCenter.x + cosf(fRadian) * m_spInfo.fRadius;
		float y = m_spInfo.vCenter.y + sinf(fRadian) * m_spInfo.fRadius;
		*/
		float x = vPos.x + cosf(fRadian) * m_spInfo.fRadius;
		float y = vPos.y + sinf(fRadian) * m_spInfo.fRadius;

		LineTo(_dc, (int)x, (int)y);
	}

	SelectObject(_dc, hPrePen);

#endif // _DEBUG
}

bool ColliderSphere::collision(Collider* _pDesCollider)
{
	switch (_pDesCollider->getColliderType())
	{
	case ECOLLIDER_TYPE::ECOLLISION_TYPE_BOX:
		return Collision::collisionBoxToSphere((ColliderBox*)_pDesCollider, this);
	case ECOLLIDER_TYPE::ECOLLISION_TYPE_SPHERE:
		return Collision::collisionSphereToSphere(this, (ColliderSphere*)_pDesCollider);
	case ECOLLIDER_TYPE::ECOLLISION_TYPE_POINT:
		break;
	}

	return false;
}

bool ColliderSphere::collisionMouse(const Vec& _vMousePos)
{
	float fDist = distance(m_spInfo.vCenter, _vMousePos);

	return fDist <= m_spInfo.fRadius;
}
