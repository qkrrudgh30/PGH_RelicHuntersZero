// Texture.h

#pragma once
#include "../Ref.h"

class Scene;

struct TextureInfo
{
    // 이미지파일을 불러와서 HBITMAP을 만들고 이 HBITMAP을 화면에 출력할
    // 메모리DC를 만들어서 출력하게 한다.
    HDC				hDC;
    HBITMAP			hBmp;
    HBITMAP			hDefaultBmp;
    BITMAP			BmpInfo;
    bool			bColorKeyEnable;
    unsigned int	uColorKey;
    TCHAR           strFileName[MAX_PATH];

    TextureInfo() :
        hDC(0),
        hBmp(0),
        hDefaultBmp(0),
        BmpInfo{},
        bColorKeyEnable(false),
        uColorKey(0),
        strFileName{}
    {
    }

    ~TextureInfo()
    {
        // 원래의 HGDIOBJ로 되돌려준다.
        SelectObject(hDC, hDefaultBmp);

        // HBITMAP과 HDC를 제거한다.
        DeleteObject(hBmp);

        DeleteDC(hDC);
    }
};

class Texture :
    public Ref
{
public:
    Texture();
    virtual ~Texture();

    void render(HDC _dc, const Vec& _vPosInWindow, const Vec& _vPosInTexture,
        const Vec& _vScale, size_t _uIdx = 0);

    bool loadTexture(const wstring& _strName, const TCHAR* _strFileName,
        const wstring& _strPath = TEXTURE_PATH);
    bool loadTexture(const wstring& _strName, const vector<wstring>& _vecFileName,
        const wstring& _strPath = TEXTURE_PATH);
    bool loadTextureFullPath(const wstring& _strName, const TCHAR* _strFullPath);

    TextureInfo* findTexture(wstring _strName)
    {
        auto iter = m_vecTextureInfo.begin();
        auto endIter = m_vecTextureInfo.end();
        for (; iter != endIter;)
        {
            if ((*iter)->strFileName == _strName)
            {
                return *iter;
            }
            ++iter;
        }
        return nullptr;
    }
    ETEXTURETYPE getTextureType() const { return m_eTextureType; }

    unsigned int getTextureWidth(size_t _uIdx = 0) const { return (unsigned int)m_vecTextureInfo[_uIdx]->BmpInfo.bmWidth; }
    unsigned int getTextureHeight(size_t _uIdx = 0) const { return (unsigned int)m_vecTextureInfo[_uIdx]->BmpInfo.bmHeight; }
    TCHAR* getTextureFileName(size_t _uIdx = 0) { return m_vecTextureInfo[_uIdx]->strFileName; }

    void setTextureColorKey(const unsigned char _r, const unsigned char _g, const unsigned char _b, size_t _uIdx = 0)
    {
        m_vecTextureInfo[_uIdx]->bColorKeyEnable = true;
        m_vecTextureInfo[_uIdx]->uColorKey = RGB(_r, _g, _b);
    }

    void setTextureColorKey(unsigned int _uColorKey, int _uIdx = 0)
    {
        m_vecTextureInfo[_uIdx]->bColorKeyEnable = true;
        m_vecTextureInfo[_uIdx]->uColorKey = _uColorKey;
    }

    size_t getTextureVecSize() { return m_vecTextureInfo.size(); }

    void  save(FILE* _pFile);
    void  load(FILE* _pFile);
    static Texture* loadStatic(FILE* _pFile, Scene* _pScene);

private:
    ETEXTURETYPE         m_eTextureType;
    vector<TextureInfo*> m_vecTextureInfo;

};

