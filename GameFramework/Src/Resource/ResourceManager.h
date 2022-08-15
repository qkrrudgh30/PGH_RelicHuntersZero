// ResourceManager.h

#pragma once

#include "Texture.h"
#include "AnimationSequence.h"
#include "Sound.h"
#include "Font.h"

class ResourceManager
{
    SINGLETON(ResourceManager);

public:
    bool init();

    void releaseTexture(const wstring& _strName);
    Texture* findTexture(const wstring& _strName);
    bool loadTexture(const wstring& _strName, const TCHAR* _strFileName,
        const wstring& _strPath = TEXTURE_PATH);
    bool loadTexture(const wstring& _strName, const vector<wstring>& _vecFileName,
        const wstring& _strPath = TEXTURE_PATH);
    bool loadTextureFullPath(const wstring& _strName, const TCHAR* _strFullPath);

    void setTextureColorKey(const wstring& _strName,
        const char _r, const char _g, const char _b, size_t _uIdx = 0);
    void setTextureColorKey(const wstring& _strName, unsigned int _uColorKey, int _uIdx = 0);

    void releaseAnimationSequence(const wstring& _strName);
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
    bool createChannelGroup(const string& _strName);
    bool setVolume(int _nVolume);
    bool setVolume(const wstring& _strGroupName, int _nVolume);
    bool playSound(const wstring&  _strName);
    bool stopSound(const wstring&  _strName);
    bool pauseSound(const wstring&  _strName);
    bool resumeSound(const wstring&  _strName);
    void releaseSound(const wstring& _strName);

    FMOD::ChannelGroup* findChannelGroup(const wstring& _strName);
    Sound* findSound(const wstring& _strName);

    Font* findFont(const wstring& _strName);
    bool loadFont(const wstring& _strName, const TCHAR* _strFontName,
        int _nWidth = 0, int _nHeight = 0);
    bool loadOtherFont(const TCHAR* _strFontName, const wstring& _strPath = FONT_PATH);


private:
    unordered_map<wstring, SharedPtr<Texture>>              m_mapTexture;
    unordered_map<wstring, SharedPtr<AnimationSequence>>    m_mapAnimationSequence;

    FMOD::System*                                           m_pSystem;
    FMOD::ChannelGroup*                                     m_pMasterGroup;
    unordered_map<wstring, FMOD::ChannelGroup*>             m_mapChannelGroup;
    unordered_map<wstring, SharedPtr<Sound>>                m_mapSound;

    list<wstring>                                           m_lsFontLoadList;
    unordered_map<wstring, SharedPtr<Font>>                 m_mapFont;

};

