"""Utility implementations for testing.
"""

visibility("//...")

def compatible_sh_test(**kwargs):
    """Compatible `sh_test`.

    Args:
        Same keyword arguments as `sh_test`.
    """

    # A windows executable need the extension ".exe"
    if native.repository_os.name == "windows":
        kwargs["name"] += ".exe"

    native.sh_test(
        **kwargs
    )
