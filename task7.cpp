#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>

using namespace std;

void dijkstra(const unordered_map<char, vector<char>>& graph, char startNode) {
    unordered_map<char, int> distance;
    unordered_map<char, char> previous;
    priority_queue<pair<int, char>, vector<pair<int, char>>, greater<pair<int, char>>> pq;

    for (const auto& node : graph) {
        distance[node.first] = node.first == startNode ? 0 : INT_MAX;
        pq.push({distance[node.first], node.first});
    }

    while (!pq.empty()) {
        char current = pq.top().second;
        pq.pop();

        for (char neighbor : graph.at(current)) {
            int alt = distance[current] + 1; // Assuming each edge has a weight of 1 (hop count)
            if (alt < distance[neighbor]) {
                distance[neighbor] = alt;
                previous[neighbor] = current;
                pq.push({distance[neighbor], neighbor});
            }
        }
    }

    // Output routing table
    cout << "Routing table for node " << startNode << ":\n";
    for (const auto& node : distance) {
        if (node.first != startNode) {
            cout << "To reach node " << node.first << ", next hop is: " << previous[node.first] << endl;
        }
    }
}

int main() {
    unordered_map<char, vector<char>> graph = {
        {'A', {'B', 'C', 'D'}},
        {'B', {'A', 'C'}},
        {'C', {'A', 'B', 'D'}},
        {'D', {'A', 'C'}}
    };

    for (const auto& node : graph) {
        dijkstra(graph, node.first);
    }

    return 0;
}
}