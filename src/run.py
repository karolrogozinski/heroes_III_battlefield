all__ = ['main']

import pygame
import pygame_menu
from pygame_menu.examples import create_example_window

import os
from typing import Optional


dirname = os.path.dirname(os.path.abspath(__file__))

# Constants and global variables
FPS = 30
WINDOW_SIZE = (1200, 800)

sound: Optional['pygame_menu.sound.Sound'] = None
surface: Optional['pygame.Surface'] = None
main_menu: Optional['pygame_menu.Menu'] = None

background_image = pygame_menu.BaseImage(
    image_path=os.path.join(dirname, 'images/menu_background.jpg')
)


def main_background() -> None:
    """
    Background color of the main menu, on this function user can plot
    images, play sounds, etc.
    """
    background_image.draw(surface)


def create_main_menu() -> pygame_menu.Menu:
    main_menu_theme = pygame_menu.themes.THEME_DARK.copy()
    main_menu_theme.set_background_color_opacity(0.75)
    main_menu_theme.title_font_size = 30

    main_menu = pygame_menu.Menu(
        height=WINDOW_SIZE[1] * 0.7,
        onclose=pygame_menu.events.EXIT,
        theme=main_menu_theme,
        title='Main Menu',
        width=WINDOW_SIZE[0] * 0.8
    )

    return main_menu, main_menu_theme


def create_play_menu(main_theme) -> pygame_menu.Menu:
    play_theme = main_theme.copy()
    play_theme.background_color = pygame_menu.BaseImage(
        image_path=pygame_menu.baseimage.IMAGE_EXAMPLE_CARBON_FIBER
    )

    play_menu = pygame_menu.Menu(
        height=WINDOW_SIZE[1] * 0.7,
        onclose=pygame_menu.events.EXIT,
        theme=play_theme,
        title='Game will start here',
        width=WINDOW_SIZE[0] * 0.8
    )
    play_menu.add.button('Back', pygame_menu.events.BACK)

    return play_menu


def create_settings_menu(main_theme) -> pygame_menu.Menu:
    settings_theme = main_theme.copy()

    settings_menu = pygame_menu.Menu(
        height=WINDOW_SIZE[1] * 0.7,
        onclose=pygame_menu.events.EXIT,
        theme=settings_theme,
        title='Settings',
        width=WINDOW_SIZE[0] * 0.8
    )    
    settings_menu.add.button('Back', pygame_menu.events.BACK)

    return settings_menu


def main() -> None:
    global main_menu
    global sound
    global surface

    surface = create_example_window('Heroes with AI', WINDOW_SIZE)
    clock = pygame.time.Clock()

    main_menu, main_menu_theme = create_main_menu()
    play_menu = create_play_menu(main_menu_theme)
    settings_menu = create_settings_menu(main_menu_theme)

    main_menu.add.button('Play', play_menu)
    main_menu.add.button('Settings', settings_menu)
    main_menu.add.button('Quit', pygame_menu.events.EXIT)

    pygame.mixer.music.load(os.path.join(dirname, 'music/VistaPoint.mp3'))
    pygame.mixer.music.play(-1)

    while True:
        clock.tick(FPS)
        main_menu.mainloop(surface, main_background, fps_limit=FPS)
        pygame.display.flip()


if __name__ == '__main__':
    main()
