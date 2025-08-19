#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits> // for numeric_limits
using namespace std;

const double INF = numeric_limits<double>::max();

// Dijkstra’s Algorithm
void dijkstra(int source, const vector<vector<pair<int, double>>>& adjList) {
    int n = adjList.size();
    vector<double> distance(n, INF);
    distance[source] = 0;

    // Min-heap priority queue: (distance, node)
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        double dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        // If the popped distance is already more than the current, skip
        if (dist > distance[node]) continue;

        for (auto& neighbor : adjList[node]) {
            int nextNode = neighbor.first;
            double edgeWeight = neighbor.second;

            if (distance[node] + edgeWeight < distance[nextNode]) {
                distance[nextNode] = distance[node] + edgeWeight;
                pq.push({distance[nextNode], nextNode});
            }
        }
    }

    // Display shortest distances
    cout << "\n============= SHORTEST DISTANCES FROM BIN " << source << " =============\n";
    for (int i = 0; i < n; ++i) {
        if (distance[i] == INF) {
            cout << "Bin " << i << " : INF (not reachable)\n";
        } else {
            cout << "Bin " << i << " : " << distance[i] << "\n";
        }
    }
}

int main() {
    int n;
    cout << "Enter number of bins: ";
    cin >> n;

    vector<vector<pair<int, double>>> adjList(n);

    cout << "Enter edges as: from to distance (-1 to stop):\n";
    while (true) {
        int u, v;
        double w;
        cin >> u;
        if (u == -1) break;
        cin >> v >> w;
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w}); // undirected
    }

    int source = 0; // depot (Bin 0) as starting point
    dijkstra(source, adjList);

    return 0;
}
