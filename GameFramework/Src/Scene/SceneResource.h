// SceneResource.h

#pragma once

#include "../Resource/Texture.h"
#include "../Resource/AnimationSequence.h"
#include "../Resource/Sound.h"

class SceneResource
{
public:
    SceneResource();
    virtual ~SceneResource();

    Texture* findTexture(const wstring& _strName);
    bool loadTexture(Texture* _pTexture);
    bool loadTexture(const wstring& _strName, const TCHAR* _strFileName,
        const wstring& _strPath = TEXTURE_PATH);
    bool loadTexture(const wstring& _strName, const vector<wstring>& _vecFileName,
        const wstring& _strPath = TEXTURE_PATH);
    bool loadTextureFullPath(const wstring& _strName, const TCHAR* _strFullPath);

    void setTextureColorKey(const wstring& _strName,
        const unsigned char _r, const unsigned char _g, const unsigned char _b, size_t _uIdx = 0);
    void setTextureColorKey(const wstring& _strName, unsigned int _uColorKey, int _uIdx = 0);

    AnimationSequence* findAnimationSequence(const wstring& _strName);
    bool createAnimationSequence(const wstring& _strName, const wstring& _strTextureName);
    bool createAnimationSequence(const wstring& _strName, const wstring& _strTextureName,
        const TCHAR* _strFileName, const wstring& _strPath = TEXTURE_PATH);
    bool createAnimationSequence(const wstring& _strName, const wstring& _strTextureName,
        const vector<wstring>& _vecFileName,
        const wstring& _strPath = TEXTURE_PATH);
    void addAnimationFrameData(const wstring& _strName, const Vec& _vStartPos, const Vec& _vScale);
    void addAnimationFrameData(const wstring& _strName, float _fPosX, float _fPosY, float _fScaleX, float _fScaleY);

    bool loadSound(const wstring& _strGroupName, bool _bLoop,
        const wstring& _strName, const char* _strFileName,
        const wstring& _strPath = SOUND_PATH);
    bool setVolume(int _nVolume);
    bool setVolume(const wstring& _strGroupName, int _nVolume);
    bool playSound(const wstring& _strName);
    bool stopSound(const wstring& _strName);
    bool pauseSound(const wstring& _strName);
    bool resumeSound(const wstring& _strName);

    Sound* findSound(const wstring& _strName);

private:
    unordered_map<wstring, SharedPtr<Texture>>              m_mapTextures;
    unordered_map<wstring, SharedPtr<AnimationSequence>>    m_mapAnimationSequence;
    unordered_map<wstring, SharedPtr<Sound>>                m_mapSound;


    friend class Scene;
};

