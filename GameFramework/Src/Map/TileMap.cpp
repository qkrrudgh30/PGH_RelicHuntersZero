#include "../GameInfo.h"
#include "TileMap.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "Tile.h"
#include "../Object/Object.h"
#include "../Object/Player.h"
#include "../Object/Bullet.h"
#include "../Object/Monster.h"
#include "../Object/Gun.h"
#include "../Scene/SceneResource.h"
#include "../Object/EffectHit.h"
#include "../UI/UIWindow.h"
#include "../UI/UIWindowMain.h"
#include "../UI/UIWidget.h"
#include "../UI/UIWidgetImage.h"
#include "../UI/UIWidgetButton.h"
#include "../UI/UIWindowHUD.h"
#include "../Resource/Sound.h"
#include "../Object/SpawnPlayer.h"
#include "../Object/SpawnMonster.h"
#include "../Object/KamikazeLite.h"
#include "../Object/KamikazeCage.h"
#include "../Object/KamikazeBoss.h"
#include "../Object/Potal.h"
#include "../Map/TileMap.h"

TileMap::TileMap()
	: m_pTileTexture(nullptr)
	, m_nTileCountX(0)
	, m_nTileCountY(0)
	, m_vTileSize{}
	, m_nStartX(-1)
	, m_nStartY(-1)
	, m_nEndX(-1)
	, m_nEndY(-1)
	, m_nObjectCount(0)
{
	// m_vecTile.resize(1000, nullptr);
}

TileMap::~TileMap()
{
	size_t uSize = m_vecTile.size();
	for (size_t i = 0; i < 30; ++i)
	{
		if (nullptr != m_vecTile[i])
		{
			SAFE_DELETE(m_vecTile[i]);
		}
	}
	m_vecTile.clear();
}

bool TileMap::init()
{
	MapBase::init();
	return true;
}

void TileMap::update()
{
	MapBase::update();

	if (!m_vecTile.empty())
	{
		Camera* pCamera = m_pOwnerScene->getCamera();
		Vec vCameraLT = pCamera->getCameraLT();
		Vec vCameraRB = pCamera->getCameraRB();
		m_nStartX = (int)(vCameraLT.x / m_vTileSize.x);
		m_nStartY = (int)(vCameraLT.y / m_vTileSize.y);
		m_nEndX = (int)(vCameraRB.x / m_vTileSize.x);
		m_nEndY = (int)(vCameraRB.y / m_vTileSize.y);

		m_nStartX = m_nStartX < 0 ? 0 : m_nStartX;
		m_nStartY = m_nStartY < 0 ? 0 : m_nStartY;
		m_nEndX = m_nTileCountX <= m_nEndX ? m_nTileCountX - 1 : m_nEndX;
		m_nEndY = m_nTileCountY <= m_nEndY ? m_nTileCountY - 1 : m_nEndY;

		for (int i = m_nStartY; i <= m_nEndY; ++i)
		{
			for (int j = m_nStartX; j <= m_nEndX; ++j)
			{
				m_vecTile[(long long int)i * m_nTileCountX + j]->update();
			}
		}
	}
}

void TileMap::postUpdate()
{
	MapBase::postUpdate();
	if (!m_vecTile.empty())
	{
		if (m_nStartX == -1 || m_nStartY == -1 || m_nEndX == -1 || m_nEndY == -1)
		{
			return;
		}
		for (int i = m_nStartY; i <= m_nEndY; ++i)
		{
			for (int j = m_nStartX; j <= m_nEndX; ++j)
			{
				m_vecTile[(long long int)i * m_nTileCountX + j]->postUpdate();
			}
		}
	}
}

void TileMap::preRender()
{
	MapBase::preRender();
	if (!m_vecTile.empty())
	{
		if (m_nStartX == -1 || m_nStartY == -1 || m_nEndX == -1 || m_nEndY == -1)
		{
			return;
		}
		for (int i = m_nStartY; i <= m_nEndY; ++i)
		{
			for (int j = m_nStartX; j <= m_nEndX; ++j)
			{
				m_vecTile[(long long int)i * m_nTileCountX + j]->preRender();
			}
		}
	}
}

void TileMap::render(HDC _hDC)
{
	MapBase::render(_hDC);
	if (!m_vecTile.empty())
	{
		if (m_nStartX == -1 || m_nStartY == -1 || m_nEndX == -1 || m_nEndY == -1)
		{
			return;
		}
		for (int i = m_nStartY; i <= m_nEndY; ++i)
		{
			for (int j = m_nStartX; j <= m_nEndX; ++j)
			{
				m_vecTile[(long long int)i * m_nTileCountX + j]->render(_hDC);
			}
		}
	}
}

