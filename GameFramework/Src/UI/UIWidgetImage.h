// UIWidgetImage.h

#pragma once

#include "UIWidget.h"
#include "../Resource/Texture.h"

class UIWidgetImage :
    public UIWidget
{
public:
    UIWidgetImage();
    UIWidgetImage(const UIWidgetImage& _Other);
    virtual ~UIWidgetImage();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);
    virtual void render(const Vec& _vPos, HDC _hDC);

    SharedPtr<Texture> getImageTexture() { return m_pTexture; }
    void setImageTexture(Texture* _pTexture)
    {
        m_pTexture = _pTexture;
        if (nullptr != m_pTexture)
        {
            m_vScale.x = (float)m_pTexture->getTextureWidth();
            m_vScale.y = (float)m_pTexture->getTextureHeight();
        }
    }
    void setImageTexture(const wstring& _strName);
    void setImageTexture(const wstring& _strName, const TCHAR* _strFileName,
        const wstring& _strPath = TEXTURE_PATH);
    void setImageTexture(const wstring& _strName, const TCHAR* _strFullPath);
    void setImageTextureColorKey(unsigned char _r, unsigned char _g, unsigned char _b, size_t _uIdx = 0);

    void addFrameData(const Vec& _vPos, const Vec& _vScale)
    {
        AnimationFrameData data = {};
        data.vStartPos = _vPos;
        data.vScale = _vScale;
        m_vecFrameData.push_back(data);
    }

    void changeTexture(const wstring& _strName, const TCHAR* _strFileName,
        const wstring& _strPath = TEXTURE_PATH);

protected:
    SharedPtr<Texture>          m_pTexture;
    vector<AnimationFrameData>  m_vecFrameData;
    int                         m_nFrameIndex;
    float                       m_fPlaytime;
    float                       m_fAniTime;
    Vec                         m_vOffset;

};

