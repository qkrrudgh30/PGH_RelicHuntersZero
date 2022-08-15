// MainScene.h

#pragma once
#include "Scene.h"
class MainScene :
    public Scene
{
public:
    MainScene();
    virtual ~MainScene();

    virtual bool init();

private:

    void loadSound();
    void loadAnimationSequence();
    void load(const wstring& _strName, const wstring& _strPath, int _nFrameCount, float _fSizeX, float _fSizeY);

    friend class SceneManager;

};