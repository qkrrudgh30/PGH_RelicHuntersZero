#pragma once
#include "MapBase.h"
#include "../Resource/Texture.h"
class ScrollMap :
    public MapBase
{
public:
    ScrollMap();
    virtual ~ScrollMap();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void preRender();
    virtual void render(HDC _hDC);
    virtual void start();

    virtual void save(FILE* _pFile);
    virtual void load(FILE* _pFile);

	void setScrollRatio(float x, float y)
	{
		m_vScrollRatio = Vec(x, y);
	}

	void setLoop(bool Loop)
	{
		m_bLoop = Loop;
	}

	void setTexture(const wstring& Name, const TCHAR* FileName,
		const wstring& PathName = TEXTURE_PATH);
	void setTextureFullPath(const wstring& Name,
		const TCHAR* FullPath);
	void setTexture(const wstring& Name, const vector<wstring>& vecFileName,
		const wstring& PathName = TEXTURE_PATH);
	void setTexture(const wstring& Name);
	void setTextureColorKey(const unsigned char r, const unsigned char g,
		const unsigned char b);

protected:
    SharedPtr<Texture>  m_pScollTexture;
    Vec                 m_vScrollRatio;
    bool                m_bLoop;

private:

    friend class Scene;

};

