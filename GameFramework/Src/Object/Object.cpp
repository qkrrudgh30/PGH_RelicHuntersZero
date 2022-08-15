// Object.cpp

#include "../GameInfo.h"
#include "Object.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Timer.h"
#include "../Scene/SceneResource.h"
#include "../Resource/AnimationSequence.h"
#include "../Collision/Collider.h"
#include "../Scene/SceneCollision.h"
#include "../Scene/Camera.h"

Object::Object()
    : m_vCurCenterPos{}
    , m_vPreCenterPos{}
    , m_vRenderPos{}
    , m_vScale{}
    , m_vVelocity{}
    , m_vAcceleration{}
    , m_vImageStart{}
    , m_fSpeed(0.f)
    , m_fTimeScale(1.f)
    , m_pOwnerScene(nullptr)
    , m_pTexture(nullptr)
    , m_pCurAnimation(nullptr)
    , m_bCameraCull(false)
    , m_bStart(false)
    , m_bDamageEnable(true)
    , m_eObjectType(EOBJECT_TYPE::OBJECT)
    , m_bInfiniteMana(false)
    , m_pPreAnimation(nullptr)
    , m_bTopWallCheck(false)
    , m_bSideWallCheck(false)
    , m_bBottomWallCheck(false)
{
}

Object::~Object()
{
    SAFE_DELETE(m_pCurAnimation);

    auto iter = m_lsColliders.begin();
    auto iterEnd = m_lsColliders.end();
    for (; iter != iterEnd;)
    {
        (*iter)->clearCollisionList();
        ++iter;
    }
}

Object::Object(const Object& _Other)
    : Ref(_Other)
{
    // *this = _Other; ´õÀÌ»ó ¾èÀº º¹»ç´Â ¾ÈµÊ.

    m_pOwnerScene = _Other.m_pOwnerScene;

    if (_Other.m_pCurAnimation)
    {
        m_pCurAnimation = _Other.m_pCurAnimation->Clone();
    }
    m_pCurAnimation->m_pOwnerObject = this;
    
    m_lsColliders.clear();
    auto iter = _Other.m_lsColliders.begin();
    auto endIter = _Other.m_lsColliders.end();
    for (; iter != endIter;)
    {
        Collider* pCollider = (*iter)->Clone();
        pCollider->setOwnerObject(this);
        pCollider->setOwnerScene(m_pOwnerScene);
        m_lsColliders.push_back(pCollider);
        ++iter;
    }

    m_lsUIComponent.clear();
    {
        auto iter = _Other.m_lsUIComponent.begin();
        auto endIter = _Other.m_lsUIComponent.end();
        for (; iter != endIter;)
        {
            UIComponent* pComponent = (*iter)->Clone();
            pComponent->setOwnerObject(this);
            pComponent->setOwnerScene(m_pOwnerScene);

            m_lsUIComponent.push_back(pComponent);
            ++iter;
        }
    }

    m_vCurCenterPos = _Other.m_vCurCenterPos;
    m_vPreCenterPos = _Other.m_vPreCenterPos;
    m_vRenderPos = _Other.m_vRenderPos;
    m_vScale = _Other.m_vScale;
    m_vVelocity = _Other.m_vVelocity;
    m_vAcceleration = _Other.m_vAcceleration;
    m_vImageStart = _Other.m_vImageStart;
    m_fSpeed = _Other.m_fSpeed;
    m_fTimeScale = _Other.m_fTimeScale;
    m_pTexture = _Other.m_pTexture;
    m_bCameraCull = _Other.m_bCameraCull;
    m_bStart = false;
    m_bDamageEnable = _Other.m_bDamageEnable;
    m_eObjectType = _Other.m_eObjectType;
    m_bInfiniteMana = _Other.m_bInfiniteMana;
    m_pPreAnimation = _Other.m_pPreAnimation;
}

Object* Object::Clone()
{
    return new Object(*this);
}

bool Object::init()
{
    return true;
}

