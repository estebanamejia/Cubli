cc_library(
    name = "math",
    hdrs = ["Pose.h",
            "Frame.h",
            "Point.h"],
    srcs = ["Pose.cpp",
            "Frame.cpp",
            "Point.cpp"],
    includes = ["."],
    strip_include_prefix = ".",
    visibility = ["//visibility:public"],
    deps = ["@rbdl//:rbdl"]
)