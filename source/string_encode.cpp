#include "iconv.h"
#include "localcharset.h"
#include "string_encode.h"

std::string GetLocaleCharset()
{
    std::string tmp = locale_charset();
    return std::move(tmp);
}

#define INNER_BUF_SIZE   256
int TransEncoding(const char* fromEncoding, const char* toEncoding, const std::string& input, std::string& output)
{
    char szTmp[INNER_BUF_SIZE] = { 0 };
    const char* pSource = input.c_str();
    char* pTmp = szTmp;
    std::size_t outRemain = INNER_BUF_SIZE;
    std::size_t inRemain = input.length();
    int trans = 0;

    iconv_t cd = iconv_open(toEncoding, fromEncoding);
    if (reinterpret_cast<unsigned long long>(cd) == 0xFFFFFFFF)
        return 0;

    while (inRemain > 0)
    {
        iconv(cd, &pSource, &inRemain, &pTmp, &outRemain);
        if (outRemain == INNER_BUF_SIZE)
            break;

        output.append(szTmp, 0, INNER_BUF_SIZE - outRemain);
        trans += (INNER_BUF_SIZE - outRemain);
        pTmp = szTmp;
        memset(szTmp, 0, INNER_BUF_SIZE);
        outRemain = INNER_BUF_SIZE;
    }
    iconv_close(cd);

    return trans;
}

int LocalCharsetToUTF8(const std::string& input, std::string& output)
{
    std::string lcharset = GetLocaleCharset();

    return TransEncoding(lcharset.c_str(), "utf-8", input, output);
}

int UTF8ToLocalCharset(const std::string& input, std::string& output)
{
    std::string lcharset = GetLocaleCharset();

    return TransEncoding("utf-8", lcharset.c_str(), input, output);
}

//For windows, wchar_t is 16-bit type using a little-endian UTF-16
//For linux, wchar_t is 32-bit type in the system's native endianness
int LocalCharsetToWcharT(const std::string& input, std::wstring& output)
{
    char szTmp[INNER_BUF_SIZE] = { 0 };
    const char* pSource = input.c_str();
    char* pTmp = szTmp;
    std::size_t outRemain = INNER_BUF_SIZE;
    std::size_t inRemain = input.length();
    int trans = 0;

    iconv_t cd = iconv_open("UCS-2LE", GetLocaleCharset().c_str());
    if (reinterpret_cast<unsigned long long>(cd) == 0xFFFFFFFF)
        return 0;

    while (inRemain > 0)
    {
        iconv(cd, &pSource, &inRemain, &pTmp, &outRemain);
        if (outRemain == INNER_BUF_SIZE)
            break;

        output.append((wchar_t*)szTmp, 0, (INNER_BUF_SIZE - outRemain)/2);
        trans += (INNER_BUF_SIZE - outRemain) / 2;
        pTmp = szTmp;
        memset(szTmp, 0, INNER_BUF_SIZE);
        outRemain = INNER_BUF_SIZE;
    }
    iconv_close(cd);

    return trans;
}

int WcharTToLocalCharset(const std::wstring& input, std::string& output)
{
    char szTmp[INNER_BUF_SIZE] = { 0 };
    const char* pSource = (const char*)input.c_str();
    char* pTmp = szTmp;
    std::size_t outRemain = INNER_BUF_SIZE;
    std::size_t inRemain = input.length() * sizeof(wchar_t);
    int trans = 0;

    iconv_t cd = iconv_open(GetLocaleCharset().c_str(), "UCS-2LE");
    if (reinterpret_cast<unsigned long long>(cd) == 0xFFFFFFFF)
        return 0;

    while (inRemain > 0)
    {
        iconv(cd, &pSource, &inRemain, &pTmp, &outRemain);
        if (outRemain == INNER_BUF_SIZE)
            break;

        output.append(szTmp, 0, INNER_BUF_SIZE - outRemain);
        trans += (INNER_BUF_SIZE - outRemain);
        pTmp = szTmp;
        memset(szTmp, 0, INNER_BUF_SIZE);
        outRemain = INNER_BUF_SIZE;
    }
    iconv_close(cd);

    return trans;
}
