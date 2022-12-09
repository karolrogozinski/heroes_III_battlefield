#include <utility>
#include <string>
class Unit
{
    std::string _name;
    int _attack;
    int _protection;
    std::pair<int, int> _damage;
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

        Unit(std::string name,
             int hp, int attack, int prot,
             std::pair<int, int> damage = {})
        {
            _name = name;
            _hp = hp;
            _attack = attack;
            _protection = prot;
            _damage = damage;
        }

        std::string GetName() {return _name;}
        int GetHP() {return _hp;}
        int GetAttack() {return _attack;}
        int GetProtection() {return _protection;}
        std::pair<int, int> GetDamage() {return _damage;}

        void SetName(std::string sGname) {_name = sGname;}
        void SetHP(int hp) {_hp = hp;}
        void SetAttack(int att) {_attack = att;}
        void SetProtection(int prot) {_protection = prot;}
        void SetDamage(std::pair<int, int> damage) {_damage = damage;}

        void AddHP(int hp) {_hp += hp;}
        void AddAttack(int att) {_attack += att;}
        void AddProtection(int prot) {_protection += prot;}
        void AddDamage(int dam) {_damage.first += dam; _damage.second += dam;}

        void Attack(Unit* Enemy);
        int rtsth(int a);

};