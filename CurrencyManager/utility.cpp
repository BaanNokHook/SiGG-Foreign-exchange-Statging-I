/**
 * @file utility.cpp
 * @author SiGG (Project::SiGG-Foreign exchange-Statging-I)
 * @brief 
 * @version 0.1
 * @date 2022-12-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "utility.hpp"

namespace Utility
{
    static const std::string path {"/home/chaginsergey/Downloads/"};

    const string loadDocument(const string& file_name)
    {
        ifstream ifile;
        ifile.open(file_name);

        if(!ifile)
        {
            qDebug() <<"Cannot open file: "<<file_name.c_str()<<Qt::endl;
            return "";
        }

        string doc, line;

        while(getline(ifile, line))
            doc+=line;

        return doc;
    }

    bool saveDocument(const std::string& filename, const std::string& data)
    {
        std::ofstream ofile(filename);
        if (!ofile) { qDebug() << "Cannot open file"<<Qt::endl; return false; }
        ofile << data;
        ofile.close();
        return true;

    }

    const std::string parseDataFromPage(const std::string& where, const std::string& lstr, const std::string& rstr, bool with_left)
    {
        size_t lpos{}, rpos{};
        std::string ret_val;

        if ((where.find(lstr) == std::string::npos) || (where.find(rstr) == std::string::npos))
        {
            qDebug()<<"No data to parse\n"<<Qt::endl;
            return "";
        }

        if (!with_left)
        {
            lpos = where.find(lstr);
            rpos = where.find(rstr, lpos);
            ret_val = where.substr(lpos + lstr.size(), rpos - lpos - lstr.size());
        }
        else
        {
            lpos = where.find(lstr);
            rpos = where.find(rstr, lpos);
            ret_val = where.substr(lpos, rpos - lpos);
        }

        while ((lpos = ret_val.find("\"")) != std::string::npos) ret_val.erase(lpos, 1);

        return ret_val;
    }



    void normalizeString(std::string& where, const std::string& what)
    {
        size_t to_remove{};

        while((to_remove = where.find(what)) != std::string::npos)
               where.erase(to_remove, 1);
    }

    std::string normalizeString(std::string where)
    {
        where.erase(remove(where.begin(), where.end(), '\t'), where.end());
        where.erase(remove(where.begin(), where.end(), '\r'), where.end());
        where.erase(remove(where.begin(), where.end(), '\n'), where.end());
        where.erase(remove(where.begin(), where.end(), ' '), where.end());

        return where;
    }

    const string getDateTime()
    {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::stringstream ss; ss<< put_time(&tm, "%d.%m.%Y %T");
        return ss.str();
    }

    std::vector<std::string> readSettings(const string& file)
    {
        std::vector<std::string> settings;

        std::ifstream ifile;
        ifile.open(file);
        if(!ifile)
        {
            qDebug()<<"Cannot open file "<<file.c_str();
            throw Exception("Cannot open file " +file );
        }

        string line;
        while(getline(ifile, line, ';'))
            settings.push_back(line);

        return settings;
    }

    const string getHostFromUrl(const string &file)
    {
        std::string temp;
        temp = file.substr(file.find("//")+2);
        temp = temp.substr(0, temp.find("/"));

        return temp;
    }

    bool is_equal(double x, double y)
    {
        return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
    }

}
