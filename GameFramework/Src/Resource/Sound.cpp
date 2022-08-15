// Sound.cpp

#include "../GameInfo.h"
#include "Sound.h"
#include "../PathManager.h"

Sound::Sound()
	: m_strName{}
	, m_pSystem(nullptr)
	, m_pSound(nullptr)
	, m_pChannelGroup(nullptr)
	, m_pChannel(nullptr)
	, m_bPlay(false)
	, m_bLoop(false)
{
}

Sound::~Sound()
{
	if (nullptr != m_pSound)
	{
		m_pSound->release();
	}
}

void Sound::play()
{
	m_pSystem->playSound(m_pSound, m_pChannelGroup, false, &m_pChannel);
	m_bPlay = true;
}

void Sound::stop()
{
	if (nullptr != m_pChannel)
	{
		bool bPlaying = false;
		m_pChannel->isPlaying(&bPlaying);
		if (bPlaying)
		{
			m_pChannel->stop();
			m_pChannel = nullptr;
			m_bPlay = false;
		}
	}
}

void Sound::pause()
{
	if (nullptr == m_pChannel)
	{
		return;
	}

	bool bPlaying = false;
	m_pChannel->isPlaying(&bPlaying);
	if (bPlaying)
	{
		m_pChannel->setPaused(true);
	}
	m_bPlay = false;
}

void Sound::resume()
{
	if (nullptr == m_pChannel)
	{
		return;
	}

	bool bPlaying = false;
	m_pChannel->isPlaying(&bPlaying);
	if (!bPlaying)
	{
		m_pChannel->setPaused(false);
	}
	m_bPlay = true;	
}

bool Sound::loadSound(FMOD::System* _pSystem, FMOD::ChannelGroup* _pChannelGroup, bool _bLoop, const wstring& _strName, const char* _strFileName, const wstring& _strPath)
{
	m_strName = _strName;	
	m_pSystem = _pSystem;
	m_pChannelGroup = _pChannelGroup;
	m_bLoop = _bLoop;

	char strFullPath[MAX_PATH] = {};
	const PathInfo* pPathInfo = PathManager::getInst()->findPath(_strPath);
	if (nullptr != pPathInfo)
	{
		strcpy_s(strFullPath, pPathInfo->m_strMulPath);
	}
	strcat_s(strFullPath, _strFileName);

	FMOD_MODE eMode = FMOD_DEFAULT;
	if (_bLoop)
	{
		eMode = FMOD_LOOP_NORMAL;
	}

	if (FMOD_OK != m_pSystem->createSound(strFullPath, eMode, nullptr, &m_pSound))
	{
		return false;
	}

	return true;
}
