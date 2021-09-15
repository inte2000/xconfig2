#include "framework.h"
#include "XConfig.h"
#include "XVisitor.h"

#if _SUPPORT_INI
#include "IniStorage.h"
#include "IniFile.h"


bool IniStorage::LoadConfig(const std::string& position, XConfig& cfg)
{
    IniFile ini(position);
    if (!ini.Valid())
        return false;

    std::string section = "Global";
    for (std::size_t i = 0; i < ini.GetLineCount(); i++)
    {
        std::string line = ini.GetLine(i);
        if (IsSection(line))
        {
            GetSectionName(line, section);
        }
        else if (IsAttribute(line))
        {
            std::string attr, value;
            if (GetAttribute(line, attr, value))
            {
                cfg.SetStringAttr(section, attr, value);
            }
        }
        else
        {
        }
    }
    return true;
}

class IniVisitor : public XVisitor
{
public:
    IniVisitor(IniFile& ini) : m_ini(ini)
    {
    }
    void OnSectionBegin(const std::string& section)
    {
        m_ini.AppendLine("[" + section + "]");
    }

    void OnSectionEnd(const std::string& section)
    {
        m_ini.AppendLine("");
    }

    void OnAttribute(const std::string& attr, const std::string& value)
    {
        m_ini.AppendLine(attr + " = " + value);
    }
protected:
    IniFile& m_ini;
};

bool IniStorage::SaveConfig(const std::string& position, const XConfig& cfg)
{
    IniFile ini;
    IniVisitor visitor(ini);
    
    cfg.Travel(visitor);

    return ini.SaveFile(position);
}

bool IniStorage::IsSection(const std::string& line)
{
    if (line.length() > 3 && (line[0] == '[') && (line[line.length() - 1] == ']'))
        return true;

    return false;
}

bool IniStorage::GetSectionName(const std::string& line, std::string& name)
{
    if (IsSection(line))
    {
        name = line.substr(1, line.size() - 2);
        return true;
    }

    return false;
}

bool IniStorage::IsAttribute(const std::string& line)
{
    if (std::count_if(line.begin(), line.end(), [](char c) { return (c == '='); }) == 1)
        return true;

    return false;
}

bool IniStorage::GetAttribute(const std::string& line, std::string& attr, std::string& value)
{
    std::size_t pos = line.find('=', 0);
    if (pos != std::string::npos)
    {
        attr = line.substr(0, pos);
        boost::algorithm::trim_right(attr);
        value = line.substr(pos + 1, -1);
        boost::algorithm::trim_left(value);

        return true;
    }

    return false;
}
#endif
