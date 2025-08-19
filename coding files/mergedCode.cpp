#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Bin {
    int id;
    double x, y;
    double fill;
};

const double INF = numeric_limits<double>::max();

// Calculate Euclidean distance
double calculateDistance(const Bin& a, const Bin& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Dijkstra for shortest paths from a source
vector<double> dijkstra(int source, const vector<vector<pair<int, double>>>& adj, int n) {
    vector<double> dist(n, INF);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        auto [current_dist, u] = pq.top();
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (auto [v, weight] : adj[u]) {
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// Find the nearest unvisited bin in the priority list (Greedy)
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

    // Build adjacency list and distance matrix
    vector<vector<pair<int, double>>> adj(n);
    vector<vector<double>> dist_matrix(n, vector<double>(n, INF));

    for (int i = 0; i < n; ++i) {
        dist_matrix[i][i] = 0;
        for (int j = i + 1; j < n; ++j) {
            double dist = calculateDistance(bins[i], bins[j]);
            adj[i].push_back({j, dist});
            adj[j].push_back({i, dist});
            dist_matrix[i][j] = dist;
            dist_matrix[j][i] = dist;
        }
    }

    // Export bins.csv
    ofstream binsFile("bins.csv");
    binsFile << "id,x,y,fill\n";
    for (const auto& b : bins) {
        binsFile << b.id << "," << b.x << "," << b.y << "," << b.fill << "\n";
    }
    binsFile.close();
    cout << "✅ bins.csv created.\n";

    // Export edges.csv
    ofstream edgesFile("edges.csv");
    edgesFile << "from,to,weight\n";
    for (int i = 0; i < n; ++i) {
        for (auto [j, w] : adj[i]) {
            if (i < j) { // avoid duplicate edges
                edgesFile << i << "," << j << "," << w << "\n";
            }
        }
    }
    edgesFile.close();
    cout << "✅ edges.csv created.\n";

    // Dijkstra from Bin 0
    vector<double> distances = dijkstra(0, adj, n);

    cout << "\n============= SHORTEST DISTANCES FROM BIN 0 =============\n";
    for (int i = 0; i < n; ++i) {
        cout << "Bin " << i << " : ";
        if (distances[i] == INF)
            cout << "INF (not reachable)\n";
        else
            cout << fixed << setprecision(2) << distances[i] << "\n";
    }

    // Priority bins for collection (fill% >= 50)
    vector<int> bins_to_visit;
    for (const auto& b : bins) {
        if (b.fill >= 50 || b.id == 0) {
            bins_to_visit.push_back(b.id);
        }
    }

    // Greedy Route Planning
    vector<bool> visited(n, false);
    int current = 0;
    visited[current] = true;
    double total_distance = 0;
    vector<int> route = {current};

    while (true) {
        int next = findNearest(current, bins_to_visit, dist_matrix, visited);
        if (next == -1) break;
        total_distance += dist_matrix[current][next];
        current = next;
        visited[current] = true;
        route.push_back(current);
    }

    cout << "\n============= PLANNED COLLECTION ROUTE (GREEDY) =============\n";
    for (int b : route) {
        cout << "Bin " << b << " -> ";
    }
    cout << "END\n";
    cout << "Total distance for collection: " << fixed << setprecision(2) << total_distance << "\n";

    // Export planned_route.csv
    ofstream routeFile("planned_route.csv");
    routeFile << "bin_id,x,y,fill\n";
    for (int b : route) {
        routeFile << bins[b].id << "," << bins[b].x << "," << bins[b].y << "," << bins[b].fill << "\n";
    }
    routeFile.close();
    cout << "✅ planned_route.csv created for visualization.\n";

    return 0;
}
