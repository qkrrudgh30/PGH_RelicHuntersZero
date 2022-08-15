// Camera.cpp

#include "../GameInfo.h"
#include "Camera.h"
#include "../GameManager.h"
#include "../Timer.h"
#include "../Resource/Texture.h"
#include "../Resource/ResourceManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/SceneIntro.h"

Camera::Camera()
    : m_vCameraPos{}
    , m_vCameraResolution{}
    , m_vWorldResolution{}
    , m_vTargetOffset{}
    , m_vTargetPivot{}
    , m_vCameraLT{}
    , m_vCameraRB{}
    , m_pTarget(nullptr)
    , m_dMoveTime(0.)
    , m_bSmoothOn(false)
    , m_fSpeed(0.f)
    , m_dDestTime(0.)
    , m_bAccelOn(false)
    , m_eCurEffect(CAM_EFFECT::NONE)
    , m_pVeil(nullptr)
    , m_bEndingOn(false)
    , m_bShakeOn(false)
    , m_bShakeHold(false)
    , m_fShakeCoefficienty(50.f)
    , m_dShakeTime(0.)
    , m_vCamPos{}
{
    POINT ptRes = GameManager::getInst()->getMainRes();
    m_vCameraPos.x = (float)ptRes.x / 2.f;
    m_vCameraPos.y = (float)ptRes.y / 2.f;
    m_vCameraResolution.x = (float)ptRes.x;
    m_vCameraResolution.y = (float)ptRes.y;

    ResourceManager::getInst()->loadTexture(L"veil", L"veil.bmp");
    Texture* temp = ResourceManager::getInst()->findTexture(L"veil");
    temp->setTextureColorKey(255, 0, 255);
    m_pVeil = temp->findTexture(L"veil.bmp");
    m_pVeil->bColorKeyEnable = true;
    m_pVeil->uColorKey = RGB(255, 0, 255);
}

Camera::~Camera()
{
}

bool Camera::init()
{
    return true;
}

