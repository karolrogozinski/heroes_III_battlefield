#include "character.h"

class CHero : public CCharacter
{
    public:
        int nLevel;
        int nExp;
        std::vector<CAbility> CAbilities; 

    CHero(std::string sGname,
          int nGhp,
          int nGattack,
          int nGprotection,
          int nGlevel = 0,
          int nGexp = 0)
    {
        sName = sGname;
        nHP = nGhp;
        nAttack = nGattack;
        nProtection = nGprotection;
        CAbilities = {};
        nLevel = nGlevel;
        nExp = nGexp;
    }

    void AddAbility(const CAbility& cGability);
    void Attack(CHero* cEnemy);
};