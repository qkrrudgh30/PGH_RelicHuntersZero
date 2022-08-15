#pragma once
#include "Scene.h"


class KamikazeBoss;

class SceneStage2 :
    public Scene
{
public:
    SceneStage2();
    virtual ~SceneStage2();

    virtual bool init();
    virtual bool update();
    virtual bool postUpdate();
    virtual bool collision();
    virtual bool render(HDC _hDC);

private:
    size_t m_uCageCount;
    bool m_bBossSpawned;
    KamikazeBoss* m_pKamikazeBoss;


    void loadSound();
    void loadAnimationSequence();
    void load(const wstring& _strName, const wstring& _strPath, int _nFrameCount, float _fSizeX, float _fSizeY);

    friend class SceneManager;
};

