#pragma once
#include "MapBase.h"
#include "../Resource/Texture.h"
#include "Tile.h"

struct ObjectInfo_t
{
    wstring strName;
    Vec     vPos;
};

class TileMap :
    public MapBase
{
public:
    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void preRender();
    virtual void render(HDC _hDC);
    virtual void start();

    bool createTile(int _nCountX, int _nCountY, const Vec& _vTileSize);
    bool setTileTexture(Texture* _pTexture);
    bool setTileTexture(Texture* _pTexture, int _nIdxX, int _nIdxY);
    bool setTileTexture(const Vec& _vPos, Texture* _pTexture);
    void changeTileOption(const Vec& _vPos, ETILE_OPTION _eOption);
    void setTileFrame(const Vec& _vPos, const Vec& _vStart, const Vec&  _vEnd);
    Tile* getTile(const Vec& _vPos);
    Tile* getTile(int _nIdx);
    Tile* getTile(int _nIdxX, int nIdxY);
    int getTileIndexX(float _fPosX);
    int getTileIndexY(float _fPosY);
    int getTileIndex(const Vec& _vPos);
    int getOriginTileIndexX(float PosX);
    int getOriginTileIndexY(float PosY);


    virtual void save(FILE* _pFile);
    virtual void load(FILE* _pFile);

    void tileImageAllClear();

    list<ObjectInfo_t>* getObjectList() { return &m_lsObjectInfo; }

    Vec* findObj(const wstring& _strName)
    {
        auto iter = m_lsObjectInfo.begin();
        auto endIter = m_lsObjectInfo.end();
        for (; iter != endIter;)
        {
            if (iter->strName == _strName)
            {
                return &(iter->vPos);
            }
            ++iter;
        }
        return nullptr;
    }

    void pushBackObj(ObjectInfo_t* _pInfo) {
        if (_pInfo) { m_lsObjectInfo.push_back(*_pInfo); }
    }

    void upObjCount() { ++m_nObjectCount; }
    int getObjCount() { return m_nObjectCount; }

    void createObj();
    void createObjInEdit();

protected:
    TileMap();
    virtual ~TileMap();

    vector<Tile*>       m_vecTile;
    SharedPtr<Texture>  m_pTileTexture;
    int                 m_nTileCountX;
    int                 m_nTileCountY;
    Vec                 m_vTileSize;
    int                 m_nStartX;
    int                 m_nStartY;
    int                 m_nEndX;
    int                 m_nEndY;
    list<ObjectInfo_t>  m_lsObjectInfo;
    int                 m_nObjectCount;

private:



    friend class Scene;
    friend class SceneEditStage;
};

