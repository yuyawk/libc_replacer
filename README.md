# libc_replacer

Replace libc APIs with user-defined functions

When using the implementations of this module, C/C++ toolchain must satisfy the following conditions:

- Supports C11
- Able to fully statically link all the libraries to the application
- Able to have its linker wrap symbols, such as `--wrap` in [GNU ld][gnu-ld].

<!-- below are reference links -->

[gnu-ld]: https://linux.die.net/man/1/ld
