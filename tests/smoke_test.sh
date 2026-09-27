#!/usr/bin/env bash
set -euo pipefail
# Use a temporary working directory so test runs never overwrite a user's readings.
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
mkdir -p "$TMP/data" "$TMP/reports"
cd "$TMP"
printf '2\n\n3\n\n4\n\n5\n\n6\n6\n\n7\n\n8\n\n9\n' | "$ROOT/smartmeter" > output.txt
grep -q 'Total pulses: 2000' output.txt
grep -q 'Total energy: 2.000 kWh' output.txt
grep -q '\[ALERT\] Hour 8' output.txt
grep -q 'Estimated usage cost: Rs 12.00' output.txt
test -s data/readings.csv
test -s reports/energy_report.txt
grep -q '^8,430,' reports/alerts.csv
echo 'PASS: simulation, totals, anomaly, bill, CSV and report generation'
