#!/usr/bin/env python

import pygame
from pygame.locals import *
from enum import Enum

class Stone(Enum):
    SPACE = ' '
    WHITE = 'O'
    BLACK = 'X'

object_printer = \
{
    Stone.SPACE: lambda screen, pos: pygame.draw.circle(screen, (0,150,0), pos, 30),
    Stone.WHITE: lambda screen, pos: pygame.draw.circle(screen, (255,255,255), pos, 30),
    Stone.BLACK: lambda screen, pos: pygame.draw.circle(screen, (0,0,0), pos, 30)
}
    
from board import BoardInfo, BoardBase

class OthelloBoard(BoardBase):
    dr_tuple = ((0,-1), (1,-1), (1,0), (1,1), (0,1), (-1,1), (-1,0), (-1,-1))
    
    def __init__(self, info):
        super(OthelloBoard, self).__init__(info, Stone.SPACE)
        self.insert(info.row//2-1, info.col//2-1, Stone.WHITE)
        self.insert(info.row//2, info.col//2, Stone.WHITE)
        self.insert(info.row//2, info.col//2-1, Stone.BLACK)
        self.insert(info.row//2-1, info.col//2, Stone.BLACK)
        self.active_stone, self.enemy_stone = Stone.WHITE, Stone.BLACK

    def insert(self, x, y, stone = None):
        if stone == None: stone = self.active_stone
        super(OthelloBoard, self).insert(x, y, stone)
        
    def switch_stone(self):
        self.active_stone, self.enemy_stone = self.enemy_stone, self.active_stone

    def get_reversible_length(self, x, y, dr):
        length = 1
        while self.is_inside(x + length*dr[0], y + length*dr[1]):
            if self.data[self.get_access_num(x + length*dr[0], y + length*dr[1])] == self.active_stone:
                return length - 1
            elif self.data[self.get_access_num(x + length*dr[0], y + length*dr[1])] == Stone.SPACE:
                break
            length += 1
        return 0

    def can_reverse(self, x, y):
        for dr in OthelloBoard.dr_tuple:
            if self.get_reversible_length(x, y, dr) != 0:
                return True
        return False

    def reverse(self, x, y):
        for dr in OthelloBoard.dr_tuple:
            reverse_length = self.get_reversible_length(x, y, dr)
            for i in range(1, reverse_length+1):
                self.insert(x + reverse_length*dr[0], y + reverse_length*dr[1], self.active_stone)
    
    def count_stone(self, stone):
        return self.data.count(stone)
    
if __name__ == '__main__':
    info = BoardInfo(8, 8, 800, 800)
    board = OthelloBoard(info)
    print(board)
    dr = {True: 1, False: 0}
    a = []
    for x in range(8):
        for y in range(8):  
            a.append(dr.get(board.can_reverse(x, y)))

    for x in range(8):
        for y in range(8):  
            print(a[board.get_access_num(x,y)], end=' ')
        print()

    board.insert(4, 2, Stone.WHITE)
    board.reverse(4, 2)
    print(board)
