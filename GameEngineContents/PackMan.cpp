// PackMan.cpp

#include "PackMan.h"
#include "TitleLevel.h"
#include "FirstMazeLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

PackMan::PackMan()
{
}

PackMan::~PackMan()
{
}

void PackMan::GameInit()
{
    GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

    CreateLevel<TitleLevel>("Title");
    CreateLevel<FirstMazeLevel>("FirstMaze");
    CreateLevel<EndingLevel>("Ending");

    ChangeLevel("FirstMaze");
}

void PackMan::GameLoop()
{

}
void PackMan::GameEnd()
{

}