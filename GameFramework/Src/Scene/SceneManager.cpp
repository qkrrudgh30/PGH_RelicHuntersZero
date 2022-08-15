// SceneManager.cpp

#include "../GameInfo.h"
#include "SceneManager.h"
#include "../Input.h"

SceneManager::SceneManager()
    : m_pCurScene(nullptr)
    , m_pNextScene(nullptr)
{
}

SceneManager::~SceneManager()
{
    SAFE_DELETE(m_pCurScene);
    SAFE_DELETE(m_pNextScene);
}

bool SceneManager::init()
{
    m_pCurScene = new Scene;

    m_pCurScene->init();

    return true;

}

bool SceneManager::update()
{
    m_pCurScene->update();
    return changeScene();
}

bool SceneManager::postUpdate()
{
    m_pCurScene->postUpdate();
    return changeScene();
}

bool SceneManager::collision()
{
    m_pCurScene->collision();
    return changeScene();
}

bool SceneManager::render(HDC _dc)
{
    m_pCurScene->render(_dc);
    return changeScene();
}

bool SceneManager::changeScene()
{
    if (nullptr != m_pNextScene)
    {
        SAFE_DELETE(m_pCurScene);
        Input::getInst()->clearCallback();

        m_pCurScene = m_pNextScene;
        m_pNextScene = nullptr;

        return true;
    }

    return false;
}
