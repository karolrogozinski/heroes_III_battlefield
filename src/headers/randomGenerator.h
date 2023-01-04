#include <utility>
#include <string>
#include <random>

class RandomGenerator
{
    std::mt19937 gen;

    public:
        RandomGenerator()
        {
            std::random_device rd;
            std::mt19937 gen(rd());
        }

        int GetIntInRange(int first, int second)
        {
            std::uniform_int_distribution<> distr(first, second);
            return distr(gen);
        }

};
