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
        self.__board = [SPACE for x in range(width*height)]
        self.__active_stone = WHITE

    def __get_access_num(self, x, y):
        return self.__width * y + x
        
    def show(self):
        print("==========================")
        for y in range(self.__height):
            for x in range(self.__width):
                print(self.__board[self.__get_access_num(x, y)], end = " ")
            print("")
        print("==========================")

    def insert(self, x, y, stone):
        self.__board[self.__get_access_num(x, y)] = stone

def main():
    board = Board(8, 8)
    board.show()
    board.insert(2, 2, BLACK)
    board.show()

if __name__ == "__main__":
    main()
