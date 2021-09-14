#include <fstream>
#include <sstream>
/*
std::pair<bool, std::string> LoadJsonFile(const std::string& filename, Json::Value& root)
{
    try
    {
        std::ifstream inf(filename); 
        if(inf.fail())
            return { false, "std::ifstream fail to open read file!" };
        
        Json::CharReaderBuilder builder;
        builder["collectComments"] = true;
        JSONCPP_STRING errs;
        if (!parseFromStream(builder, inf, &root, &errs)) 
        {
            return {false, "Parse error code: " + errs };
        }
    }
    catch (...)
    {
        return { false, "Read json file got an unknown exception!" };
    }

    return { true, "" };
}

std::pair<bool, std::string> SaveJsonFile(const std::string& filename, const Json::Value& root)
{
    try
    {
        std::ofstream outf(filename);
        if (outf.fail())
            return { false, "std::ofstream fail to open write file!" };

        Json::StreamWriterBuilder builder;
        const std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
        writer->write(root, &outf);

        outf.close();
    }
    catch (...)
    {
        return { false, "Write json file got an unknown exception!" };
    }

    return { true, "" };
}
*/