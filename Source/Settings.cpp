#include "Settings.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

std::map<std::string, std::string> Settings::config;

bool Settings::save()
{

    std::ofstream out("Settings.ini");
    out << toString();
    out.close();

    return true;
}

std::string Settings::toString()
{
    std::stringstream ss;

    for (const auto& p : config)
    {
        ss << p.first << "=" << p.second << std::endl;
    }

    return ss.str();
}

bool Settings::parseFile(std::string contents)
{

    if (contents.length() == 0)
        throw std::invalid_argument("Settings.ini content is empty!");


    const auto oldConfig = config;
    config.clear();

    std::string line;

    std::istringstream input(contents);
    while (std::getline(input, line))
    {
        // remove spaces
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

        if (line.length() == 0)
            continue;

        const std::string delimiter = "=";
        const auto posEqual = line.find(delimiter);

        // can't find the delimiter
        if (posEqual == std::string::npos)
        {
            config = oldConfig;
            return false;
        }
        std::string key = line.substr(0, posEqual);
        std::string value = line.substr(posEqual + delimiter.length());

        // to lowercase
        std::transform(key.begin(), key.end(), key.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        config[key] = value;
    }

    return true;
}

bool Settings::load()
{


    std::ifstream file("Settings.ini");

    if (file)
    {

        std::stringstream buffer;
        buffer << file.rdbuf();

        file.close();


        return parseFile(buffer.str());
    } else
    {
        std::cout << "ERROR: can't load settings file" << std::endl << std::endl;
        return false;
    }
}