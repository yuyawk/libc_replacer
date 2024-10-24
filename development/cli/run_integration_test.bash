#!/usr/bin/env bash
#
# Run integration tests.

set -euo pipefail

SCRIPT_DIR=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
source "${SCRIPT_DIR}/common.bash"

cd "${REPO_ROOT_DIR}/integration_test/bazel"

"${BAZEL_EXECUTABLE[@]}" test -s //...