void TileMap::start()
{
	MapBase::start();
}

bool TileMap::createTile(int _nCountX, int _nCountY, const Vec& _vTileSize)
{
	m_nTileCountX = _nCountX;
	m_nTileCountY = _nCountY;
	m_vTileSize = _vTileSize;
	{
		auto begIter = m_vecTile.begin();
		auto endIter = m_vecTile.end();
		for (; begIter != endIter;)
		{
			SAFE_DELETE((*begIter));
			++begIter;
		}
		m_vecTile.clear();
	}

	m_vScale = m_vTileSize * Vec((float)m_nTileCountX, (float)m_nTileCountY);

	Camera* pCamera = m_pOwnerScene->getCamera();
	pCamera->setWorldResolution(m_vScale);

	for (int i = 0; i < m_nTileCountY; ++i)
	{
		for (int j = 0; j < m_nTileCountX; ++j)
		{
			Tile* pTile = new Tile;
			pTile->m_pOwnerScene = m_pOwnerScene;
			pTile->init();

			Vec vPos = Vec((float)j, (float)i) * m_vTileSize;
			pTile->setTileInfo(vPos, m_vTileSize, j, i, i * m_nTileCountX + j, m_pTileTexture);
			if (i * m_nTileCountX + j == 30)
			{
				int a = 100;
			}
			m_vecTile.push_back(pTile);
		}
	}

	for (int i = 0; i < m_nTileCountY; ++i)
	{
		for (int j = 0; j < m_nTileCountX; ++j)
		{
			m_vecTile[(long long int)i * m_nTileCountX + j]->setTileTexture(m_pTileTexture);
		}
	}

	return true;
}

bool TileMap::setTileTexture(Texture* _pTexture)
{
	m_pTileTexture = _pTexture;
	for (int i = 0; i < m_nTileCountY; ++i)
	{
		for (int j = 0; j < m_nTileCountX; ++j)
		{
			m_vecTile[(long long int)i * m_nTileCountX + j]->setTileTexture(m_pTileTexture);
		}
	}

	return true;
}

bool TileMap::setTileTexture(Texture* _pTexture, int _nIdxX, int _nIdxY)
{
	m_pTileTexture = _pTexture;
	m_vecTile[(long long int)_nIdxY * m_nTileCountX + _nIdxX]->setTileTexture(m_pTileTexture);

	return true;
}

bool TileMap::setTileTexture(const Vec& _vPos, Texture* _pTexture)
{
	Tile* pTile = getTile(_vPos);
	if (!pTile)
	{
		return false;
	}
	pTile->setTileTexture(_pTexture);
	return true;
}

void TileMap::changeTileOption(const Vec& _vPos, ETILE_OPTION _eOption)
{
	Tile* pTile = getTile(_vPos);
	if (!pTile)
	{
		return;
	}
	pTile->setTileOption(_eOption);
}

void TileMap::setTileFrame(const Vec& _vPos, const Vec& _vStart, const Vec& _vEnd)
{
	Tile* pTile = getTile(_vPos);
	if (!pTile)
	{
		return;
	}
	pTile->setStartFrame(_vStart);
	pTile->setEndFrame(_vEnd);
}

Tile* TileMap::getTile(const Vec& _vPos)
{
	int nIdxX = (int)(_vPos.x / m_vTileSize.x);
	int nIdxY = (int)(_vPos.y / m_vTileSize.y);

	if (nIdxX < 0 || m_nTileCountX <= nIdxX)
	{
		return nullptr;
	}

	if (nIdxY < 0 || m_nTileCountY <= nIdxY)
	{
		return nullptr;
	}

	return m_vecTile[(long long int)nIdxY * m_nTileCountX + nIdxX];
}

Tile* TileMap::getTile(int _nIdx)
{
	return m_vecTile[_nIdx];
}

Tile* TileMap::getTile(int _nIdxX, int _nIdxY)
{
	return m_vecTile[_nIdxY * m_nTileCountX + _nIdxX];
}

int TileMap::getTileIndexX(float _fPosX)
{
	int nIdxX = (int)(_fPosX / m_vTileSize.x);

	if (nIdxX < 0 || nIdxX >= m_nTileCountX)
	{
		return -1;
	}

	return nIdxX;
}

int TileMap::getTileIndexY(float _fPosY)
{
	int nIdxY = (int)(_fPosY / m_vTileSize.y);

	if (nIdxY < 0 || nIdxY >= m_nTileCountY)
	{
		return -1;
	}

	return nIdxY;
}

