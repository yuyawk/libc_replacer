"""The only user-facing bzl file.
"""

load(
    "//cc:internal_defs.bzl",
    _cc_libc_replacer_binary = "cc_libc_replacer_binary",
    _cc_libc_replacer_test = "cc_libc_replacer_test",
)

visibility("public")

# Re-exporting
cc_libc_replacer_binary = _cc_libc_replacer_binary
cc_libc_replacer_test = _cc_libc_replacer_test
