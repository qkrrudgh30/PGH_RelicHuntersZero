// Player.h

#pragma once
#include "Character.h"
#include "../UI/UIWindowHUD.h"
#include "../Scene/Scene.h"
#include "../UI/UIComponent.h"
#include "../UI/UIWidgetText.h"

class Gun;

class Player :
    public Character
{
public:
    Player();
    Player(Vec _vPos);
    virtual ~Player();

    Player(const Player& _Other);

    virtual Player* Clone();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _dc);
    virtual void start();

    virtual void setAttackSpeed(float _fAttackSpeed)
    {
        Character::setAttackSpeed(_fAttackSpeed);

        setAniPlayScale(L"spr_shotgun_heavy_fire", _fAttackSpeed);
    }

    virtual float setDamage(float _fDamage)
    {
        _fDamage = Character::setDamage(_fDamage);

        UIWindowHUD* pPlayerHUD = m_pOwnerScene->findUIWindow<UIWindowHUD>(L"PlayerStateHUD");
        if (nullptr != pPlayerHUD)
        {
            pPlayerHUD->setHPBar(m_CharacterInfo.nHP / (float)m_CharacterInfo.nMaxHP);
        }

        return _fDamage;
    }

    virtual float setMana(float _fMana)
    {
        _fMana = Character::setMana(_fMana);
        UIWindowHUD* pPlayerHUD = m_pOwnerScene->findUIWindow<UIWindowHUD>(L"PlayerStateHUD");
        if (nullptr != pPlayerHUD)
        {
            pPlayerHUD->setMPBar(m_CharacterInfo.nMP / (float)m_CharacterInfo.nMaxMP);
        }
        return _fMana;
    }

    void setMoveUpLock(bool _bLock) { m_bMoveUpLock = _bLock; }
    void setMoveDownLock(bool _bLock) { m_bMoveDownLock = _bLock; }
    void setMoveLeftLock(bool _bLock) { m_bMoveLeftLock = _bLock; }
    void setMoveRightLock(bool _bLock) { m_bMoveRightLock = _bLock; }

    void cameraTargetOn();

    

private:
    bool                    m_bTimeStop;
    SharedPtr<UIComponent>  m_pTextComponent;
    SharedPtr<UIWidgetText> m_pText;
    double                  m_dAccTime;
    double                  m_dHitMotionTime;
    int                     m_nDir;
    bool                    m_bAniChangeRock;
    bool                    m_bDie;
    bool                    m_bMoveUpLock;
    bool                    m_bMoveDownLock;
    bool                    m_bMoveLeftLock;
    bool                    m_bMoveRightLock;
    bool                    m_bCameraTargetOn;

    void collisionBegin(Collider* _pSrc, Collider* _pDes);
    void hitRightEnd();
    void hitLeftEnd();
    void dieEnd();

    // 외부에선 사용할 일이 없는 함수들이기에 private
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void fireBullet();
    void pause();
    void resume();
    void timeStop();
    void timeSlow();

    void showText(const wstring& _strText);

};