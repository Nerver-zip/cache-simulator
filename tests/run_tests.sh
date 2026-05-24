#!/bin/bash

set -euo pipefail

ROOT_DIR="$(git rev-parse --show-toplevel)"

TEST_DIR="$ROOT_DIR/tests/ci/cases"
OUTPUT_DIR="$ROOT_DIR/build/tests"

mkdir -p "$OUTPUT_DIR"

for file in "$TEST_DIR"/*.args; do
    name=$(basename "$file" .args)

    echo "Running CI test: $name"

    args=$(cat "$file")

    OUTPUT_FILE="$OUTPUT_DIR/${name}.out"

    "$ROOT_DIR/cache_simulator" $args > "$OUTPUT_FILE"

    diff -u \
        "$OUTPUT_FILE" \
        "$TEST_DIR/${name}.expected"

    echo "Passed: $name"
done
