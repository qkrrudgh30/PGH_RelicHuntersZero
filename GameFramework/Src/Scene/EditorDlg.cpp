#include "EditorDlg.h"
#include "../GameManager.h"
#include "../PathManager.h"
#include "Scene.h"
#include "SceneResource.h"
#include "SceneEditStage.h"
#include "../Input.h"
#include "../UI/UIWindowEdit.h"
#include "SceneManager.h"
#include "SceneIntro.h"

EditorDlg* g_pDlg;

EditorDlg::EditorDlg()
	: m_nID(0)
	, m_hDlg(0)
	, m_bOpen(true)
	, m_pOwnerScene(nullptr)
	, m_strSelectTextureListText{}
	, m_nSelectFrameIdx(-1)
	, m_eTileEditMode(ETILE_EDITMODE::END)
	, m_eTileOption(ETILE_OPTION::END)
	, m_hEditModeCombo(0)
	, m_hFrameListBox(0)
	, m_hTextureListBox(0)
	, m_hTileOptionCombo(0)
	, m_nSelectTextureListIdx(0)
{
	g_pDlg = this;
}

EditorDlg::~EditorDlg()
{
	if (m_hDlg)
	{
		DestroyWindow(m_hDlg);
	}
}

bool EditorDlg::init(int _nID)
{
	m_hDlg = CreateDialog(GameManager::getInst()->getMainInst(),
		MAKEINTRESOURCE(_nID), GameManager::getInst()->getMainWnd(),
		EditorDlg::WndProc);

	ShowWindow(m_hDlg, SW_SHOW);
	
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILECOUNTX, 25, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILECOUNTY, 25, TRUE);

	SetDlgItemInt(m_hDlg, IDC_EDIT_TILESIZEX, 72, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_TILESIZEY, 72, TRUE);

	SetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEX, 0, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEY, 0, TRUE);

	SetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEX, 72, TRUE);
	SetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEY, 72, TRUE);

	m_hTextureListBox = GetDlgItem(m_hDlg, IDC_LIST_TILETEXTURE);

	m_hFrameListBox = GetDlgItem(m_hDlg, IDC_LIST_TEXTUREFRAME);

	m_nSelectTextureListIdx = -1;

	m_hEditModeCombo = GetDlgItem(m_hDlg, IDC_COMBO_EDITMODE);
	TCHAR TileEditMode[(int)ETILE_EDITMODE::END][30] = { TEXT("타일옵션"), TEXT("타일이미지"), TEXT("개체설치")};
	for (int i = 0; i < (int)ETILE_EDITMODE::END; ++i)
	{
		SendMessage(m_hEditModeCombo, CB_ADDSTRING, 0, (LPARAM)TileEditMode[i]);
	}
	SendMessage(m_hEditModeCombo, CB_SETCURSEL, 0, 0);
	m_eTileEditMode = ETILE_EDITMODE::OPTION;

	m_hTileOptionCombo = GetDlgItem(m_hDlg, IDC_COMBO_TILEOPTION);
	TCHAR	TileOptionText[(int)ETILE_OPTION::END][30] =
	{
		TEXT("Normal"),
		TEXT("Wall"),
		TEXT("Slow")
	};
	for (int i = 0; i < (int)ETILE_OPTION::END; ++i)
	{
		SendMessage(m_hTileOptionCombo, CB_ADDSTRING, 0, (LPARAM)TileOptionText[i]);
	}
	SendMessage(m_hTileOptionCombo, CB_SETCURSEL, 0, 0);
	m_eTileOption = ETILE_OPTION::NORMAL;
	
	return true;
}

void EditorDlg::show()
{
	if (m_bOpen)
	{
		m_bOpen = false;
		ShowWindow(m_hDlg, SW_HIDE);
	}
	else
	{
		m_bOpen = true;
		ShowWindow(m_hDlg, SW_SHOW);
	}
}

void EditorDlg::createMap()
{
	BOOL	Transfer = FALSE;
	
	int	TileCountX = GetDlgItemInt(m_hDlg, IDC_EDIT_TILECOUNTX, &Transfer, TRUE);
	int	TileCountY = GetDlgItemInt(m_hDlg, IDC_EDIT_TILECOUNTY, &Transfer, TRUE);
	int	TileSizeX = GetDlgItemInt(m_hDlg, IDC_EDIT_TILESIZEX, &Transfer, TRUE);
	int	TileSizeY = GetDlgItemInt(m_hDlg, IDC_EDIT_TILESIZEY, &Transfer, TRUE);
	
	m_pOwnerScene->createTileMap();
	m_pOwnerScene->setTileInfo(TileCountX, TileCountY, TileSizeX, TileSizeY);
	
}

