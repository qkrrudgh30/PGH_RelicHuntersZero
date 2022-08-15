// Character.h

#pragma once
#include "Object.h"
class Character :
    public Object
{
public:
    Character();
    virtual ~Character();

    Character(const Character& _Other);

    virtual Character* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _dc);
    virtual void start();

    void setCharacterInfo(int _nAttack, int _nArmor, int _nHP, int _nMaxHP, int _nMP, int _nMaxMP,
        int _nLevel, int _nEXP, int _nGold, float _fAttackSpeed, float _fAttackDistance)
    {
        m_CharacterInfo.nAttack = _nAttack;
        m_CharacterInfo.nArmor = _nArmor;
        m_CharacterInfo.nHP = _nHP;
        m_CharacterInfo.nMaxHP = _nMaxHP;
        m_CharacterInfo.nMP = _nMP;
        m_CharacterInfo.nMaxMP = _nMaxMP;
        m_CharacterInfo.nLevel = _nLevel;
        m_CharacterInfo.nEXP = _nEXP;
        m_CharacterInfo.nGold = _nGold;
        m_CharacterInfo.fAttackSpeed = _fAttackSpeed;
        m_CharacterInfo.fAttackDistance = _fAttackDistance;
    }

    virtual void setAttackSpeed(float _fAttackSpeed)
    {
        m_CharacterInfo.fAttackSpeed = _fAttackSpeed;
    }

    virtual float setDamage(float _fDamage)
    {
        _fDamage = Object::setDamage(_fDamage);
        if (m_CharacterInfo.nHP <= 0)
        {
            m_CharacterInfo.nHP = 0;
        }
        else
        {
            m_CharacterInfo.nHP -= (int)_fDamage;
        }

        return _fDamage;        
    }

    virtual float setMana(float _fMana)
    {
        _fMana = Object::setMana(_fMana);
        if (m_CharacterInfo.nMP <= 0)
        {
            m_CharacterInfo.nMP = 0;
        }
        else
        {
            m_CharacterInfo.nMP -= (int)_fMana;
        }

        return _fMana;
    }

protected:
    CharacterInfo m_CharacterInfo;

private:

};