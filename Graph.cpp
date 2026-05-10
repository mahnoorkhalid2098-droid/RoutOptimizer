//Graph.cpp
#include "Graph.h"

Graph::Graph() {
    numCities = 0;
    for (int i = 0; i < MAX_CITIES; i++) {
        cityNames[i] = 'A' + i;
        for (int j = 0; j < MAX_CITIES; j++) {
            adjMatrix[i][j] = 0;
        }
    }
}

bool Graph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "\n[ERROR] Could not open file.\n";
        return false;
    }

    file >> numCities;
    if (numCities <= 0 || numCities > MAX_CITIES) {
        cout << "\n[ERROR] Invalid city count.\n";
        return false;
    }

    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            file >> adjMatrix[i][j];
        }
    }

    file.close();
    return true;
}

void Graph::displayMatrix() const {
    cout << "\n========================================\n";
    cout << "         ADJACENCY MATRIX\n";
    cout << "========================================\n\n";
    cout << "     ";
    for (int i = 0; i < numCities; i++) {
        cout << "  " << cityNames[i] << "  ";
    }
    cout << endl;
    for (int i = 0; i < numCities; i++) {
        cout << "  " << cityNames[i] << " | ";
        for (int j = 0; j < numCities; j++) {
            cout << " " << setw(3) << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int Graph::getNumCities() const { return numCities; }

int Graph::getDistance(int from, int to) const {
    return adjMatrix[from][to];
}

char Graph::getCityName(int index) const {
    if (index >= 0 && index < numCities) return cityNames[index];
    return '?';
}

bool Graph::isValid() const { return numCities > 0; }

int Graph::getMemoryUsage() const { return sizeof(adjMatrix); }