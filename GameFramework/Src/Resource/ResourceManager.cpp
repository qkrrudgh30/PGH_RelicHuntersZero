// ResourceManager.cpp

#include "../GameInfo.h"
#include "ResourceManager.h"
#include "../PathManager.h"

ResourceManager::ResourceManager()
    : m_pSystem(nullptr)
    , m_pMasterGroup(nullptr)
{
}

ResourceManager::~ResourceManager()
{
    m_mapTexture.clear();
    m_mapAnimationSequence.clear();
    m_mapSound.clear();
    m_mapFont.clear();

    {
        auto iter = m_mapChannelGroup.begin();
        auto endIter = m_mapChannelGroup.end();
        for (; iter != endIter;)
        {
            iter->second->release();
            ++iter;
        }

        m_mapChannelGroup.clear();
    }
    if (nullptr != m_pSystem)
    {
        m_pSystem->close();
        m_pSystem->release();
    }
    {
        auto iter = m_lsFontLoadList.begin();
        auto endIter = m_lsFontLoadList.end();

        for (; iter != endIter;)
        {
            RemoveFontResource((*iter).c_str());
            ++iter;
        }
    }
}

bool ResourceManager::init()
{
    FMOD_RESULT eResult = FMOD::System_Create(&m_pSystem);
    if (eResult != FMOD_OK)
    {
        return false;
    }

    eResult = m_pSystem->init(128, FMOD_INIT_NORMAL, nullptr);
    if (eResult != FMOD_OK)
    {
        return false;
    }

    eResult = m_pSystem->getMasterChannelGroup(&m_pMasterGroup);
    if (eResult != FMOD_OK)
    {
        return false;
    }

    m_mapChannelGroup.insert(make_pair(L"Master", m_pMasterGroup));

    createChannelGroup("BGM");
    createChannelGroup("Effect");
    createChannelGroup("UI");

    setVolume(L"Master", 10);

    loadOtherFont(TEXT("Maplestory_Bold.ttf"));
    loadOtherFont(TEXT("Maplestory_Light.ttf"));
    loadFont(L"DefaultFont", TEXT("Maplestory_Bold.ttf"));

    return true;
}

void ResourceManager::releaseTexture(const wstring& _strName)
{
    auto iter = m_mapTexture.find(_strName);
    if (1 == iter->second->getRefCount())
    {
        m_mapTexture.erase(iter);
    }
}

Texture* ResourceManager::findTexture(const wstring& _strName)
{
    auto iter = m_mapTexture.find(_strName);
    if (m_mapTexture.end() == iter)
    {
        return nullptr;
    }
    return iter->second;
}

bool ResourceManager::loadTexture(const wstring& _strName, const TCHAR* _strFileName, const wstring& _strPath)
{
    Texture* pTexture = findTexture(_strName);
    if (pTexture)
    {
        return true;
    }

    pTexture = new Texture;
    if (!pTexture->loadTexture(_strName, _strFileName, _strPath))
    {
        SAFE_RELEASE(pTexture);
        return false;
    }

    m_mapTexture.insert(make_pair(_strName, pTexture));
    
    return true;
}

bool ResourceManager::loadTexture(const wstring& _strName, const vector<wstring>& _vecFileName, const wstring& _strPath)
{
    Texture* pTexture = findTexture(_strName);
    if (pTexture)
    {
        return true;
    }

    pTexture = new Texture;
    if (!pTexture->loadTexture(_strName, _vecFileName, _strPath))
    {
        SAFE_RELEASE(pTexture);
        return false;
    }

    m_mapTexture.insert(make_pair(_strName, pTexture));

    return true;
}

bool ResourceManager::loadTextureFullPath(const wstring& _strName, const TCHAR* _strFullPath)
{
    Texture* pTexture = findTexture(_strName);
    if (pTexture)
    {
        return true;
    }

    pTexture = new Texture;
    if (!pTexture->loadTextureFullPath(_strName, _strFullPath))
    {
        SAFE_RELEASE(pTexture);
        return false;
    }

    m_mapTexture.insert(make_pair(_strName, pTexture));

    return true;
}

