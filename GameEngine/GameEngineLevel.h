// GameEngineLevel.h

#pragma once
#include "GameEngineBase/GameEngineNameObject.h"
#include <list>
#include <map>

// ���� :
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
    // �����Լ�
    virtual void Loading() = 0;
    // �� ������ ���� �����϶� �ؾ������� �����Ѵ�.
    virtual void Update() = 0;
    // Current���� => Next������ �����Ҷ� ���緹���� �����ϴ� �Լ�.
    virtual void LevelChangeStart() {}
    // Current���� => Next������ �����Ҷ� ���������� �����ϴ� �Լ�.
    virtual void LevelChangeEnd() {}

private:

};

