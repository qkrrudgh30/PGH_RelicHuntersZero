// Texture.cpp

#include "../GameInfo.h"
#include "Texture.h"
#include "../PathManager.h"
#include "../GameManager.h"
#include "../Scene/Scene.h"
#include "../Scene/SceneResource.h"

Texture::Texture()
    : m_eTextureType(ETEXTURETYPE::ETEXTURETYPE_ATLAS)
{
}

Texture::~Texture()
{
    size_t uSize = m_vecTextureInfo.size();
    for (size_t i = 0; i < uSize; ++i)
    {
        SAFE_DELETE(m_vecTextureInfo[i]);
    }
}

void Texture::render(HDC _dc, const Vec& _vPosInWindow, const Vec& _vPosInTexture, const Vec& _vScale, size_t _uIdx)
{
    bool bRes = true;
    if (m_vecTextureInfo[_uIdx]->bColorKeyEnable)
    {
        // 1������ : ����� DC�̴�.
        // 2������ : ����� ������ �󿡼��� x��ǥ
        // 3������ : ����� ������ �󿡼��� y��ǥ
        // 4������ : ����� ������ �󿡼��� xũ��
        // 5������ : ����� ������ �󿡼��� yũ��
        // 6������ : ����� �̹����� DC�̴�.
        // 7������ : ����� �̹��� �󿡼��� ���� ��ǥ x
        // 8������ : ����� �̹��� �󿡼��� ���� ��ǥ y
        // 9������ : ����� �̹��� �󿡼��� ����ũ��
        // 10������ : ����� �̹��� �󿡼��� ����ũ��
        // 11������ : ColorKey ����
        
        if (m_vecTextureInfo[_uIdx]->BmpInfo.bmWidth == 60 && m_vecTextureInfo[_uIdx]->BmpInfo.bmHeight == 22)
        {
            m_vecTextureInfo[_uIdx]->BmpInfo.bmWidth;
        }
       
        bRes = TransparentBlt(_dc, (int)_vPosInWindow.x, (int)_vPosInWindow.y, (int)_vScale.x, (int)_vScale.y,
            m_vecTextureInfo[_uIdx]->hDC, (int)_vPosInTexture.x, (int)_vPosInTexture.y,
            (int)_vScale.x, (int)_vScale.y, m_vecTextureInfo[_uIdx]->uColorKey);
    }
    else
    {
        if (m_vecTextureInfo[_uIdx]->BmpInfo.bmWidth == 60 && m_vecTextureInfo[_uIdx]->BmpInfo.bmHeight == 22)
        {
            m_vecTextureInfo[_uIdx]->BmpInfo.bmWidth;
        }
        // 1������ : ����� DC�̴�.
        // 2������ : ����� ������ �󿡼��� x��ǥ
        // 3������ : ����� ������ �󿡼��� y��ǥ
        // 4������ : ����� ������ �󿡼��� xũ��
        // 5������ : ����� ������ �󿡼��� yũ��
        // 6������ : ����� �̹����� DC�̴�.
        // 7������ : ����� �̹��� �󿡼��� ���� ��ǥ x
        // 8������ : ����� �̹��� �󿡼��� ���� ��ǥ y
        BitBlt(_dc, (int)_vPosInWindow.x, (int)_vPosInWindow.y, (int)_vScale.x, (int)_vScale.y,
            m_vecTextureInfo[_uIdx]->hDC, (int)_vPosInTexture.x, (int)_vPosInTexture.y, SRCCOPY);
    }
    bRes;
}

bool Texture::loadTexture(const wstring& _strName, const TCHAR* _strFileName, const wstring& _strPath)
{
    // ���� ��θ� ������ش�.
    const PathInfo* Info = PathManager::getInst()->findPath(_strPath);

    TCHAR	strFullPath[MAX_PATH] = {};

    if (Info)
    {
        lstrcpy(strFullPath, Info->m_strUniPath);
    }
    lstrcat(strFullPath, _strFileName);

    return loadTextureFullPath(_strName, strFullPath);
}

