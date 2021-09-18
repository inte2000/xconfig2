#include "framework.h"
#include "XConfig.h"
#include "XVisitor.h"
#ifdef _SUPPORT_JSON
#include "JsonStorage.h"
#include "string_encode.h"

void EnumJsonSectionObject(const std::string& secName, const rapidjson::Value& sessionObj, XConfig& cfg)
{
    for (auto objIt = sessionObj.Begin(); objIt != sessionObj.End(); ++objIt)
    {
        const rapidjson::Value& field = *objIt;
        for (auto attrIt = field.MemberBegin(); attrIt != field.MemberEnd(); ++attrIt)
        {
            std::string attrname = attrIt->name.GetString();
            std::string attrvalue = attrIt->value.GetString();

            cfg.SetStringAttr(secName, attrname, attrvalue);
        }
    }
}

bool JsonStorage::LoadConfig(const std::string& position, XConfig& cfg)
{
    try
    {
        std::ifstream jsonFile(position);
        std::string json_content((std::istreambuf_iterator<char>(jsonFile)), std::istreambuf_iterator<char>());
        jsonFile.close();

        rapidjson::Document dom;
        if (dom.Parse(json_content.c_str()).HasParseError())
            throw "file paser error!";
        if (!dom.HasMember("Config") || !dom["Config"].IsArray())
            throw "config file format error!";

        const rapidjson::Value& config = dom["Config"];
        for (auto objIt = config.Begin(); objIt != config.End(); ++objIt)
        {
            const rapidjson::Value& field = *objIt;
            for (auto secIt = field.MemberBegin(); secIt != field.MemberEnd(); ++secIt)
            {
                std::string secname = secIt->name.GetString();
                EnumJsonSectionObject(secname, secIt->value, cfg);
            }
        }
                    
        return true;
    }
    catch (...)
    {
        return false;
    }
}

class JsonVisitor : public XVisitor
{
public:
    JsonVisitor(rapidjson::Writer<rapidjson::StringBuffer>& writer) : m_writer(writer)
    {
    }
    void OnSectionBegin(const std::string& section)
    {
        m_writer.StartObject();
        m_writer.Key(section.c_str());
        m_writer.StartArray();
    }

    void OnSectionEnd(const std::string& section)
    {
        m_writer.EndArray();
        m_writer.EndObject();
    }

    void OnAttribute(const std::string& attr, const std::string& value)
    {
        m_writer.StartObject();
        m_writer.Key(attr.c_str());
        m_writer.String(value.c_str());
        m_writer.EndObject();
    }
protected:
    rapidjson::Writer<rapidjson::StringBuffer>& m_writer;
};

bool JsonStorage::SaveConfig(const std::string& position, const XConfig& cfg)
{
    try
    {
        rapidjson::StringBuffer strBuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strBuf);
        writer.StartObject();

        writer.Key("Config");
        writer.StartArray();
        JsonVisitor visitor(writer);
        cfg.Travel(visitor);
        writer.EndArray();

        writer.EndObject();
        std::fstream outFile(position, std::fstream::out | std::fstream::trunc);
        outFile << strBuf.GetString();

        return true;
    }
    catch (...)
    {
        return false;
    }
}
#endif  //_SUPPORT_JSON

