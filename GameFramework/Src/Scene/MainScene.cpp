// MainScene.cpp

#include "../GameInfo.h"
#include "MainScene.h"
#include "../Object/Player.h"
#include "../Object/Bullet.h"
#include "../Object/Monster.h"
#include "../Object/Gun.h"
#include "../Scene/SceneResource.h"
#include "../Object/EffectHit.h"
#include "Camera.h"
#include "../UI/UIWindow.h"
#include "../UI/UIWindowMain.h"
#include "../UI/UIWidget.h"
#include "../UI/UIWidgetImage.h"
#include "../UI/UIWindowHUD.h"
#include "../Resource/Sound.h"
#include "../Object/SpawnPlayer.h"
#include "../Object/SpawnMonster.h"
#include "../Object/KamikazeLite.h"
#include "../Object/KamikazeCage.h"
#include "../Object/KamikazeBoss.h"


MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

bool MainScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    loadSound();

    loadAnimationSequence();

    getCamera()->setWorldResolution(Vec(10000.f, 100000.f));

    EffectHit* pEffectHit = createPrototype<EffectHit>(L"BodyHit");
    EffectHit* pEffectDig = createPrototype<EffectHit>(L"spr_shovel");
    Bullet* pPlayerBullet = createPrototype<Bullet>(L"PlayerBullet");
    Bullet* pMonsterBullet = createPrototype<Bullet>(L"MonsterBullet");
    
    Player* pPlayer = createObject<Player>(L"Player", Vec(100.f, 100.f));
    Gun* pGun = createObject<Gun>(L"Gun", pPlayer->getObjPos() + Vec(10.f, 0.f), Vec(30.f, 30.f));
    SpawnPlayer* pSpawnPlayer = createObject<SpawnPlayer>(L"SpawnPlayer");
    pSpawnPlayer->setObjPos(Vec(100.f, 100.f));
    KamikazeCage* pKamikazeCage = createObject<KamikazeCage>(L"KamikazeCage", Vec(300.f, 100.f));
    KamikazeBoss* pKamikazeBoss = createObject<KamikazeBoss>(L"KamikazeBoss", Vec(500.f, 500.f));

    SpawnMonster* pSpawnMonster = createObject<SpawnMonster>(L"SpawnMonster", Vec(1000.f, 100.f));
    //KamikazeLite* pKamikazeLite = createObject<KamikazeLite>(L"KamikazeLite");

    // getCamera()->setWorldResolution(Vec(10000.f, 10000.f));
    // getCamera()->setTargetObject(pPlayer);

    UIWindow* pTestWindow = createUIWindow<UIWindow>(L"TestWindow");
    UIWidgetImage* pTestImage = pTestWindow->createWidget<UIWidgetImage>(L"TestImage");
    pTestImage->setImageTexture(L"TestImage", TEXT("StartGame.bmp"), TEXTURE_PATH);
    pTestImage->setUIWidgetPos(Vec(100.f, 100.f));
    pTestImage->setImageTextureColorKey(255, 0, 255);
    pTestImage->setUIWidgetZOrder(1);
    
    UIWidgetImage* pTestImage2 = pTestWindow->createWidget<UIWidgetImage>(L"TestImage2");
    pTestImage2->setImageTexture(L"TestImage2", TEXT("StartGameMouseOn.bmp"), TEXTURE_PATH);
    pTestImage2->setUIWidgetPos(Vec(150.f, 150.f));
    pTestImage2->setImageTextureColorKey(255, 0, 255);
    pTestImage2->setUIWidgetZOrder(2);

    UIWindowMain* pUIWindowMain = createUIWindow<UIWindowMain>(L"MainWindow");
    UIWindowHUD* pUIWindowHUD = createUIWindow<UIWindowHUD>(L"PlayerStateHUD");
    
    return true;
}

void MainScene::loadSound()
{
    getSceneResource()->loadSound(L"Effect", false, L"EffectHit", "effect_hit.mp3");
}

