#pragma once
#include "Object.h"
#include "../Map/Tile.h"

class Tile;
class Player;

class WallTile :
    public Object
{
public:
    WallTile();
    WallTile(const WallTile& _Other);
    virtual ~WallTile();

    virtual WallTile* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void preRender();
    virtual void render(HDC _hDC);
    virtual void start();

    void collisionBegin(Collider* _pSrc, Collider* _pDes);
    void collisionEnd(Collider* _pSrc, Collider* _pDes);
    /*
    Tile* getOwnerTile() { return m_pOwnerTile; }
    void setOwnerTile(Tile* _pTile) { m_pOwnerTile = _pTile; }
    */
private:
    // unordered_map<SharedPtr<Object>> m_pCollisionObject; // ���Ŀ� map �ڷ������� ��� �־�� �ҵ�. �˻��� ���. => hash;
    Player* m_pPlayer;
    bool m_bOnCollision;
    bool m_bUpLock;
    bool m_bDownLock;
    bool m_bLeftLock;
    bool m_bRightLock;

    friend class Tile;
};

