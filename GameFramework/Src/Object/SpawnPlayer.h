// SpawnPlayer.h

#pragma once
#include "Object.h"

class Player;

class SpawnPlayer :
    public Object
{
public:
    SpawnPlayer();
    SpawnPlayer(const SpawnPlayer& _Other);
    virtual ~SpawnPlayer();

    SpawnPlayer* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);
    virtual void start();

private:
    Player* m_pPlayer;

    void playerSpawnSetupEnd();
    void playerSpawnUnsetEnd();
    void playerSpawnSetup();
};
