// Player.cpp

#include "Player.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineRenderer.h>

Player::Player()
{
}

Player::~Player()
{
}


void Player::Start()
{
    SetPosition(GameEngineWindow::GetScale().Half());
    SetScale({ 100, 100 });

    GameEngineRenderer* Render = CreateRendererToScale("Idle.bmp", { 30, 30 });
    
}

void Player::Update() 
{
}

void Player::Render()
{
}
