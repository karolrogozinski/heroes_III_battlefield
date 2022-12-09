#include <vector>
#include <string>

class CAbility
{
    public:
        int a;

        CAbility()
        {
            a = 0;
        }

        CAbility(int Ga)
        {
            a = Ga;
        }

        CAbility(const CAbility& cAb)
        {
            a = cAb.a;
        }
};