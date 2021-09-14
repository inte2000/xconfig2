#pragma once

#include <string>
#include <map>
#include "XVisitor.h"

struct XSection
{
    std::string name;
    std::map<std::string, std::string> attrs;

    std::pair<bool, std::string> GetAttr(const std::string& attr) const
    {
        auto it = attrs.find(attr);
        if (it == attrs.end())
            return { false, "" };
        else
            return { true, it->second };
    }
    void SetAttr(const std::string& attr, const std::string& value)
    {
        attrs[attr] = value;
    }
};

class XConfig
{
public:
    XConfig() {}
    virtual ~XConfig() {}
    void Travel(XVisitor& visitor) const;

    bool GetBoolAttr(const std::string& section, const std::string& attr, bool defValue = false) const;
    void SetBoolAttr(const std::string& section, const std::string& attr, bool value);
    int GetIntegerAttr(const std::string& section, const std::string& attr, int defValue = 0) const;
    void SetIntegerAttr(const std::string& section, const std::string& attr, int value);
#ifdef _WINDOWS
    COLORREF GetColorAttr(const std::string& section, const std::string& attr, COLORREF defValue = RGB(0, 0, 0)) const;
    void SetColorAttr(const std::string& section, const std::string& attr, COLORREF value);
#endif   
    std::string GetStringAttr(const std::string& section, const std::string& attr) const;
    void SetStringAttr(const std::string& section, const std::string& attr, const std::string& value);
    double GetFloatAttr(const std::string& section, const std::string& attr, double defValue = 0.0) const;
    void SetFloatAttr(const std::string& section, const std::string& attr, double value);

protected:
    bool GetAttr(const std::string& attr, std::string& value);
    std::map<std::string, XSection> m_AttrMap;
};

