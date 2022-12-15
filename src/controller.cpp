#include "headers/controller.h"

void SettingsController::UpdateSettings(const std::string& section,
                                        const std::string& field,
                                        std::string value)
{
    settingsMap::iterator it = _settings.find(section);
    if (it == _settings.end())
    {
        sectionVec sectionData = sectionVec();
        rowPair rowData = rowPair(field, value); 
        sectionData.push_back(rowData);
        _settings.insert(std::make_pair(section, sectionData));
    }
    else
    {
        sectionVec sectionData = it->second;
        bool changed = false;
        if (!sectionData.size())
        {
            sectionData.push_back(std::make_pair(field, value));
        }
        else
        {
            for (rowPair row: sectionData)
            {
                if (row.first == field)
                {
                    row.second = value;
                    changed = true;
                    break;
                }
                if (!changed)
                {
                    sectionData.push_back(std::make_pair(field, value));
                }
            }
        }
    }
}

bool SettingsController::GetSetting(const std::string& section,
                                    const std::string& field,
                                    std::string& settingValue)
{
    settingsMap::iterator it = _settings.find(section);
    if (it == _settings.end())
    {
        return false;
    }
    else
    {
        sectionVec sectionData = it->second;
        if (!sectionData.size()) return false;
        else
        {
            for (rowPair row: sectionData)
            {
                if (row.first == field)
                {
                    settingValue = row.second;
                    return true;
                }
            }
            return false;
        }
    }
}

void SettingsController::ReadConfig()
{
    std::ifstream Conf(_relPath);
    std::string row;
    std::string sectionName;
    std::vector<std::string> lines = std::vector<std::string>();
    if (Conf.is_open())
    {
        while (Conf.good())
        {
            std::getline(Conf, row);

            if (row.substr(0, 1) == "[" && row.substr(row.size()-1) == "]")
            {
                sectionName = row.substr(1, row.size() - 2);
                // std::cout << sectionName << std::endl;
                _settings.insert({sectionName, sectionVec()});
                continue;
            }
            std::size_t pos = row.find("=");
            if (pos != std::string::npos)
            {
                // std::cout << row.substr(pos + 1) << std::endl;
                _settings[sectionName].push_back(
                    std::make_pair(row.substr(0, pos), row.substr(pos + 1)));
            }

        }
        Conf.close();
    }
}