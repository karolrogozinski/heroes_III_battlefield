#include "Stack.h"
#include <math.h>
#include <memory>
#include <string>
#include <vector>

class Hero {
  std::string name_;
  bool isPlayer_;
  std::vector<Stack> forces_;
  int forcesNum_ = 7;

public:
  Hero() : name_(""), isPlayer_(false) {}

  Hero(std::string name, bool is_player) : name_(name), isPlayer_(is_player) {}

  Hero(std::string name, bool is_player, std::vector<Stack> forces)
      : name_(name), isPlayer_(is_player), forces_(forces) {}

  std::string getName() { return name_; }
  bool getIsPlayer() { return isPlayer_; }
  std::vector<Stack> getForces() { return forces_; }

  void setName(std::string sGname) { name_ = sGname; }
  void setIsPlayer(bool isPlayer) { isPlayer_ = isPlayer; }
  void setForces(std::vector<Stack> forces) { forces_ = forces; }

  Stack &getStack(std::pair<int, int> cords);
  void addStack(Stack stack);
};