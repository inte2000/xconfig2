#pragma once

#include <string>

class XVisitor
{
public:
    virtual void OnSectionBegin(const std::string& section) = 0;
    virtual void OnSectionEnd(const std::string& section) = 0;
    virtual void OnAttribute(const std::string& attr, const std::string& value) = 0;
};

