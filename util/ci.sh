#! /bin/sh
set -e
cd "$(dirname "$0")"/..

for board in d1_mini esp32dev; do
    echo "-- Checking ${board}..."
    pio check -e "${board}" --fail-on-defect high
done
