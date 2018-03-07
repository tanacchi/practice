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
    def __init__(self, info):
        super(OthelloBoard, self).__init__(info, Stone.SPACE)
        self.data[self.get_access_num(info.row//2-1, info.col//2-1)] \
        = self.data[self.get_access_num(info.row//2, info.col//2)]   \
        = Stone.WHITE
        self.data[self.get_access_num(info.row//2, info.col//2-1)]   \
        = self.data[self.get_access_num(info.row//2-1, info.col//2)]\
        = Stone.BLACK

        
if __name__ == '__main__':
    info = BoardInfo(8, 8, 800, 800)
    board = OthelloBoard(info)
    print(board)
