"""bzl file to re-export user-facing C/C++ implementations.
"""

load(
    "//libc_replacer/cc:internal_defs.bzl",
    _cc_libc_replacer_binary = "cc_libc_replacer_binary",
    _cc_libc_replacer_test = "cc_libc_replacer_test",
)

visibility("public")

# Re-exporting
cc_libc_replacer_binary = _cc_libc_replacer_binary
cc_libc_replacer_test = _cc_libc_replacer_test
