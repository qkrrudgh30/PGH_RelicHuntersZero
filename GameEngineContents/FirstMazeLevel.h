// FirstMazeLevel.h

#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� :
class FirstMazeLevel : public GameEngineLevel
{
public:
    // constrcuter destructer
    FirstMazeLevel();
    ~FirstMazeLevel();

    // delete Function
    FirstMazeLevel(const FirstMazeLevel& _Other) = delete;
    FirstMazeLevel(FirstMazeLevel&& _Other) noexcept = delete;
    FirstMazeLevel& operator=(const FirstMazeLevel& _Other) = delete;
    FirstMazeLevel& operator=(FirstMazeLevel&& _Other) noexcept = delete;

protected:
    void Loading() override;
    void Update() override;
    void LevelChangeStart() override;

private:

};