int TileMap::getTileIndex(const Vec& _vPos)
{
	int nIdxX = getTileIndexX(_vPos.x);
	int nIdxY = getTileIndexX(_vPos.y);

	if (nIdxX == -1 || nIdxY == -1)
	{
		return -1;
	}

	return nIdxY * m_nTileCountX + nIdxX;
}

int TileMap::getOriginTileIndexX(float PosX)
{
	return (int)(PosX / m_vTileSize.x);
}

int TileMap::getOriginTileIndexY(float PosY)
{
	return (int)(PosY / m_vTileSize.y);
}

void TileMap::save(FILE* _pFile)
{
	MapBase::save(_pFile);

	fwrite(&m_nTileCountX, sizeof(int), 1, _pFile);
	fwrite(&m_nTileCountY, sizeof(int), 1, _pFile);
	fwrite(&m_vTileSize, sizeof(Vec), 1, _pFile);
	fwrite(&m_nStartX, sizeof(int), 1, _pFile);
	fwrite(&m_nStartY, sizeof(int), 1, _pFile);
	fwrite(&m_nEndX, sizeof(int), 1, _pFile);
	fwrite(&m_nEndY, sizeof(int), 1, _pFile);

	if (m_pTileTexture)
	{
		bool	Tex = true;
		fwrite(&Tex, sizeof(bool), 1, _pFile);

		m_pTileTexture->save(_pFile);
	}

	else
	{
		bool	Tex = false;
		fwrite(&Tex, sizeof(bool), 1, _pFile);
	}

	int	TileCount = (int)m_vecTile.size();
	fwrite(&TileCount, sizeof(int), 1, _pFile);

	for (int i = 0; i < TileCount; ++i)
	{
		m_vecTile[i]->save(_pFile);
	}

	fwrite(&m_nObjectCount, sizeof(int), 1, _pFile);
	auto iter = m_lsObjectInfo.begin();
	auto endIter = m_lsObjectInfo.end();
	for (; iter != endIter;)
	{
		/*
		int strSize = WideCharToMultiByte(CP_ACP, 0, (iter->strName).c_str(), -1, NULL, 0, NULL, NULL);
		char* str = new char[strSize];
		WideCharToMultiByte(CP_ACP, 0, (iter->strName).c_str(), -1, str, strSize, 0, 0);
		fwrite(&strSize, sizeof(int), 1, _pFile);
		fwrite(&str, sizeof(char), strSize, _pFile);
		*/

		int	Length = (int)iter->strName.size();
		fwrite(&Length, sizeof(int), 1, _pFile);
		fwrite(iter->strName.c_str(), sizeof(wchar_t), Length, _pFile);

		fwrite(&(iter->vPos.x), sizeof(float), 1, _pFile);
		fwrite(&(iter->vPos.y), sizeof(float), 1, _pFile);
		++iter;
	}

	
}

void TileMap::load(FILE* _pFile)
{
	MapBase::load(_pFile);	

	fread(&m_nTileCountX, sizeof(int), 1, _pFile);
	fread(&m_nTileCountY, sizeof(int), 1, _pFile);
	fread(&m_vTileSize, sizeof(Vec), 1, _pFile);
	fread(&m_nStartX, sizeof(int), 1, _pFile);
	fread(&m_nStartY, sizeof(int), 1, _pFile);
	fread(&m_nEndX, sizeof(int), 1, _pFile);
	fread(&m_nEndY, sizeof(int), 1, _pFile);

	bool	Tex = true;
	fread(&Tex, sizeof(bool), 1, _pFile);

	if (Tex)
	{
		m_pTileTexture = Texture::loadStatic(_pFile, m_pOwnerScene);
	}

	int	TileCount = 0;
	fread(&TileCount, sizeof(int), 1, _pFile);

	size_t	TileSize = m_vecTile.size();

	for (size_t i = 0; i < TileSize; ++i)
	{
		SAFE_DELETE(m_vecTile[i]);
	}

	m_vecTile.clear();

	for (int i = 0; i < TileCount; ++i)
	{
		Tile* pTile = new Tile;
		pTile->m_pOwnerScene = m_pOwnerScene;

		m_vecTile.push_back(pTile);

		m_vecTile[i]->load(_pFile);
	}

	fread(&m_nObjectCount, sizeof(int), 1, _pFile);
	if (m_nObjectCount != 0)
	{
		for (int i = 0; i < m_nObjectCount; ++i)
		{
			ObjectInfo_t obj;
			/*
			char* strName = new char[256];
			int strSize = 0;
			strName = nullptr;
			fread(&strSize, sizeof(int), 1, _pFile);
			fread(&strName, sizeof(char), strSize, _pFile);
			wchar_t* wcstring = new wchar_t[256];
			size_t num;
			mbstowcs_s(&num, wcstring, 256, strName, 256);
			obj.strName = wcstring;
			delete[] wcstring;
			delete[] strName;
			*/

			int	Length = 0;

			fread(&Length, sizeof(int), 1, _pFile);

			wchar_t	Name[256] = {};

			fread(Name, sizeof(wchar_t), Length, _pFile);
			/*
			wchar_t* wcstring = new wchar_t[256];
			size_t num;
			mbstowcs_s(&num, wcstring, 256, Name, 256);

			delete[] wcstring;
			*/

			obj.strName = Name;
			fread(&(obj.vPos.x), sizeof(float), 1, _pFile);
			fread(&(obj.vPos.y), sizeof(float), 1, _pFile);
			m_lsObjectInfo.push_back(obj);
		}
	}



	m_vScale = m_vTileSize * Vec((float)m_nTileCountX, (float)m_nTileCountY);
	Camera* pCam = m_pOwnerScene->getCamera();
	pCam->setWorldResolution(m_vScale);


}

