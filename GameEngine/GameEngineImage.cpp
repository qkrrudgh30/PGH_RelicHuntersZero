// GameEngineImage.cpp

#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

#pragma comment(lib, "msimg32.lib")

GameEngineImage::GameEngineImage()
    : ImageDC_(nullptr)
{
}

GameEngineImage::~GameEngineImage()
{
    if (nullptr != BitMap_)
    {
        DeleteObject(BitMap_);
        BitMap_ = nullptr;
    }

    if (nullptr != OldBitMap_)
    {
        DeleteObject(OldBitMap_);
        OldBitMap_ = nullptr;
    }

    if (nullptr != ImageDC_)
    {
        DeleteDC(ImageDC_);
        ImageDC_ = nullptr;
    }
}

bool GameEngineImage::Create(HDC _DC)
{
    ImageDC_ = _DC;
    ImageScaleCheck();
    return true;
}

bool GameEngineImage::Create(float4 _Scale)
{
    if (true == _Scale.IsZero2D())
    {
        MsgBoxAssert("ũ�Ⱑ 0�� �̹����� �����Ϸ��� �߽��ϴ�.");
        return false;
    }

    BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());

    ImageDC_ = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC_)
    {
        MsgBoxAssert("ImageDc ������ �����߽��ϴ�.");
    }

    OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

    ImageScaleCheck();

    return true;
}

bool GameEngineImage::Load(const std::string& _Path)
{
    BitMap_ = static_cast<HBITMAP>(LoadImageA(
        nullptr,
        _Path.c_str(),
        IMAGE_BITMAP,
        0,
        0,
        LR_LOADFROMFILE
    ));

    if (nullptr == BitMap_)
    {
        MsgBoxAssertString(_Path + " �̹��� �ε忡 �����߽��ϴ�. �����е��� ��������� ���� 1. ��δ� ����� �Ƴ���? 2. ������� ����� �ó���");
    }

    // ��������� �ʾƿ�
    ImageDC_ = CreateCompatibleDC(nullptr);

    if (nullptr == ImageDC_)
    {
        MsgBoxAssert("ImageDc ������ �����߽��ϴ�.");
    }

    OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

    ImageScaleCheck();

    return true;
}

void GameEngineImage::ImageScaleCheck()
{
    HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
    GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
    BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
    BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
    BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
    float4 ImagePivot = _Other->GetScale().Half();
    ImagePivot.y = _Other->GetScale().y;

    BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
    float4 ImagePivot = _Other->GetScale().Half();
    ImagePivot.y = _Other->GetScale().y;

    BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}


void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
    BitCopy(_Other, { 0, 0 }, { 0, 0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
    BitBlt(
        ImageDC_, 
        _CopyPos.ix(), 
        _CopyPos.iy(), 
        _OtherPivotScale.ix(), 
        _OtherPivotScale.iy(), 
        _Other->ImageDC_, 
        _OtherPivot.ix(), 
        _OtherPivot.iy(),
        SRCCOPY 
    );
}

void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
    const float4& _CopyScale,
    const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
    TransparentBlt(
        ImageDC_, 
        _CopyPos.ix(), 
        _CopyPos.iy(), 
        _CopyScale.ix(), 
        _CopyScale.iy(), 
        _Other->ImageDC_, 
        _OtherPivot.ix(), 
        _OtherPivot.iy(),
        _OtherScale.ix(),
        _OtherScale.iy(),
        _TransColor 
    );
}