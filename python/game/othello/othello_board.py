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

    
if __name__ == '__main__':
    info = BoardInfo(8, 8, 800, 800)
    board = OthelloBoard(info)
    print(board)
    for dr in OthelloBoard.dr_tuple:
        print(board.get_reversible_length(4, 2, dr))
