import stone
import board

class ConsoleVisualizer(object):
    @staticmethod
    def to_char(elem):
        if elem == stone.Stone.Black:
            return 'O'
        elif elem == stone.Stone.White:
            return 'X'
        else:
            return ' '

    @staticmethod
    def print(board):
        size = board.get_size()
        data = board.get_data()
        print("size: {}".format(size))
        for row in data:
            for elem in row:
                print(" {}".format(ConsoleVisualizer.to_char(elem)), end='')
            print("")


if __name__ == '__main__':
    board = board.Board()
    ConsoleVisualizer.print(board)
