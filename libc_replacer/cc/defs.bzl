"""Define Bazel implementations to wrap libc for C/C++ applications.
"""

# Internal only, some of them may be re-exported at the root package.
visibility("//...")

def _get_modified_kwargs(kwargs_dict):
    """Get the value of `kwargs` modified for libc replacer.

    Args:
        kwargs_dict(dict[str, Any]): `kwargs` passed as a dict.

    Returns:
        The value of `kwargs` modified for libc replacer.
    """

    # Fully static link to all libraries, to make sure every libc API is completely replaced
    kwargs_dict["features"] = kwargs_dict.pop("features", []) + ["fully_static_link"]
    kwargs_dict["linkstatic"] = True

    # Append all libc replacer implementations to `deps`
    kwargs_dict["deps"] = kwargs_dict.pop("deps", []) + [Label("//libc_replacer/cc")]

    return kwargs_dict

def cc_libc_replacer_binary(**kwargs):
    """`cc_binary` with libc replacer APIs.

    Args:
        **kwargs: Receive the same arguments as `cc_binary`.
    """

    kwargs = _get_modified_kwargs(kwargs)
    native.cc_binary(**kwargs)

def cc_libc_replacer_test(**kwargs):
    """`cc_test` with libc replacer APIs.

    Args:
        **kwargs: Receive the same arguments as `cc_test`.
    """

    kwargs = _get_modified_kwargs(kwargs)
    native.cc_test(**kwargs)

def cc_reexport_library(name):
    """Wrapper of `cc_library` to re-export each sub-library.

    Only for internal use.

    Args:
        name(str): Name of the sub-library.
    """
    native.cc_library(
        name = name,
        hdrs = [name + ".h"],
        # Explicitly set `include_prefix`
        # in order to use `-I` and have the user include the header with `<>`
        include_prefix = "libc_replacer/cc",
        deps = [
            "//libc_replacer/cc/{}".format(name),
        ],
        visibility = ["//:__pkg__"],
    )
