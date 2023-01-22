#include "../headers/Controller.h"

void Controller::updateSettings(const std::string &section,
                                const std::string &field, std::string value) {
  // Change value of given setting in section's field
  SettingsMap::iterator it = settings_.find(section);
  if (it == settings_.end()) {
    SectionsVec sectionData = SectionsVec();
    RowPair rowData = RowPair(field, value);
    sectionData.push_back(rowData);
    settings_.insert(std::make_pair(section, sectionData));
  } else {
    SectionsVec sectionData = it->second;
    bool changed = false;
    if (!sectionData.size()) {
      sectionData.push_back(std::make_pair(field, value));
    } else {
      for (RowPair row : sectionData) {
        if (row.first == field) {
          row.second = value;
          changed = true;
          break;
        }
        if (!changed) {
          sectionData.push_back(std::make_pair(field, value));
        }
      }
    }
  }
}

std::string Controller::getSetting(const std::string &section,
                                   const std::string &field) {
  SettingsMap::iterator it = settings_.find(section);
  if (it == settings_.end()) {
    return "";
  } else {
    SectionsVec sectionData = it->second;
    if (!sectionData.size())
      return "";
    else {
      for (RowPair row : sectionData) {
        if (row.first == field) {
          return row.second;
        }
      }
      return "";
    }
  }
}

void Controller::ReadConfig() {
  std::ifstream Conf(relPath_);
  std::string row;
  std::string sectionName;
  std::vector<std::string> lines = std::vector<std::string>();
  if (Conf.is_open()) {
    while (Conf.good()) {
      std::getline(Conf, row);

      if (row.substr(0, 1) == "[" && row.substr(row.size() - 1) == "]") {
        sectionName = row.substr(1, row.size() - 2);
        settings_.insert({sectionName, SectionsVec()});
        continue;
      }
      std::size_t pos = row.find("=");
      if (pos != std::string::npos) {
        settings_[sectionName].push_back(
            std::make_pair(row.substr(0, pos), row.substr(pos + 1)));
      }
    }
    Conf.close();
  }
}