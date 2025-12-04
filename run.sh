# cli argument to compile with
DAY=$1

if [ -z "$DAY" ]; then
  echo "Usage: $0 <DAY_NUMBER>"
  exit 1
fi

set -e

rm -f "day$DAY"
g++ -std=c++17 -O2 -g "day$DAY.cpp" -o "day$DAY"

mkdir -p outputs
INPUT="inputs/day$DAY.txt"
OUTPUT="outputs/day$DAY.txt"

if [ -f "$INPUT" ]; then
  ./"day$DAY" < "$INPUT" > "$OUTPUT"
else
  ./"day$DAY" > "$OUTPUT"
fi

cat "$OUTPUT"