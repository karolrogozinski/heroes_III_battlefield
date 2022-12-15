#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

// typedef std::vector<std::pair<std::string, std::vector<std::pair<std::string, float>>>> settingsMap;
//      settings          section_name   section        row         name     value
typedef std::pair<std::string, float> rowPair;
typedef std::vector<rowPair> sectionVec;
typedef std::map<std::string, sectionVec> settingsMap;
//               MUSIC                              VOLUME       60

class SettingsController
{
    settingsMap _settings;
    std::string _relPath = "../conf.ini";

    public:
        SettingsController()
        {
            _settings = settingsMap();
            std::cout << "readconfig" << std::endl;
            ReadConfig();
            // std::cout << _settings.size() << std::endl;
            // for (settingsMap::iterator it = _settings.begin(); it != _settings.end(); ++it)
            // {
            //     std::cout << it->first << std::endl;
            // }
            std::cout << "done" << std::endl;
        }

        SettingsController(std::string relPath)
        {
            _relPath = relPath;
            _settings = settingsMap();
            ReadConfig();
        }

        settingsMap& GetSettings() {return _settings;}
        std::string GetPath() {return _relPath;}
        void SetPath(std::string relPath) {_relPath = relPath;}

        void UpdateSettings(const std::string section,const std::string field, float value);
        bool GetSetting(const std::string section, const std::string field, float& settingValue);
        void ReadConfig();


};