void EditorDlg::loadTileTexture()
{
	TCHAR	FilePath[MAX_PATH] = {};

	OPENFILENAME	OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = m_hDlg;
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0BmpFile\0*.bmp");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = PathManager::getInst()->findPath(TEXTURE_PATH)->m_strUniPath;

	if (GetOpenFileName(&OpenFile) != 0)
	{
		// 전체 경로에서 파일 이름만 얻어온다.
		TCHAR	FileName[128] = {};

		_wsplitpath_s(FilePath, nullptr, 0, nullptr, 0, FileName, 128,
			nullptr, 0);

		char	TextureName[256] = {};

#ifdef UNICODE
		// 유니코드 문자열을 멀티바이트 문자열로 변환한다.
		int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FileName, -1, nullptr, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, FileName, -1, TextureName, ConvertLength, 0, 0);

#else
		strcpy_s(TextureName, FileName);
#endif // UNICODE


		if (!m_pOwnerScene->getSceneResource()->loadTextureFullPath(FileName, FilePath))
		{
			return;
		}


		Texture* pTexture = m_pOwnerScene->getSceneResource()->findTexture(FileName);

		pTexture->setTextureColorKey(255, 0, 255);

		SendMessage(m_hTextureListBox, LB_ADDSTRING, 0, (LPARAM)FileName);

		TileTextureFrameData	data;
		m_vecTextureFrameData.push_back(data);
	}
}

void EditorDlg::selectTexture()
{
	if (m_nSelectTextureListIdx != -1)
	{
		char TextureName[256] = {};
		m_pSelectTileTexture = m_pOwnerScene->getSceneResource()->findTexture(m_strSelectTextureListText);
		m_pOwnerScene->createTileMap();
		m_pOwnerScene->setTileTexture(m_pSelectTileTexture);
	}
}

void EditorDlg::selectList()
{
	m_nSelectTextureListIdx = (int)SendMessage(m_hTextureListBox, LB_GETCURSEL, 0, 0);

	if (m_nSelectTextureListIdx != -1)
	{
		memset(m_strSelectTextureListText, 0, sizeof(TCHAR) * 256);
		SendMessage(m_hTextureListBox, LB_GETTEXT, m_nSelectTextureListIdx,
			(LPARAM)m_strSelectTextureListText);

		int	Count = (int)SendMessage(m_hFrameListBox, LB_GETCOUNT, 0, 0);

		for (int i = 0; i < Count; ++i)
		{
			SendMessage(m_hFrameListBox, LB_DELETESTRING, 0, 0);
		}

		for (size_t i = 0; i < m_vecTextureFrameData[m_nSelectTextureListIdx].vecData.size(); ++i)
		{
			TCHAR	Text[32] = {};

			wsprintf(Text, TEXT("%d"), (int)i);

			SendMessage(m_hFrameListBox, LB_ADDSTRING, 0, (LPARAM)Text);
		}

		m_nSelectFrameIdx = -1;
	}
}

void EditorDlg::addFrame()
{
	
	if (m_nSelectTextureListIdx == -1)
		return;

	BOOL	Transfer = FALSE;
	
	int	StartFrameX = GetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEX, &Transfer, TRUE);
	int	StartFrameY = GetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEY, &Transfer, TRUE);
	int	EndFrameX = GetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEX, &Transfer, TRUE);
	int	EndFrameY = GetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEY, &Transfer, TRUE);
	
	TileFrameData	Data;
	Data.vStart.x = (float)StartFrameX;
	Data.vStart.y = (float)StartFrameY;
	Data.vEnd.x = (float)EndFrameX;
	Data.vEnd.y = (float)EndFrameY;
	
	TCHAR	Text[32] = {};

	wsprintf(Text, TEXT("%d"),
		(int)m_vecTextureFrameData[m_nSelectTextureListIdx].vecData.size());

	SendMessage(m_hFrameListBox, LB_ADDSTRING, 0, (LPARAM)Text);

	m_vecTextureFrameData[m_nSelectTextureListIdx].vecData.push_back(Data);
	
}

void EditorDlg::deleteFrame()
{
}

void EditorDlg::modifyFrame()
{
}

void EditorDlg::changeFrame()
{
	
	m_nSelectFrameIdx = (int)SendMessage(m_hFrameListBox, LB_GETCURSEL, 0, 0);

	if (m_nSelectFrameIdx != -1)
	{
		TileFrameData	Data = m_vecTextureFrameData[m_nSelectTextureListIdx].vecData[m_nSelectFrameIdx];
		
		SetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEX, (int)Data.vStart.x, TRUE);
		SetDlgItemInt(m_hDlg, IDC_EDIT_STARTFRAMEY, (int)Data.vStart.y, TRUE);

		SetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEX, (int)Data.vEnd.x, TRUE);
		SetDlgItemInt(m_hDlg, IDC_EDIT_ENDFRAMEY, (int)Data.vEnd.y, TRUE);
	}
	
}

void EditorDlg::save()
{
	TCHAR	FilePath[MAX_PATH] = {};

	OPENFILENAME	OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = m_hDlg;
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0MapFile\0*.map");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = PathManager::getInst()->findPath(MAP_PATH)->m_strUniPath;

	if (GetSaveFileName(&OpenFile) != 0)
	{

		char	FullPath[MAX_PATH] = {};

#ifdef UNICODE
		// 유니코드 문자열을 멀티바이트 문자열로 변환한다.
		int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FilePath, -1,
			nullptr, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, FilePath, -1,
			FullPath, ConvertLength, 0, 0);
#else
		strcpy_s(FullPath, FilePath);
#endif // UNICODE

		m_pOwnerScene->save(FullPath);
	}
}

