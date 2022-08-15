// Object.h

#pragma once
#include "Object.h"
class SpawnPoint :
    public Object
{
public:
    SpawnPoint();
    SpawnPoint(const SpawnPoint& _Other);
    virtual ~SpawnPoint();

    SpawnPoint* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);
    virtual void start();

private:
    void playerSpawnSetupEnd();

};

