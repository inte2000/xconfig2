#include "framework.h"
#include "ConfigMgmt.h"

bool ConfigMgmt::SwitchStorage(XStorage* Storege)
{
    if (Storege == nullptr)
        return false;

    if (m_Storege != nullptr)
        delete m_Storege;

    m_Storege = Storege;

    return true;
}

bool ConfigMgmt::LoadConfig(XConfig& cfg)
{
    if ((m_Storege == nullptr) || m_position.empty())
        return false;

    return m_Storege->LoadConfig(m_position, cfg);
}

bool ConfigMgmt::SaveConfig(const XConfig& cfg)
{
    if ((m_Storege == nullptr) || m_position.empty())
        return false;

    return m_Storege->SaveConfig(m_position, cfg);
}
