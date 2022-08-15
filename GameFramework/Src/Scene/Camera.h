// Camera.h

#pragma once

#include "../Object/Object.h"

class Texture;

struct CamEffect_t
{
    CAM_EFFECT eCurEffect;
    float      fEffectDuration;
    float      fAccTime;
};

class Camera
{
public:
    Camera();
    virtual ~Camera();

    virtual bool init();
    virtual void update();
    virtual void render(HDC _hDC);

    void calculateDifference();
    Vec calculateRenderPos(Vec _vObjPos) { return _vObjPos - m_vDiff; }
    Vec calculateAbsolutePos(Vec _vObjPos) { return _vObjPos + m_vDiff; }

    Vec getCameraPos() { return m_vCameraPos; }
    void setCameraPos(Vec _vCameraPos) { m_vCameraPos = _vCameraPos; }
    void moveCamera(const Vec _vDistance) { m_vCameraPos += _vDistance; }

    Vec getCameraResolution() { return m_vCameraResolution; }
    void setCameraResolution(Vec _vCameraResolution) { m_vCameraResolution = _vCameraResolution; }

    Vec getWorldResolution() { return m_vWorldResolution; }
    void setWorldResolution(Vec _vWorldResolution) { m_vWorldResolution = _vWorldResolution; }

    Vec getTargetOffset() { return m_vTargetOffset; }
    void setTargetOffset(Vec _vTargetOffset) { m_vTargetOffset = _vTargetOffset; }

    Vec getTargetPivot() { return m_vTargetPivot; }
    void setTargetPivot(Vec _vTargetPivot) { m_vTargetPivot = _vTargetPivot; }

    SharedPtr<Object> getTargetObject() { return m_pTarget; }
    void setTargetObject(SharedPtr<Object> _pTarget) { m_pTarget = _pTarget; }

    Vec getCameraLT() { return m_vCameraLT; }
    void setCameraLT(Vec _vCameraLT) { m_vCameraLT = _vCameraLT; }

    Vec getCameraRB() { return m_vCameraRB; }
    void setCameraRB(Vec _vCameraRB) { m_vCameraRB = _vCameraRB; }

    void moveSmoothlyCamera(Vec _vDes, double _dTime);

    void moveAccelateCamera(Vec _vDes, Vec _vAccel);

    void shakeCamera() { m_bShakeOn = !m_bShakeOn; m_bShakeHold = true; m_dShakeTime = 1.; m_vCamPos = getCameraPos(); }
    void shakeOffCamera() { m_bShakeHold = false; }

    void fadeIn(float _fDuration)
    {
        CamEffect_t ef = {};
        ef.eCurEffect = CAM_EFFECT::FADE_IN;
        ef.fEffectDuration = _fDuration;
        ef.fAccTime = 0.f;

        m_lsCamEffect.push_back(ef);

        if (0.f == ef.fEffectDuration)
        {
            assert(nullptr);
        }
    }
    void fadeOut(float _fDuration)
    {
        CamEffect_t ef = {};
        ef.eCurEffect = CAM_EFFECT::FADE_OUT;
        ef.fEffectDuration = _fDuration;
        ef.fAccTime = 0.f;

        m_lsCamEffect.push_back(ef);

        if (0.f == ef.fEffectDuration)
        {
            assert(nullptr);
        }
    }

    void changeEndingVeil();

    void setEndingOn() { m_bEndingOn = true; }

private:
    Vec                 m_vCameraPos;
    Vec                 m_vCameraResolution;
    Vec                 m_vWorldResolution;
    Vec                 m_vTargetOffset;
    Vec                 m_vTargetPivot;
    Vec                 m_vDiff;
    Vec                 m_vCameraLT;
    Vec                 m_vCameraRB;
    Vec                 m_vDestPos;
    Vec                 m_vVelocity;
    Vec                 m_vAccelation;
    Vec                 m_vDir;
    SharedPtr<Object>   m_pTarget;
    double              m_dMoveTime;
    double              m_dDestTime;
    float               m_fSpeed;
    bool                m_bSmoothOn;
    bool                m_bAccelOn;
    CAM_EFFECT          m_eCurEffect;
    TextureInfo*        m_pVeil;
    float               m_fEffectDuration;
    float               m_fAccTime;
    list<CamEffect_t>   m_lsCamEffect;
    bool                m_bEndingOn;
    bool                m_bShakeOn;
    bool                m_bShakeHold;
    float               m_fShakeCoefficienty;
    double              m_dShakeTime;
    Vec                 m_vCamPos;

};