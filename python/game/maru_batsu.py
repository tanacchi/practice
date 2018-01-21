# -*- coding:utf-8 -*-
import pygame
from pygame.locals import *
import sys

def main():
    pygame.init()
    screen = pygame.display.set_mode((600, 600))
    pygame.display.set_caption("maru_batsu")

    mark_board = [0 for i in range(9)]
    print(mark_board)

    while (True):
        pygame.display.update()
        pygame.time.wait(30)
        screen.fill((200, 200, 200, 50));
        draw_field(screen)
        
        for event in pygame.event.get():
            print(type(event))
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    pygame.quit()
                    sys.exit()

def draw_board(display_object, board_object):
    
                    
def draw_field(display_object):
    pygame.draw.line(display_object, (0,200,0), (200,0), (200, 600), 5)
    pygame.draw.line(display_object, (0,200,0), (400,0), (400, 600), 5)
    pygame.draw.line(display_object, (0,200,0), (0,200), (600, 200), 5)
    pygame.draw.line(display_object, (0,200,0), (0,400), (600, 400), 5)
    
if __name__=="__main__":
    main()
