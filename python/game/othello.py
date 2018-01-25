# -*- coding:utf-8 -*-
import pygame
from pygame.locals import *
import sys

class Board:
    SPACE = 0
    WHITE = 1
    BLACK = 2
    def __init__(self, width = 8, height = 8):
        self.__width = width
        self.__height = height
        self.__board = [[self.SPACE for x in range(width)] for y in range(height)]

    def show(self):
        print(self.__width)
        print(self. __height)
        for row in self.__board: print(row)
        
def main():
    board = Board(8, 8)
    board.show()

if __name__ == "__main__":
    main()
