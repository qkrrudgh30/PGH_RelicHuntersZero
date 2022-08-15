#include "../GameInfo.h"
#include "../GameManager.h"
#include "SceneEditStage.h"
#include "SceneResource.h"
#include "../Object/EffectHit.h"
#include "Camera.h"
#include "../UI/UIWindow.h"
#include "../UI/UIWidgetImage.h"
#include "../Input.h"
#include "EditorDlg.h"
#include "../Map/TileMap.h"
#include "../UI/UIWindowEdit.h"
#include "../Object/Object.h"
#include "../Object/Character.h"

SceneEditStage::SceneEditStage()
    : m_pDlg(nullptr)
    , m_pTileMap(nullptr)
    , m_bStart(false)
    , m_fScrollSpeed(500.f)
    , m_bSceneChange(false)
    , m_pUIWindowEdit(nullptr)
{
    GameManager::getInst()->setEditorMode(true);
}

SceneEditStage::~SceneEditStage()
{
    GameManager::getInst()->setEditorMode(false);
    SAFE_DELETE(m_pDlg);
}

void SceneEditStage::loadSound()
{
}

void SceneEditStage::loadAnimationSequence()
{
}

void SceneEditStage::loadAnimation()
{
}

bool SceneEditStage::init()
{
    Scene::init();
    loadSound();
    loadAnimationSequence();
    
    m_pDlg = new EditorDlg;
    m_pDlg->setOwnerScene(this);
    m_pDlg->init(IDD_DIALOG_EDITOR);

    ShowCursor(TRUE);
    m_pUIWindowEdit = createUIWindow<UIWindowEdit>(L"EditWindow");

    return true;
}

bool SceneEditStage::update()
{
    Scene::update();
    if (!m_bStart)
    {
        m_bStart = true;
        Input::getInst()->setCallback<SceneEditStage>(L"Editor", KeyState_Down,
            this, &SceneEditStage::onEditor);

        Input::getInst()->setCallback<SceneEditStage>(L"MouseLButton", KeyState_Down,
            this, &SceneEditStage::MouseLButton);



        Input::getInst()->setCallback<SceneEditStage>(L"MouseRButton", KeyState_Down,
            this, &SceneEditStage::MouseRButton);

        /*
        Input::getInst()->setCallback<SceneEditStage>("MoveUp", KeyState_Push,
            this, &SceneEditStage::cameraMoveUp);

        Input::getInst()->setCallback<SceneEditStage>("MoveDown", KeyState_Push,
            this, &SceneEditStage::cameraMoveDown);

        Input::getInst()->setCallback<SceneEditStage>("MoveLeft", KeyState_Push,
            this, &SceneEditStage::cameraMoveLeft);

        Input::getInst()->setCallback<SceneEditStage>("MoveRight", KeyState_Push,
            this, &SceneEditStage::cameraMoveRight);
            */

    }

    /*
    RECT rt = m_pDlg->getRect();
    Vec vMousePos = Input::getInst()->getMouseCurPos();
    
    if (rt.left <= vMousePos.x && vMousePos.x <= rt.right &&
        rt.top <= vMousePos.y && vMousePos.y <= rt.bottom)
    {
        if (!Input::getInst()->isShowCursor())
        {
            Input::getInst()->setShowCursor(true);
            ShowCursor(TRUE);
        }
    }
    else
    {
        if (!Input::getInst()->isShowCursor())
        {
            Input::getInst()->setShowCursor(false);
            ShowCursor(FALSE);
        }
    }
    */

    return true;
}

bool SceneEditStage::postUpdate()
{
    Scene::postUpdate();

    return true;
}

void SceneEditStage::onEditor()
{
    bool bCurState = GameManager::getInst()->isEditorMode();
    GameManager::getInst()->setEditorMode(!bCurState);
}

void SceneEditStage::createTileMap()
{
    if (m_pTileMap)
    {
        return;
    }
    m_pTileMap = createMap<TileMap>(L"TileMap");
}

void SceneEditStage::setTileInfo(int _nCountX, int _nCountY, int _nScaleX, int _nScaleY)
{
    m_pTileMap->createTile(_nCountX, _nCountY, Vec((float)_nScaleX, (float)_nScaleY));
}

void SceneEditStage::setTileTexture(Texture* _pTexture)
{
    m_pTileMap->setTileTexture(_pTexture);
}

