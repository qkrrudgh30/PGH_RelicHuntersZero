// Scene.cpp

#include "../GameInfo.h"
#include "Scene.h"
#include "SceneResource.h"
#include "SceneCollision.h"
#include "Camera.h"
#include "../Map/MapBase.h"
#include "../UI/UIWindowESC.h"
#include "../UI/UIWidgetImage.h"

Scene::Scene()
    : m_pSceneResource(nullptr)
    , m_pSceneCollision(nullptr)
    , m_pCamera(nullptr)
    , m_nRenderCount(0)
    , m_nRenderCapacity(2)
    , m_dpRenderArray(nullptr)
    , m_nUIWindowCount(0)
    , m_nUIWindowCapacity(2)
    , m_dpUIWindowArray(nullptr)
    , m_bSettingWindow(false)
    , m_pTileMap(nullptr)
{
    m_pSceneResource = new SceneResource;
    m_pSceneCollision = new SceneCollision;
    m_pSceneCollision->m_pOwnerScene = this;

    m_pCamera = new Camera;
    m_pCamera->init();

    m_dpRenderArray = new Object * [m_nRenderCapacity];

    m_dpUIWindowArray = new UIWindow * [m_nUIWindowCapacity];
}

Scene::~Scene()
{
    SAFE_DELETE(m_pCamera);
    SAFE_DELETE_ARRAY(m_dpRenderArray);

    for (int i = 0; i < m_nUIWindowCount; ++i)
    {
        SAFE_RELEASE(m_dpUIWindowArray[i]);
    }
    SAFE_DELETE_ARRAY(m_dpUIWindowArray);

    {
        auto iter = m_lsMapList.begin();
        auto endIter = m_lsMapList.end();
        for (; iter != endIter;)
        {
            SAFE_DELETE((*iter));
            ++iter;
        }
        m_lsMapList.clear();
    }

    m_lsObjects.clear();
    m_mapPrototypes.clear();
    SAFE_DELETE(m_pSceneResource);
    SAFE_DELETE(m_pSceneCollision);

}

bool Scene::init()
{
    return true;
}

bool Scene::update()
{
    {
        auto iter = m_lsObjects.begin();
        auto iterEnd = m_lsObjects.end();

        for (; iter != iterEnd;)
        {
            if (!(*iter)->isAlive())
            {
                iter = m_lsObjects.erase(iter);
                iterEnd = m_lsObjects.end();
                continue;
            }

            (*iter)->update();
            ++iter;
        }
    }

    {
        for (int i = 0; i < m_nUIWindowCount;)
        {
            if (false == m_dpUIWindowArray[i]->isAlive())
            {
                --m_nUIWindowCount;
                for (int j = i; j < m_nUIWindowCount; ++j)
                {
                    m_dpUIWindowArray[j] = m_dpUIWindowArray[j + 1];
                }
                continue;
            }
            else if (false == m_dpUIWindowArray[i]->isUIWindowVisible())
            {
                ++i;
                continue;
            }

            m_dpUIWindowArray[i]->update();
            ++i;
        }
    }
    

    return true;
}

