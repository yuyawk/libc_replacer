# Development guide

## Prerequisites

Ensure [`bazelisk`](https://github.com/bazelbuild/bazelisk) is installed before running any tests or development scripts.

## Testing

### Unit tests

To run unit tests, execute [`development/cli/run_unit_test.bash`](development/cli/run_unit_test.bash).

### Integration tests

To run integration tests, run [`development/cli/run_integration_test.bash`](development/cli/run_integration_test.bash).

### Code formatting and linting

For formatting and linting, execute each script under [`development/cli/style_check`](development/cli/style_check).

Here is the list of formatting and linting scripts:

- [`buildifier.bash`](development/cli/style_check/buildifier.bash): Runs [`buildifier`][bazelbuild/buildtools].
- [`clang_format.bash`](development/cli/style_check/clang_format.bash): Runs [`clang-format`][clang-format]
- [`clang_tidy_integration_test.bash`](development/cli/style_check/clang_tidy_integration_test.bash): Runs [`clang-tidy`][clang-tidy] under the integration test module.
- [`clang_tidy_root.bash`](development/cli/style_check/clang_tidy_root.bash): Runs [`clang-tidy`][clang-tidy] under the root module.

## Release process

Only an admin user can release a new version. To initiate a release, the admin should push a tag in the format `X.Y.Z` (e.g., `1.0.0`). This will trigger a CI job that:

- Builds and uploads a tarball
- Creates a GitHub release
- Opens a pull request in the [Bazel Central Registry (BCR)](https://github.com/bazelbuild/bazel-central-registry)

After the BCR PR is approved and merged, the `libc_replacer` module becomes available as a Bazel module.

<!-- below are reference links -->

[bazelbuild/buildtools]: https://github.com/bazelbuild/buildtools
[clang-format]: https://clang.llvm.org/docs/ClangFormat.html
[clang-tidy]: https://clang.llvm.org/extra/clang-tidy/
