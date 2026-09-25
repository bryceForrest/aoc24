#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"

shopt -s nullglob
max_n=0

for dir in day*; do
    [[ -d "$dir" ]] || continue
    n=${dir#day}

    if (( 10#$n > max_n )); then
        max_n=$((10#$n))
    fi
done

next=$(printf "day%02d" $((max_n + 1)))

if [[ -e "$next" ]]; then
    echo "$next already exists" >&2
    exit 1
fi

cp -r template "$next"
touch \
    "$next/sample_input_part_1.txt" \
    "$next/sample_input_part_2.txt" \
    "$next/input_part_1.txt" \
    "$next/input_part_2.txt" \
    "$next/README.md"

echo "$next created from template"