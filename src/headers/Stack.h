#include <cstdlib>
#include <memory>
#include <utility>
#include <vector>

typedef std::pair<int, int> IntPair;
class Stack {
  int ID_;
  // 0 - usual, 1 - shooter, (2- flying)
  int type_;

  unsigned int HP_;
  unsigned int unitHP_;

  int size_;
  int protection_;
  int attack_;
  int speed_;
  IntPair damage_;
  IntPair cords_;

public:
  Stack() {
    ID_ = 0;
    size_ = 1;
    protection_ = 1;
    attack_ = 1;
    speed_ = 1;
    cords_ = IntPair();
  }

  Stack(int id) {
    Stack();
    ID_ = id;
  }

  Stack(int id, int type, unsigned int unitHP, int size = 1, int speed = 1,
        int prot = 1, int att = 1)
      : ID_(id), type_(type), unitHP_(unitHP), size_(size), protection_(prot),
        attack_(att), speed_(speed) {
    HP_ = unitHP_ * size_;
    cords_ = IntPair();
  }

  ~Stack() {}

  int getID() { return ID_; }
  int getType() { return type_; }
  unsigned int getHP() { return HP_; }
  unsigned int getUnitHP() { return unitHP_; }
  int getSize() { return size_; }
  int getSpeed() { return speed_; }
  int getProtection() { return protection_; }
  int getAttack() { return attack_; }
  IntPair getDamage() { return damage_; }
  IntPair getCords() { return cords_; }

  void setID(int id) { ID_ = id; }
  void setType(int type) { type_ = type; }
  void setHP(unsigned int HP) { HP_ = HP; }
  void setUnitHP(unsigned int unit_HP) { unitHP_ = unit_HP; }
  void setSize(int size) { size_ = size; }
  void setSpeed(int speed) { speed_ = speed; }
  void setProtection(int prot) { protection_ = prot; }
  void setAttack(int attack) { attack_ = attack; }
  void setDamage(IntPair damage) { damage_ = damage; }
  void setCords(IntPair cords) { cords_ = cords; }

  bool beAttacked(int damage);
  bool attack(Stack &stack);
  void addUnits(Stack stack);

  int generateStackDamage();
  friend bool operator==(const Stack &lhs, const Stack &rhs);
};
