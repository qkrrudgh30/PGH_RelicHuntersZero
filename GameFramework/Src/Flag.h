// Flag.h

#pragma once

enum EKeyState
{
    KeyState_None,
    KeyState_Down,
    KeyState_Hold,
    KeyState_Away,
    KeyState_Max
};

enum class ETEXTURETYPE
{
    ETEXTURETYPE_ATLAS,
    ETEXTURETYPE_FRAME,
    ETEXTURETYPE_END
};

enum class ECOLLIDER_TYPE
{
    ECOLLISION_TYPE_BOX,
    ECOLLISION_TYPE_SPHERE,
    ECOLLISION_TYPE_POINT,
    ECOLLISION_TYPE_END

};

enum ECOLLISION_CHANNEL
{
    CHANNEL_OBJECT,
    CHANNEL_PLAYER,
    CHANNEL_MONSTER,
    CHANNEL_PLAYER_BULLET,
    CHANNEL_MONSTER_BULLET,
    CHANNEL_WALL,
    CHANNEL_END
};

enum class ECOLLISION_STATE
{
    NONCOLLISION,
    COLLISION,
    END
};

enum class EBUTTON_STATE
{
    ENABLE,
    MOUSE_ON,
    MOUSE_CLICK,
    DISABLE,
    END
};

enum class EOBJECT_TYPE
{
    OBJECT,
    CHARACTER,
    PLAYER,
    MONSTER,
    BULLET,
    EFFECT,
    GUN,
    END
};

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    HIT,
    DIE,
    RESPAWN,
    SKILL1,
    END
};

enum class ETILE_OPTION
{
    NORMAL,
    WALL,
    SLOW,
    END
};

enum class ETILE_EDITMODE
{
    OPTION,
    IMAGE,
    OBJECT,
    END
};

enum class CAM_EFFECT
{
    NONE,
    FADE_IN,
    FADE_OUT,
    END
};

enum class EMONSTER_STATE
{
    IDLE,
    TRACE,
    ATTACK,
    SKILL,
    DEATH
};