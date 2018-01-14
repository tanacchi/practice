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

    while (1):
        pressed_key = pygame.key.get_pressed()
        if pressed_key[K_LEFT]:  x-=1
        if pressed_key[K_RIGHT]: x+=1
        if pressed_key[K_UP]:    y-=1
        if pressed_key[K_DOWN]:  y+=1

        pygame.display.update()
        pygame.time.wait(30)
        screen.fill((0, 20, 0, 0))
        pygame.draw.circle(screen, (0, 200, 0), (x, y), 5)

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
