#include <iostream>
#include <vector>
#include<iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

using namespace std;

// Structure to store each garbage bin's data
struct Bin {
    int id;
    double x, y;
    double fill_percentage;
};

// Function to calculate Euclidean distance between two bins
double calculateDistance(const Bin& a, const Bin& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main() {
    srand(time(0)); // Seed for random generation

    int n = 10; // Number of bins (adjustable)

    vector<Bin> bins;

    // Generating simulated bins
    for(int i = 0; i < n; ++i) {
        Bin b;
        b.id = i;
        b.x = rand() % 100; // x-coordinate between 0-99
        b.y = rand() % 100; // y-coordinate between 0-99
        b.fill_percentage = 20 + (rand() % 76); // fill between 20-95
        bins.push_back(b);
    }

    // Display bins
    cout << "Bin Data:\n";
    cout << "ID\tX\tY\tFill%\n";
    for(const auto& b : bins) {
        cout << b.id << "\t" << b.x << "\t" << b.y << "\t" << b.fill_percentage << "%\n";
    }

    // Building adjacency list with distances
    vector<vector<pair<int, double>>> adjList(n);

    for(int i = 0; i < n; ++i) {
        for(int j = i+1; j < n; ++j) {
            double dist = calculateDistance(bins[i], bins[j]);
            adjList[i].push_back({j, dist});
            adjList[j].push_back({i, dist});
        }
    }
    cout << fixed << setprecision(2);


    // Display adjacency list
    cout << "\nAdjacency List with Distances:\n";
    for(int i = 0; i < n; ++i) {
        cout << "Bin " << i << " -> ";
        for(const auto& neighbor : adjList[i]) {
            cout << "(Bin " << neighbor.first << ", Dist: " << neighbor.second << ") ";
        }
        cout << endl;
    }
    
    ofstream binFile("bins.csv");
binFile << "id,x,y,fill\n";
for(const auto& b : bins) {
    binFile << b.id << "," << b.x << "," << b.y << "," << b.fill_percentage << "\n";
}
binFile.close();

ofstream edgeFile("edges.csv");
edgeFile << "from,to,weight\n";
for(int i = 0; i < n; ++i) {
    for(const auto& neighbor : adjList[i]) {
        if(i < neighbor.first) { // avoid duplicate edges
            edgeFile << i << "," << neighbor.first << "," << neighbor.second << "\n";
        }
    }
}
edgeFile.close();

    return 0;
}



