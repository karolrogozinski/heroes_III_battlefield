#include "../headers/Stack.h"
#include <iostream>

bool Stack::beAttacked(int damage) {
  int dead_units;
  int recd_damage = 0;
  for (dead_units = 0; dead_units < size_; ++dead_units) {
    if (!dead_units)
      recd_damage += HP_ - (size_ - 1) * unitHP_;
    else
      recd_damage += unitHP_;
    if (recd_damage > damage) {
      recd_damage = damage;
      break;
    }
  }
  HP_ -= recd_damage;
  size_ -= dead_units;
  return size_ <= 0 ? true : false;
}

int GetPseudoRandom(IntPair range) {
  int size = range.second - range.first + 1;
  int value = range.first + (std::rand() % size);
  return value;
}

int Stack::generateStackDamage() { return GetPseudoRandom(damage_); }

bool Stack::attack(Stack &stack) {
  const float multiplier = 0.05;
  int final_damage = size_ * generateStackDamage() +
                     multiplier * (attack_ - stack.getProtection());
  return stack.beAttacked(final_damage);
}

bool operator==(const Stack &lhs, const Stack &rhs) {
  return lhs.ID_ == rhs.ID_ && lhs.size_ == rhs.size_ &&
         lhs.protection_ == rhs.protection_ && lhs.attack_ == rhs.attack_;
}

void Stack::addUnits(Stack stack) {
  size_ += stack.getSize();
  HP_ += unitHP_ * stack.getSize();
}
