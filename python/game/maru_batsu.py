# -*- coding:utf-8 -*-
import pygame
from pygame.locals import *
import sys

def main():
    pygame.init()
    screen = pygame.display.set_mode((600, 600))
    pygame.display.set_caption("maru_batsu")

    #    mark_board = [0 for i in range(9)]
    mark_board = [0, 1, 2, 0, 1, 2, 0, 1, 2]
    while (True):
        pygame.display.update()
        pygame.time.wait(30)
        screen.fill((200, 200, 200, 50));
        show(screen, mark_board)
        
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    pygame.quit()
                    sys.exit()

def show(display_object, board_object):
    draw_field(display_object)
    pos_list = ( # REFACT NEEDED
        (100, 100), (300, 100), (500, 100),
        (100, 300), (300, 300), (500, 300),
        (100, 500), (300, 500), (500, 500)
    )
    for i in range(9):
           target = board_object[i]
           if target == 1: draw_maru(display_object, pos_list[i][0], pos_list[i][1])
           if target == 2: draw_batsu(display_object, pos_list[i][0], pos_list[i][1])
    
def draw_field(display_object):
    pygame.draw.line(display_object, (0,200,0), (200,0), (200, 600), 5)
    pygame.draw.line(display_object, (0,200,0), (400,0), (400, 600), 5)
    pygame.draw.line(display_object, (0,200,0), (0,200), (600, 200), 5)
    pygame.draw.line(display_object, (0,200,0), (0,400), (600, 400), 5)

def draw_maru(display_object, x, y):
    pygame.draw.circle(display_object, (200, 0, 0), (x, y), 50, 5)

def draw_batsu(display_object, x, y):
    pygame.draw.line(display_object, (0, 0, 200), (x-50, y-50), (x+50, y+50), 5)
    pygame.draw.line(display_object, (0, 0, 200), (x-50, y+50), (x+50, y-50), 5)
    
if __name__=="__main__":
    main()
