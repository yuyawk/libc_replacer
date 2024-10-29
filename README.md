# libc_replacer

Replace libc APIs with user-defined functions for deterministic testing.

## Description

`libc_replacer` enables developers to replace standard libc APIs with user-defined functions, providing greater control over non-deterministic behaviors in applications.

By substituting libc APIs with mock implementations, `libc_replacer` allows for more predictable and isolated testing environments. Supported libc APIs include:

- [calloc][calloc]
- [clock][clock]
- [free][free]
- [malloc][malloc]
- [realloc][realloc]
- [time][time]
- [timespec_get][timespec_get]

## Prerequisites

To use `libc_replacer`, ensure your C/C++ toolchain meets the following requirements:

- **C11 support**
- **Full static linking**: All libraries must be statically linked to the application.
- **Symbol wrapping support**: Your linker must support symbol wrapping (e.g., `--wrap` in [GNU ld][ld]).

Although `libc_replacer` can be used without [Bazel][bazel], it is designed to integrate easily with it and includes dedicated Bazel rules to simplify usage. Bazel is therefore recommended for building and testing.

## Usage

Headers for each target libc API are located under `libc_replacer/cc/{target}.h`. The library provides two main functions for each API:

- `libc_replacer_overwrite_{target}`: Overwrites the original libc function call with a specified function pointer, returning void.
- `libc_replacer_reset_{target}`: Restores the original libc function, returning void.

For usage examples, refer to the [integration tests](integration_test).

### C/C++ example

```c
#include <libc_replacer/cc/malloc.h>
#include <stdlib.h>

static void *mock_malloc(size_t size) {
  (void)size;
  return NULL; // Always returns `NULL` to simulate allocation failure
}

int main(void) {
  libc_replacer_overwrite_malloc(mock_malloc);

  const size_t size_arg = 4;
  // `malloc` is now replaced by `mock_malloc`,
  // so `got` will always be `NULL` without heap allocation.
  const void *const got = malloc(size_arg);
  libc_replacer_reset_malloc();

  // After reset, `malloc` behaves normally again.
  void *const got_after_reset = malloc(size_arg);
  free(got_after_reset);
}
```

### Bazel integration

Load `libc_replacer` from the [Bazel Central Registry][bcr] to use it as a Bazel module.

The module provides `cc_libc_replacer_binary` and `cc_libc_replacer_test`, which are similar to `cc_binary` and `cc_test`, with one additional required parameter: `libs_to_replacer`. This parameter, a list of strings, specifies the names of libc APIs to replace.

```bazel
load(
    "@libc_replacer//:cc.bzl",
    "cc_libc_replacer_binary",
    "cc_libc_replacer_test",
)

# Define a binary target that replaces `malloc` with a user-defined function.
cc_libc_replacer_binary(
    name = "your_binary",
    srcs = ["your_binary_code.c"],
    libs_to_replace = ["malloc"],  # Required: List of libc APIs to replace
)

# Define a test target that replaces `time` with a user-defined function.
cc_libc_replacer_test(
    name = "your_test",
    timeout = "short",
    srcs = ["your_test_code.c"],
    libs_to_replace = ["time"],  # Required: List of libc APIs to replace
)
```

## Contributing

Pull requests and issues are welcome! See [DEVEL.md](DEVEL.md) for development documentation.

## CI status

[![Tests](https://github.com/yuyawk/libc_replacer/actions/workflows/tests.yml/badge.svg)](https://github.com/yuyawk/libc_replacer/actions/workflows/tests.yml)

[![Bazel Steward](https://github.com/yuyawk/libc_replacer/actions/workflows/bazel-steward.yml/badge.svg)](https://github.com/yuyawk/libc_replacer/actions/workflows/bazel-steward.yml)

[![Release](https://github.com/yuyawk/libc_replacer/actions/workflows/release.yml/badge.svg)](https://github.com/yuyawk/libc_replacer/actions/workflows/release.yml)

<!-- below are reference links -->

[bazel]: https://bazel.build/
[bcr]: https://registry.bazel.build/modules/libc_replacer
[calloc]: https://www.unix.com/man-page/linux/3/calloc/
[clock]: https://www.unix.com/man-page/linux/3/clock/
[free]: https://www.unix.com/man-page/linux/3/free/
[ld]: https://www.unix.com/man-page/linux/1/ld/
[malloc]: https://www.unix.com/man-page/linux/3/malloc/
[realloc]: https://www.unix.com/man-page/linux/3/realloc/
[time]: https://www.unix.com/man-page/linux/2/time/
[timespec_get]: https://en.cppreference.com/w/c/chrono/timespec_get
