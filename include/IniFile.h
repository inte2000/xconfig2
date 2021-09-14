#pragma once

#include <string>
#include <vector>
#include <fstream>

class IniFile final
{
public:
    IniFile(const std::string& filename)
    {
        OpenFile(filename);
    }
    IniFile()
    {
        m_valid = false;
    }
    ~IniFile()
    {
    }

    bool Valid() const { return m_valid; }
    std::size_t GetLineCount() const { return m_iniLines.size(); }
    bool OpenFile(const std::string& filename);
    bool SaveFile(const std::string& filename);
    std::string GetLine(std::size_t line) const;
    bool SetLine(std::size_t line, const std::string& content);
    void AppendLine(const std::string& content);
protected:
    bool m_valid;
    std::vector<std::string> m_iniLines;
};

