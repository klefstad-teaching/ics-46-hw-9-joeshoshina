#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false); //init all vec to false since we haven't visited any
    distances[source] = 0;
    previous[source] = UNDEFINED;

    //stl format for pq minHeap, greater is the comparator functor
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({0, source}); //{weight, vertex} for minHeap ordering

    // Dijkstra's Algorithm
    while (!minHeap.empty()) {
        int u = minHeap.top().second; //pair get vert
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<int> path;
    for (int i = destination; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());
    return path;
}
void print_path(const vector<int>& v, int total){
    if (v.empty()) {
        cout << "\nTotal cost is " << total << endl; 
        return;
    }

    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << (i < v.size() - 1 ? " " : ""); 
    }
    cout << " \nTotal cost is " << total << endl;
}