#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

// typedef std::vector<std::pair<std::string, std::vector<std::pair<std::string,
// float>>>> SettingsMap;
//      settings          section_name   section        row         name value
typedef std::pair<std::string, std::string> RowPair;
typedef std::vector<RowPair> SectionsVec;
typedef std::map<std::string, SectionsVec> SettingsMap;

class Controller {
  SettingsMap settings_;
  std::string relPath_ = "../conf.ini";

  void ReadConfig();

public:
  Controller() {
    settings_ = SettingsMap();
    ReadConfig();
  }

  Controller(std::string relPath) {
    relPath_ = relPath;
    settings_ = SettingsMap();
    ReadConfig();
  }

  SettingsMap &getSettings() { return settings_; }
  std::string getPath() { return relPath_; }
  void setPath(std::string relPath) { relPath_ = relPath; }

  void updateSettings(const std::string &section, const std::string &field,
                      std::string value);
  std::string getSetting(const std::string &section, const std::string &field);
};