#!/usr/bin/env bash
#
# Run integration tests.

set -euo pipefail

compilation_mode="fastbuild"

while getopts ":c:" opt; do
    case "${opt}" in
        c)
            compilation_mode="${OPTARG}"

            if [[ "${compilation_mode}" != "fastbuild" && "${compilation_mode}" != "opt" && "${compilation_mode}" != "dbg" ]]; then
                echo "Invalid option for -c: ${compilation_mode}" >&2
                exit 1
            fi
            ;;
        ?)
            echo "Invalid option: -${OPTARG}" >&2
            exit 1
            ;;
    esac
done

SCRIPT_DIR=$(cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd)
source "${SCRIPT_DIR}/common.bash"

cd "${REPO_ROOT_DIR}/integration_test/bazel"

"${BAZEL_EXECUTABLE[@]}" test -c "${compilation_mode}" //...
