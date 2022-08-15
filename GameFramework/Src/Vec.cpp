// Vec.cpp

#include "GameInfo.h"
#include "Vec.h"

float radianToDegree(float _fRad)
{
	return _fRad * 180.f / PI;
}

float degreeToRadian(float _fDeg)
{
	return (_fDeg * PI) / 180.f;
}

float distance(const Vec& _vSrc, const Vec& _vDes)
{
	Vec res = _vSrc - _vDes;
	return res.length();
}

float getAngle(const Vec& _vSrc, const Vec& _vDes)
{
	float fH = distance(_vSrc, _vDes);
	float fB = _vDes.x - _vSrc.x;
	float fAngle = radianToDegree(acosf(fB / fH));

	if (_vDes.y < _vSrc.y)
	{
		fAngle = 360.f - fAngle;
	}

	return fAngle;
}