void Object::update()
{
    if (false == m_bStart)
    {
        start();
    }
    if (m_pCurAnimation)
    {
        m_pCurAnimation->update();
    }

    auto iter = m_lsColliders.begin();
    auto iterEnd = m_lsColliders.end();
    for (; iter != iterEnd;)
    {
        if (!(*iter)->isAlive())
        {
            iter = m_lsColliders.erase(iter);
            iterEnd = m_lsColliders.end();
            continue;
        }
        else if ((*iter)->isEnable())
        {
            (*iter)->update();
        }
        ++iter;
    }

    {
        auto iter = m_lsUIComponent.begin();
        auto endIter = m_lsUIComponent.end();
        for (; iter != endIter;)
        {
            (*iter)->update();
            ++iter;
        }
    }
}

void Object::postUpdate()
{
    if (m_pCurAnimation)
    {
        AnimationInfo* pAniInfo = m_pCurAnimation->m_pCurAnimationInfo;
        const AnimationFrameData& FrameData = pAniInfo->pSequence->getFrameData(pAniInfo->nFrame);
        m_vScale = FrameData.vScale;
    }

    {
        auto iter = m_lsColliders.begin();
        auto iterEnd = m_lsColliders.end();
        for (; iter != iterEnd;)
        {
            if (!(*iter)->isAlive())
            {
                iter = m_lsColliders.erase(iter);
                iterEnd = m_lsColliders.end();
                continue;
            }
            else if ((*iter)->isEnable())
            {
                (*iter)->postUpdate();
            }
            ++iter;
        }
    }
    {
        auto iter = m_lsUIComponent.begin();
        auto endIter = m_lsUIComponent.end();
        for (; iter != endIter;)
        {
            (*iter)->postUpdate();
            ++iter;
        }
    }
}

void Object::collision()
{
    {
        auto iter = m_lsColliders.begin();
        auto iterEnd = m_lsColliders.end();
        for (; iter != iterEnd;)
        {
            m_pOwnerScene->getSceneCollision()->addCollider(*iter);
            ++iter;
        }
    }

    {
        {
            auto iter = m_lsUIComponent.begin();
            auto endIter = m_lsUIComponent.end();
            for (; iter != endIter;)
            {
                (*iter)->collision();
                ++iter;
            }
        }
    }
}

void Object::preRender()
{
    Camera* pCamera = m_pOwnerScene->getCamera();

    m_vRenderPos = pCamera->calculateRenderPos(m_vCurCenterPos);
    Vec vScale = m_vScale;
    if (nullptr != m_pCurAnimation)
    {
        AnimationInfo* pAniInfo = m_pCurAnimation->m_pCurAnimationInfo;
        const AnimationFrameData& frameData = pAniInfo->pSequence->getFrameData(pAniInfo->nFrame);
        vScale = frameData.vScale;
    }

    m_bCameraCull = false;

    Vec vObjLT = m_vCurCenterPos - m_vScale / 2.f;
    Vec vObjRB = m_vCurCenterPos + m_vScale / 2.f;
    Vec vCameraLT = pCamera->getCameraLT();
    Vec vCameraRB = pCamera->getCameraRB();
    
    if (vObjRB.x < vCameraLT.x || vObjRB.y < vCameraLT.y)
    {
        m_bCameraCull = true;
    }

    if (vCameraRB.x < vObjLT.x || vCameraRB.y < vObjLT.y)
    {
        m_bCameraCull = true;
    }
    
}

