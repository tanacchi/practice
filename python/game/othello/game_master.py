#!/usr/bin/env python

import sys
import othello_board
import display
from enum import Enum

class Task(Enum):
    INIT = 0
    SHOW = 1
    SET = 2
    INSERT = 3
    REVERT = 4
    WRITE = 5
    JUDGE = 6
    SWITCH = 7
    ASK = 8
    ED = 9
    
class GameMaster(object):
    
    def __init__(self, board_info):
        self._board_info = board_info
        self.task = Task.INIT
        
    def task_init(self):
        self.__display = display.Display(self._board_info)
        self.__board   = othello_board.OthelloBoard((self._board_info))
        return Task.SHOW
        
    def task_show(self):
        self.__display.show(self.__board)
        self.__display.update()
        return Task.SHOW

    def task_set(self):
        pass
    
    def task_insert(self):
        pass

    def task_revert(self):
        pass

    def task_write(self):
        pass

    def task_judge(self):
        pass
    
    def task_switch(self):
        pass
    
    def task_ask(self):
        pass
    
    def task_ed(self):
        pass

    task_map = \
    {
        Task.INIT: task_init,
        Task.SHOW: task_show,
        Task.SET: task_set,
        Task.INSERT: task_insert,
        Task.REVERT: task_revert,
        Task.WRITE: task_write,
        Task.JUDGE: task_judge,
        Task.SWITCH: task_switch,
        Task.ASK: task_ask,
        Task.ED: task_ed
    }

    def run(self):
        while True:
            func = GameMaster.task_map.get(task)
            self.task = func(self)
                    
            
if __name__ == "__main__":
    master = GameMaster(othello_board.BoardInfo(8, 8, 800, 800))
    master.run()
