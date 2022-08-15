// Collision.h

#pragma once

class ColliderBox;
class ColliderSphere;

class Collision
{
public:
	static bool collisionBoxToBox(ColliderBox* _pSrc, ColliderBox* _pDes);
	static bool collisionBoxToBox(const RectInfo& _rtSrc, const RectInfo& _rtDes);

	static bool collisionSphereToSphere(ColliderSphere* _pSrc, ColliderSphere* _pDes);
	static bool collisionSphereToSphere(const SphereInfo& _spSrc, const SphereInfo& _spDes);

	static bool collisionBoxToSphere(ColliderBox* _pSrc, ColliderSphere* _pDes);
	static bool collisionBoxToSphere(const RectInfo& _rtSrc, const SphereInfo& _spDes);

private:


};

