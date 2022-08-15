#pragma once

class Scene;

class MapBase
{
public:
	virtual bool init();
	virtual void update();
	virtual void postUpdate();
	virtual void preRender();
	virtual void render(HDC _hDC);
	virtual void start();

	virtual void saveFile(const char* _strFileName, const wstring& _strPath = MAP_PATH);
	virtual void loadFile(const char* _strFileName, const wstring& _strPath = MAP_PATH);

	virtual void save(FILE* _pFile);
	virtual void load(FILE* _pFile);

	virtual void saveFullPath(const char* _strFileName);
	virtual void loadFullPath(const char* _strFileName);

	void setOwnerScene(Scene* _pScene) { m_pOwnerScene = _pScene; }
	Scene* getOwnerScene() { return m_pOwnerScene; }

	void setName(const wstring& _strName) { m_strName = _strName; }
	const wstring& getName() { return m_strName; }

	void setPos(const Vec& _vPos) { m_vPos = _vPos; }
	const Vec& getPos() { return m_vPos; }

	void setScale(const Vec& _vScale) { m_vScale = _vScale; }
	const Vec& getScale() { return m_vScale; }

	void setZOrder(int _nZOrder) { m_nZOrder = _nZOrder; }
	int getZOrder() { return m_nZOrder; }

	void setEnable(bool _bEnable) { m_bEnable = _bEnable; }
	bool isEnable() { return m_bEnable; }

	void setActive(bool _bActive) { m_bActive = _bActive; }
	bool isActive() { return m_bActive; }

protected:
	MapBase();
	virtual ~MapBase();

	Scene*		m_pOwnerScene;
	wstring		m_strName;
	Vec			m_vPos;
	Vec			m_vScale;
	int			m_nZOrder;
	bool		m_bEnable;
	bool		m_bActive;

private:

	friend class Scene;
};

