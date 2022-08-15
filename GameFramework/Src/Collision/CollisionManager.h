// CollisionManager.h

#pragma once

class CollisionManager
{
    SINGLETON(CollisionManager);

public:
    bool init();
    
    CollisionProfile* findProfile(const wstring& _strName);
    bool createProfile(const wstring& _strName, ECOLLISION_CHANNEL _eChannel,
        bool _bEnable, ECOLLISION_STATE _eState = ECOLLISION_STATE::COLLISION);
    bool setCollisionState(const wstring& _strName, ECOLLISION_CHANNEL _eChannel,
        ECOLLISION_STATE _eState);

private:
    unordered_map<wstring, CollisionProfile*> m_mapProfiles;

};

