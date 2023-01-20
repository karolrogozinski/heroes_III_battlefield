#include "../headers/Battle.h"

void Battle::generateDefUnitsCords(Hero hero, bool leftSide)
{
    int x;
    if (leftSide)
    {
        x = 0;
    } else {
        x = size_;
    }
    auto cords = std::make_pair(x, 0);
    for (Stack stack : hero.getForces())
    {
        stack.setCords(cords);
        ++cords.second;
    }
    return;
}

Battle::Battle(Hero player, Hero enemy) : player_(player), enemy_(enemy)
{
    generateDefUnitsCords(player_, true);
    generateDefUnitsCords(enemy_, false);
}

std::vector<IntPair> CalcLineCords(
    int lstep,
    int rstep,
    IntPair point,
    int yStep)
{
    std::vector<IntPair> result;
    for (int i = -lstep; i <= rstep; i++) {
        result.push_back(
            std::make_pair(point.first+i, point.second + yStep)
        );
    }
    return result;
}

std::vector<std::vector<IntPair>> CalcPossibleMovePoints(
    int step, IntPair point)
{
    std::vector<std::vector<IntPair>> final_points;
    int lstep = step;
    int rstep = step;

    final_points.push_back(CalcLineCords(lstep, rstep, point, 0));

    for (int i = 1; i <= step; i++)
    {
        if (point.second % 2 == 0){
            if(i % 2 != 0){
                lstep--;
            } else {
                rstep--;
            }
        } else {
            if(i % 2 != 0){
                rstep--;
            } else {
                lstep--;
            }
        }

        final_points.push_back(CalcLineCords(lstep, rstep, point, i));
        final_points.push_back(CalcLineCords(lstep, rstep, point, -i));
    }

    return final_points;
}

std::vector<IntPair> Battle::getPossibleMoveCords(
    IntPair cords,
    bool isPlayer)
{   
    Stack stack;
    stack = isPlayer ? player_.getStack(cords) : enemy_.getStack(cords);
    std::vector<std::vector<IntPair>> tempCords = CalcPossibleMovePoints(stack.getSpeed(), cords);
    std::vector<IntPair> currCords;
    for (auto rows: tempCords)
    {
        for (auto tuple: rows)
        {
            if (tuple.first>=0 && tuple.second>=0 && tuple.first<size_ && tuple.second<size_)
                currCords.push_back(tuple);
        }
    }
    std::vector<IntPair> occupiedCords = getAllOccupiedCords();
    for (IntPair cords: occupiedCords)
    {
        currCords.erase(std::remove_if(currCords.begin(),
                                       currCords.end(),
                                       [&](const IntPair currCord) -> bool
                                            { return currCord == cords; }),
                        currCords.end());
    }
    return currCords;
}

std::vector<IntPair> GetAllUserOccupiedCords(Hero user)
{
    std::vector<IntPair> occupiedCords = std::vector<IntPair>();
    for (auto stack: user.getForces())
    {
        if (stack.getSize() <= 0)
            continue;
        occupiedCords.push_back(stack.getCords());
    }
    return occupiedCords;
}

std::vector<IntPair> Battle::getAllOccupiedCords()
{
    std::vector<IntPair> occupiedPlayerCords;
    std::vector<IntPair> occupiedEnemyCords;

    occupiedPlayerCords = GetAllUserOccupiedCords(player_);
    occupiedEnemyCords = GetAllUserOccupiedCords(enemy_);
    occupiedPlayerCords.reserve(occupiedPlayerCords.size() + occupiedEnemyCords.size());
    occupiedPlayerCords.insert(occupiedPlayerCords.end(), occupiedEnemyCords.begin(), occupiedEnemyCords.end());

    return occupiedPlayerCords;
}

