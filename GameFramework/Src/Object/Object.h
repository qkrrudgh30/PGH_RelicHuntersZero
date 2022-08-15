// Object.h

#pragma once
#include "../Ref.h"
#include "../Resource/Texture.h"
#include "../Animation/Animation.h"
#include "../Collision/Collider.h"
#include "../UI/UIComponent.h"

class Scene;
class Collider;

class Object :
    public Ref
{
public:
    Object();
    virtual ~Object();

    Object(const Object& _Other);

    virtual Object* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void preRender();
    virtual void render(HDC _dc);
    virtual void start();

    void setTexture(Texture* _pTexture);
    void setTexture(const wstring& _strName);
    void setTexture(const wstring& _strName, const TCHAR* _strFileName,
        const wstring& _strPath = TEXTURE_PATH);
    void setTexture(const wstring& _strName, const vector<wstring>& _vecFileName,
        const wstring& _strPath = TEXTURE_PATH);
    void setTextrueFullPath(const wstring& _strName, const TCHAR* _strFullPath);
    void setTextureColorKey(unsigned char _r,
        unsigned char _g, unsigned char _b, size_t _uIdx = 0);

    void createAnimation();
    void setCurAnimation(const wstring& _strName);
    void addAnimation(const wstring& _strName,
        bool _bLoop = true, float _fPlayTime = 1.f,
        float _fPlayScale = 1.f, bool _bReverse = false, Vec _vOffset = Vec(0.f, 0.f));
    void setAniLoop(const wstring& _strName, bool _bLoop);
    void setAniPlayTime(const wstring& _strName, float _fPlayTime);
    void setAniPlayScale(const wstring& _strName, float _fPlayScale);
    void setAniReverse(const wstring& _strName, bool _bReverse);
    void changeAnimation(const wstring& _strName);
    bool checkCurAnimation(const wstring& _strName);

    template <typename T>
    void setAnimationEndNotify(wstring& _strName, T* _Obj, void (T::* _Func)())
    {
        m_pCurAnimation->setEndNotify<T>(_strName, _Obj, _Func);
    }

    template <typename T>
    void addAnimationNotify(wstring& _strName, int _nFrame, T* _Obj, void (T::* _Func)())
    {
        m_pCurAnimation->addNotify<T>(_strName, _nFrame, _Obj, _Func);
    }

    Collider* findCollider(const wstring& _strName);
    template <typename T>
    T* addCollider(const wstring& _strName)
    {
        T* pCollider = new T;
        pCollider->setObjName(_strName);
        pCollider->setOwnerScene(m_pOwnerScene);
        pCollider->setOwnerObject(this);
        
        if (!pCollider->init())
        {
            SAFE_DELETE(pCollider);
            return nullptr;
        }

        m_lsColliders.push_back(pCollider);

        return pCollider;
    }

    void move(const Vec& _vDir);
    void move(const Vec& _vDir, float _fSpeed);

    Vec getObjPos() { return m_vCurCenterPos; }
    void setObjPos(Vec _vPos) { m_vCurCenterPos = _vPos; }
    float getObjBottom() const
    {
        Vec vScale = m_vScale;
        if (nullptr != m_pCurAnimation)
        {
            AnimationInfo* pAniInfo = m_pCurAnimation->m_pCurAnimationInfo;
            const AnimationFrameData& frameData = pAniInfo->pSequence->getFrameData(pAniInfo->nFrame);
            vScale = frameData.vScale;
        }

        return m_vCurCenterPos.y + (vScale.y / 2.f);
    }

    Vec getObjPrePos() { return m_vPreCenterPos; }
    void getObjPrePos(Vec _vPrePos) { m_vPreCenterPos = _vPrePos; }

    Vec getObjScale() { return m_vScale; }
    void setObjScale(Vec _vScale) { m_vScale = _vScale; }

    float getObjSpeed() { return m_fSpeed; }
    void setObjSpeed(float _fSpeed) { m_fSpeed = _fSpeed; }

    Scene* getOwnerScene() { return m_pOwnerScene; }
    void setOwnerScene(Scene* _pOwnerScene) { m_pOwnerScene = _pOwnerScene; }

    float getObjTimeScale() { return m_fTimeScale; }
    void setObjTimeScale(float _fTimeScale) { m_fTimeScale = _fTimeScale; }

    Vec getObjVelocity() { return m_vVelocity; }
    void setObjVelocity(Vec _vVelocity) { m_vVelocity = _vVelocity; }

    Vec getObjAcceleration() { return m_vAcceleration; }
    void setObjAcceleration(Vec _vAcceleration) { m_vAcceleration = _vAcceleration; }

    Scene* getObjOwnerScene() { return m_pOwnerScene; }
    SharedPtr<Texture> getObjTexture() { return m_pTexture; }
    Animation* getObjCurAnimation() { return m_pCurAnimation; }

    list<SharedPtr<Collider>> getColliders() { return m_lsColliders; }

    Vec getObjOffset() { return m_vOffset; }
    void setObjOffset(Vec _vOffset) { m_vOffset = _vOffset; }

    Vec getObjRenderPos() { return m_vRenderPos; }

    bool isObjCameraCull() { return m_bCameraCull; }

    virtual bool getDamage() { return m_bDamageEnable; }
    virtual float setDamage(float _fDamage) { return m_bDamageEnable ? _fDamage : 0.f; }

    EOBJECT_TYPE getObjType() { return m_eObjectType; }

    virtual float setMana(float _fMana) { return m_bInfiniteMana ? 0.f : _fMana; }

    UIComponent* findUIComponent(const wstring& _strName);
    UIComponent* createUIComponent(const wstring& _strName);

    void setTopWallCheck(bool _bCheck) { m_bTopWallCheck = _bCheck; }
    void setSideWallCheck(bool _bCheck) { m_bSideWallCheck = _bCheck; }
    void setBottomWallCheck(bool _bCheck) { m_bBottomWallCheck = _bCheck; }

    void setImageStart(Vec _ImageStart) { m_vImageStart = _ImageStart; }

protected:
    Vec                          m_vCurCenterPos;       
    Vec                          m_vPreCenterPos;
    Vec                          m_vRenderPos;
    Vec                          m_vScale;
    Vec                          m_vVelocity;
    Vec                          m_vAcceleration;
    Vec                          m_vImageStart;
    Vec                          m_vOffset;
    float                        m_fSpeed;
    float                        m_fTimeScale;
    Scene*                       m_pOwnerScene;
    SharedPtr<Texture>           m_pTexture;
    Animation*                   m_pCurAnimation;
    Animation*                   m_pPreAnimation;
    list<SharedPtr<Collider>>    m_lsColliders;
    bool                         m_bCameraCull;
    bool                         m_bStart;
    bool                         m_bDamageEnable;
    bool                         m_bInfiniteMana;
    EOBJECT_TYPE                 m_eObjectType;
    list<SharedPtr<UIComponent>> m_lsUIComponent;
    bool                         m_bTopWallCheck;
    bool                         m_bSideWallCheck;
    bool                         m_bBottomWallCheck;

    friend class Scene;

};    