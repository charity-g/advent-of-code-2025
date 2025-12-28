#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;

// Calculates the straight line distance between two junction boxes
long straightLineDistance(const vector<int> a, const vector<int> b) {
    long dist = pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2);
    return dist;
}

// MODIFIES: 
//  - [sometimes] disjoint_set: joins two circuits in the disjoint set
void joinCircuits(vector<int>& disjoint_set, pair<int, int> edge) {
    int root1 = edge.first;
    int root2 = edge.second;

    // Find roots
    while (disjoint_set[root1] >= 0) {
        root1 = disjoint_set[root1];
    }
    while (disjoint_set[root2] >= 0) {
        root2 = disjoint_set[root2];
    }

    if (root1 != root2) {
        if (root1 <= root2) {
            disjoint_set[root1] += disjoint_set[root2];
            disjoint_set[root2] = root1;
        } else {
            disjoint_set[root2] += disjoint_set[root1];
            disjoint_set[root1] = root2;
        }
    }

}

// returns sorted by weight of edges
vector<pair<pair<int, int>, long>> calculatePossibleEdges(const vector<vector<int>>& junction_boxes) {
    vector<pair<pair<int, int>, long>> edges;
    int n = junction_boxes.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long dist = straightLineDistance(junction_boxes[i], junction_boxes[j]);
            edges.push_back({{i, j}, dist});
        }
    }

    sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    return edges;
}

void printEdges(const vector<pair<pair<int, int>, long>>& edges) {
    for (const auto& edge : edges) {
        cout << "(" << edge.first.first << ", " << edge.first.second 
             << ") : dist=" << edge.second << endl;
    }
}

void printDisjointSet(const vector<int>& disjoint_set) {
    cout << "Disjoint Set: ";
    for (const auto& val : disjoint_set) {
        cout << val << " ";
    }
    cout << endl;
}

void partA(const vector<vector<int>>& junction_boxes, int n) {
    vector<int> disjoint_set(junction_boxes.size(), -1);
    vector<pair<pair<int, int>, long>> poss_edges = calculatePossibleEdges(junction_boxes);
    // printEdges(poss_edges);
    for (int i = 0; i < n; ++i) {
        pair<int, int> edge = poss_edges[i].first;
        joinCircuits(disjoint_set, edge);
        // cout << "Joined junction box " << edge.first << " and " << edge.second << endl;
        // printDisjointSet(disjoint_set);
    }
    
    sort(disjoint_set.begin(), disjoint_set.end());
    long res = disjoint_set[0] * disjoint_set[1] * disjoint_set[2] * -1;
    cout << "Part A result: " << res << endl;
}

bool isSingleCircuit(const vector<int>& disjoint_set) {
    int count = 0;
    for (const auto& val : disjoint_set) {
        if (val < 0) {
            count++;
        }
    }
    return count <= 1;
}

void partB(const vector<vector<int>>& junction_boxes) {
    vector<int> disjoint_set(junction_boxes.size(), -1);
    vector<pair<pair<int, int>, long>> poss_edges = calculatePossibleEdges(junction_boxes);
    // printEdges(poss_edges);

    int i = 0;
    while (!isSingleCircuit(disjoint_set)) {
        pair<int, int> edge = poss_edges[i].first;
        joinCircuits(disjoint_set, edge);
        i++;
    }

    pair<int, int> last_edge = poss_edges[i - 1].first;
    cout << junction_boxes[last_edge.first][0] << " " << junction_boxes[last_edge.second][0] << endl;
    long res = (long) junction_boxes[last_edge.first][0] * (long) junction_boxes[last_edge.second][0];
    cout << "Part B result: " << res << endl;
}

int main(int argc, char** argv) {
    int n = 1000;
    ifstream infile("inputs/day8.txt");
    string line;
    vector<vector<int>> junction_boxes;

    while (getline(infile, line)) {
        vector<int> box;
        int prev_i = 0;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == ',') {
                box.push_back(stoi(line.substr(prev_i, i - prev_i)));
                prev_i = i + 1;
            }
        }
        box.push_back(stoi(line.substr(prev_i)));
        junction_boxes.push_back(box);
    }

    // partA(junction_boxes, n);
    partB(junction_boxes);
    return 0;
}
