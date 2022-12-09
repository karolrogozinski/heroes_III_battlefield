#include "unit.h"
#include <vector>
#include <memory>

typedef std::shared_ptr<Unit> UPtr;

class Stack
{
    std::vector<UPtr> _units;
    int _size;
    int _protection;
    int _attack;

    public:
        Stack()
        {
            _units = {};
            _size = 0;
            _protection = 0;
            _attack = 0;
        }

        std::vector<UPtr> GetUnits() {return _units;}
        int GetSize() {return _size;}
        int GetProtection() {return _protection;}
        int GetAttack() {return _attack;}

        void AddUnit();
        void AddUnit(UPtr unit);

        void BeAttacked(float damage);
        void Attack(Stack& stack);
};
