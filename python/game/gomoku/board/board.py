import stone

class Board(object):
    def __init__(self, width=8, height=8):
        self.__width  = width
        self.__height = height
        self.__data   = [[stone.Stone.Space for _ in range(width)] for _ in range(height)]

    def get_size(self):
        return (self.__width, self.__height)

    def get_data(self):
        return self.__data


if __name__ == '__main__':
    board = Board(8, 8)