void SceneEditStage::MouseLButton()
{
    if (!m_pTileMap || m_bSceneChange || !GameManager::getInst()->isEditorMode())
    {
        return;
    }
    ETILE_EDITMODE eEditMode = m_pDlg->getTileEditMode();
    Vec vMousePos = Input::getInst()->getMouseCurPos();
    Camera* pCamera = getCamera();
    vMousePos = pCamera->calculateAbsolutePos(vMousePos);
    Vec vCamRes = pCamera->getCameraResolution();


    if (vMousePos.x < 0.f || vMousePos.x > (pCamera->getCameraLT()+vCamRes).x ||
        vMousePos.y < 0.f || vMousePos.y > (pCamera->getCameraLT()+vCamRes).y)
        return;

    switch (eEditMode)
    {
    case ETILE_EDITMODE::OPTION:
    {
        ETILE_OPTION eOption = m_pDlg->getTileOption();
        m_pTileMap->changeTileOption(vMousePos, eOption);
    }
    break;
    case ETILE_EDITMODE::IMAGE:
    {
        TileFrameData FrameData = m_pDlg->getTileFrameData();
        m_pTileMap->setTileFrame(vMousePos, FrameData.vStart, FrameData.vEnd);
    }
    break;
    case ETILE_EDITMODE::OBJECT:
    {
        ETILE_OPTION eOption = m_pDlg->getTileOption();
        if (ETILE_OPTION::WALL == eOption)
        {
            return;
        }
        Texture* pTexture = m_pUIWindowEdit->getMouseImage()->getImageTexture();
        Vec vScale = Vec((float)pTexture->getTextureWidth(), (float)pTexture->getTextureHeight());
        wstring strName = pTexture->getObjName();
        Object* pTemp;
        if (L"PlayerSpawn" == strName ||
            L"KamikazeBossSpawn" == strName ||
            L"Stage1Potal" == strName ||
            L"Stage2Potal" == strName)
        {
            pTemp = findObject(strName);
            if (nullptr != pTemp)
            {
                pTemp->setObjPos(vMousePos);

                m_pTileMap->findObj(strName)->x = vMousePos.x;
                m_pTileMap->findObj(strName)->y = vMousePos.y;
            }
            else
            {
                // 유일 개체인데 처음 만들어지는 경우
                pTemp = createObject<Object>(strName, vMousePos, vScale);
                pTemp->setTexture(pTexture->getObjName());

                ObjectInfo_t Obj;
                Obj.strName = strName;
                Obj.vPos = vMousePos;
                m_pTileMap->pushBackObj(&Obj);
                m_pTileMap->upObjCount();
            }
        }
        else
        {
            // 유일 개체가 아닌 경우
            pTemp = createObject<Object>(strName, vMousePos, vScale);
            pTemp->setTexture(pTexture->getObjName());

            ObjectInfo_t Obj;
            Obj.strName = strName;
            Obj.vPos = vMousePos;
            m_pTileMap->pushBackObj(&Obj);
            m_pTileMap->upObjCount();
        }

        
    }
    break;
    }
}

void SceneEditStage::MouseRButton()
{
    if (!m_pTileMap || m_bSceneChange || !GameManager::getInst()->isEditorMode())
    {
        return;
    }
    m_pUIWindowEdit->getMouseImage()->setImageTexture(nullptr);

    if (!m_pTileMap)
    {
        return;
    }

    ETILE_EDITMODE eEditMode = m_pDlg->getTileEditMode();
    Vec vMousePos = Input::getInst()->getMouseCurPos();
    Camera* pCamera = getCamera();
    vMousePos = pCamera->calculateAbsolutePos(vMousePos);

    if (vMousePos.x < 0.f || vMousePos.x > pCamera->getCameraResolution().x ||
        vMousePos.y < 0.f || vMousePos.y > pCamera->getCameraResolution().y)
        return;

    switch (eEditMode)
    {
    case ETILE_EDITMODE::OPTION:
    {
        m_pTileMap->changeTileOption(vMousePos, ETILE_OPTION::NORMAL);
    }
    break;
    case ETILE_EDITMODE::IMAGE:
    {
        m_pTileMap->setTileTexture(vMousePos, nullptr);
    }
    break;
    }

}

void SceneEditStage::load(const char* FullPath)
{
    if (!m_pTileMap)
    {
        m_pTileMap = createMap<TileMap>(L"TileMap");
    }
    m_pTileMap->loadFullPath(FullPath);

    if (m_pTileMap->getObjCount() != 0)
    {
        m_pTileMap->createObjInEdit();
    }
}

void SceneEditStage::save(const char* FullPath)
{
    if (!m_pTileMap)
    {
        MessageBox(0, TEXT("맵을 생성하세요."), TEXT("Error"), MB_OK);
        return;
    }
    m_pTileMap->saveFullPath(FullPath);
}

void SceneEditStage::tileImageAllClear()
{
    if (!m_pTileMap)
    {
        return;
    }
    m_pTileMap->tileImageAllClear();
}

