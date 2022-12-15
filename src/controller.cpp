#include "headers/controller.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(controller, m)
{
    py::class_<Controller>(m, "Controller")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def("GetSettings", &Controller::GetSettings)
        .def("GetPath", &Controller::GetPath)
        .def("SetPath", &Controller::SetPath)
        .def("UpdateSettings", &Controller::UpdateSettings)
        .def("GetSetting", &Controller::GetSetting);
}

void Controller::UpdateSettings(const std::string& section,
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

std::string Controller::GetSetting(const std::string& section,
                                    const std::string& field)
{
    settingsMap::iterator it = _settings.find(section);
    if (it == _settings.end())
    {
        return "";
    }
    else
    {
        sectionVec sectionData = it->second;
        if (!sectionData.size()) return "";
        else
        {
            for (rowPair row: sectionData)
            {
                if (row.first == field)
                {
                    return row.second;
                }
            }
            return "";
        }
    }
}

void Controller::ReadConfig()
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