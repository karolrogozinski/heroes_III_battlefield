#include "ability.h"

class CCharacter
{
    public:
        std::string sName;
        int nHP;
        int nAttack;
        int nProtection;
        
        CCharacter()
        {
            sName = "";
            nHP = 0;
            nAttack = 0;
            nProtection = 0;
        }
    
        //void Attack(CCharacter* cEnemy);
        int rtsth(int a);

};