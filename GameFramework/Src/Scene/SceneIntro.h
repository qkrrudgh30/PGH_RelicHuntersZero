// SceneIntro.h

#pragma once
#include "Scene.h"
class SceneIntro :
    public Scene
{
public:
    SceneIntro();
    virtual ~SceneIntro();

    virtual bool init();

private:
    void loadAnimationSequence();
    void load(const wstring& _strName, const wstring& _strPath, int _nFrameCount, float _fSizeX, float _fSizeY);

    friend class SceneManager;

};