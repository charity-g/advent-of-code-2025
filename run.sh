# cli argument to compile with
DAY=$1

g++ day$DAY.cpp -o day$DAY
./day$DAY < inputs/day$DAY.txt 

cat outputs/day$DAY.txt