void Camera::update()
{
    if (GetAsyncKeyState(VK_UP) & 0x8000)
    {
        m_vCameraPos.y -= 500.f * fDT;
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000)
    {
        m_vCameraPos.y += 500.f * fDT;
    }

    if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    {
        m_vCameraPos.x -= 500.f * fDT;
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    {
        m_vCameraPos.x += 500.f * fDT;
    }

    if (m_bSmoothOn == true && m_bAccelOn == false)
    {
        m_dMoveTime += DT;
        m_vCameraPos += m_vVelocity * fDT;
        if (m_dDestTime <= m_dMoveTime)
        {
            m_vCameraPos = m_vDestPos;
            m_vVelocity = Vec(0.f, 0.f);
            m_bSmoothOn = false;
        }

        /*
        if (m_dDestTime <= m_dMoveTime || 
            m_vDestPos.x <= m_vCameraPos.x ||
            m_vDestPos.y <= m_vCameraPos.y)
        {
            m_vCameraPos = m_vDestPos;
            m_vVelocity = Vec(0.f, 0.f);
            m_bSmoothOn = false;
        }
        
        */
    }

    if (m_bSmoothOn == false && m_bAccelOn == true)
    {
        m_vCameraPos += m_vVelocity * fDT;
        m_vVelocity += m_vAccelation * fDT;

        if (m_vDir.x <= 0.f && m_vDir.y <= 0.f)
        {
            if (m_vDestPos.x >= m_vCameraPos.x || m_vDestPos.y >= m_vCameraPos.y)
            {
                m_vCameraPos = m_vDestPos;
                m_bAccelOn = false;
                m_vVelocity = Vec(0.f, 0.f);
            }
        }
        else if (m_vDir.x > 0.f && m_vDir.y <= 0.f)
        {
            if (m_vDestPos.x >= m_vCameraPos.x ||
                m_vDestPos.y <= m_vCameraPos.y)
            {
                m_vCameraPos = m_vDestPos;
                m_bAccelOn = false;
                m_vVelocity = Vec(0.f, 0.f);
            }
        }
        else if (m_vDir.x <= 0.f && m_vDir.y > 0.f)
        {
            if (m_vDestPos.x <= m_vCameraPos.x ||
                m_vDestPos.y >= m_vCameraPos.y)
            {
                m_vCameraPos = m_vDestPos;
                m_bAccelOn = false;
                m_vVelocity = Vec(0.f, 0.f);
            }
        }
        else if (m_vDir.x > 0.f && m_vDir.y > 0.f)
        {
            if (m_vDestPos.x <= m_vCameraPos.x ||
                m_vDestPos.y <= m_vCameraPos.y)
            {
                m_vCameraPos = m_vDestPos;
                m_bAccelOn = false;
                m_vVelocity = Vec(0.f, 0.f);
            }
        }

    }

    m_vCameraLT = m_vCameraPos - m_vCameraResolution / 2.f;
    m_vCameraRB = m_vCameraPos + m_vCameraResolution / 2.f;

    if (nullptr != m_pTarget)
    {
        if (false == m_pTarget->isAlive())
        {
            m_pTarget = nullptr;
        }
        else
        {
            m_vCameraPos = m_pTarget->getObjPos();
        }
    }
    
    if (m_bShakeOn == true)
    {
        
        
        /*
        if (m_dShakeTime <= 0.25)
        {
            // setCameraPos(Vec(vCamPos.x + m_fShakeCoefficienty, vCamPos.y));
            moveSmoothlyCamera(Vec(m_vCamPos.x + m_fShakeCoefficienty, m_vCamPos.y), 0.25);
            m_bShakeOn = false;
        }
        else if (m_dShakeTime <= 0.5)
        {
            // setCameraPos(Vec(vCamPos.x - m_fShakeCoefficienty, vCamPos.y));
            moveSmoothlyCamera(Vec(m_vCamPos.x - m_fShakeCoefficienty, m_vCamPos.y), 0.25);
        }
        else if (m_dShakeTime <= 0.75)
        {
            // setCameraPos(Vec(vCamPos.x, vCamPos.y - m_fShakeCoefficienty));
            moveSmoothlyCamera(Vec(m_vCamPos.x, m_vCamPos.y - m_fShakeCoefficienty), 0.25);
        }
        else
        {
            // setCameraPos(Vec(vCamPos.x, vCamPos.y + m_fShakeCoefficienty));
            moveSmoothlyCamera(Vec(m_vCamPos.x, m_vCamPos.y + m_fShakeCoefficienty), 0.25);
        }

        setCameraPos(Vec(m_vCamPos.x, m_vCamPos.y));
        */
        float ft = fDT;
        if (m_bShakeHold == true)
        {
            m_vCameraPos.y = m_vCamPos.y * (1 + (sinf(m_dShakeTime * 10.f) * powf(0.5f, m_dShakeTime)) * 0.1);
        }
        else {
            m_dShakeTime -= DT;
            if (0.0001 <= m_dShakeTime)
            {
                m_vCameraPos.y = m_vCamPos.y * (1 + (sinf(m_dShakeTime * 10.f) * powf(0.5f, m_dShakeTime)) * 0.1);
            }
        }


        
    }
    calculateDifference();
}

void Camera::render(HDC _hDC)
{
    if (m_lsCamEffect.empty())
    {
        return;
    }

    CamEffect_t& ef = m_lsCamEffect.front();
    ef.fAccTime += fDT;

    if (CAM_EFFECT::NONE == ef.eCurEffect)
    {
        return;
    }

    float fRatio = 0.f;
    fRatio = ef.fAccTime / ef.fEffectDuration;

    if (fRatio < 0.f)
    {
        fRatio = 0.f;
    }
    if (fRatio > 1.f)
    {
        fRatio = 1.f;
    }

    int iAlpha = 0;
    if (CAM_EFFECT::FADE_OUT == ef.eCurEffect)
    {
        iAlpha = (int)(255.f * fRatio);
    }
    else if (CAM_EFFECT::FADE_IN == ef.eCurEffect)
    {
        iAlpha = (int)(255.f * (1.f - fRatio));
    }

    BLENDFUNCTION bf = {};

    bf.BlendOp = AC_SRC_OVER;
    bf.BlendFlags = 0;
    bf.AlphaFormat = 0;
    bf.SourceConstantAlpha = iAlpha;

    int nWidth = (int)m_pVeil->BmpInfo.bmWidth;
    int nHeight = (int)m_pVeil->BmpInfo.bmHeight;
    bool bRes = false;
    bRes = AlphaBlend(_hDC, 0, 0
        , nWidth, nHeight
        , m_pVeil->hDC
        , 0, 0, nWidth, nHeight
        , bf);

    if (ef.fEffectDuration < ef.fAccTime)
    {
        m_lsCamEffect.pop_front();
        if (m_bEndingOn)
        {
            SceneManager::getInst()->createScene<SceneIntro>();
        }
        // m_eCurEffect = CAM_EFFECT::NONE;
    }
}

void Camera::calculateDifference()
{
    POINT ptRes = GameManager::getInst()->getMainRes();
    Vec vCenter;
    vCenter.x = (int)ptRes.x / 2.f;
    vCenter.y = (int)ptRes.y / 2.f;
    m_vDiff = m_vCameraPos - vCenter;

    if (m_vCameraLT.x < 0.f)
    {
        m_vCameraPos.x = m_vCameraResolution.x / 2.f;
    }

    if (m_vCameraLT.y < 0.f)
    {
        m_vCameraPos.y = m_vCameraResolution.y / 2.f;
    }

    if (m_vWorldResolution.x < m_vCameraRB.x)
    {
        m_vCameraPos.x = m_vWorldResolution.x - m_vCameraResolution.x / 2.f;
    }

    if (m_vWorldResolution.y < m_vCameraRB.y)
    {
        m_vCameraPos.y = m_vWorldResolution.y - m_vCameraResolution.y / 2.f;
    }
}

void Camera::moveSmoothlyCamera(Vec _vDes, double _dTime)
{
    m_dDestTime = _dTime;
    m_vDestPos = _vDes;
    float fDistance = (_vDes - m_vCameraPos).length();
    Vec vDir = (_vDes - m_vCameraPos);
    vDir.normalize();
    m_fSpeed = fDistance / (float)m_dDestTime;
    m_vVelocity = vDir * m_fSpeed;
    m_dMoveTime = 0.;
    m_bSmoothOn = true;
}

void Camera::moveAccelateCamera(Vec _vDes, Vec _vAccel)
{
    m_vVelocity = Vec(0.f, 0.f);
    m_vDestPos.x = _vDes.x <= getCameraResolution().x / 2.f ? getCameraResolution().x / 2.f : _vDes.x;
    m_vDestPos.y = _vDes.y <= getCameraResolution().y / 2.f ? getCameraResolution().y / 2.f : _vDes.y;
    m_vDir = (_vDes - m_vCameraPos);
    m_vDir.normalize();
    
    m_vAccelation.x = m_vDir.x <= 0.f ? _vAccel.x * -1 : _vAccel.x;
    m_vAccelation.y = m_vDir.y <= 0.f ? _vAccel.y * -1 : _vAccel.y;

    m_fSpeed = 500.f;
    
    m_vVelocity = m_vDir * m_fSpeed + _vAccel;

    m_bAccelOn = true;
}

void Camera::changeEndingVeil()
{
    ResourceManager::getInst()->loadTexture(L"veil2", L"veil2.bmp");
    Texture* temp = ResourceManager::getInst()->findTexture(L"veil2");
    temp->setTextureColorKey(255, 0, 255);
    m_pVeil = temp->findTexture(L"veil2.bmp");
    m_pVeil->bColorKeyEnable = true;
    m_pVeil->uColorKey = RGB(255, 0, 255);
}