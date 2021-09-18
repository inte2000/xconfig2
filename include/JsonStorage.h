#pragma once

#include <string>
#include "XStorage.h"

#ifdef _SUPPORT_JSON

class JsonStorage: public XStorage
{
public:
    virtual bool LoadConfig(const std::string& position, XConfig& cfg);
    virtual bool SaveConfig(const std::string& position, const XConfig& cfg);

protected:
};

#endif //_SUPPORT_JSON