bool Scene::postUpdate()
{
    {
        auto iter = m_lsObjects.begin();
        auto iterEnd = m_lsObjects.end();

        for (; iter != iterEnd;)
        {
            if (!(*iter)->isAlive())
            {
                iter = m_lsObjects.erase(iter);
                iterEnd = m_lsObjects.end();
                continue;
            }

            (*iter)->postUpdate();
            ++iter;
        }
    }
    

    {
        for (int i = 0; i < m_nUIWindowCount;)
        {
            if (false == m_dpUIWindowArray[i]->isAlive())
            {
                --m_nUIWindowCount;
                for (int j = i; j < m_nUIWindowCount; ++j)
                {
                    m_dpUIWindowArray[j] = m_dpUIWindowArray[j + 1];
                }
                continue;
            }
            else if (false == m_dpUIWindowArray[i]->isUIWindowVisible())
            {
                ++i;
                continue;
            }

            m_dpUIWindowArray[i]->postUpdate();
            ++i;
        }
    }

    m_pCamera->update();

    {
        auto	iter = m_lsMapList.begin();
        auto	iterEnd = m_lsMapList.end();

        for (; iter != iterEnd;)
        {
            if (!(*iter)->isActive())
            {
                SAFE_DELETE((*iter));
                iter = m_lsMapList.erase(iter);
                iterEnd = m_lsMapList.end();
                continue;
            }

            else if (!(*iter)->isEnable())
            {
                ++iter;
                continue;
            }

            (*iter)->update();
            ++iter;
        }
    }

    {
        auto	iter = m_lsMapList.begin();
        auto	iterEnd = m_lsMapList.end();

        for (; iter != iterEnd;)
        {
            if (!(*iter)->isActive())
            {
                SAFE_DELETE((*iter));
                iter = m_lsMapList.erase(iter);
                iterEnd = m_lsMapList.end();
                continue;
            }

            else if (!(*iter)->isEnable())
            {
                ++iter;
                continue;
            }

            (*iter)->postUpdate();
            ++iter;
        }
    }

    return true;
}

bool Scene::collision()
{
    {
        auto iter = m_lsObjects.begin();
        auto iterEnd = m_lsObjects.end();

        for (; iter != iterEnd;)
        {
            if (!(*iter)->isAlive())
            {
                iter = m_lsObjects.erase(iter);
                iterEnd = m_lsObjects.end();
                continue;
            }

            (*iter)->collision();
            ++iter;
        }
    }

    {
        if (m_nUIWindowCount >= 2)
        {
            qsort(m_dpUIWindowArray, (size_t)m_nUIWindowCount, sizeof(UIWindow*),
                Scene::SortZ);
        }

        for (int i = 0; i < m_nUIWindowCount;)
        {
            if (false == m_dpUIWindowArray[i]->isAlive())
            {
                --m_nUIWindowCount;
                for (int j = i; j < m_nUIWindowCount; ++j)
                {
                    m_dpUIWindowArray[j] = m_dpUIWindowArray[j + 1];
                }
                continue;
            }
            else if (false == m_dpUIWindowArray[i]->isUIWindowVisible())
            {
                ++i;
                continue;
            }

            m_dpUIWindowArray[i]->collision();

            m_pSceneCollision->addUIWindow(m_dpUIWindowArray[i]);

            ++i;
        }
    }
    
    m_pSceneCollision->collisionMouse();
    m_pSceneCollision->collision();

    return true;
}

int Scene::SortY(const void* _pSrc, const void* _pDes)
{
    Object* pSrcObj = *(Object**)_pSrc;
    Object* pDesObj = *(Object**)_pDes;
    float fSrcY = pSrcObj->getObjBottom();
    float fDesY = pDesObj->getObjBottom();

    if (fSrcY < fDesY)
    {
        return -1;
    }
    else if (fSrcY > fDesY)
    {
        return 1;
    }
    return 0;
}

int Scene::SortZ(const void* _pSrc, const void* _pDes)
{
    UIWindow* pSrcWindow = *(UIWindow**)_pSrc;
    UIWindow* pDesWindow = *(UIWindow**)_pDes;
    int fSrcZ = pSrcWindow->getUIWindowZOrder();
    int fDesZ = pDesWindow->getUIWindowZOrder();

    if (fSrcZ > fDesZ)
    {
        return -1;
    }
    else if (fSrcZ < fDesZ)
    {
        return 1;
    }
    return 0;
}

