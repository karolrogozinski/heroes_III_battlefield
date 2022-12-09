#include "character.h"

class Hero : public Character
{
    
    int _level;
    int _exp;
    std::vector<Ability*> _abilities; 

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
        _abilities = std::vector<Ability*>();
        _level = level;
        _exp = exp;
    }

    int GetLevel() {return _level;}
    int GetExp() {return _exp;}
    std::vector<Ability*> GetAbilities() {return _abilities;}

    void SetLevel(int nGlevel) {_level = nGlevel;}
    void SetExp (int nGexp) {_exp = nGexp;}
    void AddExp (int nGexp) {_exp += nGexp;}

    void AddAbility(const Ability& Ab);
    

};