void ResourceManager::setTextureColorKey(const wstring& _strName, const char _r, const char _g, const char _b, size_t _uIdx)
{
    Texture* pTexture = findTexture(_strName);
    if (!pTexture)
    {
        return;
    }

    pTexture->setTextureColorKey(_r, _g, _b, _uIdx);
}

void ResourceManager::setTextureColorKey(const wstring& _strName, unsigned int _uColorKey, int _uIdx)
{
    Texture* pTexture = findTexture(_strName);
    if (!pTexture)
    {
        return;
    }

    pTexture->setTextureColorKey(_uColorKey, _uIdx);
}

void ResourceManager::releaseAnimationSequence(const wstring& _strName)
{
    auto iter = m_mapAnimationSequence.find(_strName);
    if (1 == iter->second->getRefCount())
    {
        m_mapAnimationSequence.erase(iter);
    }
}

AnimationSequence* ResourceManager::findAnimationSequence(const wstring& _strName)
{
    auto iter = m_mapAnimationSequence.find(_strName);
    if (m_mapAnimationSequence.end() == iter)
    {
        return nullptr;
    }

    return iter->second;
}

bool ResourceManager::createAnimationSequence(const wstring& _strName,
    const wstring& _strTextureName)
{
    AnimationSequence* pSequence = findAnimationSequence(_strName);
    if (pSequence)
    {
        return true;
    }

    pSequence = new AnimationSequence;
    Texture* pTexture = findTexture(_strTextureName);
    if (!pSequence->init(_strName, pTexture))
    {
        SAFE_DELETE(pSequence);
        return false;
    }
    m_mapAnimationSequence.insert(make_pair(_strName, pSequence));

    return true;
}

bool ResourceManager::createAnimationSequence(const wstring& _strName,
    const wstring& _strTextureName, const TCHAR* _strFileName,
    const wstring& _strPath)
{
    AnimationSequence* pSequence = findAnimationSequence(_strName);
    if (pSequence)
    {
        return true;
    }

    if (!loadTexture(_strTextureName, _strFileName, _strPath))
    {
        return false;
    }

    pSequence = new AnimationSequence;
    Texture* pTexture = findTexture(_strTextureName);
    if (!pSequence->init(_strName, pTexture))
    {
        SAFE_DELETE(pSequence);
        return false;
    }

    m_mapAnimationSequence.insert(make_pair(_strName, pSequence));

    return false;
}

bool ResourceManager::createAnimationSequence(const wstring& _strName,
    const wstring& _strTextureName, const vector<wstring>& _vecFileName,
    const wstring& _strPath)
{
    AnimationSequence* pSequence = findAnimationSequence(_strName);
    if (pSequence)
    {
        return true;
    }

    if (!loadTexture(_strTextureName, _vecFileName, _strPath))
    {
        return false;
    }

    pSequence = new AnimationSequence;
    Texture* pTexture = findTexture(_strTextureName);
    if (!pSequence->init(_strName, pTexture))
    {
        SAFE_DELETE(pSequence);
        return false;
    }

    m_mapAnimationSequence.insert(make_pair(_strName, pSequence));

    return true;
}

void ResourceManager::addAnimationFrameData(const wstring& _strName,
    const Vec& _vStartPos, const Vec& _vScale)
{
    AnimationSequence* pSequence = findAnimationSequence(_strName);
    if (pSequence)
    {
        return;
    }
    pSequence->addFrameData(_vStartPos, _vScale);
}

void ResourceManager::addAnimationFrameData(const wstring& _strName,
    float _fPosX, float _fPosY, float _fScaleX, float _fScaleY)
{
    AnimationSequence* pSequence = findAnimationSequence(_strName);
    if (pSequence)
    {
        return;
    }
    pSequence->addFrameData(_fPosX, _fPosY, _fScaleX, _fScaleY);
}

bool ResourceManager::loadSound(const wstring& _strGroupName, bool _bLoop, const wstring& _strName, const char* _strFileName, const wstring& _strPath)
{
    Sound* pSound = findSound(_strName);
    if (nullptr != pSound)
    {
        return true;
    }
    
    FMOD::ChannelGroup* pGroup = findChannelGroup(_strGroupName);
    if (nullptr == pGroup)
    {
        return false;
    }

    pSound = new Sound;
    if (false == pSound->loadSound(m_pSystem, pGroup, _bLoop, _strName, _strFileName, _strPath))
    {
        SAFE_DELETE(pSound);
        return false;
    }

    m_mapSound.insert(make_pair(_strName, pSound));

    return true;
}

