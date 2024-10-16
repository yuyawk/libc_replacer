"""Utility implementations for testing.
"""

visibility("//...")

def compatible_sh_test(**kwargs):
    """Compatible `sh_test`.

    Args:
        Same keyword arguments as `sh_test`.
    """

    # A windows executable need the extension ".exe"
    kwargs["name"] = kwargs["name"] + select({
        "@platforms//os:windows": ".exe",
        "//conditions:default": "",
    })

    native.sh_test(
        **kwargs
    )
