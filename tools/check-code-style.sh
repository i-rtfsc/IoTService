#!/bin/bash
#echo "[Clang-Format Check]"
#./cmake/check-clang-format.sh || exit 1

echo "[Clang-Tidy Check]"
cd cmake-build-debug
run-clang-tidy -p . || echo "[NOTE] Please install run-clang-tidy or use clang-tidy manually"