void MainScene::loadAnimationSequence()
{
    /* Player Animation */
    load(L"spr_jimmy_left_idle", L"Player/Left/spr_jimmy_left_idle.bmp", 12, 114.f, 94.f);
    load(L"spr_jimmy_right_idle", L"Player/Right/spr_jimmy_right_idle.bmp", 12, 114.f, 94.f);
    load(L"spr_jimmy_left_walk", L"Player/Left/spr_jimmy_left_walk.bmp", 6, 114.f, 94.f);
    load(L"spr_jimmy_right_walk", L"Player/Right/spr_jimmy_right_walk.bmp", 6, 114.f, 94.f);
    load(L"spr_jimmy_left_holo", L"Player/Left/spr_jimmy_left_holo.bmp", 17, 114.f, 94.f);
    load(L"spr_jimmy_right_holo", L"Player/Right/spr_jimmy_right_holo.bmp", 17, 114.f, 94.f);
    load(L"spr_jimmy_left_hit", L"Player/Left/spr_jimmy_left_hit.bmp", 2, 114.f, 94.f);
    load(L"spr_jimmy_right_hit", L"Player/Right/spr_jimmy_right_hit.bmp", 2, 114.f, 94.f);
    load(L"spr_jimmy_left_die", L"Player/Left/spr_jimmy_left_die.bmp", 14, 114.f, 94.f);
    load(L"spr_jimmy_right_die", L"Player/Right/spr_jimmy_right_die.bmp", 14, 114.f, 94.f);
    load(L"spr_jimmy_left_respawn", L"Player/Left/spr_jimmy_left_respawn.bmp", 15, 114.f, 94.f);
    load(L"spr_jimmy_right_respawn", L"Player/Right/spr_jimmy_right_respawn.bmp", 15, 114.f, 94.f);

    /* Gun Animation */
    load(L"spr_shotgun_heavy_right_idle", L"Gun/Right/ShotgunHeavy/spr_shotgun_heavy_right_idle.bmp", 1, 60.f, 22.f);
    load(L"spr_shotgun_heavy_left_idle", L"Gun/Left/ShotgunHeavy/spr_shotgun_heavy_left_idle.bmp", 1, 60.f, 22.f);
    load(L"spr_shotgun_heavy_right_fire", L"Gun/Right/ShotgunHeavy/spr_shotgun_heavy_right_fire.bmp", 3, 60.f, 22.f);
    load(L"spr_shotgun_heavy_left_fire", L"Gun/Left/ShotgunHeavy/spr_shotgun_heavy_left_fire.bmp", 3, 60.f, 22.f);
    
    /* Bullet Animation */
    load(L"spr_bullet_right_blue", L"Bullet/Right/Blue/spr_bullet_right_blue.bmp", 2, 46.f, 30.f);
    load(L"spr_bullet_left_blue", L"Bullet/Left/Blue/spr_bullet_left_blue.bmp", 2, 46.f, 30.f);
    load(L"spr_bullet_fire", L"Bullet/Right/Fire/spr_bullet_fire.bmp", 8, 24.f, 44.f);

    /* Monster Animation */
    load(L"spr_kamikazelite_left_idle", L"Monster/Left/Kamikazelite/spr_kamikazelite_left_idle.bmp", 16, 114.f, 94.f);
    load(L"spr_kamikazelite_left_hit", L"Monster/Left/Kamikazelite/spr_kamikazelite_left_hit.bmp", 2, 114.f, 94.f);
    load(L"spr_kamikazelite_left_die", L"Monster/Left/Kamikazelite/spr_kamikazelite_left_die.bmp", 16, 114.f, 94.f);
    load(L"spr_kamikazelite_right_idle", L"Monster/Right/Kamikazelite/spr_kamikazelite_right_idle.bmp", 16, 114.f, 94.f);
    load(L"spr_kamikazelite_right_hit", L"Monster/Right/Kamikazelite/spr_kamikazelite_right_hit.bmp", 2, 114.f, 94.f);
    load(L"spr_kamikazelite_right_die", L"Monster/Right/Kamikazelite/spr_kamikazelite_right_die.bmp", 16, 114.f, 94.f);
    load(L"spr_kamikazelite_explosion", L"Monster/Right/Kamikazelite/spr_kamikazelite_explosion.bmp", 12, 114.f, 94.f);

    load(L"spr_Kamikaze_left_idle", L"Monster/Left/Kamikaze/spr_Kamikaze_left_idle.bmp", 16, 114.f, 94.f);
    load(L"spr_Kamikaze_left_hit", L"Monster/Left/Kamikaze/spr_Kamikaze_left_hit.bmp", 2, 114.f, 94.f);
    load(L"spr_Kamikaze_left_die", L"Monster/Left/Kamikaze/spr_Kamikaze_left_die.bmp", 16, 114.f, 94.f);
    load(L"spr_Kamikaze_right_idle", L"Monster/Right/Kamikaze/spr_Kamikaze_right_idle.bmp", 16, 114.f, 94.f);
    load(L"spr_Kamikaze_right_hit", L"Monster/Right/Kamikaze/spr_Kamikaze_right_hit.bmp", 2, 114.f, 94.f);
    load(L"spr_Kamikaze_right_die", L"Monster/Right/Kamikaze/spr_Kamikaze_right_die.bmp", 16, 114.f, 94.f);
    load(L"spr_Kamikaze_explosion", L"Monster/Right/Kamikaze/spr_Kamikaze_explosion.bmp", 11, 114.f, 94.f);

    load(L"spr_kamikazecage_die", L"Monster/Right/KamikazeCage/spr_kamikazecage_die.bmp", 13, 270.f, 160.f);
    load(L"spr_kamikazecage_hit", L"Monster/Right/KamikazeCage/spr_kamikazecage_hit.bmp", 2, 170.f, 160.f);
    load(L"spr_kamikazecage_idle", L"Monster/Right/KamikazeCage/spr_kamikazecage_idle.bmp", 12, 170.f, 160.f);

    load(L"spr_kamikazeboss_right_die", L"Monster/Right/KamikazeBoss/spr_kamikazeboss_right_die.bmp", 13, 114.f, 112.f);
    load(L"spr_kamikazeboss_right_hit", L"Monster/Right/KamikazeBoss/spr_kamikazeboss_right_hit.bmp", 2, 114.f, 112.f);
    load(L"spr_kamikazeboss_right_idle", L"Monster/Right/KamikazeBoss/spr_kamikazeboss_right_idle.bmp", 24, 114.f, 112.f);
    load(L"spr_kamikazeboss_right_attack", L"Monster/Right/KamikazeBoss/spr_kamikazeboss_right_attack.bmp", 3, 114.f, 112.f);
    load(L"spr_kamikazeboss_right_bomb", L"Monster/Right/KamikazeBoss/spr_kamikazeboss_right_bomb.bmp", 8, 114.f, 112.f);
    load(L"spr_kamikazeboss_left_die", L"Monster/Left/KamikazeBoss/spr_kamikazeboss_left_die.bmp", 13, 114.f, 112.f);
    load(L"spr_kamikazeboss_left_hit", L"Monster/Left/KamikazeBoss/spr_kamikazeboss_left_hit.bmp", 2, 114.f, 112.f);
    load(L"spr_kamikazeboss_left_idle", L"Monster/Left/KamikazeBoss/spr_kamikazeboss_left_idle.bmp", 24, 114.f, 112.f);
    load(L"spr_kamikazeboss_left_attack", L"Monster/Left/KamikazeBoss/spr_kamikazeboss_left_attack.bmp", 3, 114.f, 112.f);
    load(L"spr_kamikazeboss_left_bomb", L"Monster/Left/KamikazeBoss/spr_kamikazeboss_left_bomb.bmp", 8, 114.f, 112.f);

    /* Effect Animation */
    getSceneResource()->createAnimationSequence(L"BodyHit", L"BodyHit",
        L"Hit/BodyHit.bmp");
    getSceneResource()->setTextureColorKey(L"BodyHit", 255, 0, 255);
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            getSceneResource()->addAnimationFrameData(L"BodyHit",
                j * 92.f, i * 92.f, 92.f, 92.f);
        }
    }
    load(L"spr_shovel", L"spr_shovel.bmp", 7, 114.f, 94.f);
    load(L"spr_hit_fire", L"Hit/spr_hit_fire.bmp", 12, 133.f, 147.f);
    load(L"spr_hit_bomb", L"Hit/spr_hit_bomb.bmp", 14, 266.f, 255.f);

    /* Spawn Animation */
    load(L"spr_player_spawn_setup", L"spr_player_spawn_setup.bmp", 18, 114.f, 128.f);
    load(L"spr_player_spawn_unset", L"spr_player_spawn_unset.bmp", 21, 114.f, 128.f);
    getSceneResource()->createAnimationSequence(L"spr_player_spawn_idle", L"spr_player_spawn_idle",
        L"spr_player_spawn_idle.bmp");
    getSceneResource()->setTextureColorKey(L"spr_player_spawn_idle", 255, 0, 255);
    for (int i = 0; i < 16; ++i)
    {
        getSceneResource()->addAnimationFrameData(L"spr_player_spawn_idle",
            0.f, 135.f * i, 114.f, 135.f);
    }
    load(L"spr_monster_spawn_idle", L"spr_monster_spawn_idle.bmp", 3, 68.f, 34.f);

}

void MainScene::load(const wstring& _strName, const wstring& _strPath, int _nFrameCount, float _fSizeX, float _fSizeY)
{
    const TCHAR* temp = _strPath.c_str();
    getSceneResource()->createAnimationSequence(_strName, _strName, temp);
    getSceneResource()->setTextureColorKey(_strName, 255, 0, 255);
    for (int i = 0; i < _nFrameCount; ++i)
    {
        getSceneResource()->addAnimationFrameData(_strName,
            i * _fSizeX, 0.f, _fSizeX, _fSizeY);
    }
}
