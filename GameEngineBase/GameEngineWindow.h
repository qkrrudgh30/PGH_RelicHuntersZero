// GameEngineWindow.h

#pragma once
#include <Windows.h>
#include <string>
#include "GameEngineMath.h"

// 설명 :
class GameEngineWindow
{
private:
    static GameEngineWindow* Inst_;

public:
    inline static GameEngineWindow& GetInst()
    {
        return *Inst_;
    }

    static void Destroy()
    {
        if (nullptr != Inst_)
        {
            delete Inst_;
            Inst_ = nullptr;
        }
    }

public:
    void RegClass(HINSTANCE _hInst);
    void CreateGameWindow(HINSTANCE _hInst, const std::string& _Title);
    void ShowGameWindow();
    void MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)());

    void SetWindowScaleAndPosition(float4 _Pos, float4 _Scale);

    void Off();

    static inline HDC GetHDC()
    {
        return Inst_->HDC_;
    }

    static inline float4 GetScale()
    {
        return Inst_->Scale_;
    }

protected:

private:
    std::string Title_;
    bool WindowOn_;
    HINSTANCE hInst_;
    HWND hWnd_;
/*
    HDC란, RAM에 올라와있는 깊이 RGB인 2차원 배열에 접근해서 데이터를 수정할 수 있는 핸들.
*/
    HDC HDC_;
    float4 Scale_;

    // constrcuter destructer
    GameEngineWindow();
    ~GameEngineWindow();

    // delete Function
    GameEngineWindow(const GameEngineWindow& _Other) = delete;
    GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
    GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
    GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;

};

