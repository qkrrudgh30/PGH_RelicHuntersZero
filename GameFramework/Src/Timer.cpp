// Timer.cpp

#include "GameInfo.h"
#include "Timer.h"
#include "GameManager.h"

Timer::Timer()
    : m_llCurCount{}
    , m_llPreCount{}
    , m_llFrequency{}
    , m_dDT(0.)
    , m_dAccTime(0)
    , m_uCallCount(0)
    , m_uFPS(0)
    , m_fGameTimeScale(1.f)
{
}

Timer::~Timer()
{
}

void Timer::init()
{
    QueryPerformanceCounter(&m_llPreCount);
    QueryPerformanceFrequency(&m_llFrequency);
}

void Timer::update()
{
    QueryPerformanceCounter(&m_llCurCount);

    m_dDT = (double)(m_llCurCount.QuadPart - m_llPreCount.QuadPart) / (double)m_llFrequency.QuadPart;

    m_llPreCount = m_llCurCount;

    ++m_uCallCount;
    
    m_dAccTime += m_dDT;
    if (m_dAccTime > 1.f)
    {
        m_uFPS = m_uCallCount;

        m_dAccTime = 0.;
        m_uCallCount = 0;
#ifdef _DEBUG
        wchar_t buff[101];
        swprintf_s(buff, L"FPS: %zu, DT: %.10lf", m_uFPS, m_dDT);
        SetWindowText(GameManager::getInst()->getMainWnd(), buff);
#endif // _DEBUG

    }
    
}

