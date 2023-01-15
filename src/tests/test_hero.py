from hero import Hero, Stack

def test_def_constructor():
    hero = Hero()
    assert hero.get_name() == ""
    assert not hero.get_is_player()
    assert not len(hero.get_forces())

def test_constructor_with_args():
    hero = Hero("test", True)
    assert hero.get_name() == "test"
    assert hero.get_is_player()
    assert not len(hero.get_forces())
    
def test_add_stack():
    hero = Hero("test", True)
    stack1 = Stack(1, 2, 10, 3, 4, 5, 6)
    stack1.set_cords((21, 37))
    stack2 = Stack(2, 3, 10, 4, 5, 5, 7)
    stack2.set_cords((6, 9))
    hero.add_stack(stack1)
    hero.add_stack(stack2)
    assert len(hero.get_forces()) == 2
    assert hero.get_forces()[0].get_cords() == (21, 37)
    assert hero.get_forces()[1].get_hp() == 40

def test_get_stack():
    hero = Hero("test", True)
    stack1 = Stack(1, 2, 10, 3, 4, 5, 6)
    stack1.set_cords((21, 37))
    stack2 = Stack(2, 3, 10, 4, 5, 5, 7)
    stack2.set_cords((6, 9))
    hero.add_stack(stack1)
    hero.add_stack(stack2)
    ret_stack = hero.get_stack((6, 9))
    assert ret_stack.get_cords() == (6, 9)
    assert hero.get_stack((21, 37)).get_hp() == 30
