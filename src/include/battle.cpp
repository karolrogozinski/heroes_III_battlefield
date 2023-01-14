#include "./headers/battle.h"
// #include <pybind11/pybind11.h>
// namespace py = pybind11;
// PYBIND11_DECLARE_HOLDER_TYPE(Stack, std::shared_ptr<Stack>)
// PYBIND11_MODULE(battlefield, m)
// {
//     py::class_<Battle>(m, "Battle")
//         .def(py::init<HPtr, HPtr>())
//         .def(py::init<Hero&, Hero&>())
//         .def("MoveStack", &Battle::MoveStack)
//         .def("Attack", &Battle::Attack)
//         .def("GetAllOccupiedCords", &Battle::GetAllOccupiedCords)
//         .def("GetPossibleMoveCords", &Battle::GetPossibleMoveCords);
// }


void Battle::generateDefUnitsCords(HPtr Hero, bool leftSide)
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
    return;
}

Battle::Battle(HPtr player, HPtr enemy) : mPlayer(player), mEnemy(enemy)
{
    generateDefUnitsCords(mPlayer, true);
    generateDefUnitsCords(mEnemy, false);
}

Battle::Battle(Hero& player, Hero& enemy)
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

std::vector<cordsT> Battle::GetPossibleMoveCords(
    cordsT cords,
    bool isPlayer)
{   
    SPtr stackPtr;
    stackPtr = isPlayer ? mPlayer->GetStack(cords) : mEnemy->GetStack(cords);
    std::vector<cordsT> currCords = CalcPossibleMovePoints(stackPtr->getSpeed(), cords);
    std::vector<cordsT> occupiedCords = GetAllOccupiedCords();
    // for (cordsT cords: occupiedCords)
    // {
    //     currCords.erase(std::remove_if(currCords.begin(), currCords.end(), ))
    // }
    return currCords;
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

std::vector<cordsT> Battle::GetAllOccupiedCords()
{
    std::vector<cordsT> occupiedPlayerCords;
    std::vector<cordsT> occupiedEnemyCords;

    occupiedPlayerCords = GetAllUserOccupiedCords(mPlayer);
    occupiedEnemyCords = GetAllUserOccupiedCords(mEnemy);
    occupiedPlayerCords.reserve(occupiedPlayerCords.size() + occupiedEnemyCords.size());
    occupiedPlayerCords.insert(occupiedPlayerCords.end(), occupiedEnemyCords.begin(), occupiedEnemyCords.end());

    return occupiedPlayerCords;
}

bool Battle::MoveStack(cordsT startCords,
                            cordsT finalCords,
                            bool isPlayer)
{
    std::vector<cordsT> moveCords = GetPossibleMoveCords(startCords, isPlayer);

    bool isPossible =  std::find(moveCords.begin(), moveCords.end(), finalCords) != moveCords.end();
    
    if (!isPossible)
        return isPossible;
    
    if (isPlayer)
        mPlayer->GetStack(startCords)->setCords(finalCords);
    else
        mEnemy->GetStack(startCords)->setCords(finalCords);
    return isPossible;
}

std::pair<bool, cordsT> Battle::GetPossibleMoveCords(cordsT itsCords, cordsT opponentCords, bool isPlayer)
{   
    const std::vector<cordsT> possibleMovsDiffs = {{-1, -1}, {-1, 0}, {0, 1}, {1, 0}, {1, -1}, {0, 1}};
    for (cordsT moveDiff: possibleMovsDiffs)
    {
        if (MoveStack(itsCords,
                     {opponentCords.first + moveDiff.first,
                      opponentCords.second + moveDiff.second}, 
                      isPlayer))
            {
                return {true, moveDiff};
            }
    }
    return {false, {}};
}

bool Battle::CheckBasicAttackPoss(cordsT itsCords, cordsT opponentCords, bool isPlayer)
{
    std::vector<cordsT> cordsOfAttacking = GetAllUserOccupiedCords(isPlayer ? mPlayer : mEnemy);
    if (!(std::find(cordsOfAttacking.begin(),
                    cordsOfAttacking.end(),
                    itsCords) != cordsOfAttacking.end()))
        return false;
    
    std::vector<cordsT> cordsOfAttacked = GetAllUserOccupiedCords(isPlayer ? mEnemy : mPlayer);
    if (!(std::find(cordsOfAttacked.begin(),
                    cordsOfAttacked.end(),
                    opponentCords) != cordsOfAttacked.end()))
        return false;
    return true;
}


std::pair<bool, bool> Battle::PerformAttack(cordsT itsCords, cordsT opponentCords,
                                            bool isPlayer, int attackingStackType)
{
    if (!CheckBasicAttackPoss(itsCords, opponentCords, isPlayer))
        return {false, false};
    if (attackingStackType == 1)
    {
        std::pair<bool, cordsT> possibleMoveResponse = GetPossibleMoveCords(itsCords,
                                                                        opponentCords,
                                                                        isPlayer);
        bool moveHappened = MoveStack(itsCords, possibleMoveResponse.second, isPlayer);
        if (!possibleMoveResponse.first || !moveHappened)
            return {false, false};
    }

    SPtr attackingStack = isPlayer ? mPlayer->GetStack(itsCords) : mEnemy->GetStack(itsCords);
    SPtr attackedStack = isPlayer ? mEnemy->GetStack(itsCords) : mPlayer->GetStack(itsCords);
    
    return {true, attackedStack->Attack(attackedStack)};
}