bool Texture::loadTexture(const wstring& _strName, const vector<wstring>& _vecFileName, const wstring& _strPath)
{
    // ���� ��θ� ������ش�.
    const PathInfo* Info = PathManager::getInst()->findPath(_strPath);

    size_t uSize = _vecFileName.size();

    for (size_t i = 0; i < uSize; ++i)
    {
        TCHAR strFullPath[MAX_PATH] = {};

        if (Info)
        {
            lstrcpy(strFullPath, Info->m_strUniPath);
        }
        lstrcat(strFullPath, _vecFileName[i].c_str());

        if (!loadTextureFullPath(_strName, strFullPath))
        {
            return false;
        }
    }

    return true;
}

bool Texture::loadTextureFullPath(const wstring& _strName, const TCHAR* _strFullPath)
{
    setObjName(_strName);

    // FileName �κи��� ���´�.
    TCHAR	FileName[MAX_PATH] = {};

    char	FullPathMultibyte[MAX_PATH] = {};

#ifdef UNICODE
    // �����ڵ� ���ڿ��� ��Ƽ����Ʈ ���ڿ��� ��ȯ�Ѵ�.
    int ConvertLength = WideCharToMultiByte(CP_ACP, 0, _strFullPath, -1,
        nullptr, 0, 0, 0);

    WideCharToMultiByte(CP_ACP, 0, _strFullPath, -1,
        FullPathMultibyte, ConvertLength, 0, 0);
#else
    strcpy_s(FullPathMultibyte, FullPath);
#endif // UNICODE

    _strupr_s(FullPathMultibyte);

    int	PathLength = (int)strlen(FullPathMultibyte);

    // ���� ��� �̷��� ������ D:/Project/Bin/Texture/Player/Test.bmp
    for (int i = PathLength - 1; i >= 0; --i)
    {
        if (FullPathMultibyte[i] == '\\')
        {
            char	FolderName[9] = {};
            strcpy_s(FolderName, "ERUTXET\\");

            bool	Find = true;

            for (int j = 1; j <= 8; ++j)
            {
                if (FullPathMultibyte[i - j] != FolderName[j - 1])
                {
                    Find = false;
                    break;
                }
            }

            if (Find)
                lstrcpy(FileName, &_strFullPath[i + 1]);
        }
    }

    TextureInfo* Info = new TextureInfo;

    lstrcpy(Info->strFileName, FileName);
    // �޸� DC ����
    Info->hDC = CreateCompatibleDC(GameManager::getInst()->getMainDC());
    HINSTANCE temp = GameManager::getInst()->getMainInst();
    Info->hBmp = (HBITMAP)LoadImage(GameManager::getInst()->getMainInst(),
        _strFullPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    // ������ ������ �޸� DC�� �ҷ��� ��Ʈ���� �������ش�.
    // SelectObject�� �Ʒ�ó�� HGDIOBJ�� �����ϸ� ���� ������ �ִ�
    // HGDIOBJ�� ��ȯ���ش�.
    // �׷��� �� DC�� �����ٶ����� �ݵ�� ���� HGDIOBJ�� ������ �صΰ�
    // ������� �Ѵ�.
    Info->hDefaultBmp = (HBITMAP)SelectObject(Info->hDC, Info->hBmp);

    // ��Ʈ�� ������ ���ͼ� ����.
    GetObject(Info->hBmp, sizeof(BITMAP), &Info->BmpInfo);

    m_vecTextureInfo.push_back(Info);

    if (1 == m_vecTextureInfo.size())
    {
        m_eTextureType = ETEXTURETYPE::ETEXTURETYPE_ATLAS;
    }
    else
    {
        m_eTextureType = ETEXTURETYPE::ETEXTURETYPE_FRAME;
    }

    return true;
}

void Texture::save(FILE* _pFile)
{
    int	Length = (int)getObjName().length();
    char* pCStr;
    pCStr = new char[Length];
    WideCharToMultiByte(CP_ACP, 0, getObjName().c_str(), -1, pCStr, Length, 0, 0);
    pCStr[Length] = '\0';

    fwrite(&Length, sizeof(int), 1, _pFile);
    fwrite(pCStr, sizeof(char), Length, _pFile);

    fwrite(&m_eTextureType, sizeof(ETEXTURETYPE), 1, _pFile);

    int	Count = (int)m_vecTextureInfo.size();
    fwrite(&Count, sizeof(int), 1, _pFile);

    for (int i = 0; i < Count; ++i)
    {
        fwrite(&m_vecTextureInfo[i]->bColorKeyEnable, sizeof(bool), 1, _pFile);
        fwrite(&m_vecTextureInfo[i]->uColorKey, sizeof(unsigned int), 1, _pFile);

        int	NameCount = lstrlen(m_vecTextureInfo[i]->strFileName);
        fwrite(&NameCount, sizeof(int), 1, _pFile);

        WideCharToMultiByte(CP_ACP, 0, m_vecTextureInfo[i]->strFileName, -1, pCStr, NameCount, 0, 0);
        pCStr[NameCount] = '\0';

        fwrite(pCStr, sizeof(char), NameCount, _pFile);
    }
}

void Texture::load(FILE* _pFile)
{
    int	Length = 0;
    char	Name[256] = {};

    fread(&Length, sizeof(int), 1, _pFile);
    fread(Name, sizeof(char), Length, _pFile);

    wchar_t* wcstring = new wchar_t[256];
    mbstowcs_s((size_t*)&Length, wcstring, 256, Name, 256);
    setObjName(wcstring);

    fread(&m_eTextureType, sizeof(ETEXTURETYPE), 1, _pFile);

    int	Count = 0;
    fread(&Count, sizeof(int), 1, _pFile);

    bool	ColorKeyEnable = false;
    unsigned int ColorKey = 0;

    fread(&ColorKeyEnable, sizeof(bool), 1, _pFile);
    fread(&ColorKey, sizeof(unsigned int), 1, _pFile);

    int	NameCount = 0;
    fread(&NameCount, sizeof(int), 1, _pFile);

    TCHAR	FileName[MAX_PATH] = {};

    fread(&FileName, sizeof(TCHAR), NameCount, _pFile);

    loadTexture(getObjName(), FileName);

    if (ColorKeyEnable)
    {
        setTextureColorKey(ColorKey);
    }

    /*
    if (Count == 1)
    {
        bool	ColorKeyEnable = false;
        unsigned int ColorKey = 0;

        fread(&ColorKeyEnable, sizeof(bool), 1, _pFile);
        fread(&ColorKey, sizeof(unsigned int), 1, _pFile);

        int	NameCount = 0;
        fread(&NameCount, sizeof(int), 1, _pFile);

        TCHAR	FileName[MAX_PATH] = {};

        fread(&FileName, sizeof(TCHAR), NameCount, _pFile);

        loadTexture(getObjName(), FileName);

        if (ColorKeyEnable)
        {
            setTextureColorKey(ColorKey);
        }
    }

    else
    {
        std::vector<std::wstring> vecFileName;
        std::vector<bool>	vecColorKeyEnable;
        std::vector<unsigned int>	vecColorKey;

        for (int i = 0; i < Count; ++i)
        {
            bool	ColorKeyEnable = false;
            unsigned int ColorKey = 0;

            fread(&ColorKeyEnable, sizeof(bool), 1, _pFile);
            fread(&ColorKey, sizeof(unsigned int), 1, _pFile);

            vecColorKeyEnable.push_back(ColorKeyEnable);
            vecColorKey.push_back(ColorKey);

            int	NameCount = 0;
            fread(&NameCount, sizeof(int), 1, _pFile);

            TCHAR	FileName[MAX_PATH] = {};

            fread(&FileName, sizeof(TCHAR), NameCount, _pFile);

            vecFileName.push_back(FileName);
        }

        loadTexture(getObjName(), vecFileName);

        for (int i = 0; i < Count; ++i)
        {
            if (!vecColorKeyEnable[i])
                continue;

            setTextureColorKey(vecColorKey[i], i);
        }
    }
    */
}

Texture* Texture::loadStatic(FILE* _pFile, Scene* _pScene)
{
    Texture* Result = nullptr;

    int	Length = 0;
    char	Name[256] = {};

    fread(&Length, sizeof(int), 1, _pFile);
    fread(Name, sizeof(char), Length, _pFile);

    wchar_t* wcstring = new wchar_t[256];
    size_t num;
    mbstowcs_s(&num, wcstring, 256, Name, 256);
    wstring wName = wcstring;
    

    ETEXTURETYPE TextureType;

    fread(&TextureType, sizeof(ETEXTURETYPE), 1, _pFile);

    int	Count = 0;
    fread(&Count, sizeof(int), 1, _pFile);

    bool	ColorKeyEnable = false;
    unsigned int ColorKey = 0;

    fread(&ColorKeyEnable, sizeof(bool), 1, _pFile);
    fread(&ColorKey, sizeof(unsigned int), 1, _pFile);

    int	NameCount = 0;
    fread(&NameCount, sizeof(int), 1, _pFile);

    TCHAR	FileName[MAX_PATH] = {};
    fread(&Name, sizeof(char), NameCount, _pFile);
    mbstowcs_s(&num, wcstring, 256, Name, 256);

    _pScene->getSceneResource()->loadTexture(wName, wcstring);

    if (ColorKeyEnable)
    {
        _pScene->getSceneResource()->setTextureColorKey(wName, ColorKey);
    }

    Result = _pScene->getSceneResource()->findTexture(wName);

    /*
    if (Count == 1)
    {
        bool	ColorKeyEnable = false;
        unsigned int ColorKey = 0;

        fread(&ColorKeyEnable, sizeof(bool), 1, _pFile);
        fread(&ColorKey, sizeof(unsigned int), 1, _pFile);

        int	NameCount = 0;
        fread(&NameCount, sizeof(int), 1, _pFile);

        TCHAR	FileName[MAX_PATH] = {};

        fread(&FileName, sizeof(TCHAR), NameCount, _pFile);

        _pScene->getSceneResource()->loadTexture(wName, FileName);

        if (ColorKeyEnable)
        {
            _pScene->getSceneResource()->setTextureColorKey(wName, ColorKey);
        }

        Result = _pScene->getSceneResource()->findTexture(wName);

    }
    else
    {
        std::vector<std::wstring> vecFileName;
        std::vector<bool>	vecColorKeyEnable;
        std::vector<unsigned int>	vecColorKey;

        for (int i = 0; i < Count; ++i)
        {
            bool	ColorKeyEnable = false;
            unsigned int ColorKey = 0;

            fread(&ColorKeyEnable, sizeof(bool), 1, _pFile);
            fread(&ColorKey, sizeof(unsigned int), 1, _pFile);

            vecColorKeyEnable.push_back(ColorKeyEnable);
            vecColorKey.push_back(ColorKey);

            int	NameCount = 0;
            fread(&NameCount, sizeof(int), 1, _pFile);

            TCHAR	FileName[MAX_PATH] = {};

            fread(&FileName, sizeof(TCHAR), NameCount, _pFile);

            vecFileName.push_back(FileName);
        }

        _pScene->getSceneResource()->loadTexture(wName, vecFileName);

        for (int i = 0; i < Count; ++i)
        {
            if (!vecColorKeyEnable[i])
                continue;

            _pScene->getSceneResource()->setTextureColorKey(wName, vecColorKey[i]);
        }

        Result = _pScene->getSceneResource()->findTexture(wName);
    }
    */
    delete[] wcstring;
    return Result;
}
