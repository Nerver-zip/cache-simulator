#!/bin/bash

set -e

for file in tests/*.args; do
    name=$(basename "$file" .args)

    echo "Running $name"

    args=$(cat "$file")

    ./cache_simulator $args > output.txt

    diff -u output.txt tests/${name}.expected

    echo "Passed $name"
done
