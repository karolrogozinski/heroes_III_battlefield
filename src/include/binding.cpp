
#include "../headers/battle.h"
#include "../headers/controller.h"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
PYBIND11_MAKE_OPAQUE(std::vector<Stack>);
namespace py = pybind11;


PYBIND11_MODULE(hero, m)
{
    py::class_<Stack>(m, "Stack")
        .def(py::init<>())
        .def(py::init<int>())
        .def(py::init<int, int, int, int, int, int, int>())

        .def("get_id", &Stack::getID)
        .def("get_type", &Stack::getType)
        .def("get_hp", &Stack::getHP)
        .def("get_unit_hp", &Stack::getUnitHP)
        .def("get_size", &Stack::getSize)
        .def("get_speed", &Stack::getSpeed)
        .def("get_protection", &Stack::getProtection)
        .def("get_attack", &Stack::getAttack)
        .def("get_damage", &Stack::getDamage)
        .def("get_cords", &Stack::getCords)

        .def("set_id", &Stack::setID)
        .def("set_type", &Stack::setType)
        .def("set_hp", &Stack::setHP)
        .def("set_unit_hp", &Stack::setUnitHP)
        .def("set_size", &Stack::setSize)
        .def("set_speed", &Stack::setSpeed)
        .def("set_protection", &Stack::setProtection)
        .def("set_attack", &Stack::setAttack)
        .def("set_damage", &Stack::setDamage)
        .def("set_cords", &Stack::setCords)
        
        .def("be_attacked", &Stack::BeAttacked)
        .def("attack", &Stack::Attack)
        .def("add_units", &Stack::AddUnits)
        .def("generate_stack_damage", &Stack::GenerateStackDamage);

    py::class_<std::vector<Stack>>(m, "StackVector")
        .def(py::init<>())
        .def("clear", &std::vector<Stack>::clear)
        .def("push_back", (void (std::vector<Stack>::*)(const Stack &)) &std::vector<Stack>::push_back)
        .def("__setitem__", [](std::vector<Stack> &v, int i, Stack item) { v[i] = item; })
        .def("pop_back", &std::vector<Stack>::pop_back)
        .def("__len__", [](const std::vector<Stack> &v) {return v.size();})
        .def("__getitem__", [](std::vector<Stack>&v, size_t index) {return v[index];})
        .def("__iter__", [](std::vector<Stack> &v) {
            return py::make_iterator(v.begin(), v.end());
            }, py::keep_alive<0, 1>());

    py::class_<Hero>(m, "Hero")
        .def(py::init<>())
        .def(py::init<std::string, bool>())

        .def("get_name", &Hero::getName)
        .def("get_is_player", &Hero::getIsPlayer)
        .def("get_forces", &Hero::getForces)

        .def("set_name", &Hero::setName)
        .def("set_is_player", &Hero::setIsPlayer)
        .def("set_forces", &Hero::setForces)

        .def("get_stack", &Hero::GetStack)
        .def("add_stack", &Hero::AddStack);

    py::class_<Battle>(m, "Battle")
        .def(py::init<Hero, Hero>())
        .def("get_player", &Battle::getPlayer)
        .def("get_enemy", &Battle::getEnemy)
        .def("get_size", &Battle::getSize)
        .def("set_player", &Battle::setPlayer)
        .def("set_enemy", &Battle::setEnemy)
        .def("generate_def_units_cords", &Battle::GenerateDefUnitsCords)
        .def("move_stack", &Battle::MoveStack)
        .def("check_basic_attack_poss", &Battle::CheckBasicAttackPoss)
        .def("perform_attack", &Battle::PerformAttack)
        .def("get_all_cccupied_cords", &Battle::GetAllOccupiedCords)
        .def("get_possible_move_cords", &Battle::GetPossibleMoveCords)
        .def("get_possible_attack_cords", &Battle::GetPossibleAttackCords);

    py::class_<Controller>(m, "Controller")
        .def(py::init<>())
        .def(py::init<std::string>())
        .def("get_settings", &Controller::getSettings)
        .def("get_path", &Controller::getPath)
        .def("set_path", &Controller::setPath)
        .def("update_settings", &Controller::UpdateSettings)
        .def("get_setting", &Controller::GetSetting);
}