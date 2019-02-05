def func(name, age):
    print("Hello, I'm {}.".format(name))
    print("I'm {} years old.".format(age))


if __name__ == '__main__':
    func("Tanaka", 21)

    args = ["Tanaka", 21]
    func(*args)
