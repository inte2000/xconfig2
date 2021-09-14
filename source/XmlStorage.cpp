#ifdef _SUPPORT_XML
#include "framework.h"
#include "XConfig.h"
#include "XVisitor.h"
#include "XmlStorage.h"
#include "string_encode.h"

bool XmlStorage::LoadConfig(const std::string& position, XConfig& cfg)
{
    try
    {
        rapidxml::file<> xmlFile(position.c_str());
        rapidxml::xml_document<> doc;
        doc.parse<0>(xmlFile.data());

        rapidxml::xml_node<>* root = doc.first_node();
        if (std::strcmp(root->name(), "config") != 0)
            throw "invalid config file format!";
        rapidxml::xml_node<>* section = root->first_node();
        while (section != nullptr)
        {
            std::string sectionName = section->name();
            rapidxml::xml_node<>* attr = section->first_node();
            while (attr != nullptr)
            {
                std::string attrName = attr->name();
                std::string attrValue = attr->value();
                cfg.SetStringAttr(sectionName, attrName, attrValue);

                attr = attr->next_sibling();
            }

            section = section->next_sibling();
        }

        return true;
    }
    catch(rapidxml::parse_error& e)
    {
        return false;
    }
    catch (...)
    {
        return false;
    }
}

class XmlVisitor : public XVisitor
{
public:
    XmlVisitor(rapidxml::xml_document<>& doc) : m_doc(doc)
    {
        m_curSection = nullptr;
    }
    void OnSectionBegin(const std::string& section)
    {
        rapidxml::xml_node<>* root = m_doc.first_node();
        m_curSection = m_doc.allocate_node(rapidxml::node_element, section.c_str(), nullptr);
        root->append_node(m_curSection);
    }

    void OnSectionEnd(const std::string& section)
    {
        m_curSection = nullptr;
    }

    void OnAttribute(const std::string& attr, const std::string& value)
    {
        if (m_curSection != nullptr)
        {
            rapidxml::xml_node<>* attrNode = m_doc.allocate_node(rapidxml::node_element, attr.c_str(), value.c_str());
            m_curSection->append_node(attrNode);
        }
    }
protected:
    rapidxml::xml_document<>& m_doc;
    rapidxml::xml_node<>* m_curSection;
};

bool XmlStorage::SaveConfig(const std::string& position, const XConfig& cfg)
{
    try
    {
        rapidxml::xml_document<> doc;
        rapidxml::xml_node<>* frot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
        doc.append_node(frot);
        rapidxml::xml_node<>* root = doc.allocate_node(rapidxml::node_element, "config", nullptr);
        doc.append_node(root);

        XmlVisitor visitor(doc);
    
        cfg.Travel(visitor);

        std::fstream outFile(position, std::fstream::out | std::fstream::trunc);
        outFile << doc;

        return true;
    }
    catch (rapidxml::parse_error& e)
    {
        return false;
    }
    catch (...)
    {
        return false;
    }
}
#endif

