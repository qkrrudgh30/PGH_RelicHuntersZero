// GameEngineLevel.h

#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>

// 설명 :
class GameEngine;
class GameEngineActor;
class GameEngineLevel : public GameEngineNameObject
{
    friend GameEngine;
public:
    // constrcuter destructer
    GameEngineLevel();
    virtual ~GameEngineLevel();

    // delete Function
    GameEngineLevel(const GameEngineLevel& _Other) = delete;
    GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
    GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
    GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

protected:
    // 시점함수
    virtual void Loading() = 0;
    // 이 레벨이 현재 레벨일때 해야할일을 실행한다.
    virtual void Update() = 0;
    // Current레벨 => Next레벨로 이전할때 현재레벨이 실행하는 함수.
    virtual void LevelChangeStart() {}
    // Current레벨 => Next레벨로 이전할때 이전레벨이 실행하는 함수.
    virtual void LevelChangeEnd() {}

private:

};

