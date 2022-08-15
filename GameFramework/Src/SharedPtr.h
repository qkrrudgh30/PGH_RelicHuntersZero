// SharedPtr.h

#pragma once

template <typename T>
class SharedPtr
{
public:
    SharedPtr()
        : m_pPtr(nullptr)
    {

    }

    SharedPtr(T* _pPtr)
    {
        m_pPtr = _pPtr;
        if (m_pPtr)
        {
            m_pPtr->addRefCount();
        }
    }

    SharedPtr(const SharedPtr<T>& _pPtr)
    {
        m_pPtr = _pPtr.m_pPtr;
        if (m_pPtr)
        {
            m_pPtr->addRefCount();
        }
    }

    ~SharedPtr()
    {
        if (m_pPtr)
        {
            m_pPtr->subRefCount();
        }
    }

    void operator = (T* _pPtr)
    {
        // 기존에 가지고 있는 레퍼런스 개체가 있으면 일단 감소
        if (m_pPtr)
        {
            m_pPtr->subRefCount();
        }

        // 대입 되는 새 개체를 연결 해줌
        m_pPtr = _pPtr;

        // 만약 새 레퍼런스 개체가 있을 경우 다시 증가.
        if (m_pPtr)
        {
            m_pPtr->addRefCount();
        }
    }

    void operator = (const SharedPtr<T>& _pPtr)
    {
        // 기존에 가지고 있는 레퍼런스 개체가 있으면 일단 감소
        if (m_pPtr)
        {
            m_pPtr->subRefCount();
        }

        // 대입 되는 새 개체를 연결 해줌
        m_pPtr = _pPtr.m_pPtr;

        // 만약 새 레퍼런스 개체가 있을 경우 다시 증가.
        if (m_pPtr)
        {
            m_pPtr->addRefCount();
        }
    }

    bool operator == (T* _pPtr) const
    {
        return m_pPtr == _pPtr;
    }

    bool operator == (const SharedPtr<T>& _pPtr) const
    {
        return m_pPtr == _pPtr.m_pPtr;
    }

    bool operator != (T* _pPtr) const
    {
        return m_pPtr != _pPtr;
    }

    bool operator != (const SharedPtr<T>& _pPtr) const
    {
        return m_pPtr != _pPtr.m_pPtr;
    }

    // 변환연산자(operator conversion)
    operator T* () const
    {
        /*
        SharedPtr<Player> p1;
        Player* p2 = p1; // 이때 문제가 생기는데, 이걸 안생기게끔 하는게 변환 연산자.
                         // 왜냐하면 m_pPtr을 반환하면 Player* 자료형이기 때문.
        */
        return m_pPtr;
    }

    T* operator -> () const
    {
        return m_pPtr;
    }

private:
    T* m_pPtr;

};