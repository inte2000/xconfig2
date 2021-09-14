#pragma once

#include <string>

class XConfig;

class XStorage
{
public:
    virtual bool LoadConfig(const std::string& position, XConfig& cfg) = 0;
    virtual bool SaveConfig(const std::string& position, const XConfig& cfg) = 0;
};