void TileMap::tileImageAllClear()
{
	size_t uSize = m_vecTile.size();
	for (size_t i = 0; i < uSize; ++i)
	{
		m_vecTile[i]->setTileTexture(nullptr);
	}
	m_lsObjectInfo.clear();
	m_pOwnerScene->getObjectList()->clear();
}


void TileMap::createObj()
{
	auto iter = m_lsObjectInfo.begin();
	auto endIter = m_lsObjectInfo.end();

	for (; iter != endIter;)
	{
		
		if (iter->strName == L"PlayerSpawn")
		{
			SpawnPlayer* pTemp = m_pOwnerScene->createObject<SpawnPlayer>(iter->strName, iter->vPos);
		}
		else if (iter->strName == L"KamikazeLiteSpawn")
		{
			SpawnMonster* pTemp = m_pOwnerScene->createObject<SpawnMonster>(iter->strName, iter->vPos);
		}
		else if (iter->strName == L"KamikazeSpawn")
		{
			KamikazeCage* pTemp = m_pOwnerScene->createObject<KamikazeCage>(iter->strName, iter->vPos);
		}
		else if (iter->strName == L"KamikazeBossSpawn")
		{
			KamikazeBoss* pTemp = m_pOwnerScene->createObject<KamikazeBoss>(iter->strName, iter->vPos);
		}
		else if (iter->strName == L"Stage1Potal")
		{
			// KamikazeBoss* pTemp = m_pOwnerScene->createObject<KamikazeBoss>(iter->strName, iter->vPos);
		}
		else if (iter->strName == L"Stage2Potal")
		{
			// pTemp->setTexture(iter->strName, L"spr_set_pota2.bmp", MOUSE_PATH);
		}

		++iter;
	}
}

void TileMap::createObjInEdit()
{
	auto iter = m_lsObjectInfo.begin();
	auto endIter = m_lsObjectInfo.end();

	for (; iter != endIter;)
	{
		Object* pTemp = m_pOwnerScene->createObject<Object>(iter->strName, iter->vPos);
		if (iter->strName == L"PlayerSpawn")
		{
			pTemp->setTexture(iter->strName, L"spr_set_jimmy.bmp", MOUSE_PATH);
		}
		else if (iter->strName == L"KamikazeLiteSpawn")
		{
			pTemp->setTexture(iter->strName, L"spr_set_spawn1.bmp", MOUSE_PATH);

		}
		else if (iter->strName == L"KamikazeSpawn")
		{
			pTemp->setTexture(iter->strName, L"spr_set_spawn2.bmp", MOUSE_PATH);
		}
		else if (iter->strName == L"KamikazeBossSpawn")
		{
			pTemp->setTexture(iter->strName, L"spr_set_egg.bmp", MOUSE_PATH);
		}
		else if (iter->strName == L"Stage1Potal")
		{
			pTemp->setTexture(iter->strName, L"spr_set_pota1.bmp", MOUSE_PATH);
		}
		else if (iter->strName == L"Stage2Potal")
		{
			pTemp->setTexture(iter->strName, L"spr_set_pota2.bmp", MOUSE_PATH);
		}
		pTemp->setTextureColorKey(255, 0, 255);

		++iter;
	}
}
