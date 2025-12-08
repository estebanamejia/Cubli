cc_library(
    name = "math",
    hdrs = ["Pose.h",
            "Frame.h",
            "FrameID.h",
            "Point.h",
            "Orientation.h",
            "FrameTransform.h"],
    srcs = ["Pose.cpp",
            "Frame.cpp",
            "Point.cpp",
            "Orientation.cpp",
            "FrameTransform.cpp"],
    includes = ["."],
    strip_include_prefix = ".",
    visibility = ["//visibility:public"],
    deps = ["@rbdl//:rbdl"]
)