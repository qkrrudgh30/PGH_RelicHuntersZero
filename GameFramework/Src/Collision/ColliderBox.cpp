// ColliderBox.cpp

#include "../GameInfo.h"
#include "ColliderBox.h"
#include "../Object/Object.h"
#include "../GameManager.h"
#include "Collision.h"

ColliderBox::ColliderBox()
	: m_fWidth(100.f)
	, m_fHeight(100.f)
	, m_rtInfo{}
{
	m_eColliderType = ECOLLIDER_TYPE::ECOLLISION_TYPE_BOX;
}

ColliderBox::~ColliderBox()
{
}

ColliderBox::ColliderBox(const ColliderBox& _Other)
	: Collider(_Other)
{
	m_fWidth = _Other.m_fWidth;
	m_fHeight = _Other.m_fHeight;
	m_rtInfo = _Other.m_rtInfo;
}

Collider* ColliderBox::Clone()
{
	return new ColliderBox(*this);
}

bool ColliderBox::init()
{
	if (!Collider::init())
	{
		return false;
	}

	return true;
}

void ColliderBox::update()
{
	Collider::update();
}

void ColliderBox::postUpdate()
{
	Collider::postUpdate();
	Object* temp = getOwnerObject();

	// Vec vPos = m_pOwnerObject->getObjRenderPos();
	Vec vPos = m_pOwnerObject->getObjPos();
	m_vCenterPos = vPos + m_vOffset;
	m_rtInfo.Left = vPos.x - m_fWidth / 2.f + m_vOffset.x;
	m_rtInfo.Top = vPos.y - m_fHeight / 2.f + m_vOffset.y;
	m_rtInfo.Right = vPos.x + m_fWidth / 2.f + m_vOffset.x;
	m_rtInfo.Bottom = vPos.y + m_fHeight / 2.f + m_vOffset.y;
}

void ColliderBox::render(HDC _dc)
{
	Collider::render(_dc);

#ifdef _DEBUG
	HBRUSH hBrush = GameManager::getInst()->getGreenBrush();

	if (!m_lsPreCollision.empty())
	{
		hBrush = GameManager::getInst()->getRedBrush();
	}

	Vec vPos = m_pOwnerObject->getObjRenderPos();
	RectInfo rect;
	rect.Left = vPos.x - m_fWidth / 2.f + m_vOffset.x;
	rect.Top = vPos.y - m_fHeight / 2.f + m_vOffset.y;
	rect.Right = vPos.x + m_fWidth / 2.f + m_vOffset.x;
	rect.Bottom = vPos.y + m_fHeight / 2.f + m_vOffset.y;

	RECT rt = {
		(long)rect.Left,
		(long)rect.Top,
		(long)rect.Right,
		(long)rect.Bottom,
	};

	FrameRect(_dc, &rt, hBrush);

#endif /* _DEBUG */
}

bool ColliderBox::collision(Collider* _pDesCollider)
{
	switch (_pDesCollider->getColliderType())
	{
	case ECOLLIDER_TYPE::ECOLLISION_TYPE_BOX:
		return Collision::collisionBoxToBox(this, (ColliderBox*)_pDesCollider);
	case ECOLLIDER_TYPE::ECOLLISION_TYPE_SPHERE:
		return Collision::collisionBoxToSphere(this, (ColliderSphere*)_pDesCollider);
	case ECOLLIDER_TYPE::ECOLLISION_TYPE_POINT:	
		break;
	}

	return false;
}

bool ColliderBox::collisionMouse(const Vec& _vMousePos)
{
	if (m_rtInfo.Left > _vMousePos.x)
	{
		return false;
	}
	else if (m_rtInfo.Right < _vMousePos.x)
	{
		return false;
	}
	else if (m_rtInfo.Top > _vMousePos.y)
	{
		return false;
	}
	else if (m_rtInfo.Bottom < _vMousePos.y)
	{
		return false;
	}

	return true;
}
