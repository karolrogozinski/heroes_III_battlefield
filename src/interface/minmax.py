from copy import deepcopy
from random import choice


class MinMaxBoard:
    def __init__(self, board, active_unit) -> None:
        self.board = board
        self.active_unit = active_unit
        self.create_queue()
        self.sort_queue()

    def create_queue(self) -> None:
        self.queue = self.board.get_player().get_forces()
        self.queue += self.board.get_enemy().get_forces()

    def sort_queue(self) -> None:
            n = len(self.queue)
            for i in range(n):
                for j in range(0, n-i-1):
                    if self.queue[j].get_speed() < self.queue[j+1].get_speed():
                        self.queue[j], self.queue[j+1] =\
                            self.queue[j+1], self.queue[j]

    def next_unit(self) -> None:
        active_idx = [
            i for i, x in enumerate(self.queue)
            if x.get_cords() == self.active_unit.get_cords()
        ][0]
        for i in range(len(self.queue)):
            idx = (active_idx+i+1) % len(self.queue)
            if self.queue[idx].get_size():
                self.active_unit = self.queue[idx]
                break

    def move_unit(self, destination: tuple[int]) -> None:
        player_move = int(self.active_unit.get_id()) < 8
        self.board.move_stack(
            self.active_unit.get_cords(),
            destination,
            player_move
        )
        self.next_unit()

    def attack(self, destination: tuple[int]) -> None:
        player_move = int(self.active_unit.get_id()) < 8
        self.board.perform_attack(
            self.active_unit.get_cords(),
            destination,
            player_move
        )
        self.next_unit()

    def are_neighbours(self, target: list[int],
                       possible_moves: list[list[int]]) -> bool:
        even_diffs = ((-1, 0), (0, 1), (1, -1), (1, 0), (1, 1), (0, 1))
        odd_diffs = ((-1, 0), (-1, -1), (0, -1), (1, 0), (0, 1), (-1, 1))
        diffs = even_diffs if not target[1] % 2 else odd_diffs
        for move in possible_moves:
            for diff in diffs:
                move_X, move_Y = diff
                if (move[0] == target[0]+move_X) and\
                   (move[1] == target[1]+move_Y):
                    return True
        return False

    def get_possible_enemy_attacks(self, possible_moves: list[tuple[int]],
                                   is_player: bool) -> list[tuple[int]]:
        possible_attacks = list()

        if is_player:
            targets = self.board.get_enemy().get_forces()
        else:
            targets = self.board.get_player().get_forces()

        if self.active_unit.get_type():
            for target in targets:
                possible_attacks.append(target.get_cords())
        else:
            for target in targets:
                if self.are_neighbours(target.get_cords(), possible_moves):
                    possible_attacks.append(target.get_cords())
        return possible_attacks

    def end(self) -> bool:
        if not self.board.get_player().get_forces():
            return 1
        if not self.board.get_enemy().get_forces():
            return 1
        return 0

    def evaluate_board(self):
        score = 0

        for stack in self.board.get_player().get_forces():
            size = stack.get_size()
            attack = stack.get_attack()
            shooter = stack.get_type()
            hp = stack.get_hp()
            score += hp
            if shooter:
                score += size * attack * 2
            else:
                score += size * attack

        for stack in self.board.get_enemy().get_forces():
            size = stack.get_size()
            attack = stack.get_attack()
            shooter = stack.get_type()
            hp = stack.get_hp()
            score -= hp
            if shooter:
                score -= size * attack * 2
            else:
                score -= size * attack

        return score


def minimax_a_b(board, depth, move_max):
    player_move = int(board.active_unit.get_id()) < 8
    pos_moves = board.board.get_possible_move_cords(
        board.active_unit.get_cords(),
        player_move
    )
    pos_attacks = board.get_possible_enemy_attacks(
        pos_moves,
        player_move
    )
    best_move = [choice(pos_moves)]

    if move_max:
        evaluation = float('-inf')
    else:
        evaluation = float('inf')

    a = float('-inf')
    b = float('inf')

    all_moves = pos_moves + pos_attacks
    for idx, move in enumerate(all_moves):
        cp_board = deepcopy(board)
        if idx < len(pos_moves):
            cp_board.move_unit(move)
        else:
            cp_board.attack(move)

        curr_evaluation = minimax_a_b_recurr(cp_board, depth-1, not move_max, a, b) 

        if move_max and curr_evaluation > evaluation:
            evaluation = curr_evaluation
            best_move = [move]
        if move_max and curr_evaluation == evaluation:
            best_move.append(move)

        if not move_max and curr_evaluation < evaluation:
            evaluation = curr_evaluation
            best_move = [move]
        if not move_max and curr_evaluation == evaluation:
            best_move.append(move)

    return choice(best_move)


def minimax_a_b_recurr(board, depth, move_max, a, b):
    player_move = int(board.active_unit.get_id()) < 8
    pos_moves = board.board.get_possible_move_cords(
        board.active_unit.get_cords(), player_move
    )

    if depth == 0 or board.end():
        return board.evaluate_board()

    if move_max:
        for mv in pos_moves:
            curr_board = deepcopy(board)
            curr_board.move_unit(mv)

            a = max(a, minimax_a_b_recurr(curr_board, depth-1, False, a, b))
            if a >= b:
                return b
        return a

    if not move_max:
        for mv in pos_moves:
            curr_board = deepcopy(board)
            curr_board.move_unit(mv)

            b = min(b, minimax_a_b_recurr(curr_board, depth-1, True, a, b))
            if a >= b:
                return a
        return b
