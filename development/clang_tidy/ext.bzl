"""Define module extension.
"""

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@toolchains_llvm//toolchain:deps.bzl", "bazel_toolchain_dependencies")
load("@toolchains_llvm//toolchain:rules.bzl", "llvm_toolchain")

def _clang_tidy_deps_impl(_module_ctx):
    """Pull dependencies.

    Args:
        _module_ctx: Module context.
    """
    git_repository(
        name = "bazel_clang_tidy",
        commit = "26417c9635a9b0ddc6c5b1ff73220934423d9372",
        remote = "https://github.com/yuyawk/bazel_clang_tidy.git",
    )

    bazel_toolchain_dependencies()

    llvm_toolchain(
        name = "llvm_toolchain",
        llvm_version = "19.1.0",
    )

clang_tidy_deps = module_extension(
    implementation = _clang_tidy_deps_impl,
)
