from enum import Enum

class EnumA(Enum):
    ONE = 1,
    TWO = 2,
    THREE = 3

class EnumB(Enum):
    OWATA = (1, lambda: print('\\(^o^)/'))
    FUJISAN = ('2', lambda: print('/(^o^)\\'))

if __name__ == '__main__':
    print(EnumB.FUJISAN.value[0])
