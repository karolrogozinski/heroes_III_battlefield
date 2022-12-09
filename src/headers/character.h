#include "ability.h"
#include <iostream>
#include <tuple>
class Character
{
    public:
        std::string _name;
        int _attack;
        int _protection;
        
        Character()
        {
            _name = "";
            _attack = 0;
            _protection = 0;
        }

        std::string GetName() {return _name;}
        int GetAttack() {return _attack;}
        int GetProtection() {return _protection;}

        void SetName(std::string sGname) {_name = sGname;}
        void SetAttack(int nGatt) {_attack = nGatt;}
        void SetProtection(int nGprot) {_protection = nGprot;}

        void AddAttack(int nGatt) {_attack += nGatt;}
        void AddProtection(int nGprot) {_protection += nGprot;}

        void Attack(Character* cEnemy);
        int rtsth(int a);

};