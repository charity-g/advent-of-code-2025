#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

long calculateArea(const pair<int,int>& a, const pair<int,int>& b) {
    long length = abs(a.first - b.first) + 1;
    long width = abs(a.second - b.second) + 1;
    return length * width;
}

void partA(const vector<pair<int,int>>& red_tiles) {
    int n = red_tiles.size();
    long max_area = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            long area = calculateArea(red_tiles[i], red_tiles[j]);
            // cout << "Area between (" << red_tiles[i].first << "," << red_tiles[i].second << ") and ("
            //      << red_tiles[j].first << "," << red_tiles[j].second << ") is " << area << endl;
            if (area > max_area) {
                max_area = area;
            }
        }
    }

    cout << "Part A's result, largest rect area is: " << max_area << endl;
}


// taken from https://www.reddit.com/user/Gabba333/ [Accessed Dec 28 2025]
// * poster: https://www.reddit.com/r/adventofcode/comments/1phywvn/2025_day_9_solutions/
void partB(const vector<pair<int,int>>& red_tiles) {
    //compress tiles
    //mark polygon on compressed grid
    //generate 2d-prefix sum aka Summed Area Table (SAT)
    // generate all rectangles
    // sort rectangles by area descending
    // for each rectangle, check if it is fully covered by red tiles using SAT
    // uncompress top rectangle found
        
    long max_area = 0;
    cout << "Part B's result, largest rect area is: " << max_area << endl;
}

int main(int argc, char** argv) {
    ifstream infile("inputs/day9.txt");
    string line;
    
    vector<pair<int,int>> red_tiles;

    while (getline(infile, line)) {
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ',') {
                red_tiles.push_back({stoi(line.substr(0, i)), stoi(line.substr(i + 1))});
                break;
            }
        }
    }

    // partA(red_tiles);
    partB(red_tiles);

    return 0;
}
