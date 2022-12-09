class Ability
{
    public:
        int _a;

        Ability()
        {
            _a = 0;
        }

        Ability(int a)
        {
            _a = a;
        }

        Ability(const Ability& Ab)
        {
            _a = Ab._a;
        }

        const int GetAbility() {return _a;}
};