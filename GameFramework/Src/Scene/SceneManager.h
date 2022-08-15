// SceneManager.h

#pragma once

#include "Scene.h"

class SceneManager
{
    SINGLETON(SceneManager);

public:
    bool init();
    bool update();
    bool postUpdate();
    bool collision();
    bool render(HDC _dc);

    template <typename T>
    bool createScene();

    Scene* getCurScene() { return m_pCurScene; }

private:
    Scene* m_pCurScene;
    Scene* m_pNextScene;

    bool changeScene();

};

template<typename T>
inline bool SceneManager::createScene()
{
    m_pNextScene = new T;

    if (!m_pNextScene->init())
    {
        SAFE_DELETE(m_pNextScene);
        return false;
    }

    return true;
}
