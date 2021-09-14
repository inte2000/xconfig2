#pragma once

#include <string>

int GBKToUTF8(const std::string& input, std::string& output);
int UTF8ToGBK(const std::string& input, std::string& output);

[[nodiscard]]
inline std::string UTF8FromGBK(const std::string& input)
{
    std::string output;
    GBKToUTF8(input, output);
    return std::move(output);
}

[[nodiscard]]
inline std::string GBKFromUTF8(const std::string& input)
{
    std::string output;
    UTF8ToGBK(input, output);
    return std::move(output);
}

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
