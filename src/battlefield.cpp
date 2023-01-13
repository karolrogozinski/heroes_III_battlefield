#include "./headers/battlefield.h"
#include <pybind11/pybind11.h>
namespace py = pybind11;

PYBIND11_MODULE(battlefield, m)
{
    py::class_<Battlefield>(m, "Battlefield")
        .def(py::init<HPtr, HPtr>())
        .def(py::init<Hero&, Hero&>())
        .def("MoveStack", &Battlefield::MoveStack)
        .def("Attack", &Battlefield::Attack)
        .def("GetAllOccupiedCords", &Battlefield::GetAllOccupiedCords)
        .def("GetPossibleMoveCords", &Battlefield::GetPossibleMoveCords);
}

void Battlefield::generateDefUnitsCords(HPtr Hero, bool leftSide)
{
    int x;
    if (leftSide)
    {
        x = 0;
    } else {
        x = mSize;
    }
    auto cords = std::make_pair(x, 0);
    for (SPtr stackPtr : Hero->getForces())
    {
        stackPtr->setCords(cords);
        ++cords.second;
    }
}

Battlefield::Battlefield(HPtr player, HPtr enemy) : mPlayer(player), mEnemy(enemy)
{
    generateDefUnitsCords(mPlayer, true);
    generateDefUnitsCords(mEnemy, false);
}

Battlefield::Battlefield(Hero& player, Hero& enemy)
{
    mPlayer = std::make_shared<Hero>(player);
    mEnemy = std::make_shared<Hero>(enemy);
    generateDefUnitsCords(mPlayer, true);
    generateDefUnitsCords(mEnemy, false);
}

std::vector<cordsT> CalcLineCords(
    std::vector<int> lrSteps,
    cordsT point,
    int yStep)
{
    std::vector<cordsT> result;
    for (int i = -lrSteps[0]; i <= lrSteps[1]; i++) {
        result.emplace_back(
            std::make_pair(point.first+i, point.second + yStep)
        );
    }
    return result;
}

std::vector<cordsT> CalcPossibleMovePoints(
    int step, cordsT point)
{
    std::vector<cordsT> final_points;
    std::vector<int> lrSteps = {step, step};
    final_points.reserve(final_points.size() + CalcLineCords(lrSteps, point, 0).size());
    final_points.insert(final_points.end(), CalcLineCords(lrSteps, point, 0).begin(), CalcLineCords(lrSteps, point, 0).end());
    for (int i = 1; i <= step; i++) {
        if (i % 2 == 0 && point.second % 2 != 0) {
            lrSteps[1]--;
        } else {
            lrSteps[0]--;
        }

        final_points.reserve(final_points.size() + CalcLineCords(lrSteps, point, i).size());
        final_points.insert(final_points.end(), CalcLineCords(lrSteps, point, i).begin(), CalcLineCords(lrSteps, point, i).end());
        
        final_points.reserve(final_points.size() + CalcLineCords(lrSteps, point, -i).size());
        final_points.insert(final_points.end(), CalcLineCords(lrSteps, point, -i).begin(), CalcLineCords(lrSteps, point, i).end());
    }
    final_points.erase(std::remove(final_points.begin(), final_points.end(), point), final_points.end());
    std::sort(final_points.begin(), final_points.end());
    // we cannot have points foreign to battlefield
    final_points.erase(std::remove_if(final_points.begin(), final_points.end(), [](const auto& p)
        { return p.first < 0 || p.first > 11 || p.second < 0 || p.second > 11; }), final_points.end());

    return final_points;
}

std::vector<cordsT> Battlefield::GetPossibleMoveCords(
    cordsT cords,
    bool isPlayer)
{   
    SPtr stackPtr;
    stackPtr = isPlayer ? mPlayer->getStack(cords) : mEnemy->getStack(cords);
    return CalcPossibleMovePoints(stackPtr->getSpeed(), cords);
}

std::vector<cordsT> Battlefield::GetAllOccupiedCords()
{
    std::vector<cordsT> occupiedPlayerCords;
    std::vector<cordsT> occupiedEnemyCords;

    occupiedPlayerCords = GetAllUserOccupiedCords(mPlayer);
    occupiedEnemyCords = GetAllUserOccupiedCords(mEnemy);
    occupiedPlayerCords.reserve(occupiedPlayerCords.size() + occupiedEnemyCords.size());
    occupiedPlayerCords.insert(occupiedPlayerCords.end(), occupiedEnemyCords.begin(), occupiedEnemyCords.end());

    return occupiedPlayerCords;
}

std::vector<cordsT> GetAllUserOccupiedCords(HPtr user)
{
    std::vector<cordsT> occupiedCords = std::vector<cordsT>();
    for (auto stackPtr: user->getForces())
    {
        occupiedCords.push_back(stackPtr->getCords());
    }
    return occupiedCords;
}


bool Battlefield::MoveStack(cordsT startCords,
                            cordsT finalCords,
                            bool isPlayer)
{
    std::vector<cordsT> moveCords = GetPossibleMoveCords(startCords, isPlayer);

    bool isPossible =  std::find(moveCords.begin(), moveCords.end(), finalCords) != moveCords.end();
    
    if (!isPossible)
        return isPossible;
    
    if (isPlayer)
        mPlayer->getStack(startCords)->setCords(finalCords);
    else
        mEnemy->getStack(startCords)->setCords(finalCords);
    return isPossible;
}

bool Battlefield::Attack(cordsT itsCords, cordsT enemyCords, bool isPlayer)
{
    SPtr attackingStack;
    SPtr attackedStack;
    bool isPossible;
    std::vector<cordsT> cordsOfAttacking = GetAllUserOccupiedCords(isPlayer ? mPlayer : mEnemy);

    isPossible = std::find(cordsOfAttacking.begin(),
                           cordsOfAttacking.end(),
                           itsCords) != cordsOfAttacking.end();
    if (!isPossible)
        return isPossible;
    
    std::vector<cordsT> cordsOfAttacked = GetAllUserOccupiedCords(isPlayer ? mEnemy : mPlayer);
    isPossible = std::find(cordsOfAttacked.begin(),
                           cordsOfAttacked.end(),
                           enemyCords) != cordsOfAttacked.end();
    if (!isPossible)
        return isPossible;

    attackingStack = isPlayer ? mPlayer->getStack(itsCords) : mEnemy->getStack(itsCords);
    attackedStack = isPlayer ? mEnemy->getStack(itsCords) : mPlayer->getStack(itsCords);

    attackedStack->Attack(attackedStack);
    return true;
}