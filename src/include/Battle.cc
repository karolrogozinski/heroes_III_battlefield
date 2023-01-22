#include "../headers/Battle.h"

std::vector<IntPair> CalcLineCords(int lstep, int rstep, IntPair point,
                                   int ystep) {
  // Calc cords in line, only to use in calcing possible moves
  std::vector<IntPair> result;
  for (int i = -lstep; i <= rstep; i++) {
    result.push_back(std::make_pair(point.first + i, point.second + ystep));
  }
  return result;
}

std::vector<std::vector<IntPair>> CalcPossibleMovePoints(int step,
                                                         IntPair point) {
  // Calc possible move points for stack in given point (cords) by given step
  std::vector<std::vector<IntPair>> final_points;
  int lstep = step;
  int rstep = step;

  final_points.push_back(CalcLineCords(lstep, rstep, point, 0));

  for (int i = 1; i <= step; i++) {
    if (point.second % 2 == 0) {
      if (i % 2 != 0) {
        lstep--;
      } else {
        rstep--;
      }
    } else {
      if (i % 2 != 0) {
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

std::vector<IntPair> Battle::getPossibleMoveCords(IntPair cords,
                                                  bool is_player) {
  // Return possible move cords for stack in given cords
  Stack stack = is_player ? player_.getStack(cords) : enemy_.getStack(cords);
  std::vector<std::vector<IntPair>> temp_cords =
      CalcPossibleMovePoints(stack.getSpeed(), cords);
  std::vector<IntPair> curr_cords;
  for (auto rows : temp_cords) {
    for (auto tuple : rows) {
      if (tuple.first >= 0 && tuple.second >= 0 && tuple.first < size_ &&
          tuple.second < size_)
        curr_cords.push_back(tuple);
    }
  }
  std::vector<IntPair> occupiedCords = getAllOccupiedCords();
  for (IntPair cords : occupiedCords) {
    curr_cords.erase(std::remove_if(curr_cords.begin(), curr_cords.end(),
                                    [&](const IntPair curr_cord) -> bool {
                                      return curr_cord == cords;
                                    }),
                     curr_cords.end());
  }
  return curr_cords;
}

std::vector<IntPair> getAllUserOccupiedCords(Hero user) {
  std::vector<IntPair> occupied_cords = std::vector<IntPair>();
  for (auto stack : user.getForces()) {
    if (stack.getSize() <= 0)
      continue;
    occupied_cords.push_back(stack.getCords());
  }
  return occupied_cords;
}

std::vector<IntPair> Battle::getAllOccupiedCords() {
  std::vector<IntPair> occupied_player_cords = getAllUserOccupiedCords(player_);
  std::vector<IntPair> occupied_enemy_cords = getAllUserOccupiedCords(enemy_);
  
  occupied_player_cords.reserve(occupied_player_cords.size() +
                                occupied_enemy_cords.size());
  occupied_player_cords.insert(occupied_player_cords.end(),
                               occupied_enemy_cords.begin(),
                               occupied_enemy_cords.end());

  return occupied_player_cords;
}

bool Battle::moveStack(IntPair start_cords, IntPair final_cords,
                       bool is_player) {
  std::vector<IntPair> move_cords =
      getPossibleMoveCords(start_cords, is_player);
  bool possible = std::find(move_cords.begin(), move_cords.end(),
                            final_cords) != move_cords.end();
  if (!possible)
    return possible;

  if (is_player) {
    player_.getStack(start_cords).setCords(final_cords);
  } else
    enemy_.getStack(start_cords).setCords(final_cords);
  return possible;
}

bool Battle::checkMovePossibility(IntPair its_cords, IntPair final_cords,
                                  bool is_player) {
  std::vector<IntPair> move_cords = getPossibleMoveCords(its_cords, is_player);
  bool possible = std::find(move_cords.begin(), move_cords.end(),
                            final_cords) != move_cords.end();
  return possible;
}

std::pair<bool, IntPair> Battle::getPossibleAttackCords(IntPair its_cords,
                                                        IntPair opponent_cords,
                                                        bool is_player) {
  std::vector<IntPair> possible_movs_diffs;
  if (opponent_cords.second % 2 == 0) {
    possible_movs_diffs = {{-1, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}};
  } else {
    possible_movs_diffs = {{-1, 0}, {-1, -1}, {0, -1}, {1, 0}, {0, 1}, {-1, 1}};
  }
  for (IntPair move_diff : possible_movs_diffs) {
    if (checkMovePossibility(its_cords,
                             {opponent_cords.first + move_diff.first,
                              opponent_cords.second + move_diff.second},
                             is_player)) {
      IntPair ret_cords = {opponent_cords.first + move_diff.first,
                           opponent_cords.second + move_diff.second};
      return {true, ret_cords};
    }
  }
  return {false, {}};
}

bool Battle::checkBasicAttackPoss(IntPair its_cords, IntPair opponent_cords,
                                  bool is_player) {
  // Check if attak of stack(its_cords) is able on second stack(opponent_cords)
  std::vector<IntPair> attacking_cords =
      getAllUserOccupiedCords(is_player ? player_ : enemy_);
  if (std::find(attacking_cords.begin(), attacking_cords.end(), its_cords) ==
        attacking_cords.end())
    return false;
  std::vector<IntPair> attacked_cords =
      getAllUserOccupiedCords(is_player ? enemy_ : player_);
  return std::find(attacked_cords.begin(), attacked_cords.end(),
                   opponent_cords) != attacked_cords.end();
}

std::vector<bool> Battle::performAttack(IntPair its_cords,
                                        IntPair opponent_cords,
                                        bool is_player) {
  if (!checkBasicAttackPoss(its_cords, opponent_cords, is_player))
    return {false, false, false};
  Hero temp_hero = is_player ? player_ : enemy_;
  int attacking_type = temp_hero.getStack(its_cords).getType();
  std::pair<bool, IntPair> possible_move_response;
  if (attacking_type == 0) {
    possible_move_response =
        getPossibleAttackCords(its_cords, opponent_cords, is_player);
    bool move_happened =
        moveStack(its_cords, possible_move_response.second, is_player);
    if (!possible_move_response.first || !move_happened)
      return {false, false, false};
  }
  return contrattack(is_player, possible_move_response, its_cords,
                     opponent_cords, attacking_type);
}

std::vector<bool> Battle::contrattack(bool is_player,
                                      std::pair<bool, IntPair> possible_moves,
                                      IntPair its_cords, IntPair opponent_cords,
                                      int attacking_type) {
  bool attacked_dead;
  bool attacking_dead = false;
  Hero &attacker = is_player ? player_ : enemy_;
  Hero &defender = is_player ? enemy_ : player_;
  IntPair attacker_cords = possible_moves.second;
  auto attack = [&](Hero &attacker, IntPair attacker_cords, Hero &defender,
                    IntPair defender_cords) {
    return attacker.getStack(attacker_cords)
        .attack(defender.getStack(defender_cords));
  };
  if (attacking_type == 0) {
    attacked_dead = attack(attacker, attacker_cords, defender, opponent_cords);
    if (!attacked_dead) {
      attacking_dead =
          attack(defender, opponent_cords, attacker, attacker_cords);
    }
    return {true, attacked_dead, attacking_dead};
  }

  return {true, attack(attacker, its_cords, defender, opponent_cords), false};
}
