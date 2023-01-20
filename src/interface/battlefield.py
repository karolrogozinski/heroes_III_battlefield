import os
from time import sleep

import pygame

from .hexfield import HexFieldInterface
from .unit import UnitInterface

from ..bindings import Battle


class BattefieldInterface:
    def __init__(self, battle: Battle) -> None:
        pygame.init()
        self.window_size = (1280, 720)
        self.dirname = os.path.dirname(os.path.abspath(__file__))
        self.screen = pygame.display.set_mode(self.window_size)
        self.battlefield = []
        self.RUN_BF = True
        self.transparency = 50
        self.transparency_step = 0.5
        self.music_path = os.path.join(
            self.dirname,
            '../music/Fortuna.mp3'
        )
        self.units = []
        self.battle = battle
        self.start_cords = [(0, 0), (10, 0), (0, 2), (10, 2), (0, 4), (10, 4),
                            (0, 5), (10, 5), (0, 6), (10, 6), (0, 8), (10, 8),
                            (0, 10), (10, 10)]

    def create_battlefield(self, color: tuple[int], size: int) -> None:
        self.battlefield = []
        for x in range(size):
            for y in range(size):
                if y % 2:
                    pos = 300
                else:
                    pos = 332
                hf = HexFieldInterface(
                    points=HexFieldInterface.generate_hexagon(
                        33, x, y, pos, 100
                    ),
                    screen=self.screen,
                    color=color,
                    cords=(x, y)
                )
                hf.create_polygon()
                self.battlefield.append(hf)

    def draw_battlefield(self) -> None:
        for hf in self.battlefield:
            hf.draw_polygon()

    def create_bg(self) -> None:
        self.background_image = pygame.image.load(
            os.path.join(
                self.dirname,
                '../images/bg.jpeg'
            ))
        self.blue_flag = pygame.image.load(
            os.path.join(
                self.dirname,
                'sprites/blue_flag.png'
            ))
        self.red_flag = pygame.image.load(
            os.path.join(
                self.dirname,
                'sprites/red_flag.png'
            ))
        desc_frame = pygame.Surface((250, 300))
        desc_frame = desc_frame.convert_alpha()
        desc_frame.fill((255, 204, 0))
        desc_frame.fill((0, 0, 0, 100), desc_frame.get_rect().inflate(-5, -5))
        self.stat_box = desc_frame

    def create_cursors(self) -> None:
        self.cursor_attack_mele = pygame.image.load(
            os.path.join(
                self.dirname,
                'sprites/attack_mele.png'
            )).convert_alpha()
        self.cursor_attack_range = pygame.image.load(
            os.path.join(
                self.dirname,
                'sprites/attack_range.png'
            )).convert_alpha()
        self.cursor_move = pygame.image.load(
            os.path.join(
                self.dirname,
                'sprites/move_coursor.png'
            )).convert_alpha()
        self.cursor_other = pygame.image.load(
            os.path.join(
                self.dirname,
                'sprites/menu_coursor.png'
            )).convert_alpha()

    def draw_bg(self) -> None:
        self.screen.blit(self.background_image, (0, 0))
        self.screen.blit(
            self.stat_box,
            self.stat_box.get_rect(topleft=(25, 400))
        )
        self.screen.blit(
            self.stat_box,
            self.stat_box.get_rect(topleft=(1015, 400))
        )
        self.screen.blit(self.blue_flag, (220, 400))
        self.screen.blit(self.red_flag, (1210, 400))

    def get_active(self) -> HexFieldInterface:
        for hf in self.battlefield:
            if hf.is_active():
                return hf

    def create_units(self) -> None:
        for (stack, enemy) in zip(self.battle.get_player().get_forces(),
                                  self.battle.get_enemy().get_forces()):
            if stack.get_size() > 0:
                tmp_unit = UnitInterface(stack.get_id(),
                                         stack.get_size(),
                                         stack.get_speed(), 1,
                                         stack.get_attack(),
                                         stack.get_protection(),
                                         stack.get_damage(),
                                         stack.get_hp())
                self.units.append(tmp_unit)

            if enemy.get_size() > 0:
                tmp_unit = UnitInterface(enemy.get_id(),
                                         enemy.get_size(),
                                         enemy.get_speed(), 1,
                                         enemy.get_attack(),
                                         enemy.get_protection(),
                                         enemy.get_damage(),
                                         enemy.get_hp(),
                                         True)
                self.units.append(tmp_unit)

    def set_units(self) -> None:
        for idx, unit in enumerate(self.units):
            self.find_by_cords(self.start_cords[idx]).set_unit(unit)

    def set_start_cords(self) -> None:
        player_forces = list()
        enemy_forces = list()

        for idx, (stack, enemy) in enumerate(
                zip(self.battle.get_player().get_forces(),
                    self.battle.get_enemy().get_forces())):
            stack.set_cords(self.start_cords[2*idx])
            enemy.set_cords(self.start_cords[2*idx+1])

            player_forces.append(stack)
            enemy_forces.append(enemy)

        player = self.battle.get_player()
        player.set_forces(player_forces)
        enemy = self.battle.get_enemy()
        enemy.set_forces(enemy_forces)

        self.battle.set_player(player)
        self.battle.set_enemy(enemy)

    def sort_units(self) -> None:
        n = len(self.units)
        for i in range(n):
            for j in range(0, n-i-1):
                if self.units[j].speed < self.units[j+1].speed:
                    self.units[j], self.units[j+1] =\
                        self.units[j+1], self.units[j]

    def sort_battlefield(self) -> None:
        n = len(self.battlefield)
        for i in range(n):
            for j in range(0, n-i-1):
                if self.battlefield[j].cords[1] >\
                        self.battlefield[j+1].cords[1]:
                    self.battlefield[j], self.battlefield[j+1] =\
                        self.battlefield[j+1], self.battlefield[j]

    def determine_polygon(self, x, y) -> tuple[int]:
        for hf in self.battlefield:
            if hf.object.collidepoint((x, y)):
                return hf
        return False

    def color_map(self, color) -> None:
        for hf in self.battlefield:
            self.change_color(color, hf)

    def set_available_moves(self, cords: list[tuple[int]]) -> None:
        for hf in self.battlefield:
            if hf.cords in cords:
                self.change_color((0, 0, 0, self.transparency), hf)

    def set_attack_moves(self, cords: tuple[int], shooter: bool) -> tuple[int]:
        dest_cords = self.get_active().get_cords()
        for hf in self.battlefield:
            if not shooter:
                if hf.cords == cords:
                    dest_cords = hf.cords
                    self.change_color((150, 0, 0, self.transparency), hf)
            if hf.cords == self.get_active().get_cords():
                self.change_color((150, 0, 0, self.transparency), hf)
        return dest_cords

    def change_color(self, color: tuple[int], hf: HexFieldInterface) -> None:
        hf.color = color
        hf.create_polygon()

    def find_by_cords(self, cords: tuple[int]) -> HexFieldInterface:
        for hf in self.battlefield:
            if hf.cords == cords:
                return hf

    def move_unit(self, destination: tuple[int]) -> None:
        unit = self.get_active().take_unit()
        self.find_by_cords(destination).set_unit(unit)

        player_forces = list()
        enemy_forces = list()

        for idx, (stack, enemy) in enumerate(
                zip(self.battle.get_player().get_forces(),
                    self.battle.get_enemy().get_forces())):
            if unit.get_id() == stack.get_id():
                stack.set_cords(destination)
            if unit.get_id() == enemy.get_id():
                enemy.set_cords(destination)

            player_forces.append(stack)
            enemy_forces.append(enemy)

        player = self.battle.get_player()
        player.set_forces(player_forces)
        enemy = self.battle.get_enemy()
        enemy.set_forces(enemy_forces)

        self.battle.set_player(player)
        self.battle.set_enemy(enemy)

    def next_unit(self) -> None:
        active_idx = [i for i, x in enumerate(self.units) if x.is_active()][0]
        self.units[active_idx].active = False
        for i in range(len(self.units)):
            if self.units[(active_idx+i+1) % len(self.units)].is_alive():
                self.units[(active_idx+i+1) % len(self.units)].active = True
                return

    def update_transparency(self) -> None:
        self.transparency += self.transparency_step
        if self.transparency == 175 or self.transparency == 50:
            self.transparency_step = -self.transparency_step

    def get_possible_enemy_attacks(self, possible_moves) -> list[tuple[int]]:
        possible_attacks = list()
        for hf in self.battlefield:
            if hf.get_unit():
                if hf.get_unit().is_enemy():
                    continue
                if self.battle.get_enemy().get_stack(
                   self.get_active().get_cords()).get_type():
                    possible_attacks.append(hf.get_cords())
                    continue
                if self.isin_neighbourhood(hf, possible_moves):
                    possible_attacks.append(hf.get_cords())
        return possible_attacks

    def move_enemy(self, possible_moves) -> None:
        possible_attack_cords = self.get_possible_enemy_attacks(possible_moves)
        if possible_attack_cords:
            a_cords = self.battle.get_possible_attack_cords(
                self.get_active().get_cords(), possible_attack_cords[0], False)

            new_cords = self.set_attack_moves(
                    a_cords[1],
                    self.battle.get_enemy().get_stack(
                        self.get_active().get_cords()).get_type()
                )

            attack = self.battle.perform_attack(
                self.get_active().get_cords(),
                possible_attack_cords[0],
                False
            )

            if attack[0]:
                self.update_stacks(new_cords, possible_attack_cords[0], False)

            if attack[1]:
                if self.find_by_cords(
                   possible_attack_cords[0]).is_active():
                    self.next_unit()
                    self.changed_active = 1
                corpse = self.find_by_cords(
                    possible_attack_cords[0]).take_unit()
                corpse.alive = False
                self.find_by_cords(
                    possible_attack_cords[0]).corpse = corpse

            if attack[2]:
                if self.find_by_cords(a_cords[1]).is_active():
                    self.next_unit()
                    self.changed_active = 1
                corpse = self.find_by_cords(a_cords[1]).take_unit()
                corpse.alive = False
                self.find_by_cords(a_cords[1]).corpse = corpse
        else:
            self.move_unit(possible_moves[0])

    @staticmethod
    def are_neighbours(hex_1: HexFieldInterface,
                       hex_2: HexFieldInterface) -> bool:
        even_diffs = ((-1, 0), (0, 1), (1, -1), (1, 0), (1, 1), (0, 1))
        odd_diffs = ((-1, 0), (-1, -1), (0, -1), (1, 0), (0, 1), (-1, 1))
        diffs = even_diffs if not hex_2.get_cords()[1] % 2 else odd_diffs
        for diff in diffs:
            move_X, move_Y = diff
            if (hex_1.get_cords()[0] == hex_2.get_cords()[0]+move_X) and\
               (hex_1.get_cords()[1] == hex_2.get_cords()[1]+move_Y):
                return True
        return False

    def isin_neighbourhood(self, hex: HexFieldInterface,
                           cords_list: list[tuple[int]]) -> bool:
        for cord in cords_list:
            if self.find_by_cords(cord):
                if BattefieldInterface.are_neighbours(
                        self.find_by_cords(cord), hex):
                    return True
        return False

    def update_stacks(self, hex_attack, hex_def, player: bool) -> None:
        if player:
            attacker = self.battle.get_player().get_stack(hex_attack)
            defender = self.battle.get_enemy().get_stack(hex_def)
        else:
            attacker = self.battle.get_enemy().get_stack(hex_attack)
            defender = self.battle.get_player().get_stack(hex_def)

        a_unit = self.find_by_cords(self.get_active().get_cords()).take_unit()
        a_unit.stack_size = attacker.get_size()
        a_unit.hp = attacker.get_hp()
        self.find_by_cords(hex_attack).set_unit(a_unit)
        self.find_by_cords(hex_attack).active = True

        d_unit = self.find_by_cords(hex_def).take_unit()
        d_unit.stack_size = defender.get_size()
        d_unit.hp = defender.get_hp()
        self.find_by_cords(defender.get_cords()).set_unit(d_unit)

    def play_music(self) -> None:
        pygame.mixer.music.load(self.music_path)
        pygame.mixer.music.play(-1)

    def check_end(self) -> int:
        player_alive = 0
        enemy_alive = 0

        for unit in self.units:
            if unit.is_alive():
                if unit.is_enemy():
                    enemy_alive += 1
                else:
                    player_alive += 1

        if not player_alive:
            return 2
        if not enemy_alive:
            return 1
        return 0

    def draw_cursor(self, cursor: pygame.Surface,
                    mouse_x: int, mouse_y: int) -> None:
        cursor = pygame.transform.scale(cursor, (30, 30))
        self.screen.blit(
            cursor,
            cursor.get_rect(center=(mouse_x, mouse_y))
        )

    def draw_cursor_screen(self, polygon: HexFieldInterface, shooter: bool,
                           mouse_x: int, mouse_y: int,
                           possible_moves: list[tuple[int]]) -> None:
        if polygon:
            if polygon.get_unit():
                self.draw_frame(polygon.get_unit().get_desc_surf(),
                                25, 400, not polygon.get_unit().is_enemy())
                if polygon.get_unit().is_enemy():
                    if shooter:
                        self.draw_cursor(self.cursor_attack_range,
                                         mouse_x, mouse_y)
                    else:
                        if self.isin_neighbourhood(polygon, possible_moves):
                            self.draw_cursor(self.cursor_attack_mele,
                                             mouse_x, mouse_y)
                        else:
                            self.draw_cursor(self.cursor_other,
                                             mouse_x, mouse_y)
                else:
                    self.draw_cursor(self.cursor_other, mouse_x, mouse_y)
            else:
                if polygon.get_cords() in possible_moves:
                    self.draw_cursor(self.cursor_move, mouse_x, mouse_y)
                else:
                    self.draw_cursor(self.cursor_other, mouse_x, mouse_y)
        else:
            self.draw_cursor(self.cursor_other, mouse_x, mouse_y)

    def draw_frame(self, frame: pygame.Surface,
                   x_cord: int, y_cord: int, is_player: bool) -> None:
        if is_player:
            self.screen.blit(
                frame,
                frame.get_rect(topleft=(x_cord, y_cord))
            )
            self.screen.blit(self.blue_flag, (220, 400))
        else:
            self.screen.blit(
                frame,
                frame.get_rect(topleft=(x_cord+990, y_cord))
            )
            self.screen.blit(self.red_flag, (1210, 400))

    def run(self) -> None:
        self.play_music()
        self.create_bg()
        self.create_cursors()
        self.create_battlefield(color=(0, 0, 0, 255), size=11)
        self.sort_battlefield()
        self.create_units()
        self.set_units()
        self.set_start_cords()
        self.sort_units()

        mouse_x, mouse_y = 0, 0
        clock = pygame.time.Clock()

        pygame.mouse.set_visible(False)
        self.units[0].active = True

        possible_moves = self.battle.get_possible_move_cords(
            self.get_active().get_cords(), True)

        self.set_available_moves(possible_moves)

        while self.RUN_BF:
            clock.tick(120)
            self.changed_active = 0
            moved = 0
            mouse_clicked = False
            if not self.get_active().get_unit().is_enemy():
                shooter = self.battle.get_player().get_stack(
                    self.get_active().get_cords()
                    ).get_type()
            else:
                shooter = self.battle.get_enemy().get_stack(
                    self.get_active().get_cords()
                    ).get_type()

            self.update_transparency()
            self.draw_bg()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.RUN_BF = False
                elif event.type == pygame.MOUSEMOTION:
                    mouse_x, mouse_y = event.pos
                elif event.type == pygame.MOUSEBUTTONUP:
                    mouse_x, mouse_y = event.pos
                    if event.button == 1:
                        mouse_clicked = True

            self.color_map((0, 0, 0, 175))
            polygon = self.determine_polygon(mouse_x, mouse_y)
            if polygon and not mouse_clicked:
                self.change_color((150, 150, 0, 50), polygon)

            self.set_available_moves(possible_moves)

            if self.get_active().get_unit().is_enemy():
                self.move_enemy(possible_moves)
                moved = 1

            self.change_color((0, 150, 0, 175), self.get_active())

            if not self.get_active().get_unit().is_enemy():
                if polygon and not mouse_clicked:
                    if polygon.get_unit():
                        if polygon.get_unit().is_enemy():
                            if self.isin_neighbourhood(polygon, possible_moves)\
                            and not shooter:
                                a_cords = self.battle.get_possible_attack_cords(
                                    self.get_active().get_cords(),
                                    polygon.get_cords(),
                                    True
                                )
                                self.set_attack_moves(
                                    a_cords[1],
                                    self.battle.get_player().get_stack(
                                        self.get_active().get_cords()).get_type()
                                )

                            if shooter:
                                self.set_attack_moves((), shooter)
                            self.change_color((150, 0, 0, 50), polygon)

            if polygon and mouse_clicked:
                if polygon.cords in possible_moves:
                    moved = 1
                    self.move_unit(polygon.cords)
                elif polygon.get_unit():
                    if polygon.get_unit().is_enemy():
                        a_cords = self.battle.get_possible_attack_cords(
                                self.get_active().get_cords(),
                                polygon.get_cords(),
                                True
                            )
                        new_cords = self.set_attack_moves(
                                a_cords[1],
                                self.battle.get_player().get_stack(
                                    self.get_active().get_cords()).get_type()
                            )

                        attack = self.battle.perform_attack(
                            self.get_active().get_cords(),
                            polygon.get_cords(),
                            True
                        )
                        if attack[0]:
                            moved = 1
                            self.update_stacks(
                                new_cords,
                                polygon.get_cords(),
                                True
                            )
                        if attack[1]:
                            if self.find_by_cords(
                               polygon.get_cords()).is_active():
                                self.next_unit()
                                self.changed_active = 1
                            corpse = self.find_by_cords(
                                polygon.get_cords()).take_unit()
                            corpse.alive = False
                            self.find_by_cords(
                                polygon.get_cords()).corpse = corpse

                        if attack[2]:
                            if self.find_by_cords(a_cords[1]).is_active():
                                self.next_unit()
                                self.changed_active = 1
                            corpse = self.find_by_cords(a_cords[1]).take_unit()
                            corpse.alive = False
                            self.find_by_cords(a_cords[1]).corpse = corpse

            if polygon and not mouse_clicked and\
               polygon.get_cords() in possible_moves:
                self.change_color((0, 150, 0, 50), polygon)

            self.draw_battlefield()
            self.draw_cursor_screen(polygon, shooter, 
                                    mouse_x, mouse_y, possible_moves)

            end_cond = self.check_end()
            if end_cond == 1:
                print('You won!')
                break
            if end_cond == 2:
                print('You lose!')
                break

            if moved:
                if not self.changed_active:
                    self.next_unit()
                is_player = False if self.get_active().get_unit().is_enemy()\
                    else True
                possible_moves = self.battle.get_possible_move_cords(
                    self.get_active().get_cords(), is_player)

            pygame.display.flip()
