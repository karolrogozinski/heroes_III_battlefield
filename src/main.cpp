#include <iostream>
#include "../src/headers/hero.h"
#include "../src/headers/unit.h"


int main()
{
    // CCharacter cNoName = CCharacter();
    Ability Fury = Ability(6);
    std::string name1 = "Nico";
    std::string name2 = "Niner";
    Unit* Nico = new Unit(name1, 20, 5, 2);
    Unit* Niner = new Unit(name2, 10, 6, 3);

    Nico->Attack(Niner);

    std::cout << Niner->GetHP() << std::endl;
    // Niner->AddAbility(Fury);

    // std::cout << cNiner->GetAbilities()[0]->a<< std::endl;

    delete Nico;
    delete Niner;

    return 0;
}