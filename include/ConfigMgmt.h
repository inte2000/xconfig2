#pragma once

#include <string>
#include "XConfig.h"
#include "modules.h"

#if _SUPPORT_INI
#include "IniStorage.h"
#endif

#if _SUPPORT_XML
#include "XmlStorage.h"
#endif

class ConfigMgmt
{

public:
    ConfigMgmt() 
    { 
        m_Storege = nullptr; 
    }
    ConfigMgmt(XStorage* Storege, const std::string& position)
    { 
        m_Storege = Storege; 
        m_position = position;
    }
    virtual ~ConfigMgmt()
    {
        if (m_Storege)
            delete m_Storege;
    }

    void SetPosition(const std::string& position) { m_position = position; }
    bool SwitchStorage(XStorage* Storege);
    bool LoadConfig(XConfig& cfg);
    bool SaveConfig(const XConfig& cfg);

protected:
    std::string m_position;
    XStorage *m_Storege;
};

template <class storage>
bool LoadConfig(const std::string& position, XConfig& cfg)
{
    ConfigMgmt mgmt(new storage, position);
    return mgmt.LoadConfig(cfg);
}

template <class storage>
bool SaveConfig(const std::string& position, const XConfig& cfg)
{
    ConfigMgmt mgmt(new storage, position);
    return mgmt.SaveConfig(cfg);
}
