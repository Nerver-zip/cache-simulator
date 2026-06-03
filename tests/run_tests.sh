#!/bin/bash

set -euo pipefail

ROOT_DIR="$(git rev-parse --show-toplevel)"

TEST_DIR="$ROOT_DIR/tests/ci/cases"
OUTPUT_DIR="$ROOT_DIR/build/tests"

mkdir -p "$OUTPUT_DIR"

compare_float() {
    local actual="$1"
    local expected="$2"
    local epsilon="$3"

    awk -v a="$actual" -v e="$expected" -v eps="$epsilon" '
    BEGIN {
        diff = a - e
        if (diff < 0)
            diff = -diff

        exit(diff <= eps ? 0 : 1)
    }'
}

compare_outputs() {
    local output_file="$1"
    local expected_file="$2"
    local epsilon="$3"

    read -ra actual < "$output_file"
    read -ra expected < "$expected_file"

    if [[ ${#actual[@]} -ne ${#expected[@]} ]]; then
        echo "FAIL: number of fields differs"
        echo "Expected: ${#expected[@]}"
        echo "Actual:   ${#actual[@]}"
        return 1
    fi

    # Primeiro campo deve ser exato (acessos)
    if [[ "${actual[0]}" != "${expected[0]}" ]]; then
        echo "FAIL: field 0 differs"
        echo "Expected: ${expected[0]}"
        echo "Actual:   ${actual[0]}"
        return 1
    fi

    for ((i = 1; i < ${#actual[@]}; i++)); do
        if ! compare_float "${actual[i]}" "${expected[i]}" "$epsilon"; then
            echo "FAIL: field $i differs"
            echo "Expected: ${expected[i]}"
            echo "Actual:   ${actual[i]}"
            echo "Tolerance: $epsilon"
            return 1
        fi
    done
}

for file in "$TEST_DIR"/*.args; do
    name=$(basename "$file" .args)

    echo "Running CI test: $name"

    args=$(cat "$file")
    echo "ARGS=[$args]"

    read -ra args_array <<< "$args"
    policy="${args_array[3]}"

    OUTPUT_FILE="$OUTPUT_DIR/${name}.out"

    "$ROOT_DIR/cache_simulator" $args > "$OUTPUT_FILE"

    if [[ "$policy" == "R" ]]; then
        compare_outputs \
            "$OUTPUT_FILE" \
            "$TEST_DIR/${name}.expected" \
            "0.015"
    else
        diff -u \
            "$TEST_DIR/${name}.expected" \
            "$OUTPUT_FILE"
    fi

    echo "Passed: $name"
done

echo
echo "All tests passed."
