// FirstMazeLevel.cpp

#include "FirstMazeLevel.h"
#include "Player.h"
#include "BotUI.h"

enum class ORDER
{
    BACKGROUND,
    PLAYER,
    MONSTER,
    UI
};

FirstMazeLevel::FirstMazeLevel()
{
}

FirstMazeLevel::~FirstMazeLevel()
{
}

void FirstMazeLevel::Loading()
{
}

void FirstMazeLevel::Update()
{
}

void FirstMazeLevel::LevelChangeStart()
{
    CreateActor<Player>("Player", (int)ORDER::PLAYER);
    CreateActor<BotUI>("BotUI", (int)ORDER::UI);
}
