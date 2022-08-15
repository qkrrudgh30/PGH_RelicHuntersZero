// Timer.h

#pragma once
class Timer
{
    SINGLETON(Timer);

public:
    void init();
    void update();

    double getDT() { return m_dDT * (double)m_fGameTimeScale; }
    float getfDT() { return (float)m_dDT * m_fGameTimeScale; }

    float getGameTimeScale() { return m_fGameTimeScale; }
    void setGameTimeScale(float _fGameTimeScale) { m_fGameTimeScale = _fGameTimeScale; }

private:
    LARGE_INTEGER m_llCurCount;
    LARGE_INTEGER m_llPreCount;
    LARGE_INTEGER m_llFrequency;

    double		  m_dDT;
    double        m_dAccTime;
    size_t        m_uCallCount;
    size_t        m_uFPS;
    float         m_fGameTimeScale;

};