void EditorDlg::load()
{
	TCHAR	FilePath[MAX_PATH] = {};

	OPENFILENAME	OpenFile = {};

	OpenFile.lStructSize = sizeof(OPENFILENAME);
	OpenFile.hwndOwner = m_hDlg;
	OpenFile.lpstrFilter = TEXT("모든파일\0*.*\0MapFile\0*.map");
	OpenFile.lpstrFile = FilePath;
	OpenFile.nMaxFile = MAX_PATH;
	OpenFile.lpstrInitialDir = PathManager::getInst()->findPath(MAP_PATH)->m_strUniPath;

	if (GetOpenFileName(&OpenFile) != 0)
	{

		char	FullPath[MAX_PATH] = {};

#ifdef UNICODE
		// 유니코드 문자열을 멀티바이트 문자열로 변환한다.
		int ConvertLength = WideCharToMultiByte(CP_ACP, 0, FilePath, -1,
			nullptr, 0, 0, 0);

		WideCharToMultiByte(CP_ACP, 0, FilePath, -1,
			FullPath, ConvertLength, 0, 0);
#else
		strcpy_s(FullPath, FilePath);
#endif // UNICODE

		m_pOwnerScene->load(FullPath);
	}
}

void EditorDlg::tileImageAllClear()
{
	m_pOwnerScene->tileImageAllClear();
}

void EditorDlg::gotoIntro()
{
	if (m_hDlg)
	{
		DestroyWindow(m_hDlg);
	}
	GameManager::getInst()->setEditorMode(false);
	m_pOwnerScene->setSceneChange(true);
	SceneManager::getInst()->createScene<SceneIntro>();
}

void EditorDlg::setPlayer()
{
	m_pOwnerScene->getUIWindowEdit()->setMousePlayerImage();
}

void EditorDlg::setKamikazeLiteSpawn()
{
	m_pOwnerScene->getUIWindowEdit()->setMouseKamikazeLiteSpawnImage();
}

void EditorDlg::setKamikazeSpawn()
{
	m_pOwnerScene->getUIWindowEdit()->setMouseKamikazeSpawnImage();
}

void EditorDlg::setKamikazeBossSpawn()
{
	m_pOwnerScene->getUIWindowEdit()->setMouseKamikazeBossSpawnImage();
}

void EditorDlg::setStage1Potal()
{
	m_pOwnerScene->getUIWindowEdit()->setMouseStage1PotalImage();
}

void EditorDlg::setStage2Potal()
{
	m_pOwnerScene->getUIWindowEdit()->setMouseStage2PotalImage();
}

LRESULT EditorDlg::WndProc(HWND _hWnd, UINT _uMessage, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uMessage)
	{
	case WM_CLOSE:
		DestroyWindow(_hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(_wParam))
		{
		case IDC_LIST_TILETEXTURE:
			switch (HIWORD(_wParam))
			{
			case LBN_SELCHANGE:
			{
				g_pDlg->selectList();
			}
			break;
			}
			break;
		case IDC_LIST_TEXTUREFRAME:
			switch (HIWORD(_wParam))
			{
			case LBN_SELCHANGE:
			{
				g_pDlg->changeFrame();
			}
			break;
			}
			break;
			break;
		case IDOK:
			break;
		case IDCANCEL:
			break;
		case IDC_BUTTON_CREATEMAP:
			g_pDlg->createMap();
			break;
		case IDC_BUTTON_TILETEXTURELOAD:
			g_pDlg->loadTileTexture();
			break;
		case IDC_BUTTON_SETTEXTURE:
			g_pDlg->selectTexture();
			break;
		case IDC_BUTTON_ADDFRAME:
			g_pDlg->addFrame();
			break;
		case IDC_BUTTON_DELETEFRAME:
			g_pDlg->deleteFrame();
			break;
		case IDC_BUTTON_MODIFYFRAME:
			g_pDlg->modifyFrame();
			break;
		case IDC_BUTTON_SAVE:
			g_pDlg->save();
			break;
		case IDC_BUTTON_LOAD:
			g_pDlg->load();
			break;
		case IDC_BUTTON_IMAGECLEAR:
			g_pDlg->tileImageAllClear();
			break;
		case IDC_BUTTON_SETPLAYER:
			g_pDlg->setPlayer();
			break;
		case IDC_BUTTON_SETMONSTER1:
			g_pDlg->setKamikazeLiteSpawn();
			break;
		case IDC_BUTTON_SETMONSTER2:
			g_pDlg->setKamikazeSpawn();
			break;
		case IDC_BUTTON_SETBOSS:
			g_pDlg->setKamikazeBossSpawn();
			break;
		case IDC_BUTTON_SETPOTAL1:
			g_pDlg->setStage1Potal();
			break;
		case IDC_BUTTON_SETPOTAL2:
			g_pDlg->setStage2Potal();
			break;
		case IDC_BUTTON_GOTOINTRO:
			g_pDlg->gotoIntro();
			break;

			
		}
		break;
	default:
		break;
	}

	return 0;
}