bool Battle::moveStack(IntPair startCords,
                            IntPair finalCords,
                            bool isPlayer)
{
    std::vector<IntPair> moveCords = getPossibleMoveCords(startCords, isPlayer);
    bool isPossible =  std::find(moveCords.begin(), moveCords.end(), finalCords) != moveCords.end();
    if (!isPossible)
        return isPossible;
    
    if (isPlayer) {
        player_.getStack(startCords).setCords(finalCords);
    } else
        enemy_.getStack(startCords).setCords(finalCords);
    return isPossible;
}

bool Battle::checkMovePossibility(IntPair itsCords, IntPair finalCords, bool isPlayer)
{
    std::vector<IntPair> moveCords = getPossibleMoveCords(itsCords, isPlayer);
    bool isPossible =  std::find(moveCords.begin(), moveCords.end(), finalCords) != moveCords.end();
    return isPossible;
}

std::pair<bool, IntPair> Battle::getPossibleAttackCords(IntPair itsCords, IntPair opponentCords, bool isPlayer)
{   
    std::vector<IntPair> possibleMovsDiffs;
    if (opponentCords.second % 2 == 0) {
        possibleMovsDiffs = {{-1, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}};
    } else {
        possibleMovsDiffs = {{-1, 0}, {-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}};
    } 
    for (IntPair moveDiff: possibleMovsDiffs)
    {
        if (checkMovePossibility(itsCords,
                     {opponentCords.first + moveDiff.first,
                      opponentCords.second + moveDiff.second}, 
                      isPlayer))
            {
                IntPair retCords = {opponentCords.first + moveDiff.first,
                                   opponentCords.second + moveDiff.second}; 
                return {true, retCords};
            }
    }
    return {false, {}};
}

bool Battle::checkBasicAttackPoss(IntPair itsCords, IntPair opponentCords, bool isPlayer)
{
    std::vector<IntPair> cordsOfAttacking = GetAllUserOccupiedCords(isPlayer ? player_ : enemy_);
    if (!(std::find(cordsOfAttacking.begin(),
                    cordsOfAttacking.end(),
                    itsCords) != cordsOfAttacking.end()))
        return false;
    
    std::vector<IntPair> cordsOfAttacked = GetAllUserOccupiedCords(isPlayer ? enemy_ : player_);
    if (!(std::find(cordsOfAttacked.begin(),
                    cordsOfAttacked.end(),
                    opponentCords) != cordsOfAttacked.end()))
        return false;
    return true;
}


std::vector<bool> Battle::performAttack(IntPair itsCords, IntPair opponentCords,
                                            bool isPlayer)
{
    if (!checkBasicAttackPoss(itsCords, opponentCords, isPlayer))
        return {false, false, false};
    Hero tempHero = isPlayer ? player_ : enemy_;
    int attackingType = tempHero.getStack(itsCords).getType();
    bool attackedDead;
    bool attackingDead = false;
    if (attackingType == 0)
    {
        std::pair<bool, IntPair> possibleMoveResponse = getPossibleAttackCords(itsCords,
                                                                        opponentCords,
                                                                        isPlayer);
        bool moveHappened = moveStack(itsCords, possibleMoveResponse.second, isPlayer);
        if (!possibleMoveResponse.first || !moveHappened)
            return {false, false, false};

        if (isPlayer)
            attackedDead = player_.getStack(possibleMoveResponse.second).attack(enemy_.getStack(opponentCords));
        else
            attackedDead = enemy_.getStack(possibleMoveResponse.second).attack(player_.getStack(opponentCords));

        if (!attackedDead)
        {
            if (isPlayer)
                attackingDead = enemy_.getStack(opponentCords).attack(player_.getStack(possibleMoveResponse.second));
            else
                attackingDead = player_.getStack(opponentCords).attack(enemy_.getStack(possibleMoveResponse.second));
        }
        return {true, attackedDead, attackingDead};
    }
    if (isPlayer)
        return {true, player_.getStack(itsCords).attack(enemy_.getStack(opponentCords)), false};
    else
        return {true, enemy_.getStack(itsCords).attack(player_.getStack(opponentCords)), false};
}
