#!/usr/bin/env python

import sys
import othello_board
import display
        
class GameMaster(object):
    def __init__(self, board_info):
        pygame.init()
        self.__display = Display(board_info)
        self.__board   = othello_board.OthelloBoard((board_info), Stone.SPACE)
    def run(self):
        self.__board.insert(2, 5, Stone.BLACK)
        for _ in range(100):
            self.__display.show(self.__board)

if __name__ == "__main__":
    master = GameMaster(board.BoardInfo(8, 9, 800, 800))
    master.run()
