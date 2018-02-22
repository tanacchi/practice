# -*- coding:utf-8 -*-
import pygame
from pygame.locals import *
import sys

SPACE = 0
MARU  = 1
BATSU = 2

pos_list = (
    (100, 100), (300, 100), (500, 100),
    (100, 300), (300, 300), (500, 300),
    (100, 500), (300, 500), (500, 500)
)

def main():    
    pygame.init()
    screen = pygame.display.set_mode((600, 600))
    pygame.display.set_caption("maru_batsu")

    mark_board = [SPACE for i in range(9)]
    turn = MARU
    is_game_active = True
    
    while (True):
        pygame.display.update()
        pygame.time.wait(30)
        screen.fill((200, 200, 200, 50))
        show(screen, mark_board)

        if is_game_active:
            if update_board(mark_board, turn):
                if is_finish(mark_board, turn):
                    is_game_active = False
                if turn == MARU: turn = BATSU
                else: turn = MARU
        else:
            screen.fill((200, 200, 0, 50))

        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            if event.type == KEYDOWN:
                if event.key == K_ESCAPE:
                    pygame.quit()
                    sys.exit()


def update_board(board_object, turn):
    pressed_mouse = pygame.mouse.get_pressed()
    if pressed_mouse[0]:
        x, y = pygame.mouse.get_pos()
        for i in range(9):
            if is_inside(x, y, pos_list[i][0], pos_list[i][1]) and board_object[i] == SPACE:
                board_object[i] = turn
                return True
    return False

def is_inside(x, y, range_x, range_y):
    if range_x-100 < x and x < range_x+100 and range_y-100 < y and y < range_y+100:
        return True
    else:
        return False
    
def show(display_object, board_object):
    draw_field(display_object)
    for i in range(9):
        target = board_object[i]
        if target == MARU: draw_maru(display_object, pos_list[i][0], pos_list[i][1])
        if target == BATSU: draw_batsu(display_object, pos_list[i][0], pos_list[i][1])
    
def draw_field(display_object):
    pygame.draw.line(display_object, (0,200,0), (200,0), (200, 600), 5)
    pygame.draw.line(display_object, (0,200,0), (400,0), (400, 600), 5)
    pygame.draw.line(display_object, (0,200,0), (0,200), (600, 200), 5)
    pygame.draw.line(display_object, (0,200,0), (0,400), (600, 400), 5)

def draw_maru(display_object, x, y):
    pygame.draw.circle(display_object, (200, 0, 0), (x, y), 50, 10)

def draw_batsu(display_object, x, y):
    pygame.draw.line(display_object, (0, 0, 200), (x-50, y-50), (x+50, y+50), 10)
    pygame.draw.line(display_object, (0, 0, 200), (x-50, y+50), (x+50, y-50), 10)

def is_finish(board_object, turn):
    finish_sample = [turn for i in range(3)]
    for i in range(3):
        if board_object[3*i:3*i+3:] == finish_sample: return True
    for i in range(3):
        if board_object[i::3] == finish_sample: return True
    if board_object[::4] == finish_sample: return True
    if board_object[3::2] == finish_sample: return True
    return False
    
if __name__=="__main__":
    main()