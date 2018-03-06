class BoardInfo(object):
    def __init__(self, row: int, col:int, width: int, height: int):
        self.row = row
        self.col = col
        self.width = width
        self.height = height
        self.row_unit = height // row
        self.col_unit = width // col

    def __str__(self):
        return '<row: {}, col: {}>\n<height: {}, width: {}>'\
            .format(self.row, self.col, self.height, self.width)


class Board(object):
    def __init__(self, info: BoardInfo, initial_value):
        self.__info = info
        self.__data_type = type(initial_value)
        self.__data = [initial_value for _ in range(info.row*info.col)]
            
    def __str__(self):
        data_splited = list(zip(*[iter(self.__data)]*self.__info.col))
        for row in data_splited:
            print(row)
        return str(self.__info)

    def is_inside(self, x:int, y:int):
        return 0 <= x < self.__info.col and 0 <= y < self.__info.row

    def __get_access_num(self, x, y):
        if (not self.is_inside(x, y)):
            raise 'Invalid access'
        return self.__info.col*y + x

    def insert(self, x, y, value):
        if (not isinstance(value, self.__data_type)):
            raise 'Invalid type of value'
        self.__data[self.__get_access_num(x, y)] = value

    def get_data(self):
        return tuple(self.__data)
        
if __name__ == '__main__':
    board1 = Board(BoardInfo(6, 6, 600, 600), 't')
    board2 = Board(BoardInfo(6, 6, 600, 600), 't')
    print(board1)

    board1.insert(3, 2, 'x')
    print(board1)
    print(board1 == board2)
