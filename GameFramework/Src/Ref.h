// Ref.h

#pragma once
class Ref
{
public:
    Ref();
    virtual ~Ref();

    Ref(const Ref& _Other);

    const wstring& getObjName() { return m_strName; }
    void setObjName(const wstring& _strName) { m_strName = _strName; }

    bool isAlive() const { return m_bAlive; }
    void destroy() { m_bAlive = false; }

    int getRefCount() { return m_nRefCount; }
    int addRefCount() { ++m_nRefCount; return m_nRefCount; }
    int subRefCount()
    {
        --m_nRefCount;

        if (0 >= m_nRefCount)
        {
            delete this;
            return 0;
        }
        return m_nRefCount;
    }

private:
    wstring m_strName;
    bool    m_bAlive;
    int     m_nRefCount;

};
