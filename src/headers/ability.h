class Ability
{
    public:
        int mValue;

        Ability()
        {
            mValue = 0;
        }

        Ability(int a)
        {
            mValue = a;
        }

        Ability(const Ability& Ab)
        {
            mValue = Ab.mValue;
        }

        const int getAbility() {return mValue;}
};