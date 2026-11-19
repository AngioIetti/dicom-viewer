#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

cd "$ROOT_DIR"

if command -v xhost >/dev/null; then
    xhost +SI:localuser:root >/dev/null
    trap 'xhost -SI:localuser:root >/dev/null' EXIT
fi

docker compose run --rm dev ./build/src/dicom-viewer
