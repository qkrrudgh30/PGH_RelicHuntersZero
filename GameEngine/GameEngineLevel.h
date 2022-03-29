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

    template<typename ActorType>
    ActorType* CreateActor(int _Order = 0, const std::string& _Name = "")
    {
        ActorType* NewActor = new ActorType();
        GameEngineActor* StartActor = NewActor;
        NewActor->SetName(_Name);
        NewActor->SetLevel(this);
        StartActor->Start();
        std::list<GameEngineActor*>& Group = AllActor_[_Order];
        Group.push_back(NewActor);
        /*
            map���� [] �����ڴ� find�� insert�� ���ÿ� ��.
            ��, �Ʒ��� ���� �����ϴ� ��.
            std::map<int, std::list<GameEngineActor*>>::iterator FindGroup = AllActor_.find(_Order);

            if (FindGroup == AllActor_.end())
            {
                AllActor_.insert(std::map<int, std::list<GameEngineActor*>>::value_type(_Order, std::list<GameEngineActor*>()));
                // == AllActor_.insert(std::make_pair(_Order, std::list<GameEngineActor*>())); ���� �ڵ�����, �� �ڵ尡 �� �� ����.
            }
        */

        return NewActor;
    }

protected:
    virtual void Loading() = 0;
    virtual void Update() = 0;
    virtual void LevelChangeStart() {}
    virtual void LevelChangeEnd() {}

    


private:
    std::map<int, std::list<GameEngineActor*>> AllActor_;

    void ActorUpdate();
    void ActorRender();
    void ActorRelease();

};

