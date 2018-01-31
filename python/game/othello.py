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
    def __init__(self, width: int, height: int, row = 8: int, col = 8: int):
        self.__width = width
        self.__height = height
        self.__row = row
        self.__col = col
        self.__screen = pygame.display.set_mode((width, height))
        self.__position_list = [[]]
        pygame.display.set_caption("othello")

    def show(self, board: Board):
        pygame.time.wait(30)
        self.__screen.fill((0, 150, 0))
        board_data = board.get_data()
        
        pygame.display.update()

def main():
    pygame.init()
    board = Board(8, 8)
    board.cout()
    board.insert(2, 5, BLACK)
    board.cout()
    display = Display(600, 600, board)
    
    for _ in range(100):
        display.show(board)

if __name__ == "__main__":
    main()
