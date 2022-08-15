// Collision.cpp

#include "../GameInfo.h"
#include "Collision.h"
#include "ColliderBox.h"
#include "ColliderSphere.h"

bool Collision::collisionBoxToBox(ColliderBox* _pSrc, ColliderBox* _pDes)
{
	if (collisionBoxToBox(_pSrc->getInfo(), _pDes->getInfo()))
	{
		return true;
	}
	return false;
}

bool Collision::collisionBoxToBox(const RectInfo& _rtSrc, const RectInfo& _rtDes)
{
	if (_rtSrc.Left > _rtDes.Right)
	{
		return false;
	}

	if (_rtSrc.Right < _rtDes.Left)
	{
		return false;
	}

	if (_rtSrc.Top > _rtDes.Bottom)
	{
		return false;
	}

	if (_rtSrc.Bottom < _rtDes.Top)
	{
		return false;
	}

	return true;
}

bool Collision::collisionSphereToSphere(ColliderSphere* _pSrc, ColliderSphere* _pDes)
{
	if (collisionSphereToSphere(_pSrc->getInfo(), _pDes->getInfo()))
	{
		return true;
	}
	return false;
}

bool Collision::collisionSphereToSphere(const SphereInfo& _spSrc, const SphereInfo& _spDes)
{
	float dist = distance(_spSrc.vCenter, _spDes.vCenter);

	return dist <= _spSrc.fRadius + _spDes.fRadius;
}

bool Collision::collisionBoxToSphere(ColliderBox* _pSrc, ColliderSphere* _pDes)
{
	if (collisionBoxToSphere(_pSrc->getInfo(), _pDes->getInfo()))
	{
		return true;
	}
	return false;
}

bool Collision::collisionBoxToSphere(const RectInfo& _rtSrc, const SphereInfo& _spDes)
{
	Vec vRectScale;
	vRectScale.x = _rtSrc.Right - _rtSrc.Left;
	vRectScale.y = _rtSrc.Bottom - _rtSrc.Top;
	Vec vRectPos;
	vRectPos.x = _rtSrc.Left + (vRectScale.x / 2.f);
	vRectPos.y = _rtSrc.Top + (vRectScale.y / 2.f);
	float fDist = distance(vRectPos, _spDes.vCenter);

	/*
	if ((_rtSrc.Left <= _spDes.vCenter.x && _spDes.vCenter.x <= _rtSrc.Right) ||
		(_rtSrc.Top <= _spDes.vCenter.y && _spDes.vCenter.y <= _rtSrc.Bottom))
	{
		if (_spDes.vCenter.x + _spDes.fRadius <= _rtSrc.Left)
		{ 3847 »óÇÏ
			return true;
		}
		else if (_spDes.vCenter.x - _spDes.fRadius <= _rtSrc.Right)
		{
			return true;
		}
		else if (_spDes.vCenter.y + _spDes.fRadius <= _rtSrc.Top)
		{
			return true;
		}
		else if (_spDes.vCenter.y - _spDes.fRadius <= _rtSrc.Bottom)
		{
			return true;
		}
	}
	*/

	if (_rtSrc.Left <= _spDes.vCenter.x - _spDes.fRadius)
	{
		// 1 O O
		// 4 O O
		// 7 O O
		if (_spDes.vCenter.x + _spDes.fRadius <= _rtSrc.Right)
		{
			// 1 O 3
			// 4 O 6
			// 7 O 9
			return fDist <= _spDes.fRadius + vRectScale.y / 2.f;
		}
		else
		{
			// 1 2 O
			// 4 5 O
			// 7 8 O
			if (_spDes.vCenter.y + _spDes.fRadius <= _rtSrc.Top ||
				_rtSrc.Bottom <= _spDes.vCenter.y - _spDes.fRadius)
			{
				// 1 2 O
				// 4 5 6
				// 7 8 O
				float fDiagonal = distance(vRectPos, Vec(_rtSrc.Right, _rtSrc.Bottom));
				return fDist <= _spDes.fRadius + fDiagonal;
			}
			else
			{
				// 1 2 3
				// 4 5 O
				// 7 8 9
				return fDist <= _spDes.fRadius + vRectScale.x / 2.f;
			}
		}
	}
	else
	{
		// O 2 3
		// O 5 6
		// O 8 9
		if (_spDes.vCenter.y + _spDes.fRadius <= _rtSrc.Top ||
			_rtSrc.Bottom <= _spDes.vCenter.y - _spDes.fRadius)
		{
			// O 2 3
			// 4 5 6
			// O 8 9
			float fDiagonal = distance(vRectPos, Vec(_rtSrc.Left, _rtSrc.Top));
			return fDist <= _spDes.fRadius + fDiagonal;
		}
		else
		{
			// 1 2 3
			// O 5 6
			// 7 8 9
			return fDist <= _spDes.fRadius + vRectScale.x / 2.f;
		}
	}

}
