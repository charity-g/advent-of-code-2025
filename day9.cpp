#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

void printGrid(const vector<vector<bool>>& grid) {
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            cout << (grid[i][j] ? '#' : '.');
        }
        cout << endl;
    }
}

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

pair<vector<pair<int,int>>, pair<vector<int>, vector<int>>> compressTiles(const vector<pair<int,int>>& red_tiles) {
    set<int> x_set;
    set<int> y_set;
    map<int, int> x_reverse_map;
    map<int, int> y_reverse_map;

    for (const auto& tile : red_tiles) {
        x_set.insert(tile.first);
        y_set.insert(tile.second);
    }

    vector<int> x_map(x_set.begin(), x_set.end());
    vector<int> y_map(y_set.begin(), y_set.end());

    sort(x_map.begin(), x_map.end());
    sort(y_map.begin(), y_map.end());
    for (int i = 0; i < x_map.size(); ++i) {
        x_reverse_map[x_map[i]] = i;
    }
    for (int i = 0; i < y_map.size(); ++i) {
        y_reverse_map[y_map[i]] = i;
    }

    vector<pair<int,int>> compressed_tiles;
    for (const auto& tile : red_tiles) {
        compressed_tiles.push_back({x_reverse_map[tile.first], y_reverse_map[tile.second]});
    }

    return {compressed_tiles, {x_map, y_map}};
}

void floodfill(vector<vector<bool>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    
    for (int i = 0; i < rows; ++i) {
        grid[i].insert(grid[i].begin(), true); //sentinal col at left
        grid[i].push_back(true); //sentinal col at right
    }
    
    grid.insert(grid.begin(), vector<bool>(cols + 2, true)); //sentinal row at top
    grid.push_back(vector<bool>(cols + 2, true)); //sentinal row at bottom
    printGrid(grid);
    cout << "before flood fill after snetinel" << endl;

    vector<pair<int,int>> stack;
    stack.push_back({0, 0});
    while (!stack.empty()) {
        pair<int,int> curr = stack.back();
        stack.pop_back();

        if (curr.first < 0 || curr.first > rows + 1 || curr.second < 0 || curr.second > cols + 1) {
            continue;
        }
        if (!grid[curr.first][curr.second]) {
            continue;
        }

        grid[curr.first][curr.second] = false;
        stack.push_back({curr.first + 1, curr.second});
        stack.push_back({curr.first - 1, curr.second});
        stack.push_back({curr.first, curr.second + 1});
        stack.push_back({curr.first, curr.second - 1});
    }

    grid.erase(grid.begin()); //remove sentinal row at top
    grid.pop_back(); //remove sentinal row at bottom
    for (int i = 0; i < rows; ++i) {
        grid[i].erase(grid[i].begin()); //remove sentinal col at left
        grid[i].pop_back(); //remove sentinal col at right  
    }
}

// returns grid where grid[i][j] is true if (i,j) is inside polygon
vector<vector<bool>> markPolygononGrid(const vector<pair<int,int>>& compressed_tiles, int rows, int cols) {
    vector<vector<bool>> grid(rows, vector<bool>(cols, true));
    pair<int,int> prev = compressed_tiles[compressed_tiles.size() - 1];

    // mark polygon perimeter on grid
    for (int i = 0; i < compressed_tiles.size(); ++i) {
        pair<int,int> curr = compressed_tiles[i];
        if (prev.first == curr.first) { //x is the same, fill y
            for (int y = min(prev.second, curr.second); y <= max(prev.second, curr.second); ++y) {
                grid[prev.first][y] = false;
            }
        } else { //y is the same, fill x
            for (int y = min(prev.first, curr.first); y <= max(prev.first, curr.first); ++y) {
                grid[y][prev.second] = false;
            }
        }
        prev = curr;
    }
    // flood fill the polygon
    floodfill(grid);
    
    // mark polygon perimeter on grid
    for (int i = 0; i < compressed_tiles.size(); ++i) {
        pair<int,int> curr = compressed_tiles[i];
        
        if (prev.first == curr.first) { //x is the same, fill y
            for (int y = min(prev.second, curr.second); y <= max(prev.second, curr.second); ++y) {
                grid[prev.first][y] = true;
            }
        } else { //y is the same, fill x
            for (int y = min(prev.first, curr.first); y <= max(prev.first, curr.first); ++y) {
                grid[y][prev.second] = true;
            }
        }
        prev = curr;
    }
    cout << endl;
    
    printGrid(grid);


    return grid;
}

vector<vector<int>> generateSat(const vector<vector<bool>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();
    vector<vector<int>> sat(rows + 1, vector<int>(cols + 1, 0));

    //TODO
    return sat;
}

// idea/startegy taken from https://www.reddit.com/user/Gabba333/ [Accessed Dec 28 2025]
// post: https://www.reddit.com/r/adventofcode/comments/1phywvn/2025_day_9_solutions/
void partB(const vector<pair<int,int>>& red_tiles) {
    //compress tiles
    auto [compressed_tiles, xy_maps] = compressTiles(red_tiles);
    //mark polygon on compressed grid
    vector<vector<bool>> grid = markPolygononGrid(compressed_tiles, xy_maps.first.size(), xy_maps.second.size());
    //generate 2d-prefix sum aka Summed Area Table (SAT)
    vector<vector<int>> sat = generateSat(grid);
    
    // generate all rectangles
    //TODO

    
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
