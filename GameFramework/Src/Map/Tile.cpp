
#include "../GameInfo.h"
#include "../Object/Object.h"
#include "Tile.h"
#include "../GameManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Scene/Camera.h"
#include "../GameManager.h"
#include "../Collision/ColliderBox.h"


Tile::Tile()
	: m_pOwnerScene(nullptr)
	, m_pTexture(nullptr)
	, m_vStartFrame{}
	, m_vEndFrame{}
	, m_vPos{}
	, m_vScale{}
	, m_nIdxX(0)
	, m_nIdxY(0)
	, m_nIdx(0)
	, m_eOption(ETILE_OPTION::NORMAL)
	, m_pWallTile(nullptr)
{
}

Tile::~Tile()
{
}

bool Tile::init()
{
	/*
	ColliderBox* pPlayerBody = addCollider<ColliderBox>(L"PlayerBody");
	pPlayerBody->setExtent(30.f, 30.f);
	pPlayerBody->setOffset(Vec(0.f, 30.f));
	pPlayerBody->setProfile(L"Player");
	pPlayerBody->setCollisionBeginFunc<Player>(this, &Player::collisionBegin);
	*/ 

	return true;
}

void Tile::update()
{
}

void Tile::postUpdate()
{
}

void Tile::preRender()
{
}

void Tile::render(HDC _hDC)
{
	Camera* pCamera = SceneManager::getInst()->getCurScene()->getCamera();

	Vec vCameraLT = pCamera->getCameraLT();
	Vec vCameraRB = pCamera->getCameraRB();
	if (m_pTexture)
	{
		m_pTexture->render(_hDC, pCamera->calculateRenderPos(m_vPos), m_vStartFrame, m_vScale);
	}

	if (GameManager::getInst()->isEditorMode())
	{
		HBRUSH hBrush = 0;
		switch (m_eOption)
		{
		case ETILE_OPTION::NORMAL:
			hBrush = GameManager::getInst()->getGreenBrush();
			break;
		case ETILE_OPTION::WALL:
			hBrush = GameManager::getInst()->getRedBrush();
			break;
		case ETILE_OPTION::SLOW:
			hBrush = GameManager::getInst()->getYellowBrush();
			break;
		}

		RECT rt;
		rt.left = (LONG)m_vPos.x - (LONG)vCameraLT.x;
		rt.top = (LONG)m_vPos.y - (LONG)vCameraLT.y;
		rt.right = (LONG)m_vPos.x + (LONG)m_vScale.x - (LONG)vCameraLT.x;
		rt.bottom = (LONG)m_vPos.y + (LONG)m_vScale.y - (LONG)vCameraLT.y;

		FrameRect(_hDC, &rt, hBrush);
	}
}

void Tile::start()
{
}

void Tile::save(FILE* _pFile)
{
	fwrite(&m_vPos, sizeof(Vec), 1, _pFile);
	fwrite(&m_vScale, sizeof(Vec), 1, _pFile);

	fwrite(&m_nIdxX, sizeof(int), 1, _pFile);
	fwrite(&m_nIdxY, sizeof(int), 1, _pFile);
	fwrite(&m_nIdx, sizeof(int), 1, _pFile);

	fwrite(&m_vStartFrame, sizeof(Vec), 1, _pFile);
	fwrite(&m_vEndFrame, sizeof(Vec), 1, _pFile);
	fwrite(&m_eOption, sizeof(ETILE_OPTION), 1, _pFile);

	if (m_pTexture)
	{
		bool	Tex = true;
		fwrite(&Tex, sizeof(bool), 1, _pFile);

		m_pTexture->save(_pFile);
	}

	else
	{
		bool	Tex = false;
		fwrite(&Tex, sizeof(bool), 1, _pFile);
	}
}

void Tile::load(FILE* _pFile)
{
	fread(&m_vPos, sizeof(Vec), 1, _pFile);
	fread(&m_vScale, sizeof(Vec), 1, _pFile);

	fread(&m_nIdxX, sizeof(int), 1, _pFile);
	fread(&m_nIdxY, sizeof(int), 1, _pFile);
	fread(&m_nIdx, sizeof(int), 1, _pFile);

	fread(&m_vStartFrame, sizeof(Vec), 1, _pFile);
	fread(&m_vEndFrame, sizeof(Vec), 1, _pFile);
	fread(&m_eOption, sizeof(ETILE_OPTION), 1, _pFile);

	bool	Tex = true;
	fread(&Tex, sizeof(bool), 1, _pFile);

	if (Tex)
	{
		m_pTexture = Texture::loadStatic(_pFile, m_pOwnerScene);
	}
	
	if (ETILE_OPTION::WALL == m_eOption &&
		!GameManager::getInst()->isEditorMode())
	{
		m_pWallTile = getOwnerScene()->createObject<WallTile>(L"WallTile", m_vPos + m_vScale, m_vScale);
		// m_pWallTile->setOwnerTile(this);
		// m_pWallTile->setImageStart(m_vStartFrame);
		// m_pWallTile->setTexture(L"WallTile", L"spr_tile_stage1.bmp");
		
	}
	
	if (ETILE_OPTION::WALL == m_eOption ||
		ETILE_OPTION::SLOW == m_eOption)
	{
		m_pOwnerScene->getWallTileList()->push_back(this);
	}


	
	/*
	if (ETILE_OPTION::WALL == m_eOption ||
		ETILE_OPTION::SLOW == m_eOption)
	{
		
		if (216.f <= m_vStartFrame.x)
		{
			return;
		}
		
		if (ETILE_OPTION::WALL == m_eOption &&
			!GameManager::getInst()->isEditorMode())
		{
			m_pWallTile = getOwnerScene()->createObject<WallTile>(L"WallTile", m_vPos + m_vScale, m_vScale);
		}
		
		m_pOwnerScene->getWallTileList()->push_back(this);
	}
	*/
}
