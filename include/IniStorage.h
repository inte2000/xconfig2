#pragma once

#include <string>
#include "XStorage.h"

#if _SUPPORT_INI

class IniStorage: public XStorage
{
public:
    virtual bool LoadConfig(const std::string& position, XConfig& cfg);
    virtual bool SaveConfig(const std::string& position, const XConfig& cfg);

protected:
    bool IsSection(const std::string& line);
    bool GetSectionName(const std::string& line, std::string& name);
    bool IsAttribute(const std::string& line);
    bool GetAttribute(const std::string& line, std::string& attr, std::string& value);
};
#endif
