// PathManager.h

#pragma once

struct PathInfo
{
    TCHAR m_strUniPath[MAX_PATH];
    char  m_strMulPath[MAX_PATH];

    PathInfo()
        : m_strUniPath{}
        , m_strMulPath{}
    {}
};

class PathManager
{
    SINGLETON(PathManager);

public:
    bool init();
    const PathInfo* findPath(const wstring& _strName);
    bool addPath(const wstring& _strName, const TCHAR* _strUniPath,
        const wstring& _strBasePath = ROOT_PATH);
 
private:
    unordered_map<wstring, PathInfo*> m_mapPath;

};

