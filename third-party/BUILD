load("@rules_foreign_cc//foreign_cc:cmake.bzl", "cmake")


cmake(
    name = "rbdl-ext",
    lib_source = "@rbdl-git//:all",
    # out_static_libs = ["rbdl.a"]
)

cc_library(
    name = "rbdl",
    deps = ["rbdl-ext"]
)