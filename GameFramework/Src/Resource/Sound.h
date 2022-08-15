// Sound.h

#pragma once
#include "../Ref.h"
class Sound :
    public Ref
{
public:
    Sound();
    virtual ~Sound();

    void play();
    void stop();
    void pause();
    void resume();

    bool loadSound(FMOD::System* _pSystem, FMOD::ChannelGroup* _pChannelGroup,
        bool _bLoop, const wstring& _strName, const char* _strFileName,
        const wstring& _strPath = SOUND_PATH);

    bool isPlay() const { return m_bPlay; }

    bool isLoop() const { return m_bLoop; }

private:
    wstring             m_strName;
    FMOD::System*       m_pSystem;
    FMOD::Sound*        m_pSound;
    FMOD::ChannelGroup* m_pChannelGroup;
    FMOD::Channel*      m_pChannel;
    bool                m_bPlay;
    bool                m_bLoop;

    friend class ResourceManager;


};

