// Bullet.cpp

#include "Bullet.h"
#include <GameEngineBase/GameEngineTime.h>

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::Start()
{
    CreateRenderer("bullet.bmp");

    Death(2.0f);
}

void Bullet::Update()
{
    SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.0f);
}
