#!/usr/bin/env bash
#
# Execute clang-format.

set -euo pipefail

SCRIPT_DIR=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
source "${SCRIPT_DIR}/../common.bash"

cd "${REPO_ROOT_DIR}"

clang_format_targets="$(
    git ls-files | \
        grep -E '\.c$|\.h$|\.cpp$|\.hpp$' | \
        xargs -I{} echo "$(pwd)/{}"
)"

"${BAZEL_EXECUTABLE[@]}" run -- @clang_tools//:clang_format -i ${clang_format_targets}
