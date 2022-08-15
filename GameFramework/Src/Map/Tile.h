#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"
#include "../Object/WallTile.h"

class Scene;
class WallTile;

class Tile
{
public:
    Tile();
    virtual ~Tile();
    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void preRender();
    virtual void render(HDC _hDC);
    virtual void start();
    void save(FILE* _pFile);
    void load(FILE* _pFile);

    void setOwnerScene(Scene* _pScene) { m_pOwnerScene = _pScene; }
    Scene* getOwnerScene() { return m_pOwnerScene; }

    void setTileTexture(Texture* _pTexture) { m_pTexture = _pTexture; }
    Texture* getTileTexture() { return m_pTexture; }

    void setStartFrame(const Vec& _vStartFrame) { m_vStartFrame = _vStartFrame; }
    Vec& getStartFrame() { return m_vStartFrame; }

    void setEndFrame(const Vec& _vEndFrame) { m_vEndFrame = _vEndFrame; }
    Vec& getEndFrame() { return m_vEndFrame; }

    void setPos(const Vec& _vPos) { m_vPos = _vPos; }
    Vec& getPos() { return m_vPos; }

    void setScale(const Vec& _vScale) { m_vScale = _vScale; }
    Vec& getScale() { return m_vScale; }

    void setIdxX(int _nIdxX) { m_nIdxX = _nIdxX; }
    int  getIdxX() { return m_nIdxX; }

    void setIdxY(int _nIdxY) { m_nIdxY = _nIdxY; }
    int  getIdxY() { return m_nIdxY; }

    void setIdx(int _nIdx) { m_nIdx = _nIdx; }
    int  getIdx() { return m_nIdx; }

    void setTileOption(ETILE_OPTION _eTileOption) { m_eOption = _eTileOption; }
    ETILE_OPTION getTileOption() { return m_eOption; }

    void setTileInfo(const Vec _vPos, const Vec& _vScale,
        int _nIdxX, int _nIdxY, int _nIdx, Texture* _pTexture)
    {
        m_vPos = _vPos;
        m_vScale = _vScale;
        m_nIdxX = _nIdxX;
        m_nIdxY = _nIdxY;
        m_nIdx = _nIdx;
        m_pTexture = _pTexture;
        m_vEndFrame = _vScale;
    }

    WallTile* getWallTile() { return m_pWallTile; }
    void setWallTile(WallTile* _pWallTile) { m_pWallTile = _pWallTile; }

private:
    Scene*              m_pOwnerScene;
    Texture*            m_pTexture;
    Vec                 m_vStartFrame;
    Vec                 m_vEndFrame;
    Vec                 m_vPos;
    Vec                 m_vScale;
    int                 m_nIdxX;
    int                 m_nIdxY;
    int                 m_nIdx;
    ETILE_OPTION        m_eOption;
    WallTile*           m_pWallTile;

    friend class WallTile;
    friend class TileMap;
    friend class SceneStage1;
    friend class SceneStage2;
};

