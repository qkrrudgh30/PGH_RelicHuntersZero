
#include "../GameInfo.h"
#include "WallTile.h"
#include "Monster.h"
#include "../Timer.h"
#include "../Scene/Scene.h"
#include "../Collision/ColliderBox.h"
#include "../Scene/Camera.h"
#include "../Object/Player.h"

class ColliderBox;

WallTile::WallTile()
	: m_bOnCollision(false)
	, m_pPlayer(nullptr)
	, m_bUpLock(false)
	, m_bDownLock(false)
	, m_bLeftLock(false)
	, m_bRightLock(false)
{
	setObjSpeed(0.f);
}

WallTile::WallTile(const WallTile& _Other)
	: Object(_Other)
{
}

WallTile::~WallTile()
{
}

WallTile* WallTile::Clone()
{
	return new WallTile(*this);
}

bool WallTile::init()
{
	if (!Object::init())
	{
		return false;
	}

	ColliderBox* pWallTile = addCollider<ColliderBox>(L"WallTile");
	pWallTile->setExtent(m_vScale.x, m_vScale.y);
	pWallTile->setOffset(Vec(-1.f * (m_vScale.x / 2.f), -1 * (m_vScale.y / 2.f)));
	pWallTile->setProfile(L"Wall");
	pWallTile->setCollisionBeginFunc<WallTile>(this, &WallTile::collisionBegin);
	pWallTile->setCollisionEndFunc<WallTile>(this, &WallTile::collisionEnd);

	return true;
}

void WallTile::update()
{
	Object::update();
	/*
	if (m_bOnCollision)
	{
		Vec vDir = (getObjPos() + getObjScale() / 2.f) - m_pCollisionObject->get;
		// vDir.normalize();
		if (vDir.y < 0 && vDir.x < 0)
		{
			// ж->鼻 醱給
			int a = 0;
		}
		else if (vDir.y < 0 && vDir.x > 0)
		{
			// 謝->辦 醱給
			int a = 0;
		}
		else if (vDir.y < 0 && vDir.x < 0)
		{
			// 謝->辦 醱給
			int a = 0;
		}
		else if (vDir.y < 0 && vDir.x < 0)
		{
			// 謝->辦 醱給
			int a = 0;
		}
		m_pCollisionObject->setObjPos(m_pCollisionObject->getObjPos()+vDir*Vec(1.f, 1.f));
		m_bOnCollision = false;
	}
	*/
}

void WallTile::postUpdate()
{
	Object::postUpdate();
}

void WallTile::collision()
{
	Object::collision();
}

void WallTile::preRender()
{
	Object::preRender();
}

void WallTile::render(HDC _hDC)
{
	Object::render(_hDC);
	/*
	auto iter = m_lsColliders.begin();
	auto iterEnd = m_lsColliders.end();
	for (; iter != iterEnd;)
	{
		if (!(*iter)->isAlive())
		{
			iter = m_lsColliders.erase(iter);
			iterEnd = m_lsColliders.end();
			continue;
		}
		else if ((*iter)->isEnable())
		{
			(*iter)->render(_hDC);
		}
		++iter;
	}
	*/
}

void WallTile::start()
{
	Object::start();
}

void WallTile::collisionBegin(Collider* _pSrc, Collider* _pDes)
{
	
	if (_pDes->getOwnerObject()->getObjName() == L"Player")
	{
		
		Vec vSrcColliderPos = _pSrc->getOwnerObject()->getObjPos() + _pSrc->getOffset();
		Vec vDesColliderPos = _pDes->getOwnerObject()->getObjPos() + _pDes->getOffset();
		Vec vDir = vDesColliderPos - vSrcColliderPos;
		m_pPlayer = (Player*)(_pDes->getOwnerObject());
		
		if (vDir.x <= -49.f)
		{
			// 謝 -> 辦
			m_pPlayer->setMoveUpLock(false);
			m_pPlayer->setMoveDownLock(false);
			m_pPlayer->setMoveLeftLock(false);
			m_pPlayer->setMoveRightLock(true);
			
		}
		else if (vDir.x >= 49.f)
		{
			// 辦 -> 謝
			m_pPlayer->setMoveUpLock(false);
			m_pPlayer->setMoveDownLock(false);
			m_pPlayer->setMoveLeftLock(true);
			m_pPlayer->setMoveRightLock(false);
			
		}
		else if (vDir.y <= -49.f)
		{
			// 鼻 -> ж
			m_pPlayer->setMoveUpLock(false);
			m_pPlayer->setMoveDownLock(true);
			m_pPlayer->setMoveLeftLock(false);
			m_pPlayer->setMoveRightLock(false);
			
		}
		else if (vDir.y >= 49.f)
		{
			// ж -> 鼻
			m_pPlayer->setMoveUpLock(true);
			m_pPlayer->setMoveDownLock(false);
			m_pPlayer->setMoveLeftLock(false);
			m_pPlayer->setMoveRightLock(false);
		}
	}
}

void WallTile::collisionEnd(Collider* _pSrc, Collider* _pDes)
{
	if (_pDes->getOwnerObject()->getObjName() == L"Player")
	{
		m_pPlayer->setMoveUpLock(false);
		m_pPlayer->setMoveDownLock(false);
		m_pPlayer->setMoveLeftLock(false);
		m_pPlayer->setMoveRightLock(false);
	}
}
