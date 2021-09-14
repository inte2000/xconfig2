#include "stdafx.h"
#include <sstream>
#include "XConfig.h"

void XConfig::Travel(XVisitor& visitor) const
{
    for (auto& sec : m_AttrMap)
    {
        visitor.OnSectionBegin(sec.first);
        for (auto& attr : sec.second.attrs)
        {
            visitor.OnAttribute(attr.first, attr.second);
        }
        visitor.OnSectionEnd(sec.first);
    }
}

bool XConfig::GetBoolAttr(const std::string& section, const std::string& attr, bool default) const
{
    auto secIt = m_AttrMap.find(section);
    if (secIt == m_AttrMap.end())
        return default;

    auto rtn = secIt->second.GetAttr(attr);
    if(rtn.first)
        return (rtn.second == "true") ? true : false;

    return default;
}

void XConfig::SetBoolAttr(const std::string & section, const std::string & attr, bool value)
{
    auto& sec = m_AttrMap[section];
    if (sec.name.empty())
        sec.name = section;

    sec.SetAttr(attr, value ? "true" : "false");
}

int XConfig::GetIntegerAttr(const std::string & section, const std::string & attr, int default) const
{
    auto secIt = m_AttrMap.find(section);
    if (secIt == m_AttrMap.end())
        return default;

    auto rtn = secIt->second.GetAttr(attr);
    if (rtn.first)
        return std::atoi(rtn.second.c_str());

    return default;
}

void XConfig::SetIntegerAttr(const std::string & section, const std::string & attr, int value)
{
    auto& sec = m_AttrMap[section];
    if (sec.name.empty())
        sec.name = section;

    std::stringstream ss;
    ss << value;
    sec.SetAttr(attr, ss.str());
}

// ^#([0-9a-fA-F]{6}|[0-9a-fA-F]{6})$  
// Æ¥Åä #9844F3
// /^[rR][gG][Bb][Aa]?[\(]([\s]*(2[0-4][0-9]|25[0-5]|[01]?[0-9][0-9]?),){2}[\s]*(2[0-4][0-9]|25[0-5]|[01]?[0-9][0-9]?),?[\s]*(0\.\d{1,2}|1|0)?[\)]{1}$/g
// Æ¥Åä rgba(5,56,34,0.81)
//^[rR][gG][Bb][\(]((?:(?:25[0-5]|2[0-4]\d|[01]?\d?\d)\,){2}(?:25[0-5]|2[0-4]\d|[01]?\d?\d))[\)]$
COLORREF XConfig::GetColorAttr(const std::string & section, const std::string & attr, COLORREF default) const
{
    auto secIt = m_AttrMap.find(section);
    if (secIt == m_AttrMap.end())
        return default;

    auto rtn = secIt->second.GetAttr(attr);
    if (rtn.first)
    {
        std::regex re("^[rR][gG][Bb][\\(]((?:(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d)\\,){2}(?:25[0-5]|2[0-4]\\d|[01]?\\d?\\d))[\\)]$");
        std::smatch m;
        auto ret = std::regex_match(rtn.second, m, re);
        if (ret)
        {
            return RGB(0,0,0);
        }
    }

    return default;
}

void XConfig::SetColorAttr(const std::string & section, const std::string & attr, COLORREF value)
{
    auto& sec = m_AttrMap[section];
    if (sec.name.empty())
        sec.name = section;

    std::stringstream ss;
    ss << "(" << GetRValue(value) << "," << GetGValue(value) << "," << GetBValue(value) << ")";
    sec.SetAttr(attr, ss.str());
}

std::string XConfig::GetStringAttr(const std::string & section, const std::string & attr) const
{
    auto secIt = m_AttrMap.find(section);
    if (secIt == m_AttrMap.end())
        return "";

    auto rtn = secIt->second.GetAttr(attr);
    if (rtn.first)
        return rtn.second;

    return "";
}

void XConfig::SetStringAttr(const std::string & section, const std::string & attr, const std::string & value)
{
    auto& sec = m_AttrMap[section];
    if (sec.name.empty())
        sec.name = section;

    sec.SetAttr(attr, value);
}

double XConfig::GetFloatAttr(const std::string & section, const std::string & attr, double default) const
{
    auto secIt = m_AttrMap.find(section);
    if (secIt == m_AttrMap.end())
        return default;

    auto rtn = secIt->second.GetAttr(attr);
    if (rtn.first)
        return std::atof(rtn.second.c_str());

    return default;
}

void XConfig::SetFloatAttr(const std::string & section, const std::string & attr, double value)
{
    auto& sec = m_AttrMap[section];
    if (sec.name.empty())
        sec.name = section;

    std::stringstream ss;
    ss << value;
    sec.SetAttr(attr, ss.str());
}