bool ResourceManager::createChannelGroup(const string& _strName)
{
    wstring wstrName;
    wstrName.assign(_strName.begin(), _strName.end());
    wprintf(wstrName.c_str());
    FMOD::ChannelGroup* pGroup = findChannelGroup(wstrName);
    if (nullptr != pGroup)
    {
        return true;
    }
    
    
    FMOD_RESULT eResult = m_pSystem->createChannelGroup(_strName.c_str(), &pGroup);
    if (eResult != FMOD_OK)
    {
        return false;
    }

    m_pMasterGroup->addGroup(pGroup, false);
    m_mapChannelGroup.insert(make_pair(wstrName, pGroup));

    return true;
}

bool ResourceManager::setVolume(int _nVolume)
{
    m_pMasterGroup->setVolume(_nVolume / 100.f);

    return true;
}

bool ResourceManager::setVolume(const wstring& _strGroupName, int _nVolume)
{
    FMOD::ChannelGroup* pGroup = findChannelGroup(_strGroupName);
    if (nullptr == pGroup)
    {
        return false;
    }

    m_pMasterGroup->setVolume(_nVolume / 100.f);

    return true;
}

bool ResourceManager::playSound(const wstring& _strName)
{
    Sound* pSound = findSound(_strName);
    if (nullptr == pSound)
    {
        return false;
    }

    pSound->play();

    return true;
}

bool ResourceManager::stopSound(const wstring& _strName)
{
    Sound* pSound = findSound(_strName);
    if (nullptr == pSound)
    {
        return false;
    }

    pSound->stop();

    return true;
}

bool ResourceManager::pauseSound(const wstring& _strName)
{
    Sound* pSound = findSound(_strName);
    if (nullptr == pSound)
    {
        return false;
    }

    pSound->pause();

    return true;
}

bool ResourceManager::resumeSound(const wstring& _strName)
{
    Sound* pSound = findSound(_strName);
    if (nullptr == pSound)
    {
        return false;
    }

    pSound->resume();

    return true;
}

void ResourceManager::releaseSound(const wstring& _strName)
{
    auto iter = m_mapSound.begin();
    if (1 == iter->second->getRefCount())
    {
        m_mapSound.erase(iter);
    }
}

FMOD::ChannelGroup* ResourceManager::findChannelGroup(const wstring& _strName)
{
    auto iter = m_mapChannelGroup.find(_strName);
    if (m_mapChannelGroup.end() == iter)
    {
        return nullptr;
    }
    return iter->second;
}

Sound* ResourceManager::findSound(const wstring& _strName)
{
    auto iter = m_mapSound.find(_strName);
    if (m_mapSound.end() == iter)
    {
        return nullptr;
    }
    return iter->second;
}

Font* ResourceManager::findFont(const wstring& _strName)
{
    auto iter = m_mapFont.find(_strName);
    if (m_mapFont.end() == iter)
    {
        return nullptr;
    }
    return iter->second;
}

bool ResourceManager::loadFont(const wstring& _strName, const TCHAR* _strFontName, int _nWidth, int _nHeight)
{
    Font* pFont = findFont(_strName);
    if (nullptr != pFont)
    {
        return true;
    }
    pFont = new Font;
    if (false == pFont->loadFont(_strName, _strFontName, _nWidth, _nHeight))
    {
        SAFE_DELETE(pFont);
        return false;
    }
    m_mapFont.insert(make_pair(_strName, pFont));
    return true;
}

bool ResourceManager::loadOtherFont(const TCHAR* _strFontName, const wstring& _strPath)
{
    TCHAR strFullPath[MAX_PATH] = {};
    
    const PathInfo* pInfo = PathManager::getInst()->findPath(_strPath);
    if (nullptr != pInfo)
    {
        lstrcpy(strFullPath, pInfo->m_strUniPath);
    }
    lstrcat(strFullPath, _strFontName);

    AddFontResource(strFullPath);

    m_lsFontLoadList.push_back(strFullPath);

    return false;
}
