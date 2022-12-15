import os
from typing import Optional

import pygame
import pygame_menu
from pygame_menu.examples import create_example_window

import controller


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
        self.create_play_menu()
        self.create_settings_menu()
        self.settings_controller = controller.Controller(os.path.join(self.dirname, 'conf.ini'))
        self.set_menu_buttons()

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
        play_theme.background_color = pygame_menu.BaseImage(
            image_path=pygame_menu.baseimage.IMAGE_EXAMPLE_CARBON_FIBER
        )

        self.play_menu = pygame_menu.Menu(
            height=self.menu_size[1],
            onclose=pygame_menu.events.EXIT,
            theme=play_theme,
            title='Game will start here',
            width=self.menu_size[0]
        )
        self.play_menu.add.button('Back', pygame_menu.events.BACK)

    def create_settings_menu(self) -> None:
        settings_theme = self.main_menu_theme.copy()

        self.settings_menu = pygame_menu.Menu(
            height=self.menu_size[1],
            onclose=pygame_menu.events.EXIT,
            theme=settings_theme,
            title='Settings',
            width=self.menu_size[0]
        ) 

        volumes = [(str(i/10), i/10) for i in range (11)]

        self.settings_menu.add.selector('Music: ', [('On', True), ('Off', False)], onchange=self.change_music)
        self.settings_menu.add.selector('Volume: ', volumes, default=10, onchange=self.change_volume)

        self.settings_menu.add.button('Back', pygame_menu.events.BACK)

    def set_menu_buttons(self):
        self.main_menu.add.button('Play', self.play_menu)
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
            self.settings_controller.GetSetting('MUSIC', 'PATH')
        )
        music_volume = self.settings_controller.GetSetting('MUSIC', 'VOLUME')

        pygame.mixer.music.load(music_path)
        pygame.mixer.music.set_volume(float(music_volume))
        pygame.mixer.music.play(-1)

    def run(self) -> None:
        self.surface = create_example_window('Heroes with AI', self.window_size)
        self.clock = pygame.time.Clock()
        self.play_music()
        
        while True:
            self.clock.tick(self.fps)
            self.main_menu.mainloop(self.surface, self.main_background, fps_limit=self.fps)
            pygame.display.flip()
