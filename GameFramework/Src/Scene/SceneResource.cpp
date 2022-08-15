// SceneResource.cpp

#include "../GameInfo.h"
#include "SceneResource.h"
#include "../Resource/ResourceManager.h"
#include "../Animation/AnimationInfo.h"

SceneResource::SceneResource()
{
}

SceneResource::~SceneResource()
{
    {
        auto iter = m_mapAnimationSequence.begin();
        auto iterEnd = m_mapAnimationSequence.end();

        for (; iter != iterEnd;)
        {
            wstring strName = iter->first;
            iter = m_mapAnimationSequence.erase(iter);
            ResourceManager::getInst()->releaseAnimationSequence(strName);
        }
    }

    {
        auto	iter = m_mapTextures.begin();
        auto	iterEnd = m_mapTextures.end();

        for (; iter != iterEnd;)
        {
            wstring	strName = iter->first;

            // erase를 하면 SharedPtr이므로 자동으로 객체가 제거되며 카운트가
            // 1 감소한다. erase는 지운 다음 iterator를 반환하므로 ++을 안해줘도 됨.
            iter = m_mapTextures.erase(iter);

            ResourceManager::getInst()->releaseTexture(strName);
        }
    }

    {
        auto iter = m_mapSound.begin();
        auto endIter = m_mapSound.end();
        for (; iter != endIter;)
        {
            wstring strName = iter->first;
            iter = m_mapSound.erase(iter);
            ResourceManager::getInst()->releaseSound(strName);
        }
    }
}

Texture* SceneResource::findTexture(const wstring& _strName)
{
    auto	iter = m_mapTextures.find(_strName);

    if (m_mapTextures.end() == iter)
    {
        return nullptr;
    }
        
    return iter->second;
}

bool SceneResource::loadTexture(Texture* _pTexture)
{
    return false;
}

bool SceneResource::loadTexture(const wstring& _strName, const TCHAR* _strFileName, const wstring& _strPath)
{
    if (findTexture(_strName))
    {
        return true;
    }

    if (!ResourceManager::getInst()->loadTexture(_strName, _strFileName, _strPath))
    {
        return false;
    }

    Texture* pTexture = ResourceManager::getInst()->findTexture(_strName);
    m_mapTextures.insert(make_pair(_strName, pTexture));

    return true;
}

bool SceneResource::loadTexture(const wstring& _strName, const vector<wstring>& _vecFileName, const wstring& _strPath)
{
    if (findTexture(_strName))
    {
        return true;
    }

    if (!ResourceManager::getInst()->loadTexture(_strName, _vecFileName, _strPath))
    {
        return false;
    }

    Texture* pTexture = ResourceManager::getInst()->findTexture(_strName);

    m_mapTextures.insert(make_pair(_strName, pTexture));
    
    return true;
}

bool SceneResource::loadTextureFullPath(const wstring& _strName, const TCHAR* _strFullPath)
{
    if (findTexture(_strName))
    {
        return true;
    }

    if (!ResourceManager::getInst()->loadTextureFullPath(_strName, _strFullPath))
    {
        return false;
    }

    Texture* pTexture = ResourceManager::getInst()->findTexture(_strName);
    m_mapTextures.insert(make_pair(_strName, pTexture));

    return true;
}

void SceneResource::setTextureColorKey(const wstring& _strName, const unsigned char _r, const unsigned char _g, const unsigned char _b, size_t _uIdx)
{
    ResourceManager::getInst()->setTextureColorKey(_strName, _r, _g, _b, _uIdx);
}

void SceneResource::setTextureColorKey(const wstring& _strName, unsigned int _uColorKey, int _uIdx)
{
    ResourceManager::getInst()->setTextureColorKey(_strName, _uColorKey, _uIdx);
}

AnimationSequence* SceneResource::findAnimationSequence(const wstring& _strName)
{
    auto iter = m_mapAnimationSequence.find(_strName);
    if (m_mapAnimationSequence.end() == iter)
    {
        return nullptr;
    }
    return iter->second;
}

bool SceneResource::createAnimationSequence(const wstring& _strName,
    const wstring& _strTextureName)
{
    if (findAnimationSequence(_strName))
    {
        return true;
    }

    if (!ResourceManager::getInst()->createAnimationSequence(_strName, _strTextureName))
    {
        return false;
    }

    AnimationSequence* pSequence = ResourceManager::getInst()->findAnimationSequence(_strName);
    m_mapAnimationSequence.insert(make_pair(_strName, pSequence));

    return true;
}

