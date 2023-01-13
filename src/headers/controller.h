#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

// typedef std::vector<std::pair<std::string, std::vector<std::pair<std::string, float>>>> settingsMap;
//      settings          section_name   section        row         name     value
typedef std::pair<std::string, std::string> rowPair;
typedef std::vector<rowPair> sectionVec;
typedef std::map<std::string, sectionVec> settingsMap;

class Controller
{
    settingsMap mSettings;
    std::string mRelPath = "../conf.ini";

    void ReadConfig();

    public:
        Controller()
        {
            mSettings = settingsMap();
            std::cout << "readconfig" << std::endl;
            ReadConfig();
            // std::cout << mSettings.size() << std::endl;
            // for (settingsMap::iterator it = mSettings.begin(); it != mSettings.end(); ++it)
            // {
            //     std::cout << it->first << std::endl;
            // }
            std::cout << "done" << std::endl;
        }

        Controller(std::string relPath)
        {
            mRelPath = relPath;
            mSettings = settingsMap();
            ReadConfig();
        }

        settingsMap& getSettings() {return mSettings;}
        std::string getPath() {return mRelPath;}
        void setPath(std::string relPath) {mRelPath = relPath;}

        void UpdateSettings(const std::string& section,const std::string& field, std::string value);
        std::string GetSetting(const std::string& section, const std::string& field);
        
};