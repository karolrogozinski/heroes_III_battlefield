from ..bindings import Stack, Hero, Battle


def test_basics():
    stack1 = Stack(1)
    stack1.set_cords((1,1))
    stack2 = Stack(2)
    stack2.set_cords((2,2))
    stack3 = Stack(3)
    stack3.set_cords((2, 5))
    stack4 = Stack(4)
    stack4.set_cords((3, 4))
    
    hero1 = Hero("hero1", True)
    hero2 = Hero("hero2", False)
    hero1.add_stack(stack1)
    hero1.add_stack(stack2)
    hero2.add_stack(stack3)
    hero2.add_stack(stack4)
    
    battle = Battle(hero1, hero2)
    
    assert battle.get_player().get_forces()[1].get_id() == 2
    assert battle.get_enemy().get_forces()[0].get_cords() == (2, 5)
 
    
def test_move_stack():
    stack1 = Stack(1)
    stack1.set_cords((1,1))
    stack2 = Stack(2)
    stack2.set_cords((2,2))
    stack2.set_speed(4)
    stack3 = Stack(3)
    stack3.set_cords((2, 5))
    stack4 = Stack(4)
    stack4.set_cords((3, 4))
    
    hero1 = Hero("hero1", True)
    hero2 = Hero("hero2", False)
    hero1.add_stack(stack1)
    hero1.add_stack(stack2)
    hero2.add_stack(stack3)
    hero2.add_stack(stack4)
    
    battle = Battle(hero1, hero2)
    assert not battle.move_stack((2,2), (3,4), True)
    
    
def test_check_basic_attack_poss():
    hero1 = Hero("hero1", True)
    stack1 = Stack(1)
    stack1.set_cords((1,1))
    stack1.set_speed(1)
    stack2 = Stack(2)
    stack2.set_cords((2,2))
    hero1.add_stack(stack1)
    hero1.add_stack(stack2)
    
    hero2 = Hero("hero2", False)
    stack3 = Stack(3)
    stack3.set_cords((2, 5))
    stack4 = Stack(4)
    stack4.set_cords((8, 9))
    stack4.set_speed(1)
    hero2.add_stack(stack3)
    hero2.add_stack(stack4)
    
    battle = Battle(hero1, hero2)
    
    assert not battle.check_basic_attack_poss((0,0), (2,5), True)
    assert not battle.check_basic_attack_poss((1,1), (3,3), True)
    assert battle.check_basic_attack_poss((1,1), (2,5), True)


    