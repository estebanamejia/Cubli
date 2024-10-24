workspace(name = "cubli")

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

git_repository(
    name = "rbdl-git",
    build_file_content = all_content,
    remote = "https://github.com/rbdl/rbdl",
    commit = "d30180db66eb395f1fc768ecd0beab6554f2c927",
    recursive_init_submodules = True,
    init_submodules = True,
)