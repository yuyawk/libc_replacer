#!/usr/bin/env bash

set -o errexit -o nounset -o pipefail

TAG="${GITHUB_REF_NAME}"
PREFIX="libc_replacer-${TAG}"
ARCHIVE="libc_replacer-${TAG}.tar.gz"

git archive --format=tar "--prefix=${PREFIX}/" "${TAG}" | \
    gzip \
    > "${ARCHIVE}"

# StdOut of this script is used for release description
cat << EOF
## Using Bzlmod with Bazel 7 or greater

Add to your \`MODULE.bazel\` file:

\`\`\`starlark
bazel_dep(name = "libc_replacer", version = "${TAG}")
\`\`\`
EOF