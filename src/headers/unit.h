#include "character.h"

class Unit : public Character
{
    std::tuple<int, int> _damage;
    int _hp;

    public:
        
        Unit()
        {
            _name = "";
            _hp = 0;
            _attack = 0;
            _protection = 0;
            _damage = {0, 0};
        }

        std::string GetName() {return _name;}
        int GetHP() {return _hp;}
        int GetAttack() {return _attack;}
        int GetProtection() {return _protection;}

        void SetName(std::string sGname) {_name = sGname;}
        void SetHP(int hp) {_hp = hp;}
        void SetAttack(int att) {_attack = att;}
        void SetProtection(int prot) {_protection = prot;}

        void AddHP(int hp) {_hp += hp;}
        void AddAttack(int att) {_attack += att;}
        void AddProtection(int prot) {_protection += prot;}

        void Attack(Unit* Enemy);
        int rtsth(int a);

};