// Scene.h

#pragma once

#include "../GameInfo.h"
#include "../Object/Object.h"
#include "../UI/UIWindow.h"
#include "../Map/TileMap.h"

class SceneResource;
class SceneCollision;
class Camera;
class MapBase;

class Scene
{

public:
    virtual bool init();
    virtual bool update();
    virtual bool postUpdate();
    virtual bool collision();
    virtual bool render(HDC _dc);

    list<SharedPtr<Object>>* getObjectList() { return &m_lsObjects; }

    SceneResource* getSceneResource() const { return m_pSceneResource; }

    template <typename T>
    T* createObject(const wstring& _strName,
        const Vec& _vPos = Vec(0.f, 0.f),
        const Vec& _vScale = Vec(100.f, 100.f));

    SceneCollision* getSceneCollision() const { return m_pSceneCollision; }

    Object* findObject(const wstring& _strName);

    template <typename T>
    T* createPrototype(const wstring& _strName);
    Object* findPrototype(const wstring& _strName);
    template <typename T>
    T* createObject(const wstring& _strName, const wstring& _strPrototypeName,
        const Vec& _vPos = Vec(0.f, 0.f),
        const Vec& _vScale = Vec(100.f, 100.f));

    Camera* getCamera() { return m_pCamera; }

    static int SortY(const void* _pSrc, const void* _pDes);

    template <typename T>
    T* createUIWindow(const wstring& _strName);

    static int SortZ(const void* _pSrc, const void* _pDes);

    template <typename T>
    T* findUIWindow(const wstring& _strName);

    template <typename T>
    T* createMap(const wstring& _strName,
        const Vec& _vPos = Vec(0.f, 0.f),
        const Vec& _vScale = Vec(1000.f, 1000.f));

    bool isESCWindow() { return m_bSettingWindow; }
    void setESCWindow(bool _bSettingWindow) { m_bSettingWindow = _bSettingWindow; }

    TileMap* getTileMap() { return m_pTileMap; }

    list<Tile*>* getWallTileList() { return &m_lsWallTile; }

protected:
    Scene();
    virtual ~Scene();
    list<Tile*>                                 m_lsWallTile;

private:
    list<SharedPtr<Object>>                     m_lsObjects;
    SceneResource*                              m_pSceneResource;
    SceneCollision*                             m_pSceneCollision;
    unordered_map<wstring, SharedPtr<Object>>   m_mapPrototypes;
    Camera*                                     m_pCamera;
    int                                         m_nRenderCount;
    int                                         m_nRenderCapacity;
    Object**                                    m_dpRenderArray;
    int                                         m_nUIWindowCount;
    int                                         m_nUIWindowCapacity;
    UIWindow**                                  m_dpUIWindowArray;  
    list<MapBase*>                              m_lsMapList;
    bool                                        m_bSettingWindow;
    TileMap*                                    m_pTileMap;

    friend class SceneManager;

};

template<typename T>
inline T* Scene::createObject(const wstring& _strName, const Vec& _vPos, const Vec& _vScale)
{
    T* pObj = new T;

    pObj->setObjName(_strName);
    pObj->setObjPos(_vPos);
    pObj->setObjScale(_vScale);
    pObj->setOwnerScene(this);

    if (!pObj->init())
    {
        SAFE_DELETE(pObj);
        return nullptr;
    }

    m_lsObjects.push_back(pObj);

    return pObj;
}

template<typename T>
inline T* Scene::createPrototype(const wstring& _strName)
{
    T* pObj = new T;
    pObj->setObjName(_strName);
    pObj->setOwnerScene(this);
    // 실제 배치될 개체가 아니므로, 위치와 크기정보는 필요없음.

    if (false == pObj->init())
    {
        SAFE_DELETE(pObj);
        return nullptr;
    }

    m_mapPrototypes.insert(make_pair(_strName, pObj));

    return pObj;
}

template<typename T>
inline T* Scene::createObject(const wstring& _strName, const wstring& _strPrototypeName, const Vec& _vPos, const Vec& _vScale)
{
    Object* pPrototype = findPrototype(_strPrototypeName);
    if (nullptr == pPrototype)
    {
        return nullptr;
    }

    T* pObj = (T*)pPrototype->Clone();

    pObj->setObjName(_strName);
    pObj->setObjPos(_vPos);
    pObj->setObjScale(_vScale);
    pObj->setOwnerScene(this);
    pObj->start();

    m_lsObjects.push_back(pObj);

    return pObj;
}

template<typename T>
inline T* Scene::createUIWindow(const wstring& _strName)
{
    T* pUIWindow = new T;
    pUIWindow->setObjName(_strName);
    pUIWindow->setUIWindowOwnerScene(this);

    if (false == pUIWindow->init())
    {
        SAFE_DELETE(pUIWindow);
        return nullptr;
    }

    if (m_nUIWindowCount == m_nUIWindowCapacity)
    {
        m_nUIWindowCapacity *= 2;
        UIWindow** dpUIWindowArray = new UIWindow * [m_nUIWindowCapacity];
        memcpy(dpUIWindowArray, m_dpUIWindowArray, sizeof(UIWindow*) * m_nUIWindowCount);
        SAFE_DELETE_ARRAY(m_dpUIWindowArray);
        m_dpUIWindowArray = dpUIWindowArray;
    }

    m_dpUIWindowArray[m_nUIWindowCount] = pUIWindow;
    ++m_nUIWindowCount;

    return pUIWindow;
}

template<typename T>
inline T* Scene::findUIWindow(const wstring& _strName)
{
    for (int i = 0; i < m_nUIWindowCount; ++i)
    {
        if (_strName == m_dpUIWindowArray[i]->getObjName())
        {
            return (T*)m_dpUIWindowArray[i];
        }
    }

    return nullptr;
}

template<typename T>
inline T* Scene::createMap(const wstring& _strName, const Vec& _vPos, const Vec& _vScale)
{
    T* pMap = new T;
    pMap->setOwnerScene(this);
    pMap->setPos(_vPos);
    pMap->setScale(_vScale);
    pMap->setName(_strName);

    if (!pMap->init())
    {
        SAFE_DELETE(pMap);
        return nullptr;
    }

    if (typeid(T).hash_code() == typeid(TileMap).hash_code())
    {
        m_pTileMap = (TileMap*)pMap;
    }

    m_lsMapList.push_back(pMap);
    return pMap;
}
