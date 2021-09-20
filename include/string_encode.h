#pragma once

#include <string>


int LocalCharsetToUTF8(const std::string& input, std::string& output);
int UTF8ToLocalCharset(const std::string& input, std::string& output);

[[nodiscard]]
inline std::string LocalCharsetFromUTF8(const std::string& input)
{
    std::string output;
    UTF8ToLocalCharset(input, output);
    return std::move(output);
}

[[nodiscard]]
inline std::string UTF8FromLocalCharset(const std::string& input)
{
    std::string output;
    LocalCharsetToUTF8(input, output);
    return std::move(output);
}

int LocalCharsetToWcharT(const std::string& input, std::wstring& output);
int WcharTToLocalCharset(const std::wstring& input, std::string& output);

[[nodiscard]]
inline std::string LocalCharsetFromWcharT(const std::wstring& input)
{
    std::string output;
    WcharTToLocalCharset(input, output);
    return std::move(output);
}

[[nodiscard]]
inline std::wstring WcharTFromLocalCharset(const std::string& input)
{
    std::wstring output;
    LocalCharsetToWcharT(input, output);
    return std::move(output);
}