void Object::render(HDC _dc)
{
    Vec vRenderLT;
    vRenderLT.x = m_vRenderPos.x - m_vScale.x / 2;
    vRenderLT.y = m_vRenderPos.y - m_vScale.y / 2;
    
    if (m_pCurAnimation)
    {     
        AnimationInfo* pAniInfo = m_pCurAnimation->m_pCurAnimationInfo;
        const AnimationFrameData& frameData = pAniInfo->pSequence->getFrameData(pAniInfo->nFrame);
        vRenderLT = vRenderLT + pAniInfo->vOffset;

        if (ETEXTURETYPE::ETEXTURETYPE_ATLAS == pAniInfo->pSequence->getTextureType())
        {
            pAniInfo->pSequence->getTexture()->render(_dc, vRenderLT,
                frameData.vStartPos, frameData.vScale);
        }
        else
        {
            pAniInfo->pSequence->getTexture()->render(_dc, vRenderLT,
                frameData.vStartPos, frameData.vScale, pAniInfo->nFrame);
        }
    }
    else
    {
        if (m_pTexture)
        {
            m_pTexture->render(_dc, vRenderLT, m_vImageStart, m_vScale);
        }
        else
        {
            Rectangle(_dc,
                (int)(vRenderLT.x - m_vScale.x / 2),
                (int)(vRenderLT.y - m_vScale.y / 2),
                (int)(vRenderLT.x + m_vScale.x / 2),
                (int)(vRenderLT.y + m_vScale.y / 2));
        }
    }

    {
        auto iter = m_lsColliders.begin();
        auto iterEnd = m_lsColliders.end();
        for (; iter != iterEnd;)
        {
            if (!(*iter)->isAlive())
            {
                iter = m_lsColliders.erase(iter);
                iterEnd = m_lsColliders.end();
                continue;
            }
            else if ((*iter)->isEnable())
            {
                (*iter)->render(_dc);
            }
            ++iter;
        }
    }

    {
        {
            auto iter = m_lsUIComponent.begin();
            auto endIter = m_lsUIComponent.end();
            for (; iter != endIter;)
            {
                (*iter)->render(_dc);
                ++iter;
            }
        }
    }


    m_vPreCenterPos = m_vCurCenterPos;
    m_vVelocity = Vec(0.f, 0.f);
}

void Object::start()
{
    m_bStart = true;
}

void Object::setTexture(Texture* _pTexture)
{
    m_pTexture = _pTexture;

    if (m_pTexture)
    {
        m_vScale.x = (float)m_pTexture->getTextureWidth();
        m_vScale.y = (float)m_pTexture->getTextureHeight();
    }
}

void Object::setTexture(const wstring& _strName)
{
    m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
    if (m_pTexture)
    {
        m_vScale.x = (float)m_pTexture->getTextureWidth();
        m_vScale.y = (float)m_pTexture->getTextureHeight();
    }
}

void Object::setTexture(const wstring& _strName, const TCHAR* _strFileName, const wstring& _strPath)
{
    m_pOwnerScene->getSceneResource()->loadTexture(_strName, _strFileName, _strPath);
    m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
    if (m_pTexture)
    {
        m_vScale.x = (float)m_pTexture->getTextureWidth();
        m_vScale.y = (float)m_pTexture->getTextureHeight();
    }
}

void Object::setTexture(const wstring& _strName, const vector<wstring>& _vecFileName, const wstring& _strPath)
{
    m_pOwnerScene->getSceneResource()->loadTexture(_strName, _vecFileName, _strPath);
    m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
    if (m_pTexture)
    {
        m_vScale.x = (float)m_pTexture->getTextureWidth();
        m_vScale.y = (float)m_pTexture->getTextureHeight();
    }
}

void Object::setTextrueFullPath(const wstring& _strName, const TCHAR* _strFullPath)
{
    m_pOwnerScene->getSceneResource()->loadTextureFullPath(_strName, _strFullPath);
    m_pTexture = m_pOwnerScene->getSceneResource()->findTexture(_strName);
    if (m_pTexture)
    {
        m_vScale.x = (float)m_pTexture->getTextureWidth();
        m_vScale.y = (float)m_pTexture->getTextureHeight();
    }
}

void Object::setTextureColorKey(unsigned char _r, unsigned char _g, unsigned char _b, size_t _uIdx)
{
    if (m_pTexture)
    {
        m_pTexture->setTextureColorKey(_r, _g, _b, _uIdx);
    }
}

