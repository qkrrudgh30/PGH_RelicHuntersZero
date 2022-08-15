#pragma once
#include "Scene.h"

class EditorDlg;
class TileMap;
class Texture;
class UIWindowEdit;



class SceneEditStage :
    public Scene
{
public:
    virtual bool init();
    virtual bool update();
    virtual bool postUpdate();

    void onEditor();
    void createTileMap();
    void setTileInfo(int _nCountX, int _nCountY, int _nScaleX, int _nScaleY);
    void setTileTexture(Texture* _pTexture);

    void MouseLButton();
    void MouseRButton();

    void load(const char* FullPath);
    void save(const char* FullPath);

    void tileImageAllClear();

    UIWindowEdit* getUIWindowEdit() { return m_pUIWindowEdit; }

    void setSceneChange(bool _bOn) { m_bSceneChange = _bOn; }

private:
    SceneEditStage();
    virtual ~SceneEditStage();

    EditorDlg*          m_pDlg;
    TileMap*            m_pTileMap;
    bool                m_bStart;
    float               m_fScrollSpeed;
    UIWindowEdit*       m_pUIWindowEdit;
    ETILE_EDITMODE      m_eCurMode;
    bool                m_bSceneChange;
    

    void loadSound();
    void loadAnimationSequence();
    void loadAnimation();

    friend class SceneManager;
};

