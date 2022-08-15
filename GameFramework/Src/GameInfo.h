// GameInfo.h

#pragma once

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib, "fmod64_vc.lib")

#include <Windows.h>
#include <assert.h>
#include <crtdbg.h>
#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>
#include <math.h>

#include "resource.h"
#include "Vec.h"
#include "Flag.h"
#include "SharedPtr.h"
#include "fmod.hpp"

using namespace std;

#ifdef _DEBUG

#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif // _DEBUG

#define KEYCOUNT_MAX 256

#define	ROOT_PATH		L"RootPath"
#define	TEXTURE_PATH	L"TexturePath"
#define	SOUND_PATH		L"SoundPath"
#define FONT_PATH       L"FontPath"
#define MAP_PATH        L"MapPath"
#define MOUSE_PATH      L"MousePath"
#define MENU_PATH       L"MenuPath"

#define SINGLETON(type) \
    public: \
        static type* getInst() \
        { \
          static type mgr; \
          return &mgr; \
        } \
    \
    private: \
        type(); \
        ~type();

#define SAFE_DELETE(p) if (nullptr != p) { delete p; if(nullptr != p) { p = nullptr; } }
#define SAFE_RELEASE(p) if (nullptr != p) { p->subRefCount(); p = nullptr; }
#define SAFE_DELETE_ARRAY(p) if (nullptr != p) { delete[] p; p = nullptr; }

#define DT Timer::getInst()->getDT();
#define fDT Timer::getInst()->getfDT();

#define PI (4.f * atanf(1))

struct RectInfo
{
    float	Left;
    float	Top;
    float	Right;
    float	Bottom;

    RectInfo() :
        Left(0.f),
        Top(0.f),
        Right(0.f),
        Bottom(0.f)
    {
    }
};

struct SphereInfo
{
    Vec vCenter;
    float fRadius;

    SphereInfo()
        : vCenter{}
        , fRadius(0.f)
    {
    }
};

struct AnimationFrameData
{
    Vec vStartPos;
    Vec vScale;
};

struct CharacterInfo
{
    int     nAttack;
    int     nArmor;
    int     nHP;
    int     nMaxHP;
    int     nMP;
    int     nMaxMP;
    int     nLevel;
    int     nEXP;
    int     nGold;
    float   fAttackSpeed;
    float   fAttackDistance;
};

struct CollisionProfile
{
    wstring                  strName;
    ECOLLISION_CHANNEL       eChannel;
    bool                     bCollisionEnable;
    vector<ECOLLISION_STATE> vecState;
};
