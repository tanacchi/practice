# -*- coding:utf-8 -*-
import pygame
from pygame.locals import *
import sys

SPACE =  0
WHITE =  1
BLACK =  2

class Board:
    def __init__(self, row = 8, col = 8):
        self.__col = col
        self.__row = row
        self.__board = [SPACE for _ in range(row*col)]

    def __get_access_num(self, x, y) -> int:
        return self.__col * y + x
        
    def cout(self) -> None:
        print("==========================")
        for y in range(self.__row):
            for x in range(self.__col):
                print(self.__board[self.__get_access_num(x, y)], end = ' ')
            else: print("")
        print("==========================")
        
    def insert(self, x, y, stone) -> int:
        self.__board[self.__get_access_num(x, y)] = stone

    def get_data(self) -> tuple:
        return tuple(self.__board)

class Display:
    def __init__(self, width: int, height: int, row = 8, col = 8):
        self.__width = width
        self.__height = height
        self.__row = row
        self.__col = col
        row_unit = height // row
        col_unit = width  // col
        self.__screen = pygame.display.set_mode((width, height))
        calc_pos = lambda i, unit: i*unit + unit//2
        self.__position_list = []
        for r in range(row):
            for c in range(col):
                self.__position_list.append([calc_pos(c, col_unit), calc_pos(r, row_unit)])
        pygame.display.set_caption("othello")

    def draw_partition(self):
        row_unit = self.__height // self.__row
        col_unit = self.__width  // self.__col
        for r in range(self.__row):
            pygame.draw.line(self.__screen, (150,150,150), (0,r*row_unit), (self.__width, r*row_unit), 5)
        for c in range(self.__row):
            pygame.draw.line(self.__screen, (150,150,150), (c*col_unit,0), (c*col_unit, self.__height), 5)
        
    def draw_stone(self, index, stone):
        if stone == SPACE: pass
        elif stone == WHITE:
            pygame.draw.circle(self.__screen, (255,255,255), self.__position_list[index], 30)
        elif stone == BLACK:
            pygame.draw.circle(self.__screen, (0,0,0), self.__position_list[index], 30)
        else: raise "Invalid value of stone."
        
    def show(self, board: Board):
        pygame.time.wait(30)
        self.__screen.fill((0, 150, 0))
        board_data = board.get_data()
        self.draw_partition()
        for i in range(len(board_data)):
            self.draw_stone(i, board_data[i])
        pygame.display.update()

class GameMaster:
    def __init__(self, width, height, row, col):
        pygame.init()
        self.__display = Display(width, height, row, col)
        self.__board   = Board(row, col)
    def run(self):
        self.__board.cout()
        self.__board.insert(2, 5, BLACK)
        self.__board.cout()
        for _ in range(100):
            self.__display.show(self.__board)
        
if __name__ == "__main__":
    master = GameMaster(800, 800, 8, 8)
    master.run()
