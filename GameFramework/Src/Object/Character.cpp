// Character.cpp

#include "../GameInfo.h"
#include "Character.h"

Character::Character()
    : m_CharacterInfo{}
{
    m_eObjectType = EOBJECT_TYPE::CHARACTER;
}

Character::~Character()
{
}

Character::Character(const Character& _Other)
    : Object(_Other)
{
    m_CharacterInfo = _Other.m_CharacterInfo;
}

Character* Character::Clone()
{
    return new Character(*this);
}

bool Character::init()
{
    if (!Object::init())
    {
        return false;
    }

    return true;
}

void Character::update()
{
    Object::update();
}

void Character::postUpdate()
{
    Object::postUpdate();
}

void Character::collision()
{
    Object::collision();
}

void Character::render(HDC _dc)
{
    Object::render(_dc);
}

void Character::start()
{
    Object::start();
}

