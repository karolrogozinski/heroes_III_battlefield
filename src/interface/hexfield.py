import pygame
import numpy as np

from .unit import UnitInterface


class HexFieldInterface:
    def __init__(self, points, screen, color, cords) -> None:
        self.points = points
        self.screen = screen
        self.color = color
        self.cords = cords
        self.target_rect = None
        self.shape_surf = None
        self.object = None
        self.unit = None
        self.corpse = None

    def create_polygon(self) -> None:
        lx, ly = zip(*self.points)
        min_x, min_y, max_x, max_y = min(lx), min(ly), max(lx), max(ly)

        self.target_rect = pygame.Rect(min_x, min_y,
                                       max_x - min_x, max_y - min_y)
        self.shape_surf = pygame.Surface(self.target_rect.size,
                                         pygame.SRCALPHA)
        self.object = pygame.draw.polygon(
            self.shape_surf,
            self.color,
            [(x - min_x, y - min_y) for x, y in self.points])
        self.object.center = ((max_x + min_x)/2, (max_y + min_y)/2)

    def draw_unit(self, body) -> None:
        u_surf = body.get_unit_surf()
        center = self.target_rect.center
        self.screen.blit(
            u_surf,
            u_surf.get_rect(midbottom=(center[0], center[1]+20))
        )
        font_surf = body.get_size_surf()
        self.screen.blit(
            font_surf,
            font_surf.get_rect(midbottom=(center[0], center[1]+30))
        )

    def is_active(self) -> bool:
        if self.unit:
            return True if self.unit.is_active() else False
        return False

    def take_unit(self) -> UnitInterface:
        unit = self.unit
        self.unit = None
        return unit

    def get_unit(self) -> UnitInterface:
        return self.unit

    def get_cords(self) -> tuple[int]:
        return self.cords

    def set_unit(self, unit: UnitInterface) -> None:
        self.unit = unit

    @staticmethod
    def generate_hexagon(size, x, y, x_pad, y_pad) -> tuple[tuple[float]]:
        x *= size + size - 5
        y *= size + size - 13
        x += x_pad
        y += y_pad
        h = size * np.sqrt(3)
        return (
            (x+h/2, y),
            (x+h, y+size/2),
            (x+h, y+3*size/2),
            (x+h/2, y+2*size),
            (x, y+3*size/2),
            (x, y+size/2)
        )

    def draw_polygon(self):
        self.screen.blit(self.shape_surf, self.target_rect)

        if self.corpse:
            self.draw_unit(self.corpse)

        if self.unit:
            self.draw_unit(self.unit)
