#include <utility>
#include <string>
#include <random>

struct RandomGenerator
{
    private:
        static std::shared_ptr<RandomGenerator> mInstance;
        std::mt19937 gen;

        RandomGenerator()
        {
            std::random_device rd;
            std::mt19937 gen(rd());
        }


    public:
    int GetIntInRange(int first, int second)
    {
        std::uniform_int_distribution<> distr(first, second);
        return distr(gen);
    }

    static RandomGenerator getInstance()
    {
        if (mInstance == nullptr)
        {
            mInstance = std::shared_ptr<RandomGenerator>(new RandomGenerator());
        }
    }

};
