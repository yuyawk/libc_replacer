"""Define Bazel implementations to wrap libc for C/C++ applications.
"""

# Internal only, some of them may be re-exported at the root package.
visibility("//...")

SUPPORTED_LIBRARIES = [
    # keep sorted
    "calloc",
    "clock",
    "free",
    "malloc",
    "realloc",
    "time",
    "timespec_get",
]

def _get_modified_kwargs(libs_to_replace, kwargs_dict):
    """Get the value of `kwargs` modified for libc replacer.

    Args:
        libs_to_replace(list[str]): Target library names to be replaced.
        kwargs_dict(dict[str, Any]): `kwargs` passed as a dict.

    Returns:
        The value of `kwargs` modified for libc replacer.
    """

    # Fully static link to all libraries, to make sure every libc API is completely replaced
    kwargs_dict["features"] = kwargs_dict.pop("features", []) + ["fully_static_link"]
    kwargs_dict["linkstatic"] = True

    # Append all libc replacer implementations to `deps`
    kwargs_dict["deps"] = kwargs_dict.pop("deps", []) + [
        Label("//libc_replacer/cc:{}".format(lib))
        for lib in libs_to_replace
    ]

    return kwargs_dict

def _validate_libs_to_replace(libs_to_replace):
    """Validate the `libs_to_replace` argument for `cc_libc_replacer_*` macros.

    Args:
        libs_to_replace(list[str]): Target library names to be replaced.
    """

    if type(libs_to_replace) != "list":
        fail("Invalid argument for `list`: `libs_to_replace` must be `list[str]`.")
    if len(libs_to_replace) == 0:
        fail("`libs_to_replace` must be non-empty.")
    for lib in libs_to_replace:
        if lib not in SUPPORTED_LIBRARIES:
            fail(
                "Cannot replace library '{}': ".format(lib) +
                "Elements in `libs_to_replace`" +
                " must be either of {" +
                ", ".join(["'" + lib + "'" for lib in SUPPORTED_LIBRARIES]) +
                "}",
            )

def cc_libc_replacer_binary(*, libs_to_replace, **kwargs):
    """`cc_binary` with libc replacer APIs.

    Args:
        libs_to_replace(list[str]): Target library names to be replaced.
        **kwargs: Receive the same arguments as `cc_binary`.
    """
    _validate_libs_to_replace(libs_to_replace)
    kwargs = _get_modified_kwargs(libs_to_replace, kwargs)
    native.cc_binary(**kwargs)

def cc_libc_replacer_test(*, libs_to_replace, **kwargs):
    """`cc_test` with libc replacer APIs.

    Args:
        libs_to_replace(list[str]): Target library names to be replaced.
        **kwargs: Receive the same arguments as `cc_test`.
    """

    _validate_libs_to_replace(libs_to_replace)
    kwargs = _get_modified_kwargs(libs_to_replace, kwargs)
    native.cc_test(**kwargs)

def cc_reexport_library(*, name):
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
        visibility = ["//visibility:public"],
    )
