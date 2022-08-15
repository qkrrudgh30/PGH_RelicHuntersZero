// Animation.cpp

#include "../GameInfo.h"
#include "Animation.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"
#include "../Timer.h"

Animation::Animation()
    : m_pCurAnimationInfo(nullptr)
    , m_pOwnerObject(nullptr)
    , m_pOwnerScene(nullptr)
{
}

Animation::~Animation()
{
    auto iter = m_mapAnimation.begin();
    auto iterEnd = m_mapAnimation.end();
    for (; iter != iterEnd;)
    {
        SAFE_DELETE(iter->second);
        ++iter;
    }
}

Animation::Animation(const Animation& _Other)
    : m_pCurAnimationInfo(nullptr)
    , m_pOwnerObject(nullptr)
    , m_pOwnerScene(nullptr)
{
    unordered_map<wstring, AnimationInfo*>::const_iterator iter = _Other.m_mapAnimation.begin();
    unordered_map<wstring, AnimationInfo*>::const_iterator iterEnd = _Other.m_mapAnimation.end();

    for (; iter != iterEnd;)
    {
        AnimationInfo* info = new AnimationInfo;

        info->pSequence = iter->second->pSequence;
        info->nFrame = iter->second->nFrame;
        info->fTime = iter->second->fTime;
        info->fFrameTime = iter->second->fFrameTime;
        info->fPlayTime = iter->second->fPlayTime;
        info->fPlayScale = iter->second->fPlayScale;
        info->bLoop = iter->second->bLoop;
        info->bReverse = iter->second->bReverse;

        if (_Other.m_pCurAnimationInfo->pSequence->getObjName() == info->pSequence->getObjName())
        {
            m_pCurAnimationInfo = info;
        }
        m_mapAnimation.insert(std::make_pair(iter->first, info));
        ++iter;
    }
}

Animation* Animation::Clone()
{
    return new Animation(*this);
}

void Animation::update()
{
    m_pCurAnimationInfo->fTime += m_pCurAnimationInfo->fPlayScale * fDT;

    bool bAnimationEnd = false;
    if (m_pCurAnimationInfo->fFrameTime <= m_pCurAnimationInfo->fTime)
    {
        m_pCurAnimationInfo->fTime -= m_pCurAnimationInfo->fFrameTime;
        if (m_pCurAnimationInfo->bReverse)
        {
            --m_pCurAnimationInfo->nFrame;
            if (m_pCurAnimationInfo->nFrame < 0)
            {
                bAnimationEnd = true;
            }
        }
        else
        {
            ++m_pCurAnimationInfo->nFrame;
            if (m_pCurAnimationInfo->nFrame == m_pCurAnimationInfo->pSequence->getFrameCount())
            {
                bAnimationEnd = true;
            }
        }
    }

    size_t uSize = m_pCurAnimationInfo->vecNotify.size();
    for (size_t i = 0; i < uSize; ++i)
    {
        if (!m_pCurAnimationInfo->vecNotify[i]->bCall &&
            m_pCurAnimationInfo->vecNotify[i]->nFrame == m_pCurAnimationInfo->nFrame)
        {
            m_pCurAnimationInfo->vecNotify[i]->bCall = true;
            m_pCurAnimationInfo->vecNotify[i]->pFunction();
        }
    }

    if (bAnimationEnd)
    {
        if (m_pCurAnimationInfo->bLoop)
        {
            if (m_pCurAnimationInfo->bReverse)
            {
                m_pCurAnimationInfo->nFrame = (int)(m_pCurAnimationInfo->pSequence->getFrameCount() - 1);
            }
            else
            {
                m_pCurAnimationInfo->nFrame = 0;
            }
        }
        else
        {
            if (m_pCurAnimationInfo->bReverse)
            {
                m_pCurAnimationInfo->nFrame = 0;
            }
            else
            {
                m_pCurAnimationInfo->nFrame = (int)(m_pCurAnimationInfo->pSequence->getFrameCount() - 1);
            }
        }

        if (m_pCurAnimationInfo->pEndFunction)
        {
            m_pCurAnimationInfo->pEndFunction();
        }

        if (m_pCurAnimationInfo->bLoop)
        {
            size_t uSize = m_pCurAnimationInfo->vecNotify.size();
            for (size_t i = 0; i < uSize; ++i)
            {
                m_pCurAnimationInfo->vecNotify[i]->bCall = false;
            }
        }
    }
}

