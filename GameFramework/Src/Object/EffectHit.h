#pragma once
#include "Object.h"
class EffectHit :
    public Object
{
public:
    EffectHit();
    virtual ~EffectHit();
    EffectHit(const EffectHit& _Other);

	virtual EffectHit* Clone();

	virtual bool init();
	virtual void update();
	virtual void postUpdate();
	virtual void collision();
	virtual void render(HDC _dc);
	virtual void start();

	void animationFinish();
	void bomb();

private:
	
	friend class Scene;

};

