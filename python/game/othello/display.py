#!/usr/bin/env python

import pygame
from pygame.locals import *
import board
import othello_board

class Display(object):
    def __init__(self, board_info:board.BoardInfo):
        self.info = board_info
        self.__screen = pygame.display.set_mode((self.info.width, self.info.height))
        self.__position_list = []
        for r in range(self.info.row):
            for c in range(self.info.col):
                self.__position_list.append([c*self.info.col_unit, r*self.info.row_unit])
        pygame.init()
        pygame.display.set_caption('othello')

    def update(self):
        self.current_events = pygame.event.get()
        pygame.display.update()
        pygame.time.wait(30)
        
    def show(self, board: board.BoardBase):
        def draw_partition(self):
            for r in range(self.info.row):
                pygame.draw.line(self.__screen, (150,150,150), (0,r*self.info.row_unit), (self.info.width, r*self.info.row_unit), 5)
            for c in range(self.info.col):
                pygame.draw.line(self.__screen, (150,150,150), (c*self.info.col_unit,0), (c*self.info.col_unit, self.info.height), 5)
        
        def draw_stone(self, index, stone):
            func = othello_board.object_printer.get(stone)
            point = [self.__position_list[index][0]+self.info.col_unit//2, self.__position_list[index][1]+self.info.row_unit//2]
            func(self.__screen, point)

        self.__screen.fill((0, 150, 0))
        draw_partition(self)
        board_data = board.get_data()
        for i, data in enumerate(board_data):
            draw_stone(self, i, data)

    def get_coordinate(self, pos_num):
        x, y = self.__position_list[pos_num][0], self.__position_list[pos_num][1]
        return x, y
        
    def get_position_num(self, x, y):
        def in_range(self, x, y, point):
            return (0 <= x-point[0] < self.info.col_unit) and (0 <= y-point[1] < self.info.row_unit)

        for i, position in enumerate(self.__position_list):
            if in_range(self, x, y, position):
                return i
        else: return -1

    def get_hand(self):
        mouse_pressed = pygame.mouse.get_pressed()
        if mouse_pressed[0]:
            x, y = pygame.mouse.get_pos()
            return self.get_position_num(x, y)
        else:
            return -1
        
    def is_shutdown(self):
        for event in self.current_events:
            if event.type == QUIT or (event.type == KEYDOWN and event.key == K_ESCAPE):
                return True
        else:
            return False

    def shutdown(self):
        pygame.quit()
        
if __name__ == '__main__':
    info = board.BoardInfo(8, 8, 800, 800)
    board = othello_board.OthelloBoard(info)
    disp = Display(info)

    disp.show(board)
    disp.update()

    while not disp.is_shutdown():
        print(disp.get_hand())
        disp.update()

    disp.shutdown()
    
