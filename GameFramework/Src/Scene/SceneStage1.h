#pragma once
#include "Scene.h"

class SceneStage1 :
    public Scene
{
public:
    SceneStage1();
    virtual ~SceneStage1();

    virtual bool init();
    virtual bool update();
    virtual bool postUpdate();
    virtual bool collision();
    virtual bool render(HDC _hDC);

private:
    size_t m_uSpawnCount;
    bool m_bPotalCreated;

    void loadSound();
    void loadAnimationSequence();
    void load(const wstring& _strName, const wstring& _strPath, int _nFrameCount, float _fSizeX, float _fSizeY);

    friend class SceneManager;

};

