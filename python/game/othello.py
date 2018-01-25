# -*- coding:utf-8 -*-
import pygame
from pygame.locals import *
import sys

SPACE =  0
WHITE =  1
BLACK =  2

class Board:
    def __init__(self, width = 8, height = 8):
        self.__width = width
        self.__height = height
        self.__board = [[SPACE for x in range(width)] for y in range(height)]
        self.__active_stone = WHITE

    def show(self):
        print("==========================")
        for row in self.__board: print(row)
        print("==========================")

    def insert(self, x, y, stone):
        self.__board[y][x] = stone

def main():
    board = Board(8, 8)
    board.show()
    board.insert(2, 2, BLACK)
    board.show()

if __name__ == "__main__":
    main()
