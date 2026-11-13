#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$ROOT_DIR/build"
CXX="${CXX:-g++}"

mkdir -p "$BUILD_DIR"

sources=(
    "src/dry/validation_before.cpp"
    "src/dry/validation_after.cpp"
    "src/dry/independent_rules.cpp"
    "src/dry/premature_abstraction.cpp"
    "src/srp/order_service_before.cpp"
    "src/srp/order_service_after.cpp"
    "src/srp/student_cohesive.cpp"
    "src/srp/over_split_student.cpp"
)

for source in "${sources[@]}"; do
    name="$(basename "${source%.cpp}")"
    echo "Building $source"
    "$CXX" -std=c++17 -Wall -Wextra -Wpedantic \
        "$ROOT_DIR/$source" -o "$BUILD_DIR/$name"
done

echo
echo "All examples compiled successfully."
echo "Binaries are available in: $BUILD_DIR"
