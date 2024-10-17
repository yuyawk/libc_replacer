#!/usr/bin/env bash
#
# Execute clang-tidy at the root of the repository.

set -euo pipefail

SCRIPT_DIR=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
source "${SCRIPT_DIR}/../common.bash"

cd "${REPO_ROOT_DIR}"

"${BAZEL_EXECUTABLE[@]}" build //... --config clang-tidy
