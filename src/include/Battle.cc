#include "../headers/Battle.h"

void Battle::GenerateDefUnitsCords(Hero hero, bool leftSide)
{
    int x;
    if (leftSide)
    {
        x = 0;
    } else {
        x = mSize;
    }
    auto cords = std::make_pair(x, 0);
    for (Stack stack : hero.getForces())
    {
        stack.setCords(cords);
        ++cords.second;
    }
    return;
}

Battle::Battle(Hero player, Hero enemy) : mPlayer(player), mEnemy(enemy)
{
    GenerateDefUnitsCords(mPlayer, true);
    GenerateDefUnitsCords(mEnemy, false);
}

std::vector<cordsT> CalcLineCords(
    int lstep,
    int rstep,
    cordsT point,
    int yStep)
{
    std::vector<cordsT> result;
    for (int i = -lstep; i <= rstep; i++) {
        result.push_back(
            std::make_pair(point.first+i, point.second + yStep)
        );
    }
    return result;
}

std::vector<std::vector<cordsT>> CalcPossibleMovePoints(
    int step, cordsT point)
{
    std::vector<std::vector<cordsT>> final_points;
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

std::vector<cordsT> Battle::GetPossibleMoveCords(
    cordsT cords,
    bool isPlayer)
{   
    Stack stack;
    stack = isPlayer ? mPlayer.GetStack(cords) : mEnemy.GetStack(cords);
    std::vector<std::vector<cordsT>> tempCords = CalcPossibleMovePoints(stack.getSpeed(), cords);
    std::vector<cordsT> currCords;
    for (auto rows: tempCords)
    {
        for (auto tuple: rows)
        {
            if (tuple.first>=0 && tuple.second>=0 && tuple.first<mSize && tuple.second<mSize)
                currCords.push_back(tuple);
        }
    }
    std::vector<cordsT> occupiedCords = GetAllOccupiedCords();
    for (cordsT cords: occupiedCords)
    {
        currCords.erase(std::remove_if(currCords.begin(),
                                       currCords.end(),
                                       [&](const cordsT currCord) -> bool
                                            { return currCord == cords; }),
                        currCords.end());
    }
    return currCords;
}

std::vector<cordsT> GetAllUserOccupiedCords(Hero user)
{
    std::vector<cordsT> occupiedCords = std::vector<cordsT>();
    for (auto stack: user.getForces())
    {
        if (stack.getSize() <= 0)
            continue;
        occupiedCords.push_back(stack.getCords());
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
    
    if (isPlayer) {
        mPlayer.GetStack(startCords).setCords(finalCords);
    } else
        mEnemy.GetStack(startCords).setCords(finalCords);
    return isPossible;
}

bool Battle::CheckMovePossibility(cordsT itsCords, cordsT finalCords, bool isPlayer)
{
    std::vector<cordsT> moveCords = GetPossibleMoveCords(itsCords, isPlayer);
    bool isPossible =  std::find(moveCords.begin(), moveCords.end(), finalCords) != moveCords.end();
    return isPossible;
}

std::pair<bool, cordsT> Battle::GetPossibleAttackCords(cordsT itsCords, cordsT opponentCords, bool isPlayer)
{   
    std::vector<cordsT> possibleMovsDiffs;
    if (opponentCords.second % 2 == 0) {
        possibleMovsDiffs = {{-1, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}};
    } else {
        possibleMovsDiffs = {{-1, 0}, {-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}};
    } 
    for (cordsT moveDiff: possibleMovsDiffs)
    {
        if (CheckMovePossibility(itsCords,
                     {opponentCords.first + moveDiff.first,
                      opponentCords.second + moveDiff.second}, 
                      isPlayer))
            {
                cordsT retCords = {opponentCords.first + moveDiff.first,
                                   opponentCords.second + moveDiff.second}; 
                return {true, retCords};
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


std::vector<bool> Battle::PerformAttack(cordsT itsCords, cordsT opponentCords,
                                            bool isPlayer)
{
    if (!CheckBasicAttackPoss(itsCords, opponentCords, isPlayer))
        return {false, false, false};
    Hero tempHero = isPlayer ? mPlayer : mEnemy;
    int attackingType = tempHero.GetStack(itsCords).getType();
    bool attackedDead;
    bool attackingDead = false;
    if (attackingType == 0)
    {
        std::pair<bool, cordsT> possibleMoveResponse = GetPossibleAttackCords(itsCords,
                                                                        opponentCords,
                                                                        isPlayer);
        bool moveHappened = MoveStack(itsCords, possibleMoveResponse.second, isPlayer);
        if (!possibleMoveResponse.first || !moveHappened)
            return {false, false, false};

        if (isPlayer)
            attackedDead = mPlayer.GetStack(possibleMoveResponse.second).Attack(mEnemy.GetStack(opponentCords));
        else
            attackedDead = mEnemy.GetStack(possibleMoveResponse.second).Attack(mPlayer.GetStack(opponentCords));

        if (!attackedDead)
        {
            if (isPlayer)
                attackingDead = mEnemy.GetStack(opponentCords).Attack(mPlayer.GetStack(possibleMoveResponse.second));
            else
                attackingDead = mPlayer.GetStack(opponentCords).Attack(mEnemy.GetStack(possibleMoveResponse.second));
        }
        return {true, attackedDead, attackingDead};
    }
    if (isPlayer)
        return {true, mPlayer.GetStack(itsCords).Attack(mEnemy.GetStack(opponentCords)), false};
    else
        return {true, mEnemy.GetStack(itsCords).Attack(mPlayer.GetStack(opponentCords)), false};
}
