import pygame
from pygame.locals import *
import sys
from enum import Enum 
import board

class Stone(Enum):
    SPACE = lambda screen, pos: pygame.draw.circle(screen, (0,150,0), pos, 30)
    WHITE = lambda screen, pos: pygame.draw.circle(screen, (255,255,255), pos, 30)
    BLACK = lambda screen, pos: pygame.draw.circle(screen, (0,0,0), pos, 30)
    
class Display:
    def __init__(self, board_info:board.BoardInfo):
        self.info = board_info
        self.__screen = pygame.display.set_mode((self.info.width, self.info.height))
        calc_pos = lambda i, unit: i*unit + unit//2
        self.__position_list = []
        for r in range(self.info.row):
            for c in range(self.info.col):
                self.__position_list.append([calc_pos(c, self.info.col_unit), calc_pos(r, self.info.row_unit)])
        pygame.display.set_caption("othello")

    def draw_partition(self):
        for r in range(self.info.row):
            pygame.draw.line(self.__screen, (150,150,150), (0,r*self.info.row_unit), (self.info.width, r*self.info.row_unit), 5)
        for c in range(self.info.col):
            pygame.draw.line(self.__screen, (150,150,150), (c*self.info.col_unit,0), (c*self.info.col_unit, self.info.height), 5)
        
    def draw_stone(self, index, stone):
        stone(self.__screen, self.__position_list[index])
        
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
    def __init__(self, board_info):
        pygame.init()
        self.__display = Display(board_info)
        self.__board   = board.Board((board_info), Stone.SPACE)
    def run(self):
        print(self.__board)
        self.__board.insert(2, 5, Stone.BLACK)
        print(self.__board)
        for _ in range(100):
            self.__display.show(self.__board)

if __name__ == "__main__":
    master = GameMaster(board.BoardInfo(8, 9, 800, 800))
    master.run()
