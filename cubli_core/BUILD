cc_library(
    name = "cubli_core",
    hdrs = ["cubli.h",
            "cubli_state.h",
            "cubli_geometry.h",
            "cubli_planning.h"],
    srcs = ["cubli.cpp",
            "cubli_state.cpp",
            "cubli_planning.cpp"],
    include_prefix = "cubli",
    strip_include_prefix = ".",
    visibility = ["//visibility:public"],
    copts = ["-std=c++17"],
    deps = ["@rbdl//:rbdl",
            "//math:math"]
)