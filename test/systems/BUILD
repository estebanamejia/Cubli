cc_test(
    name = "cubli_test",
    size = "small",
    srcs = ["test_cubli.cpp"],
    copts = ["-std=c++17"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//cubli_core:cubli_core",
        "//math:math",
        "@rbdl//:rbdl",
    ],
)