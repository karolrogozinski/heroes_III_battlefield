from ..bindings import Stack

def test_always_passes():
    assert True
    
def test_constructor():
    stack = Stack(1, 2, 3, 4, 5, 6, 7)
    assert stack.get_id() == 1
    assert stack.get_cords() == (0,0)
    assert stack.get_hp() == 12
    
def test_be_attacked_not_dead():
    stack = Stack(1, 2, 10, 3, 4, 5, 6)
    result = stack.be_attacked(21.37)
    assert not result
    assert stack.get_size() == 1
    assert stack.get_hp() == 8
    
def test_be_attacked_dead():
    stack = Stack(1, 2, 10, 3, 4, 5, 6)
    result = stack.be_attacked(3849)
    assert result
    assert stack.get_size() == 0
    assert stack.get_hp() == 0
    
def test_attack_not_dead():
    stack1 = Stack(1, 2, 10, 3, 4, 5, 6)
    stack1.set_damage((2, 4))
    stack2 = Stack(2, 3, 10, 4, 5, 5, 7)
    result = stack1.attack(stack2)
    assert not result
    assert stack2.get_hp() in range(27, 34)
    assert stack2.get_size() in range(3, 5)
    
def test_attack_dead():
    stack1 = Stack(1, 2, 10, 4, 4, 5, 6)
    stack1.set_damage((2,4))
    stack2 = Stack(2, 3, 10, 1, 5, 5, 7)
    result = stack1.attack(stack2)
    assert result
    assert not stack2.get_hp()
    assert not stack2.get_size()
    
def test_generate_damage():
    stack1 = Stack(1, 2, 10, 4, 4, 5, 6)
    stack1.set_damage((2,4))
    assert stack1.generate_stack_damage() in range(2, 5)
    
def test_add_units():
    stack1 = Stack(1, 2, 10, 4, 4, 5, 6)
    stack2 = Stack(2, 3, 10, 1, 5, 5, 7)
    stack1.add_units(stack2)
    assert stack1.get_size() == 5
    assert stack1.get_hp() == 50
    