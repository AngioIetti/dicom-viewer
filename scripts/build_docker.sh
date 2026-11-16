#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd "$ROOT_DIR"

docker compose run --rm dev bash -c '
    cmake -S . -B build -G Ninja \
        -DCMAKE_BUILD_TYPE=Release &&
    cmake --build build --parallel
'