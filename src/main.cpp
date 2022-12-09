#include "../src/headers/hero.h"
#include <iostream>

int main()
{
    // CCharacter cNoName = CCharacter();
    CAbility cFury = CAbility(6);
    std::string sName1 = "Nico";
    std::string sName2 = "Niner";
    CHero* cNico = new CHero(sName1, 20, 5, 2);
    CHero* cNiner = new CHero(sName2, 10, 6, 3);

    cNico->Attack(cNiner);

    std::cout << cNiner->nHP << std::endl;

    delete cNico;
    delete cNiner;

    return 0;
}