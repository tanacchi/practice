load("@rules_python//python:defs.bzl", "py_binary")
load("@ukr_deps//:requirements.bzl", "requirement")

py_binary(
    name = "uniform",
    main = "ukr_uniform.py",
    srcs = [
        "ukr_uniform.py",
        "data.py",
        "visualizer.py",
        "utils.py",
    ],
    deps = [
        requirement("numpy"),
        requirement("scipy"),
        requirement("tqdm"),
        requirement("matplotlib"),
    ],
)
