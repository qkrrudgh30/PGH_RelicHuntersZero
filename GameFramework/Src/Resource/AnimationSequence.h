// AnimationSequence.h

#pragma once

#include "../Ref.h"
#include "Texture.h"

class AnimationSequence :
    public Ref
{
public:
    AnimationSequence();
    virtual ~AnimationSequence();

    bool init(const wstring& _strName, Texture* _pTexture);
    void addFrameData(const Vec& _vStartPos, const Vec& _vScale);
    void addFrameData(float _fPosX, float _fPosY, float _fScaleX, float _fScaleY);

    ETEXTURETYPE getTextureType() { return m_eTextureType; }

    Texture* getTexture() { return m_pTexture; }

    const AnimationFrameData& getFrameData(size_t _uIdx) const { return m_vecFrameData[_uIdx]; }

    size_t getFrameCount() const { return m_vecFrameData.size(); }
    

private:
    ETEXTURETYPE               m_eTextureType;
    SharedPtr<Texture>         m_pTexture;
    vector<AnimationFrameData> m_vecFrameData;

    friend class SceneResource;
};

