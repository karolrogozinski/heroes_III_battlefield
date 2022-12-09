#include "ability.h"
#include <iostream>
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

        std::string GetName() {return sName;}
        int GetHP() {return nHP;}
        int GetAttack() {return nAttack;}
        int GetProtection() {return nProtection;}

        void SetName(std::string sGname) {sName = sGname;}
        void SetHP(int nGhp) {nHP = nGhp;}
        void SetAttack(int nGatt) {nAttack = nGatt;}
        void SetProtection(int nGprot) {nProtection = nGprot;}

        void AddHP(int nGhp) {nHP += nGhp;}
        void AddAttack(int nGatt) {nAttack += nGatt;}
        void AddProtection(int nGprot) {nProtection += nGprot;}

        void Attack(CCharacter* cEnemy);
        int rtsth(int a);

};