void Animation::addAnimation(const wstring& _strName, bool _bLoop, float _fPlayTime,
    float _fPlayScale, bool _bReverse, Vec _vOffset)
{
    AnimationSequence* pSequence = m_pOwnerScene->getSceneResource()->findAnimationSequence(_strName);
    if (!pSequence)
    {
        return;
    }

    AnimationInfo* info = new AnimationInfo;
    info->pSequence = pSequence;
    info->bLoop = _bLoop;
    info->fPlayTime = _fPlayTime;
    info->fPlayScale = _fPlayScale;
    info->bReverse = _bReverse;
    info->fFrameTime = _fPlayTime / pSequence->getFrameCount();
    info->vOffset = _vOffset;

    if (m_mapAnimation.empty())
    {
        m_pCurAnimationInfo = info;
    }
    auto begIter = m_mapAnimation.find(_strName);
    auto endIter = m_mapAnimation.end();
    if (endIter == begIter)
    {
        m_mapAnimation.insert(make_pair(_strName, info));
    }
}

AnimationInfo* Animation::findInfo(const wstring& _strName)
{
    auto iter = m_mapAnimation.find(_strName);
    if (m_mapAnimation.end() == iter)
    {
        return nullptr;
    }
    return iter->second;
}

void Animation::setLoop(const wstring& _strName, bool _bLoop)
{
    AnimationInfo* pInfo = findInfo(_strName);
    if (!pInfo)
    {
        return;
    }
    pInfo->bLoop = _bLoop;
}

void Animation::setPlayTime(const wstring& _strName, float _fPlayTime)
{
    AnimationInfo* pInfo = findInfo(_strName);
    if (!pInfo)
    {
        return;
    }
    pInfo->fPlayTime = _fPlayTime;
}

void Animation::setPlayScale(const wstring& _strName, float _fPlayScale)
{
    AnimationInfo* pInfo = findInfo(_strName);
    if (!pInfo)
    {
        return;
    }
    pInfo->fPlayScale = _fPlayScale;
}

void Animation::setReverse(const wstring& _strName, bool _bReverse)
{
    AnimationInfo* pInfo = findInfo(_strName);
    if (!pInfo)
    {
        return;
    }
    pInfo->bReverse = _bReverse;
}

void Animation::setCurAnimation(const wstring& _strName)
{
    m_pCurAnimationInfo = findInfo(_strName);
    m_pCurAnimationInfo->nFrame = 0;
    m_pCurAnimationInfo->fTime = 0.f;

    size_t uSize = m_pCurAnimationInfo->vecNotify.size();
    for (size_t i = 0; i < uSize; ++i)
    {
        m_pCurAnimationInfo->vecNotify[i]->bCall = false;
    }
}

void Animation::changeAnimation(const wstring& _strName)
{
    if (_strName == m_pCurAnimationInfo->pSequence->getObjName())
    {
        return;
    }

    m_pCurAnimationInfo->nFrame = 0;
    m_pCurAnimationInfo->fTime = 0.f;

    size_t uSize = m_pCurAnimationInfo->vecNotify.size();
    for (size_t i = 0; i < uSize; ++i)
    {
        m_pCurAnimationInfo->vecNotify[i]->bCall = false;
    }

    m_pCurAnimationInfo = findInfo(_strName);
    m_pCurAnimationInfo->nFrame = 0;
    m_pCurAnimationInfo->fTime = 0.f;
}

bool Animation::checkCurAnimation(const wstring& _strName)
{
    return _strName == m_pCurAnimationInfo->pSequence->getObjName();
}
