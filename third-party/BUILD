load("@rules_foreign_cc//foreign_cc:cmake.bzl", "cmake")


cmake(
    name = "rbdl-ext",
    lib_source = "@rbdl-git//:all",
    out_shared_libs = ["librbdl.so",
                       "librbdl.so.3.3.1"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "rbdl",
    deps = ["rbdl-ext",
            "@eigen"],
    visibility = ["//visibility:public"]
)
