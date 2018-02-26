import pygame
from pygame.locals import *
import sys
from enum import Enum 
import board

class Stone(Enum):
    SPACE = ' '
    WHITE = 'O'
    BLACK = 'X'

    
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
        if stone == Stone.SPACE: pass
        elif stone == Stone.WHITE:
            pygame.draw.circle(self.__screen, (255,255,255), self.__position_list[index], 30)
        elif stone == Stone.BLACK:
            pygame.draw.circle(self.__screen, (0,0,0), self.__position_list[index], 30)
        else: raise "Invalid value of stone."
        
    def show(self, board: board.Board):
        pygame.time.wait(30)
        self.__screen.fill((0, 150, 0))
        board_data = board.get_data()
        self.draw_partition()
        for i in range(len(board_data)):
            self.draw_stone(i, board_data[i])
        pygame.display.update()

    def get_position_number(self, x, y):
        for i in range(len(self.__position_list)):
            pass
        
class GameMaster:
    def __init__(self, width, height, row, col):
        pygame.init()
        self.__display = Display(width, height, row, col)
        self.__board   = board.Board(board.BoardInfo(8, 8, 800, 800), Stone.SPACE)
    def run(self):
        print(self.__board)
        self.__board.insert(2, 5, Stone.BLACK)
        print(self.__board)
        for _ in range(100):
            self.__display.show(self.__board)

if __name__ == "__main__":
    master = GameMaster(800, 800, 8, 8)
    master.run()
