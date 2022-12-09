#include <vector>
#include <string>
#include <memory>
#include "ability.h"

typedef std::shared_ptr<Ability> APtr;

class Hero
{
    std::string _name;
    int _attack;
    int _protection;
    int _level;
    int _exp;
    std::vector<APtr> _abilities; 

    public:
        Hero(std::string name,
            int attack,
            int protection,
            int level = 0,
            int exp = 0)
        {
            _name = name;
            _attack = attack;
            _protection = protection;
            _abilities = std::vector<APtr>();
            _level = level;
            _exp = exp;
        }

        std::string GetName() {return _name;}
        int GetAttack() {return _attack;}
        int GetProtection() {return _protection;}
        int GetLevel() {return _level;}
        int GetExp() {return _exp;}
        std::vector<APtr> GetAbilities() {return _abilities;}

        void SetName(std::string sGname) {_name = sGname;}
        void SetAttack(int nGatt) {_attack = nGatt;}
        void SetProtection(int nGprot) {_protection = nGprot;}
        void SetLevel(int nGlevel) {_level = nGlevel;}
        void SetExp (int nGexp) {_exp = nGexp;}
        void AddExp (int nGexp) {_exp += nGexp;}

        void AddAttack(int nGatt) {_attack += nGatt;}
        void AddProtection(int nGprot) {_protection += nGprot;}
        void AddAbility(const Ability& Ab);
    

};