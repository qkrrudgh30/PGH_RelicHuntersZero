// UIWidgetButton.h

#pragma once

#include "UIWidget.h"
#include "../Resource/Texture.h"
#include "../Resource/Sound.h"

class UIWidgetButton :
    public UIWidget
{
public:
    UIWidgetButton();
    UIWidgetButton(const UIWidgetButton& _Other);
    ~UIWidgetButton();

    virtual bool init();
    virtual void update();
    virtual void postUpdate();
    virtual void collision();
    virtual void render(HDC _hDC);
    virtual void render(const Vec& _vPos, HDC _hDC);

    SharedPtr<Texture> getButtonTexture() { return m_pTexture; }
    void setButtonTexture(Texture* _pTexture) 
    {
        m_pTexture = _pTexture;
        if (nullptr != m_pTexture)
        {
            m_vScale.x = (float)m_pTexture->getTextureWidth();
            m_vScale.y = (float)m_pTexture->getTextureHeight();
        }
    }
    void setButtonTexture(const wstring& _strName);
    void setButtonTexture(const wstring& _strName, const TCHAR* _strFileName,
        const wstring& _strPath = TEXTURE_PATH);
    void setButtonTexture(const wstring& _strName, const TCHAR* _strFullPath);
    void setButtonTextureColorKey(unsigned char _r, unsigned char _g, unsigned char _b, size_t _uIdx);

    void setButtonFrameData(EBUTTON_STATE _eState, const Vec& _vStart, const Vec& _vScale);

    void setButtonEnable(bool _bEnable) { m_eCurButtonState = _bEnable ? EBUTTON_STATE::ENABLE : EBUTTON_STATE::DISABLE;  }

    template <typename T>
    void setButtonMouseOnCallback(T* _pObj, void(T::* _fpFunc)()) { m_fpButtonMouseOnCallback = bind(_fpFunc, _pObj); }

    template <typename T>
    void setButtonClickCallback(T* _pObj, void(T::* _fpFunc)()) { m_fpButtonClickCallback = bind(_fpFunc, _pObj); }

    void setButtonHoverSound(const wstring& _strName);
    void setButtonClickSound(const wstring& _strName);

protected:
    SharedPtr<Texture>  m_pTexture;
    AnimationFrameData  m_FrameData[(int)EBUTTON_STATE::END];
    EBUTTON_STATE       m_eCurButtonState;
    function<void()>    m_fpButtonMouseOnCallback;
    function<void()>    m_fpButtonClickCallback;
    SharedPtr<Sound>    m_arrButtonSound[2];

    virtual void collisionMouseHoveredCallback();
    virtual void collisionMouseReleasedCallback();


private:

    
};

