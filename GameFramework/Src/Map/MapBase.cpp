
#include "../GameInfo.h"
#include "MapBase.h"
#include "../Scene/Scene.h"
#include "../PathManager.h"

MapBase::MapBase()
    : m_pOwnerScene(nullptr)
    , m_strName{}
    , m_vPos{}
    , m_vScale{}
    , m_nZOrder(0)
    , m_bEnable(true)
    , m_bActive(true)
{
}

MapBase::~MapBase()
{
}

bool MapBase::init()
{
    return true;
}

void MapBase::update()
{
}

void MapBase::postUpdate()
{
}

void MapBase::preRender()
{
}

void MapBase::render(HDC _hDC)
{
}

void MapBase::start()
{
}

void MapBase::saveFile(const char* _strFileName, const wstring& _strPath)
{
    char	FullPath[MAX_PATH] = {};

    const PathInfo* Info = PathManager::getInst()->findPath(_strPath);

    if (Info)
        strcpy_s(FullPath, Info->m_strMulPath);
    strcat_s(FullPath, _strFileName);

    saveFullPath(FullPath);
}

void MapBase::loadFile(const char* _strFileName, const wstring& _strPath)
{
    char	FullPath[MAX_PATH] = {};

    const PathInfo* Info = PathManager::getInst()->findPath(_strPath);

    if (Info)
        strcpy_s(FullPath, Info->m_strMulPath);
    strcat_s(FullPath, _strFileName);

    loadFullPath(FullPath);
}

void MapBase::save(FILE* _pFile)
{
    int	Length = (int)m_strName.size();

    fwrite(&Length, sizeof(int), 1, _pFile);
    fwrite(m_strName.c_str(), sizeof(char), Length, _pFile);

    fwrite(&m_vPos, sizeof(Vec), 1, _pFile);
    fwrite(&m_vScale, sizeof(Vec), 1, _pFile);

    fwrite(&m_nZOrder, sizeof(int), 1, _pFile);
    fwrite(&m_bEnable, sizeof(bool), 1, _pFile);
    fwrite(&m_bActive, sizeof(bool), 1, _pFile);
}

void MapBase::load(FILE* _pFile)
{
    int	Length = 0;
    char	Name[256] = {};

    fread(&Length, sizeof(int), 1, _pFile);
    fread(Name, sizeof(char), Length, _pFile);

    wchar_t* wcstring = new wchar_t[256];
    size_t num;
    mbstowcs_s(&num, wcstring, 256, Name, 256);
    m_strName = wcstring;
    delete[] wcstring;

    fread(&m_vPos, sizeof(Vec), 1, _pFile);
    fread(&m_vScale, sizeof(Vec), 1, _pFile);

    fread(&m_nZOrder, sizeof(int), 1, _pFile);
    fread(&m_bEnable, sizeof(bool), 1, _pFile);
    fread(&m_bActive, sizeof(bool), 1, _pFile);
}

void MapBase::saveFullPath(const char* _strFileName)
{
    FILE* pFile = nullptr;

    fopen_s(&pFile, _strFileName, "wb");

    if (!pFile)
        return;

    save(pFile);

    fclose(pFile);
}

void MapBase::loadFullPath(const char* _strFileName)
{
    FILE* pFile = nullptr;

    fopen_s(&pFile, _strFileName, "rb");

    if (!pFile)
        return;

    load(pFile);

    fclose(pFile);
}
