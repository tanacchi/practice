load("@rules_python//python:defs.bzl", "py_library")
load("@rules_python//python:defs.bzl", "py_binary")
load("@ukr_deps//:requirements.bzl", "requirement")


py_library(
    name = "data",
    srcs = [
        "data.py",
    ],
    srcs_version = "PY3",
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
    srcs_version = "PY3",
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
    srcs_version = "PY3",
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
    srcs_version = "PY3",
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
    srcs_version = "PY3",
    deps = [
        ":data",
        ":utils",
        requirement("numpy"),
        requirement("scipy"),
        requirement("tqdm"),
        requirement("matplotlib"),
    ],
)

py_binary(
    name = "autograd",
    main = "ukr_autograd.py",
    srcs = [
        "ukr_autograd.py",
        "visualizer.py",
    ],
    srcs_version = "PY3",
    deps = [
        ":data",
        ":utils",
        requirement("numpy"),
        requirement("jax"),
        requirement("jaxlib"),
        requirement("scipy"),
        requirement("tqdm"),
        requirement("matplotlib"),
    ],
)

