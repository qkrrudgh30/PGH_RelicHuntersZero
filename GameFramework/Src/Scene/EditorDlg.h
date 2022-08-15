#pragma once

#include "../GameInfo.h"
#include "../Resource/Texture.h"

class SceneEditStage;

struct TileFrameData
{
	Vec vStart;
	Vec vEnd;
};

struct TileTextureFrameData
{
	vector<TileFrameData> vecData;
};

class EditorDlg
{
public:
	EditorDlg();
	virtual ~EditorDlg();

	bool init(int _nID);
	void show();
	void createMap();
	void loadTileTexture();
	void selectTexture();
	void selectList();
	void addFrame();
	void deleteFrame();
	void modifyFrame();
	void changeFrame();
	void save();
	void load();
	void tileImageAllClear();
	void gotoIntro();

	void setPlayer();
	void setKamikazeBossSpawn();
	void setStage1Potal();
	void setStage2Potal();

	void setKamikazeLiteSpawn();
	void setKamikazeSpawn();

	ETILE_OPTION getTileOption() { return (ETILE_OPTION)SendMessage(m_hTileOptionCombo, CB_GETCURSEL, 0, 0); }
	TileFrameData getTileFrameData()
	{
		if (-1 == m_nSelectFrameIdx || -1 == m_nSelectTextureListIdx)
		{
			return TileFrameData();
		}
		return m_vecTextureFrameData[m_nSelectTextureListIdx].vecData[m_nSelectFrameIdx];
	}
	ETILE_EDITMODE getTileEditMode() { return (ETILE_EDITMODE)SendMessage(m_hEditModeCombo, CB_GETCURSEL, 0, 0); }

	bool isOpen() { return m_bOpen; }

	RECT getRect()
	{
		RECT rt;
		GetWindowRect(m_hDlg, &rt);
		return rt;
	}

	void setOwnerScene(SceneEditStage* _pScene) { m_pOwnerScene = _pScene; }
	SceneEditStage* getOwnerScene() { return m_pOwnerScene; }

private:
	HWND							m_hDlg;
	int								m_nID;
	bool							m_bOpen;
	SceneEditStage*					m_pOwnerScene;
	HWND							m_hTextureListBox;
	int								m_nSelectTextureListIdx;
	TCHAR							m_strSelectTextureListText[256];
	SharedPtr<Texture>				m_pSelectTileTexture;
	vector<TileTextureFrameData>	m_vecTextureFrameData;

	HWND							m_hEditModeCombo;
	ETILE_EDITMODE					m_eTileEditMode;

	HWND							m_hTileOptionCombo;
	ETILE_OPTION					m_eTileOption;

	HWND							m_hFrameListBox;
	int								m_nSelectFrameIdx;

	static LRESULT CALLBACK WndProc(HWND _hWnd, UINT _uMessage, WPARAM _wParam, LPARAM _lParam);

};