void Object::createAnimation()
{
    if (!m_pCurAnimation)
    {
        m_pCurAnimation = new Animation;
        m_pCurAnimation->m_pOwnerObject = this;
        m_pCurAnimation->m_pOwnerScene = m_pOwnerScene;
    }
}

void Object::setCurAnimation(const wstring& _strName)
{
    if (!m_pCurAnimation)
    {
        return;
    }
    m_pCurAnimation->setCurAnimation(_strName);
}

void Object::addAnimation(const wstring& _strName, bool _bLoop,
    float _fPlayTime, float _fPlayScale, bool _bReverse, Vec _vOffset)
{
    if (!m_pCurAnimation)
    {
        m_pCurAnimation = new Animation;
        m_pCurAnimation->m_pOwnerObject = this;
        m_pCurAnimation->m_pOwnerScene = m_pOwnerScene;
    }
    m_pCurAnimation->addAnimation(_strName, _bLoop, _fPlayTime, _fPlayScale, _bReverse, _vOffset);
}

void Object::setAniLoop(const wstring& _strName, bool _bLoop)
{
    if (!m_pCurAnimation)
    {
        return;
    }
    m_pCurAnimation->setLoop(_strName, _bLoop);
}

void Object::setAniPlayTime(const wstring& _strName, float _fPlayTime)
{
    if (!m_pCurAnimation)
    {
        return;
    }
    m_pCurAnimation->setPlayTime(_strName, _fPlayTime);
}

void Object::setAniPlayScale(const wstring& _strName, float _fPlayScale)
{
    if (!m_pCurAnimation)
    {
        return;
    }
    m_pCurAnimation->setPlayScale(_strName, _fPlayScale);
}

void Object::setAniReverse(const wstring& _strName, bool _bReverse)
{
    if (!m_pCurAnimation)
    {
        return;
    }
    m_pCurAnimation->setReverse(_strName, _bReverse);
}

void Object::changeAnimation(const wstring& _strName)
{
    if (!m_pCurAnimation)
    {
        return;
    }
    if (this == nullptr) return;
    m_pCurAnimation->changeAnimation(_strName);
}

bool Object::checkCurAnimation(const wstring& _strName)
{
    return m_pCurAnimation->checkCurAnimation(_strName);
}

Collider* Object::findCollider(const wstring& _strName)
{
    auto iter = m_lsColliders.begin();
    auto iterEnd = m_lsColliders.end();

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

void Object::move(const Vec& _vDir)
{
    Vec vCurFrameVel = _vDir * m_fSpeed * m_fTimeScale * fDT;
    m_vVelocity += vCurFrameVel;
    m_vCurCenterPos += vCurFrameVel;
}

void Object::move(const Vec& _vDir, float _fSpeed)
{
    Vec vCurFrameVel = _vDir * _fSpeed * m_fTimeScale * fDT;
    m_vVelocity += vCurFrameVel;
    m_vCurCenterPos += vCurFrameVel;
}

UIComponent* Object::findUIComponent(const wstring& _strName)
{
    auto iter = m_lsUIComponent.begin();
    auto endIter = m_lsUIComponent.end();
    for (; iter != endIter;)
    {
        if ((*iter)->getObjName() == _strName)
        {
            return *iter;
        }
        ++iter;
    }

    return nullptr;
}

UIComponent* Object::createUIComponent(const wstring& _strName)
{
    UIComponent* pComponent = findUIComponent(_strName);
    if (nullptr != pComponent)
    {
        return nullptr;
    }

    pComponent = new UIComponent;
    pComponent->setObjName(_strName);
    pComponent->setOwnerObject(this);
    pComponent->setOwnerScene(m_pOwnerScene);

    if (false == pComponent->init())
    {
        SAFE_DELETE(pComponent);
        return nullptr;
    }

    m_lsUIComponent.push_back(pComponent);
    return pComponent;
}
