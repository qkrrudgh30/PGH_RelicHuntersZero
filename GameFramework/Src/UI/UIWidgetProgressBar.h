// UIWidgetProgressBar.h

#pragma once

#include "UIWidget.h"
#include "../Resource/Texture.h"

class UIWidgetProgressBar :
    public UIWidget
{
public:
    UIWidgetProgressBar();
    UIWidgetProgressBar(const UIWidgetProgressBar& _Other);
    virtual ~UIWidgetProgressBar();

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

    float getPercent() { return m_fPercent; }
    void setPercent(float _fPercent)
    {
        m_fPercent = _fPercent;
        if (m_fPercent < 0.f)
        {
            m_fPercent = 0.f;
        }
        else if (1.f < m_fPercent)
        {
            m_fPercent = 1.f;
        }
    }

protected:
    SharedPtr<Texture>  m_pTexture;
    float               m_fPercent;

};

