// PathManager.cpp

#include "GameInfo.h"
#include "PathManager.h"

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
    auto    iter = m_mapPath.begin();
    auto    iterEnd = m_mapPath.end();

    for (; iter != iterEnd; ++iter)
    {
        SAFE_DELETE(iter->second);
    }
}

bool PathManager::init()
{
    TCHAR   Path[MAX_PATH] = {};

    GetModuleFileName(0, Path, MAX_PATH);

    int nLength = lstrlen(Path);

    for (int i = nLength - 1; i > 0; --i)
    {
        if (Path[i] == '\\')
        {
            memset(&Path[i + 1], 0, sizeof(TCHAR) * (nLength - i - 1));
            break;
        }
    }

    PathInfo* Info = new PathInfo;

    lstrcpy(Info->m_strUniPath, Path);

#ifdef UNICODE
    int ConvertLength = WideCharToMultiByte(CP_ACP, 0, Path, -1, nullptr, 0, 0, 0);

    WideCharToMultiByte(CP_ACP, 0, Path, -1,
        Info->m_strMulPath, ConvertLength, 0, 0);
#else
    strcpy_s(Info->PathMultibyte, Path);
#endif 

    m_mapPath.insert(std::make_pair(ROOT_PATH, Info));

    addPath(TEXTURE_PATH, TEXT("Texture\\"));
    addPath(SOUND_PATH, TEXT("Sound\\"));
    addPath(FONT_PATH, TEXT("Font\\"));
    addPath(MAP_PATH, TEXT("Map\\"));
    addPath(MOUSE_PATH, TEXT("Texture\\Mouse\\"));
    addPath(MENU_PATH, TEXT("Texture\\Menu\\"));
    addPath(L"BulletBlueIdle", TEXT("Texture\\Bullet\\Blue\\"));
    addPath(L"ButtonPath", TEXT("Texture\\Button\\"));

    return true;
}

const PathInfo* PathManager::findPath(const wstring& _strPath)
{
    auto iter = m_mapPath.find(_strPath);

    if (m_mapPath.end() == iter)
    {
        return nullptr;
    }

    return iter->second;
}

bool PathManager::addPath(const wstring& _strName, const TCHAR* _strUniPath, const wstring& _strBasePath)
{
    if (findPath(_strName))
    {
        return false;
    }
        
    const PathInfo* BaseInfo = findPath(_strBasePath);

    if (!BaseInfo)
        return false;

    PathInfo* Info = new PathInfo;

    lstrcpy(Info->m_strUniPath, BaseInfo->m_strUniPath);
    lstrcat(Info->m_strUniPath, _strUniPath);

#ifdef UNICODE
    int ConvertLength = WideCharToMultiByte(CP_ACP, 0, Info->m_strUniPath, -1, nullptr, 0, 0, 0);

    WideCharToMultiByte(CP_ACP, 0, Info->m_strUniPath, -1,
        Info->m_strMulPath, ConvertLength, 0, 0);
#else
    strcpy_s(Info->PathMultibyte, Info->Path);
#endif

    m_mapPath.insert(std::make_pair(_strName, Info));

    return true;
}
