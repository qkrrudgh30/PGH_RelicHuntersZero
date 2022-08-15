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
        // ������ ������ �ִ� ���۷��� ��ü�� ������ �ϴ� ����
        if (m_pPtr)
        {
            m_pPtr->subRefCount();
        }

        // ���� �Ǵ� �� ��ü�� ���� ����
        m_pPtr = _pPtr;

        // ���� �� ���۷��� ��ü�� ���� ��� �ٽ� ����.
        if (m_pPtr)
        {
            m_pPtr->addRefCount();
        }
    }

    void operator = (const SharedPtr<T>& _pPtr)
    {
        // ������ ������ �ִ� ���۷��� ��ü�� ������ �ϴ� ����
        if (m_pPtr)
        {
            m_pPtr->subRefCount();
        }

        // ���� �Ǵ� �� ��ü�� ���� ����
        m_pPtr = _pPtr.m_pPtr;

        // ���� �� ���۷��� ��ü�� ���� ��� �ٽ� ����.
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

    // ��ȯ������(operator conversion)
    operator T* () const
    {
        /*
        SharedPtr<Player> p1;
        Player* p2 = p1; // �̶� ������ ����µ�, �̰� �Ȼ���Բ� �ϴ°� ��ȯ ������.
                         // �ֳ��ϸ� m_pPtr�� ��ȯ�ϸ� Player* �ڷ����̱� ����.
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