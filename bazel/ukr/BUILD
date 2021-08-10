load("@rules_python//python:defs.bzl", "py_library")
load("@rules_python//python:defs.bzl", "py_binary")
load("@ukr_deps//:requirements.bzl", "requirement")


py_library(
    name = "data",
    srcs = [
        "data.py",
    ],
    deps = [
        requirement("numpy"),
    ],
)

py_binary(
    name = "data_check",
    main = "data.py",
    srcs = [
        "data.py",
    ],
    deps = [
        ":data",
        requirement("matplotlib"),
    ],
)

py_library(
    name = "utils",
    srcs = [
        "utils.py"
    ],
    deps = [
        requirement("numpy")
    ],
)

py_binary(
    name = "utils_check",
    main = "utils.py",
    srcs = [
        "utils.py"
    ],
    deps = [
        ":utils"
    ],
)

py_binary(
    name = "uniform",
    main = "ukr_uniform.py",
    srcs = [
        "ukr_uniform.py",
        "visualizer.py",
    ],
    deps = [
        ":data",
        ":utils",
        requirement("numpy"),
        requirement("scipy"),
        requirement("tqdm"),
        requirement("matplotlib"),
    ],
)
