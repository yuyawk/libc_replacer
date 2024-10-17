"""Re-export the aspect.
"""

load("@bazel_clang_tidy//clang_tidy:clang_tidy.bzl", _clang_tidy_aspect = "clang_tidy_aspect")

clang_tidy_aspect = _clang_tidy_aspect
