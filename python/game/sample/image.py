# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
import sys

def main():
    (w,h) = (640,400)
    (x,y) = (w/2, h/2)
    pygame.init()
    pygame.display.set_mode((w, h), 0, 32)
    screen = pygame.display.get_surface()
    bg = pygame.image.load("img/back.gif").convert_alpha()
    rect_bg = bg.get_rect()
    player = pygame.image.load("img/human.gif").convert_alpha()
    rect_player = player.get_rect()
    rect_player.center = (300, 200)
    while (True):
        pygame.display.update()
        pygame.time.wait(30)
        screen.fill((0, 20, 0, 0))
        screen.blit(bg, rect_bg)
        screen.blit(player, rect_player)

        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    pygame.quit()
                    sys.exit()

if __name__ == "__main__":
    main()
