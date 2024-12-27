#include "graph.h"
#include <algorithm>

void Graph::tambahJalur(string from, string to, int jarak) {
    adjacencyList[from].push_back({to, jarak});
    adjacencyList[to].push_back({from, jarak}); // Graf tak berarah
}

void Graph::tampilkanGraf() {
    for (const auto& node : adjacencyList) {
        cout << "Stadion: " << node.first << "\n";
        for (const auto& neighbor : node.second) {
            cout << "  -> " << neighbor.first << " (" << neighbor.second << " km)\n";
        }
    }
}

void Graph::jalurTercepat(string from, string to) {
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<>> pq;

    // Inisialisasi jarak
    for (const auto& node : adjacencyList) {
        distances[node.first] = numeric_limits<int>::max();
    }
    distances[from] = 0;
    pq.push({0, from});

    while (!pq.empty()) {
        auto [currentDistance, currentNode] = pq.top();
        pq.pop();

        if (currentDistance > distances[currentNode]) continue;

        for (const auto& neighbor : adjacencyList[currentNode]) {
            int newDistance = currentDistance + neighbor.second;
            if (newDistance < distances[neighbor.first]) {
                distances[neighbor.first] = newDistance;
                previous[neighbor.first] = currentNode;
                pq.push({newDistance, neighbor.first});
            }
        }
    }

    if (distances[to] == numeric_limits<int>::max()) {
        cout << "Tidak ada jalur dari " << from << " ke " << to << ".\n";
        return;
    }

    // Menampilkan jalur terpendek
    vector<string> path;
    for (string at = to; at != ""; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "Jalur tercepat dari " << from << " ke " << to << ":\n";
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1) cout << " -> ";
    }
    cout << "\nTotal jarak: " << distances[to] << " km\n";
}
