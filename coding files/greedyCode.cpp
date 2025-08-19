#include <iostream>
#include <vector>
#include <queue>
#include <fstream> // add at top if not added
#include <utility>
#include <limits>
#include <cmath>
#include <algorithm>
using namespace std;

struct Bin {
    int id;
    double x, y;
    double fill;
};

const double INF = numeric_limits<double>::max();

double calculateDistance(const Bin& a, const Bin& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Find the next nearest unvisited bin
int findNearest(int current, const vector<int>& bins_to_visit, const vector<vector<double>>& dist_matrix, const vector<bool>& visited) {
    double min_dist = INF;
    int next_bin = -1;
    for (int b : bins_to_visit) {
        if (!visited[b] && dist_matrix[current][b] < min_dist) {
            min_dist = dist_matrix[current][b];
            next_bin = b;
        }
    }
    return next_bin;
}

int main() {
    int n;
    cout << "Enter number of bins: ";
    cin >> n;

    vector<Bin> bins(n);
    for (int i = 0; i < n; ++i) {
        cout << "Enter x y fill% for Bin " << i << ": ";
        cin >> bins[i].x >> bins[i].y >> bins[i].fill;
        bins[i].id = i;
    }

    // Build distance matrix
    vector<vector<double>> dist_matrix(n, vector<double>(n, INF));
    for (int i = 0; i < n; ++i) {
        dist_matrix[i][i] = 0;
        for (int j = i + 1; j < n; ++j) {
            double dist = calculateDistance(bins[i], bins[j]);
            dist_matrix[i][j] = dist;
            dist_matrix[j][i] = dist;
        }
    }

    // Identify bins to visit (fill% >= 50)
    vector<int> bins_to_visit;
    for (const auto& b : bins) {
        if (b.fill >= 50 || b.id == 0) { // always include depot
            bins_to_visit.push_back(b.id);
        }
    }

    vector<bool> visited(n, false);
    int current = 0; // start at depot
    visited[current] = true;
    double total_distance = 0;
    vector<int> route = {current};

    cout << "\nPlanned Route (Greedy): ";

    while (true) {
        int next = findNearest(current, bins_to_visit, dist_matrix, visited);
        if (next == -1) break;
        total_distance += dist_matrix[current][next];
        current = next;
        visited[current] = true;
        route.push_back(current);
    }

    for (int b : route) {
        cout << "Bin " << b << " -> ";
    }
    cout << "END\n";
    cout << "Total distance to collect from priority bins: " << total_distance << "\n";
    // Export planned route to CSV
ofstream routeFile("planned_route.csv");
if (!routeFile) {
    cerr << "Error opening planned_route.csv for writing.\n";
    return 1;
}
routeFile << "bin_id,x,y,fill\n";
for (int b : route) {
    routeFile << bins[b].id << "," << bins[b].x << "," << bins[b].y << "," << bins[b].fill << "\n";
}
routeFile.close();
cout << "✅ planned_route.csv created for visualization.\n";


    return 0;
}
