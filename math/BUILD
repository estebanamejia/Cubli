cc_library(
    name = "math",
    hdrs = ["Pose.h",
            
            "FrameID.h",
            "Point.h",
            "Position.h",
            "Orientation.h",
            "FrameTransform.h",
            "FrameTree.h"],
    srcs = ["Pose.cpp",
            
            "Point.cpp",
            "Position.cpp",
            "Orientation.cpp",
            "FrameTransform.cpp",
            "FrameTree.cpp"],
    includes = ["."],
    strip_include_prefix = ".",
    visibility = ["//visibility:public"],
    copts = ["-std=c++17"],
    deps = ["@rbdl//:rbdl"]
)