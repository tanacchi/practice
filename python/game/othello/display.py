#!/usr/bin/env python

import pygame
from pygame.locals import *
import board
import othello_board

class Display(object):
    def __init__(self, board_info:board.BoardInfo):
        self.info = board_info
        self.__screen = pygame.display.set_mode((self.info.width, self.info.height))
        calc_pos = lambda i, unit: i*unit + unit//2
        self.__position_list = []
        for r in range(self.info.row):
            for c in range(self.info.col):
                self.__position_list.append([calc_pos(c, self.info.col_unit), calc_pos(r, self.info.row_unit)])
        pygame.init()
        pygame.display.set_caption("othello")
        
    def show(self, board: board.BoardBase):
        def draw_partition(self):
            for r in range(self.info.row):
                pygame.draw.line(self.__screen, (150,150,150), (0,r*self.info.row_unit), (self.info.width, r*self.info.row_unit), 5)
            for c in range(self.info.col):
                pygame.draw.line(self.__screen, (150,150,150), (c*self.info.col_unit,0), (c*self.info.col_unit, self.info.height), 5)
        
        def draw_stone(self, index, stone):
            func = othello_board.object_printer.get(stone)
            func(self.__screen, self.__position_list[index])

        pygame.time.wait(30)
        self.__screen.fill((0, 150, 0))
        board_data = board.get_data()
        draw_partition(self)
        for i, data in enumerate(board_data):
            draw_stone(self, i, data)
        pygame.display.update()

    def get_position_number(self, x, y):
        for i, position in enumerate(self.__position_list):
            pass

if __name__ == '__main__':
    info = board.BoardInfo(8, 8, 800, 800)
    board = othello_board.OthelloBoard(info)
    disp = Display(info)

    for i in range(100):
        disp.show(board)
