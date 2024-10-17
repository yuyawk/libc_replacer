#!/usr/bin/env bash
#
# Execute clang-tidy in the example repository.

set -euo pipefail

SCRIPT_DIR=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
source "${SCRIPT_DIR}/../common.bash"

cd "${REPO_ROOT_DIR}/examples"

"${BAZEL_EXECUTABLE[@]}" build //... --config clang-tidy
