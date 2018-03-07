class BoardInfo(object):
    def __init__(self, row: int, col:int, width: int, height: int):
        self.row, self.col = row, col
        self.width, self.height = width, height
        self.row_unit, self.col_unit = height // row, width // col

    def __str__(self):
        return '<row: {}, col: {}>\n<height: {}, width: {}>'\
            .format(self.row, self.col, self.height, self.width)

    def __eq__(self, rhs):
        return (self.row == rhs.row
                and self.col == rhs
                and self.width == rhs.width
                and self.height == rhs.height
                and self.row_unit == rhs.row_unit
                and self.col_unit == rhs.col_unit)
    
class BoardBase(object):
    data_type = None
    
    def __init__(self, info: BoardInfo, initial_value):
        self.info = info
        if BoardBase.data_type == None:
            BoardBase.data_type = type(initial_value)
        else:
            assert BoardBase.data_type == type(initial_value), 'Invalid initialization'
        self.data = [initial_value for _ in range(info.row*info.col)]
            
    def __str__(self):
        data_splited = list(zip(*[iter(self.data)]*self.info.col))
        for row in data_splited:
            print(row)
        return str(self.info)
    
    def is_inside(self, x:int, y:int):
        return 0 <= x < self.info.col and 0 <= y < self.info.row

    def get_access_num(self, x, y):
        if (not self.is_inside(x, y)):
            raise 'Invalid access'
        return self.info.col*y + x

    def insert(self, x, y, value):
        if (not isinstance(value, BoardBase.data_type)):
            raise 'Invalid type of value'
        self.data[self.get_access_num(x, y)] = value

    def get_data(self):
        return tuple(self.data)
        
if __name__ == '__main__':
    board1 = BoardBase(BoardInfo(6, 6, 600, 600), 't')
    board2 = BoardBase(BoardInfo(6, 6, 600, 600), '1')
    print(board1)
    
    board1.insert(3, 2, 'x')
    print(board1)
    print(board1 == board2)
    print(board2)
    
