import os

import pygame


class UnitInterface:
    def __init__(self, id: int, stack_size: int, speed=1, alive: bool = True, enemy: bool = False) -> None:
        self.font = pygame.font.SysFont(None, 35)
        self.id = id
        self.stack_size = stack_size
        self.alive = alive
        self.dirname = os.path.dirname(os.path.abspath(__file__))
        self.active = False
        self.speed = speed
        self.enemy = enemy
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
        if enemy:
            self.image_alive = pygame.transform.flip(self.image_alive, True, False)
            self.image_dead = pygame.transform.flip(self.image_dead, True, False)

    def get_unit_surf(self) -> pygame.Surface:
        if self.alive:
            return self.image_alive
        return self.image_dead

    def get_size_surf(self) -> pygame.Surface:
        # if self.enemy:
            # color = (200, 0, 0)
        # else:
        color = (255, 255, 255)

        font_surf = self.font.render(f'{self.stack_size}', True, color)

        if self.alive:
            return font_surf

        font_surf = self.font.render('', True, color)
        return font_surf

    def is_active(self) -> bool:
        return self.active

    def is_enemy(self) -> bool:
        return self.enemy
