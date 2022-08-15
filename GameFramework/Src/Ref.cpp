// Ref.cpp

#include "GameInfo.h"
#include "Ref.h"

Ref::Ref()
    : m_strName{}
    , m_bAlive(true)
    , m_nRefCount(0)
{
}

Ref::~Ref()
{
}

Ref::Ref(const Ref& _Other)
    : m_bAlive(true)
    , m_nRefCount(0)
{
    m_strName = _Other.m_strName;
}
