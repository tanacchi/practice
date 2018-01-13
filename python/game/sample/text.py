# -*- coding:utf-8 -*-
import pygame
from pygame.locals import *
import sys

def main():
    pygame.init()
    screen = pygame.display.set_mode((300, 200))
    pygame.display.set_caption("GAME")
    font = pygame.font.Font(None, 55)

    while (True):
        screen.fill((0,0,0))
        text = font.render("TEST", True, (255,255,255))
        screen.blit(text, [20, 100])
        pygame.display.update()

        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()

if __name__ == "__main__":
    main()
