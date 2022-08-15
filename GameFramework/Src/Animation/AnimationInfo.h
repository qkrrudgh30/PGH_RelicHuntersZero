// AnimationInfo.h

#pragma once

#include "../GameInfo.h"
#include "../Resource/AnimationSequence.h"

struct AnimationNotify
{
    int              nFrame;
    bool             bCall;
    function<void()> pFunction;

    AnimationNotify()
        : nFrame(0)
        , bCall(false)
        , pFunction(nullptr)
    {
    }
};

struct AnimationInfo
{
    SharedPtr<AnimationSequence> pSequence;
    int		                     nFrame;	
    float	                     fTime;	
    float	                     fFrameTime;	
    float	                     fPlayTime;	
    float	                     fPlayScale;	
    bool	                     bLoop;
    bool	                     bReverse;
    Vec                          vOffset;
    function<void()>             pEndFunction;
    vector<AnimationNotify*>     vecNotify;

    AnimationInfo() 
        : nFrame(0)
        , fTime(0.f)
        , fFrameTime(0.f)
        , fPlayTime(0.f)
        , fPlayScale(1.f)
        , bLoop(false)
        , bReverse(false)
        , vOffset{}
        , pEndFunction(nullptr)
        , vecNotify{}
    {
    }

    ~AnimationInfo()
    {
        size_t uSize = vecNotify.size();
        for (size_t i = 0; i < uSize; ++i)
        {
            SAFE_DELETE(vecNotify[i]);
        }
    }

};


