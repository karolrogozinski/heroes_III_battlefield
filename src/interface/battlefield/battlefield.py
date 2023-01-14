import os
import random

import pygame

from interface.battlefield.hexfield import HexFieldInterface
from interface.battlefield.unit import UnitInterface


class BattefieldInterface():
    def __init__(self) -> None:
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
            '../../music/Fortuna.mp3'
        )
        self.amounts = None
        self.units = []
        self.start_cords = [(0, 0), (0, 2), (0, 4), (0, 5), (0, 6), (0, 8), (0, 10)]
    
    def create_battlefield(self, color: tuple[int], size: int) -> None:
        self.battlefield = []
        for x in range(size):
            for y in range(size):
                if y % 2:
                    pos = 300
                else:
                    pos = 332
                hf = HexFieldInterface(
                    points=HexFieldInterface.generate_hexagon(33, x, y, pos, 100),
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
                '../../images/battlefield_background.jpg'
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

    def draw_bg(self) -> None:
        self.screen.blit(self.background_image, (0, 0))
        self.screen.blit(self.blue_flag, (20, 0))
        self.screen.blit(self.red_flag, (1200, 0))

    def get_active(self) -> HexFieldInterface:
        for hf in self.battlefield:
            if hf.is_active():
                return hf

    def create_units(self) -> None:
        for idx, (amount, cords) in enumerate(zip(self.amounts, self.start_cords)):
            temp_unit = UnitInterface(idx+1, amount, idx)
            temp_enemy = UnitInterface(idx+8, amount*2, idx, enemy=True)
            self.units.append(temp_unit)
            self.units.append(temp_enemy)
            self.find_by_cords(cords).set_unit(temp_unit)
            self.find_by_cords((cords[0]+10, cords[1])).set_unit(temp_enemy)

    def sort_units(self) -> None:
        n = len(self.units)
        for i in range(n):
            for j in range(0, n-i-1):
                if self.units[j].speed < self.units[j+1].speed:
                    self.units[j], self.units[j+1] = self.units[j+1], self.units[j]

    def sort_battlefield(self) -> None:
        n = len(self.battlefield)
        for i in range(n):
            for j in range(0, n-i-1):
                if self.battlefield[j].cords[1] > self.battlefield[j+1].cords[1] :
                    self.battlefield[j], self.battlefield[j+1] = self.battlefield[j+1], self.battlefield[j]

    def determine_polygon(self, x, y) -> tuple[int]:
        for hf in self.battlefield:
            if hf.object.collidepoint((x, y)):
                return hf
        return False

    def color_map(self, color) -> None:
        for hf in self.battlefield:
            self.change_color(color, hf)

    def set_available_moves(self, cords) -> None:
        for hf in self.battlefield:
            if hf.cords in cords:
                self.change_color((0, 0, 0, self.transparency), hf)

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

    def next_unit(self) -> None:
        active_idx = [i for i, x in enumerate(self.units) if x.is_active()][0]
        self.units[active_idx].active = False
        self.units[(active_idx+1) % len(self.units)].active = True

    def update_transparency(self) -> None:
        self.transparency += self.transparency_step
        if self.transparency == 175 or self.transparency == 50:
            self.transparency_step = -self.transparency_step

    def move_enemy(self, possible_moves) -> None:
        if self.get_active().get_unit().is_enemy():
            self.move_unit(possible_moves[0])
            self.next_unit()

    def play_music(self) -> None:
        pygame.mixer.music.load(self.music_path)
        pygame.mixer.music.play(-1)

    def run(self) -> None:
        self.play_music()
        self.create_bg()
        self.create_battlefield(color=(0, 0, 0, 255), size=11)
        self.sort_battlefield()
        self.create_units()
        self.sort_units()

        mouse_x, mouse_y = 0, 0
        possible_moves = [(random.randint(0, 10), random.randint(0, 10)) for i in range(30)]
        self.units[0].active = True

        while self.RUN_BF:
            moved = 0
            mouse_clicked = False

            self.update_transparency()            
            self.draw_bg()

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.RUN_BF = False
                elif event.type == pygame.MOUSEMOTION:
                    mouse_x, mouse_y = event.pos
                elif event.type == pygame.MOUSEBUTTONUP:
                    mouse_x, mouse_y = event.pos
                    mouse_clicked = True

            self.color_map((0, 0, 0, 175))
            polygon = self.determine_polygon(mouse_x, mouse_y)
            if polygon and not mouse_clicked:
                self.change_color((150, 150, 0, 50), polygon)

            self.set_available_moves(possible_moves)
            self.change_color((0, 150, 0, 175), self.get_active())
            self.move_enemy(possible_moves)

            if polygon and not mouse_clicked and polygon.cords in possible_moves:
                if polygon.get_unit():
                    if polygon.get_unit().is_enemy():
                        self.change_color((150, 0, 0, 50), polygon)
                else:
                    self.change_color((0, 150, 0, 50), polygon)
            if polygon and mouse_clicked and polygon.cords in possible_moves:
                moved = 1
                self.move_unit(polygon.cords)


            self.draw_battlefield()
            if moved:
                self.next_unit()
                possible_moves = [(random.randint(0, 10), random.randint(0, 10)) for i in range(20)]

            pygame.display.flip()
