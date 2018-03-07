#!/usr/bin/env python

import sys
import othello_board
import display
        
class GameMaster(object):
    def __init__(self, board_info):
        self.__display = display.Display(board_info)
        self.__board   = othello_board.OthelloBoard((board_info))
    def run(self):
        self.__board.insert(2, 5, othello_board.Stone.BLACK)
        for _ in range(100):
            self.__display.show(self.__board)

if __name__ == "__main__":
    master = GameMaster(othello_board.BoardInfo(8, 8, 800, 800))
    master.run()