bool Scene::render(HDC _dc)
{
    {
        auto	iter = m_lsMapList.begin();
        auto	iterEnd = m_lsMapList.end();

        for (; iter != iterEnd;)
        {
            if (!(*iter)->isActive())
            {
                SAFE_DELETE((*iter));
                iter = m_lsMapList.erase(iter);
                iterEnd = m_lsMapList.end();
                continue;
            }

            else if (!(*iter)->isEnable())
            {
                ++iter;
                continue;
            }

            (*iter)->render(_dc);
            ++iter;
        }
    }

    {
        auto iter = m_lsObjects.begin();
        auto iterEnd = m_lsObjects.end();

        for (; iter != iterEnd;)
        {
            if (!(*iter)->isAlive())
            {
                iter = m_lsObjects.erase(iter);
                iterEnd = m_lsObjects.end();
                continue;
            }

            (*iter)->preRender();

            if (false == (*iter)->isObjCameraCull())
            {
                if (m_nRenderCount == m_nRenderCapacity)
                {
                    m_nRenderCapacity *= 2;

                    Object** dpRenderArray = new Object * [m_nRenderCapacity];
                    memcpy(dpRenderArray, m_dpRenderArray, sizeof(Object*) * m_nRenderCount);
                    SAFE_DELETE_ARRAY(m_dpRenderArray);
                    m_dpRenderArray = dpRenderArray;
                }
                m_dpRenderArray[m_nRenderCount] = *iter;
                ++m_nRenderCount;
            }

            ++iter;
        }
    }
    
    if (m_nRenderCount == m_nRenderCapacity)
    {
        m_nRenderCapacity *= 2;

        Object** dpRenderArray = new Object * [m_nRenderCapacity];
        memcpy(dpRenderArray, m_dpRenderArray, sizeof(Object*) * m_nRenderCount);
        SAFE_DELETE_ARRAY(m_dpRenderArray);
        m_dpRenderArray = dpRenderArray;
    }

    qsort(m_dpRenderArray, (size_t)m_nRenderCount, sizeof(Object*), Scene::SortY);

    int gunIndex = -1, playerIndex = -1;
    for (int i = 0; i < m_nRenderCount; ++i)
    {
        if (L"Gun" == m_dpRenderArray[i]->getObjName())
        {
            gunIndex = i;
            for (int j = 0; j < m_nRenderCount; ++j)
            {
                if (L"Player" == m_dpRenderArray[j]->getObjName())
                {
                    playerIndex = j;
                }
            }
        }
    }

    if (gunIndex != -1 && playerIndex != -1)
    {
        Object* temp = m_dpRenderArray[gunIndex];
        m_dpRenderArray[gunIndex] = m_dpRenderArray[playerIndex];
        m_dpRenderArray[playerIndex] = temp;
    }
    
    for (int i = 0; i < m_nRenderCount; ++i)
    {
        m_dpRenderArray[i]->render(_dc);

        
    }


    // 벽 타일 그리기
    {
        auto iter = m_lsWallTile.begin();
        auto endIter = m_lsWallTile.end();
        for (; iter != endIter;)
        {
            (*iter)->render(_dc);
            ++iter;
        }
    }

    m_nRenderCount = 0;

    {
        for (int i = 0; i < m_nUIWindowCount;)
        {
            if (false == m_dpUIWindowArray[i]->isAlive())
            {
                --m_nUIWindowCount;
                for (int j = i; j < m_nUIWindowCount; ++j)
                {
                    m_dpUIWindowArray[j] = m_dpUIWindowArray[j + 1];
                }
                continue;
            }
            
            ++i;
        }

        for (int i = m_nUIWindowCount - 1; i >= 0;)
        {
            if (false == m_dpUIWindowArray[i]->isUIWindowVisible())
            {
                --i;
                continue;
            }
            m_dpUIWindowArray[i]->render(_dc);
            --i;
        }
    }
    
    


    m_pCamera->render(_dc);

    return true;
}


Object* Scene::findObject(const wstring& _strName)
{
    auto iter = m_lsObjects.begin();
    auto iterEnd = m_lsObjects.end();
    for (; iter != iterEnd;)
    {
        if (_strName == (*iter)->getObjName())
        {
            return *iter;
        }
        ++iter;
    }
    return nullptr;
}

Object* Scene::findPrototype(const wstring& _strName)
{
    auto iter = m_mapPrototypes.find(_strName);

    if (m_mapPrototypes.end() == iter)
    {
        return nullptr;
    }
    return iter->second;
}