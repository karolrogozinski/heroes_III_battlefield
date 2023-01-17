import os

import pygame


class UnitInterface:
    def __init__(self, id: int, stack_size: int, speed: int, alive: bool,
                 attack: int, defence: int, damage: tuple[int], hp: int,
                 enemy: bool = False) -> None:
        self.font = pygame.font.SysFont(None, 36)
        self.id = id
        self.stack_size = stack_size
        self.alive = alive
        self.dirname = os.path.dirname(os.path.abspath(__file__))
        self.active = False
        self.speed = speed
        self.attack = attack
        self.defence = defence
        self.damage = damage
        self.hp = hp
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
        self.image_frame = pygame.image.load(
            os.path.join(
                self.dirname,
                'sprites/frame.png'
            )).convert_alpha()
        if enemy:
            self.image_alive = pygame.transform.flip(self.image_alive,
                                                     True, False)
            self.image_dead = pygame.transform.flip(self.image_dead,
                                                    True, False)

    def get_unit_surf(self) -> pygame.Surface:
        if self.alive:
            return self.image_alive
        return self.image_dead

    def get_size_surf(self) -> pygame.Surface:
        color = (255, 255, 255)
        font_surf = self.font.render(f'{self.stack_size}', True, color)

        if self.alive:
            return font_surf

        font_surf = self.font.render('', True, color)
        return font_surf

    def get_desc_surf(self) -> pygame.Surface:
        desc_frame = pygame.Surface((250, 300))
        desc_frame = desc_frame.convert_alpha()
        desc_frame.fill((255, 204, 0))
        desc_frame.fill((0, 0, 0, 100), desc_frame.get_rect().inflate(-5, -5))

        font_surf = self.font.render(f'Id: {self.id}', True, (255, 255, 255))
        desc_frame.blit(font_surf, font_surf.get_rect(topleft=(25, 25)))
        font_surf = self.font.render(f'Attack: {self.attack}', True, (255, 255, 255))
        desc_frame.blit(font_surf, font_surf.get_rect(topleft=(25, 70)))
        font_surf = self.font.render(f'Defence: {self.defence}', True, (255, 255, 255))
        desc_frame.blit(font_surf, font_surf.get_rect(topleft=(25, 115)))
        font_surf = self.font.render(f'Total HP: {self.hp}', True, (255, 255, 255))
        desc_frame.blit(font_surf, font_surf.get_rect(topleft=(25, 160)))
        font_surf = self.font.render(f'Damage: {self.damage[0]} - {self.damage[1]}', True, (255, 255, 255))
        desc_frame.blit(font_surf, font_surf.get_rect(topleft=(25, 205)))
        font_surf = self.font.render(f'Speed: {self.speed}', True, (255, 255, 255))
        desc_frame.blit(font_surf, font_surf.get_rect(topleft=(25, 249)))

        if self.is_alive():
            return desc_frame

    def is_active(self) -> bool:
        return self.active

    def is_enemy(self) -> bool:
        return self.enemy

    def is_alive(self) -> bool:
        return self.alive

    def get_id(self) -> bool:
        return self.id
