#include "framework.h"
#include "XConfig.h"
#include "XVisitor.h"
#ifdef _SUPPORT_REGISTRY
#include "RegistryStorage.h"
#include "string_encode.h"
#include "WzRegKey.h"

typedef std::basic_string<TCHAR> TString;

TString TStringFromString(const std::string& ansiString)
{
    TString s;
#ifdef UNICODE
    std::wstring tmp = WcharTFromLocalCharset(ansiString);
    s = tmp.c_str();
#else
    s = ansiString;
#endif
    return std::move(s);
}

std::string StringFromTString(const TString& tstring)
{
    std::string s;
#ifdef UNICODE
    s = LocalCharsetFromWcharT(std::wstring(tstring.c_str()));
#else
    s = tstring;
#endif

    return std::move(s);
}

bool RegistryStorage::LoadConfig(const std::string& position, XConfig& cfg)
{
    TString keyPath = TStringFromString(position) + _T("\\Config");
    CWzRegKey regKey(HKEY_CURRENT_USER, keyPath.c_str(), KEY_WRITE | KEY_READ);
    if (!regKey.IsValid())
        return false;

    DWORD dwKeyIndex = 0;
    TCHAR szSessionKeyName[128] = { 0 };
    DWORD SessionKeyNameLen = 128;
    while (regKey.EnumSubKey(dwKeyIndex, szSessionKeyName, &SessionKeyNameLen, NULL, NULL, NULL) == ERROR_SUCCESS)
    {
        dwKeyIndex++;
        SessionKeyNameLen = 128;
        std::string session = StringFromTString(TString(szSessionKeyName));
        CWzRegKey sessionKey;
        if (sessionKey.OpenKey(regKey, szSessionKeyName, KEY_WRITE | KEY_READ) == ERROR_SUCCESS)
        {
            DWORD dwValueIndex = 0;
            TCHAR szValueName[128] = { 0 };
            DWORD valueType;
            DWORD ValueNameLen = 128;
            TCHAR szData[512] = { 0 };
            DWORD dataBifSize = 512;
            while (sessionKey.EnumValue(dwValueIndex, szValueName, &ValueNameLen, &valueType, (LPBYTE)szData, &dataBifSize) == ERROR_SUCCESS)
            {
                std::string valuename = StringFromTString(TString(szValueName));
                std::string value = StringFromTString(TString(szData));
                cfg.SetStringAttr(session, valuename, value);
                dwValueIndex++;
                ValueNameLen = 128;
                dataBifSize = 512;
            }
        }
        sessionKey.CloseKey();
    }

    return true;
}

class RegistryVisitor : public XVisitor
{
public:
    RegistryVisitor(CWzRegKey& configKey) : m_configKey(configKey)
    {
    }
    void OnSectionBegin(const std::string& section)
    {
        TString sessionKeyName = TStringFromString(section);
        m_sessionKey.CreateKey(m_configKey, sessionKeyName.c_str(), KEY_WRITE | KEY_READ);
    }

    void OnSectionEnd(const std::string& section)
    {
        m_sessionKey.CloseKey();
    }

    void OnAttribute(const std::string& attr, const std::string& value)
    {
        TString valueName = TStringFromString(attr);
        TString valueData = TStringFromString(value);
        m_sessionKey.SetString(valueName.c_str(), valueData.c_str());
    }

protected:
    CWzRegKey& m_configKey;
    CWzRegKey m_sessionKey;
};

bool RegistryStorage::SaveConfig(const std::string& position, const XConfig& cfg)
{
    TString keyPath = TStringFromString(position) + _T("\\Config");
    CWzRegKey regKey(HKEY_CURRENT_USER, keyPath.c_str(), KEY_WRITE | KEY_READ);
    if (!regKey.IsValid())
        return false;

    RegistryVisitor visitor(regKey);
    cfg.Travel(visitor);
    
    regKey.CloseKey();

    return true;
}
#endif  //_SUPPORT_REGISTRY

