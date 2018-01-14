# -*- coding: utf-8 -*-
import pygame
from pygame.locals import *
import sys

def main():
    (w,h) = (400,400)
    (x,y) = (int(w/2), int(h/2))
    pygame.init()
    pygame.display.set_mode((w, h), 0, 32)
    screen = pygame.display.get_surface()
    player = pygame.image.load("img/human.gif").convert_alpha()
    (x, y) = (300, 200)
    while (True):
        pygame.display.update()
        pygame.time.wait(30)
        screen.fill((200, 200, 200, 0))
        screen.blit(player, (x, y))
        mouse_pressed = pygame.mouse.get_pressed()
        if mouse_pressed[0]:
            x, y = pygame.mouse.get_pos()
            x -= player.get_width() / 2
            y -= player.get_height() / 2
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
