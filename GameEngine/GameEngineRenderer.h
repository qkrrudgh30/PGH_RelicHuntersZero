// GameEngineRenderer.h

#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
// 설명 :
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
    friend GameEngineActor;

public:
    // constrcuter destructer
    GameEngineRenderer();
    ~GameEngineRenderer();

    // delete Function
    GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
    GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
    GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
    GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

    inline void SetTransColor(unsigned int _Color)
    {
        TransColor_ = _Color;
    }

    inline void SetPivot(const float4& _Pos)
    {
        RenderPivot_ = _Pos;
    }

    inline void SetType(const RenderPivot& _Type)
    {
        PivotType_ = _Type;
    }

    inline void SetScaleMode(const RenderScaleMode& _Mode)
    {
        ScaleMode_ = _Mode;
    }

    void SetImageScale();

    inline void SetScale(const float4& _Scale)
    {
        ScaleMode_ = RenderScaleMode::User;
        RenderScale_ = _Scale;
    }

    void SetImage(const std::string& _Name);

protected:
    void Render();

private:
    GameEngineImage* Image_;
    RenderPivot PivotType_; // 센터 bot
    RenderScaleMode ScaleMode_;

    float4 RenderPivot_;
    // 화면에 그려지는 크기
    float4 RenderScale_;

    // 이미지에서 잘라내는 크기
    float4 RenderImageScale_;
    float4 RenderImagePivot_;

    unsigned int TransColor_;

};

