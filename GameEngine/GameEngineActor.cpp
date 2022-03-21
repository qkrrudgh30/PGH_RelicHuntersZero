// GameEngineActor.cpp

#include "GameEngineActor.h"
#include "GameEngine/GameEngine.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineActor::GameEngineActor()
    : Level_(nullptr)
{
    // delete this;
}

GameEngineActor::~GameEngineActor()
{
}

void GameEngineActor::DebugRectRender()
{
    GameEngineRect DebugRect(Position_, Scale_);

    Rectangle(
        GameEngine::BackBufferDC(),
        DebugRect.CenterLeft(),
        DebugRect.CenterTop(),
        DebugRect.CenterRight(),
        DebugRect.CenterBot()
    );
}