bool SceneResource::createAnimationSequence(const wstring& _strName,
    const wstring& _strTextureName, const TCHAR* _strFileName,
    const wstring& _strPath)
{
    if (findAnimationSequence(_strName))
    {
        return true;
    }

    if (!loadTexture(_strTextureName, _strFileName, _strPath))
    {
        return false;
    }

    if (!ResourceManager::getInst()->createAnimationSequence(_strName, _strTextureName))
    {
        return false;
    }

    AnimationSequence* pSequence = ResourceManager::getInst()->findAnimationSequence(_strName);
    m_mapAnimationSequence.insert(make_pair(_strName, pSequence));

    return true;
}

bool SceneResource::createAnimationSequence(const wstring& _strName,
    const wstring& _strTextureName, const vector<wstring>& _vecFileName,
    const wstring& _strPath)
{
    if (findAnimationSequence(_strName))
    {
        return true;
    }

    if (!loadTexture(_strTextureName, _vecFileName, _strPath))
    {
        return false;
    }

    if (!ResourceManager::getInst()->createAnimationSequence(_strName, _strTextureName))
    {
        return false;
    }

    AnimationSequence* pSequence = ResourceManager::getInst()->findAnimationSequence(_strName);
    
    size_t uSize = pSequence->m_pTexture->getTextureVecSize();
    pSequence->m_vecFrameData.resize(uSize);

    for (size_t i = 0; i < uSize; ++i)
    {
        pSequence->m_vecFrameData[i].vStartPos = Vec(0.f, 0.f);
        pSequence->m_vecFrameData[i].vScale = Vec((float)pSequence->m_pTexture->getTextureWidth(),
            (float)pSequence->m_pTexture->getTextureHeight());
    }

    m_mapAnimationSequence.insert(make_pair(_strName, pSequence));

    return true;
}

void SceneResource::addAnimationFrameData(const wstring& _strName,
    const Vec& _vStartPos, const Vec& _vScale)
{
    AnimationSequence* pSequence = findAnimationSequence(_strName);
    if (!pSequence)
    {
        return;
    }
    pSequence->addFrameData(_vStartPos, _vScale);
}

void SceneResource::addAnimationFrameData(const wstring& _strName,
    float _fPosX, float _fPosY, float _fScaleX, float _fScaleY)
{
    AnimationSequence* pSequence = findAnimationSequence(_strName);
    if (!pSequence)
    {
        return;
    }
    pSequence->addFrameData(_fPosX, _fPosY, _fScaleX, _fScaleY);
}

bool SceneResource::loadSound(const wstring& _strGroupName, bool _bLoop, const wstring& _strName, const char* _strFileName, const wstring& _strPath)
{
    Sound* pSound = findSound(_strName);
    if (nullptr != pSound)
    {
        return true;
    }

    if (false == ResourceManager::getInst()->loadSound(_strGroupName,
        _bLoop, _strName, _strFileName, _strPath))
    {
        return false;
    }

    pSound = ResourceManager::getInst()->findSound(_strName);
   
    m_mapSound.insert(make_pair(_strName, pSound));

    return true;
}

bool SceneResource::setVolume(int _nVolume)
{
    return ResourceManager::getInst()->setVolume(_nVolume);
}

bool SceneResource::setVolume(const wstring& _strGroupName, int _nVolume)
{
    return ResourceManager::getInst()->setVolume(_strGroupName, _nVolume);
}

bool SceneResource::playSound(const wstring& _strName)
{
    return ResourceManager::getInst()->playSound(_strName);
}

bool SceneResource::stopSound(const wstring& _strName)
{
    return ResourceManager::getInst()->stopSound(_strName);
}

bool SceneResource::pauseSound(const wstring& _strName)
{
    return ResourceManager::getInst()->pauseSound(_strName);
}

bool SceneResource::resumeSound(const wstring& _strName)
{
    return ResourceManager::getInst()->resumeSound(_strName);
}

Sound* SceneResource::findSound(const wstring& _strName)
{
    auto iter = m_mapSound.find(_strName);
    if (m_mapSound.end() == iter)
    {
        return nullptr;
    }
    return iter->second;
}
