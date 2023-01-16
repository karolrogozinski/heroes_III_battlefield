import os
from typing import Optional

import pygame
import pygame_menu
from pygame_menu.examples import create_example_window
from pygame_menu.locals import ALIGN_CENTER

from .interface.battlefield import BattefieldInterface

from .controller import Controller
from .battle import Battle
from .hero import Hero
from .stack import Stack


class MainMenu():
    def __init__(self):
        pygame.init()
        self.dirname = os.path.dirname(os.path.abspath(__file__))
        self.fps = 30
        self.window_size = (1280, 720)
        self.menu_size = (900, 500)
        pygame.display.set_mode(self.window_size)
        self.surface: Optional['pygame.Surface'] = None
        self.background_image = pygame_menu.BaseImage(
            image_path=os.path.join(self.dirname, 'images/menu_background.jpg')
        )
        self.create_main_menu()
        self.create_settings_menu()
        self.create_play_menu()
        self.settings_controller = Controller(
            os.path.join(self.dirname, 'conf.ini'))
        self.set_menu_buttons()
        self.RUN_MENU = True
        self.RUN_GAME = False
        self.difficulty = 1

    def main_background(self) -> None:
        self.background_image.draw(self.surface)

    def create_main_menu(self) -> None:
        self.main_menu_theme = pygame_menu.themes.THEME_DARK.copy()
        self.main_menu_theme.set_background_color_opacity(0.75)
        self.main_menu_theme.title_font_size = 30

        self.main_menu = pygame_menu.Menu(
            height=self.menu_size[1],
            onclose=pygame_menu.events.EXIT,
            theme=self.main_menu_theme,
            title='Main Menu',
            width=self.menu_size[0]
        )

    def create_play_menu(self) -> None:
        play_theme = self.main_menu_theme.copy()

        self.play_menu = pygame_menu.Menu(
            height=self.menu_size[1],
            onclose=pygame_menu.events.EXIT,
            theme=play_theme,
            title='Main Menu',
            width=self.menu_size[0],
            columns=7,
            rows=6
        )

        volumes = [(str(10*i), 10*i) for i in range(11)]
        self.background_image = pygame_menu.BaseImage(
            image_path=os.path.join(self.dirname, 'images/menu_background.jpg')
        )

        fcts = [self.set_1, self.set_2, self.set_3, self.set_4,
                self.set_5, self.set_6, self.set_7]

        for i in range(1, 8):
            if i == 4:
                self.play_menu.add.label('Player')
            else:
                self.play_menu.add.label('')

            image = pygame_menu.BaseImage(
                image_path=os.path.join(
                    self.dirname,
                    f'interface/sprites/{i}_alive.png')
            ).resize(100, 120)
            self.play_menu.add.image(image)
            self.play_menu.add.selector(
                '',
                volumes,
                default=1,
                onchange=fcts[i-1]
            )
            self.play_menu.add.label('')

            if i == 4:
                self.play_menu.add.button(
                    'Play',
                    self.play_game,
                    align=ALIGN_CENTER
                )
                self.play_menu.add.button('Back', pygame_menu.events.BACK)
            else:
                self.play_menu.add.label('')
                self.play_menu.add.label('')

    def set_1(self, _, amount: int) -> None:
        self.p1 = amount

    def set_2(self, _, amount: int) -> None:
        self.p2 = amount

    def set_3(self, _, amount: int) -> None:
        self.p3 = amount

    def set_4(self, _, amount: int) -> None:
        self.p4 = amount

    def set_5(self, _, amount: int) -> None:
        self.p5 = amount

    def set_6(self, _, amount: int) -> None:
        self.p6 = amount

    def set_7(self, _, amount: int) -> None:
        self.p7 = amount

    def create_settings_menu(self) -> None:
        settings_theme = self.main_menu_theme.copy()

        self.settings_menu = pygame_menu.Menu(
            height=self.menu_size[1],
            onclose=pygame_menu.events.EXIT,
            theme=settings_theme,
            title='Settings',
            width=self.menu_size[0]
        )

        volumes = [(str(i/10), i/10) for i in range(11)]

        self.settings_menu.add.selector(
            'Music: ',
            [('On', True), ('Off', False)],
            onchange=self.change_music
        )
        self.settings_menu.add.selector(
            'Volume: ',
            volumes,
            default=10,
            onchange=self.change_volume
        )
        self.settings_menu.add.button('Back', pygame_menu.events.BACK)

    def set_menu_buttons(self):
        self.main_menu.add.button('New game', self.play_menu)
        self.main_menu.add.button('Settings', self.settings_menu)
        self.main_menu.add.button('Quit', pygame_menu.events.EXIT)

    @staticmethod
    def change_music(value, music) -> None:
        if not music:
            pygame.mixer.music.pause()
            return
        pygame.mixer.music.unpause()

    @staticmethod
    def change_volume(value, volume) -> None:
        pygame.mixer.music.set_volume(volume)

    def play_music(self) -> None:
        music_path = os.path.join(
            self.dirname,
            self.settings_controller.get_setting('MUSIC', 'PATH')
        )
        music_volume = self.settings_controller.get_setting('MUSIC', 'VOLUME')

        pygame.mixer.music.load(music_path)
        pygame.mixer.music.set_volume(float(music_volume))
        pygame.mixer.music.play(-1)

    def play_game(self) -> None:
        self.RUN_MENU = False
        self.RUN_GAME = True
        self.main_menu.disable()

    def run(self) -> None:
        self.surface = create_example_window(
            'Heroes with AI',
            self.window_size)
        self.clock = pygame.time.Clock()
        self.play_music()

        while self.RUN_MENU:
            self.clock.tick(self.fps)
            self.main_menu.mainloop(
                self.surface,
                self.main_background,
                fps_limit=self.fps
            )
            pygame.display.flip()

        if self.RUN_GAME:
            player = Hero('Test', 1)
            enemy = Hero('Test', 0)
            amounts = [self.p1, self.p2, self.p3, self.p4,
                       self.p5, self.p6, self.p7]

            for idx, size in enumerate(amounts):
                shooter = 0
                if idx+1 in (2, 5):
                    shooter = 1
                temp_stack = Stack(idx+1, shooter, idx, size, idx+1, 1, 1)
                temp_stack.set_damage((idx+1, idx*2))
                shooter = 0
                if idx+1 == 2:
                    shooter = 1
                temp_stack_enemy = Stack(idx+8, shooter, idx+10,
                                         size*self.difficulty, idx+1, 1, 1)
                temp_stack_enemy.set_damage((idx+1, idx*2))
                player.add_stack(temp_stack)
                enemy.add_stack(temp_stack_enemy)

            battle_ = Battle(player, enemy)
            self.b_field = BattefieldInterface(battle_)
            self.b_field.run()
