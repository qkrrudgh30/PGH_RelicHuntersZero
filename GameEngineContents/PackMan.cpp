// PackMan.cpp

#include "PackMan.h"
#include "TitleLevel.h"
#include "FirstMazeLevel.h"
#include "EndingLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>

PackMan::PackMan()
{
}

PackMan::~PackMan()
{
}

void PackMan::GameInit()
{
    GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

    GameEngineDirectory ResourcesDir;
    ResourcesDir.MoveParent("WinAPI");
    ResourcesDir.Move("Resources");
    ResourcesDir.Move("Image");

    std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile("Bmp");

    for (size_t i = 0; i < AllImageFileList.size(); i++)
    {
        GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
    }

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