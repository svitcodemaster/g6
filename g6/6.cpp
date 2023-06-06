//There are flight paths between cities. 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class Graph {
private:
    unordered_map<string, vector<pair<string, int>>> adjList;

public:
    void addFlightPath(const string& source, const string& destination, int cost) {
        adjList[source].push_back(make_pair(destination, cost));
        adjList[destination].push_back(make_pair(source, cost));
    }

    bool isConnected() {
        if (adjList.empty()) {
            // Graph is empty, so considered connected
            return true;
        }

        // Perform breadth-first search starting from an arbitrary node
        string startNode = adjList.begin()->first;
        set<string> visited;

        vector<string> queue;
        queue.push_back(startNode);

        int front = 0;

        while (front < queue.size()) {
            string current = queue[front++];
            visited.insert(current);

            for (const auto& neighbor : adjList[current]) {
                if (visited.find(neighbor.first) == visited.end()) {
                    queue.push_back(neighbor.first);
                }
            }
        }

        return visited.size() == adjList.size();
    }
};

int main() {
    Graph flightGraph;

    int numFlights;
    cout << "Enter the number of flight paths: ";
    cin >> numFlights;

    cin.ignore(); // Ignore the newline character

    for (int i = 1; i <= numFlights; i++) {
        string source, destination;
        int cost;

        cout << "Enter details for flight path " << i << ":" << endl;
        cout << "Source city/airport: ";
        getline(cin, source);
        cout << "Destination city/airport: ";
        getline(cin, destination);
        cout << "Cost: ";
        cin >> cost;

        cin.ignore(); // Ignore the newline character

        flightGraph.addFlightPath(source, destination, cost);
    }

    // Check if the graph is connected
    bool isConnected = flightGraph.isConnected();

    if (isConnected) {
        cout << "The graph is connected." << endl;
    } else {
        cout << "The graph is not connected." << endl;
    }

    return 0;
}
