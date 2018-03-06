# ================= Ex1 ========================
def deco1(func):
    import functools
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        print('--start--')
        func(*args, **kwargs)
        print('--end--')
    return wrapper

@deco1
def test1():
    print('Deco1')

# ================= Ex2 ========================
def deco2(func):
    import functools
    import os
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        res = '--start--' + os.linesep
        res += func(*args, **kwargs) + '!' + os.linesep
        res += '--end--'
        return res
    return wrapper

@deco2
def test2():
    return 'Deco2'

# ================= Ex3 ========================
def deco_html(func):
    import functools
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        res = '<html>'
        res += func(*args, **kwargs)
        res += '</html>'
        return res
    return wrapper

def deco_body(func):
    import functools
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        res = '<body>'
        res += func(*args, **kwargs)
        res += '</body>'
        return res
    return wrapper

@deco_html
@deco_body
def test3():
    return 'Deco3'

# ================= Ex4=========================
def deco_p(func):
    import functools
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        res = '<p>'
        res += func(args[0], **kwargs)
        res += '</p>'
        return res
    return wrapper

@deco_p
def test4(src):
    return src

# ================= Ex5 ========================
def deco_tag(tag):
    def _deco_tag(func):
        import functools
        @functools.wraps(func)
        def wrapper(*args, **kwargs):
            res = '<'+tag+'>'
            res += func(*args, **kwargs)
            res += '</'+tag+'>'
            return res
        return wrapper
    return _deco_tag

@deco_tag('html')
@deco_tag('body')
def test5():
    return 'Deco5'

# ================= Main ========================
if __name__ == '__main__':
    test1()
    print(test2())
    print(test3())
    print(test4('AHAHA'))
    print(test5())
