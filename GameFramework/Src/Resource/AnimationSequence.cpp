// AnimationSequence.cpp

#include "../GameInfo.h"
#include "AnimationSequence.h"

AnimationSequence::AnimationSequence()
    : m_eTextureType(ETEXTURETYPE::ETEXTURETYPE_ATLAS)
    , m_pTexture(nullptr)
    , m_vecFrameData{}
{
}

AnimationSequence::~AnimationSequence()
{
}

bool AnimationSequence::init(const wstring& _strName, Texture* _pTexture)
{
    setObjName(_strName);
    m_pTexture = _pTexture;
    m_eTextureType = m_pTexture->getTextureType();

    return true;
}

void AnimationSequence::addFrameData(const Vec& _vStartPos, const Vec& _vScale)
{
    AnimationFrameData data;
    data.vStartPos = _vStartPos;
    data.vScale = _vScale;

    m_vecFrameData.push_back(data);
}

void AnimationSequence::addFrameData(float _fPosX, float _fPosY, float _fScaleX, float _fScaleY)
{
    AnimationFrameData data;
    data.vStartPos = Vec(_fPosX, _fPosY);
    data.vScale = Vec(_fScaleX, _fScaleY);

    m_vecFrameData.push_back(data);
}
