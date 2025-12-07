cc_test(
    name = "cubli_test",
    size = "small",
    srcs = ["test_cubli.cpp"],
    deps = [
        "@googletest//:gtest",
        "@googletest//:gtest_main",
        "//cubli_core:cubli_core",
        "//math:math",
        "@rbdl//:rbdl",
    ],
    args = [
        "--gtest_print_time=1",
    ],
)