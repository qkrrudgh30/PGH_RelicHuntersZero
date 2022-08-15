// Animation.h

#pragma once

#include "AnimationInfo.h"

class Object;
class Scene;

class Animation
{
public:
    Animation();
    virtual ~Animation();

    Animation(const Animation& _Other);

    Animation* Clone();

    void update();

    void addAnimation(const wstring& _strName,
        bool _bLoop = true, float _fPlayTime = 1.f,
        float _fPlayScale = 1.f, bool _bReverse = false, Vec _vOffset = Vec(0.f, 0.f));
    AnimationInfo* findInfo(const wstring& _strName);
    void setLoop(const wstring& _strName, bool _bLoop);
    void setPlayTime(const wstring& _strName, float _fPlayTime);
    void setPlayScale(const wstring& _strName, float _fPlayScale);
    void setReverse(const wstring& _strName, bool _bReverse);

    Object* getAniOwnerObj() { return m_pOwnerObject; }

    Scene* getAniOwnerScene() { return m_pOwnerScene; }

    unordered_map<wstring, AnimationInfo*> getAniMap() { return m_mapAnimation; }

    AnimationInfo* getCurAnimationInfo() { return m_pCurAnimationInfo; }
    void setCurAnimation(const wstring& _strName);
    void changeAnimation(const wstring& _strName);
    bool checkCurAnimation(const wstring& _strName);

    template <typename T>
    void setEndNotify(wstring& _strName, T* _Obj, void (T::* _pFunc)());
    template <typename T>
    void addNotify(wstring& _strName, int _nFrame, T* _Obj, void (T::* _pFunc)());
    


private:
    Object*                                m_pOwnerObject;
    Scene*                                 m_pOwnerScene;
    unordered_map<wstring, AnimationInfo*> m_mapAnimation;
    AnimationInfo*						   m_pCurAnimationInfo;

    friend class Object;
};

template<typename T>
inline void Animation::setEndNotify(wstring& _strName, T* _Obj, void(T::* _pFunc)())
{
    AnimationInfo* pInfo = findInfo(_strName);
    if (!pInfo)
    {
        return;
    }
    pInfo->pEndFunction = bind(_pFunc, _Obj);
}

template<typename T>
inline void Animation::addNotify(wstring& _strName, int _nFrame, T* _Obj, void(T::* _pFunc)())
{
    AnimationInfo* pInfo = findInfo(_strName);
    if (!pInfo)
    {
        return;
    }

    AnimationNotify* pNotify = new AnimationNotify;
    pNotify->nFrame = _nFrame;
    pNotify->pFunction = bind(_pFunc, _Obj);

    pInfo->vecNotify.push_back(pNotify);
}
