#include "stdafx.h"
#include "IniFile.h"


bool IniFile::OpenFile(const std::string& filename)
{
    m_iniLines.clear();
    m_valid = false;
    std::fstream txtFile;
    txtFile.open(filename, std::fstream::in);
    if (!txtFile)
        return false;

    while (!txtFile.eof())
    {
        std::string content;
        std::getline(txtFile, content);
        boost::algorithm::trim_left(content);
        boost::algorithm::trim_right(content);
        m_iniLines.push_back(content);
    }

    m_valid = true;
    return true;
}

bool IniFile::SaveFile(const std::string& filename)
{
    std::fstream txtFile(filename, std::fstream::out | std::fstream::trunc);
    if (!txtFile)
        return false;

    for (auto& line : m_iniLines)
    {
        txtFile << line << std::endl;
    }

    return true;
}

std::string IniFile::GetLine(std::size_t line) const
{
    if ((line >= 0) && (line < m_iniLines.size()))
        return m_iniLines[line];

    return "";
}

bool IniFile::SetLine(std::size_t line, const std::string& content)
{
    if ((line >= 0) && (line < m_iniLines.size()))
    {
        m_iniLines[line] = content;
        return true;
    }

    return false;
}

void IniFile::AppendLine(const std::string& content)
{
    m_iniLines.push_back(content);
}
