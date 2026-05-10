// DynamicGaph.cpp
#include "DynamicGraph.h"
#include <iomanip>

DynamicGraph::DynamicGraph() {
    numCities = 0;
    for (int i = 0; i < 10; i++) {
        adjList[i] = nullptr;
        cityNames[i] = 'A' + i;
    }
}

DynamicGraph::~DynamicGraph() {
    for (int i = 0; i < numCities; i++) {
        AdjNode* curr = adjList[i];
        while (curr != nullptr) {
            AdjNode* temp = curr;
            curr = curr->next;
            delete temp;
        }
        adjList[i] = nullptr;
    }
}

bool DynamicGraph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\n[ERROR] Could not open file.\n";
        return false;
    }

    file >> numCities;
    if (numCities <= 0 || numCities > 10) {
        cout << "\n[ERROR] Invalid number of cities.\n";
        return false;
    }

    for (int i = 0; i < numCities; i++) {
        adjList[i] = nullptr;
        for (int j = 0; j < numCities; j++) {
            int weight;
            file >> weight;
            if (weight != 0) {
                AdjNode* node = new AdjNode(j, weight);
                if (adjList[i] == nullptr) {
                    adjList[i] = node;
                }
                else {
                    AdjNode* curr = adjList[i];
                    while (curr->next != nullptr) {
                        curr = curr->next;
                    }
                    curr->next = node;
                }
            }
        }
    }
    file.close();
    return true;
}

void DynamicGraph::displayList() const {
    cout << "\n========================================\n";
    cout << "         ADJACENCY LIST\n";
    cout << "========================================\n";
    for (int i = 0; i < numCities; i++) {
        cout << cityNames[i] << " -> ";
        AdjNode* curr = adjList[i];
        if (curr == nullptr) cout << "NULL";
        while (curr != nullptr) {
            cout << "[" << cityNames[curr->destCity] << ":" << curr->weight << "]";
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next;
        }
        cout << endl;
    }
}

int DynamicGraph::getNumCities() const { return numCities; }

int DynamicGraph::getDistance(int from, int to) const {
    AdjNode* curr = adjList[from];
    while (curr != nullptr) {
        if (curr->destCity == to) return curr->weight;
        curr = curr->next;
    }
    return 0;
}

char DynamicGraph::getCityName(int index) const {
    if (index >= 0 && index < numCities) return cityNames[index];
    return '?';
}

bool DynamicGraph::isValid() const { return numCities > 0; }

int DynamicGraph::getMemoryUsage() const {
    int count = 0;
    for (int i = 0; i < numCities; i++) {
        AdjNode* curr = adjList[i];
        while (curr != nullptr) {
            count++;
            curr = curr->next;
        }
    }
    return count * sizeof(AdjNode);
}