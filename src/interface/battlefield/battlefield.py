import os

import pygame

from interface.battlefield.hexfield import HexField
from interface.battlefield.unit import Unit


class Battefield():
    def __init__(self) -> None:
        pygame.init()
        self.window_size = (1280, 720)
        self.dirname = os.path.dirname(os.path.abspath(__file__))
        self.screen = pygame.display.set_mode(self.window_size)
        self.background_image = pygame.image.load(
            os.path.join(
                self.dirname,
                '../../images/battlefield_background.jpg'
            ))
        self.screen.blit(self.background_image, (0, 0))
        self.battlefield = []
        self.RUN_BF = True
        self.transparency = 50
        self.transparency_step = 0.5
        self.music_path = os.path.join(
            self.dirname,
            '../../music/Fortuna.mp3'
        )
    
    def create_battlefield(self, color: tuple[int], size: int) -> None:
        self.battlefield = []
        for x in range(size):
            for y in range(size):
                if y % 2:
                    hf = HexField(
                        points=HexField.generate_hexagon(33, x, y, 300, 100),
                        screen=self.screen,
                        color=color,
                        cords=(x, y)
                    )
                else:
                    hf = HexField(
                        points=HexField.generate_hexagon(33, x, y, 332, 100),
                        screen=self.screen,
                        color=color,
                        cords=(x, y)
                    )
                hf.create_polygon()
                self.battlefield.append(hf)

    def draw_battlefield(self) -> None:
        for hf in self.battlefield:
            hf.draw_polygon()

    def get_active(self) -> HexField:
        for hf in self.battlefield:
            if hf.is_active():
                return hf

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
                self.change_color((0, 150, 0, self.transparency/2), hf)

    def change_color(self, color: tuple[int], hf: HexField) -> None:
        hf.color = color
        hf.create_polygon()

    def find_by_cords(self, cords: tuple[int]) -> HexField:
        for hf in self.battlefield:
            if hf.cords == cords:
                return hf

    def move_unit(self, destination: tuple[int]) -> None:
        unit = self.get_active().take_unit()
        self.find_by_cords(destination).unit = unit

    def update_transparency(self) -> None:
        self.transparency += self.transparency_step
        if self.transparency == 150 or self.transparency == 50:
            self.transparency_step = -self.transparency_step

    def run(self) -> None:
        pygame.mixer.music.load(self.music_path)
        pygame.mixer.music.play(-1)

        mouse_x, mouse_y = 0, 0
        possible_moves = [(x, y) for x in range(5) for y in range(5) if x+y<8 ]

        self.create_battlefield(
            color=(0, 0, 0, 150),
            size=11
        )
        self.sort_battlefield()

        archangel = Unit(1, 50)
        archangel_dead = Unit(1, 50, alive=False)
        self.battlefield[0].unit = archangel
        self.battlefield[3].corpse = archangel_dead

        while self.RUN_BF:
            self.update_transparency()
            
            mouse_clicked = False
            self.screen.blit(self.background_image, (0, 0))
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    self.RUN_BF = False
                elif event.type == pygame.MOUSEMOTION:
                    mouse_x, mouse_y = event.pos
                elif event.type == pygame.MOUSEBUTTONUP:
                    mouse_x, mouse_y = event.pos
                    mouse_clicked = True

            self.color_map((0, 0, 0, 150))
            polygon = self.determine_polygon(mouse_x, mouse_y)

            if polygon and not mouse_clicked:
                self.change_color((150, 150, 0, 50), polygon)

            self.set_available_moves(possible_moves)
            self.change_color((0, 150, 0, 255), self.get_active())

            if polygon and not mouse_clicked and polygon.cords in possible_moves:
                self.change_color((0, 150, 0, 150), polygon)
            if polygon and mouse_clicked and polygon.cords in possible_moves:
                self.move_unit(polygon.cords)

            self.draw_battlefield()

            pygame.display.flip()
