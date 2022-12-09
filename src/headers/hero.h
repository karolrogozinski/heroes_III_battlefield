#include "character.h"

class CHero : public CCharacter
{
    
    int nLevel;
    int nExp;
    std::vector<CAbility*> CAbilities; 

    public:

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
        CAbilities = std::vector<CAbility*>();
        nLevel = nGlevel;
        nExp = nGexp;
    }

    int GetLevel() {return nLevel;}
    int GetExp() {return nExp;}
    std::vector<CAbility*> GetAbilities() {return CAbilities;}

    void SetLevel(int nGlevel) {nLevel = nGlevel;}
    void SetExp (int nGexp) {nExp = nGexp;}
    void AddExp (int nGexp) {nExp += nGexp;}

    void AddAbility(const CAbility& cGability);
    

};