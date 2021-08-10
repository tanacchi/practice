py_library(
    name = 'greeting',
    srcs = ['greeting.py'],
)

py_binary(
    name = 'hello',
    main = 'hello.py',
    srcs = ['hello.py'],
    deps = [':greeting'],
)
