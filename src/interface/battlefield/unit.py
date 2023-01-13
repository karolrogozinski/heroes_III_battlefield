import os

import pygame


class Unit:
    def __init__(self, id: int, stack_size: int, alive: bool = True) -> None:
        self.font = pygame.font.SysFont(None, 35)
        self.id = id
        self.stack_size = stack_size
        self.alive = alive
        self.dirname = os.path.dirname(os.path.abspath(__file__))
        self.active = True
        self.image_alive = pygame.image.load(
            os.path.join(
                self.dirname,
                f'sprites/{id}_alive.png'
            )).convert_alpha()
        self.image_dead = pygame.image.load(
            os.path.join(
                self.dirname,
                f'sprites/{id}_dead.png'
            )).convert_alpha()

    def get_unit_surf(self) -> pygame.Surface:
        if self.alive:
            return self.image_alive
        return self.image_dead

    def get_size_surf(self) -> pygame.Surface:
        font_surf = self.font.render(f'{self.stack_size}', True, (255, 255, 255))
        rect = font_surf.get_rect()

        if self.alive:
            # pygame.draw.rect(font_surf, (255, 255, 255), rect, 1)
            return font_surf

        font_surf = self.font.render('', True, (255, 255, 255))
        return font_surf
