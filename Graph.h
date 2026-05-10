//Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_CITIES = 10;

class Graph {
private:
    int adjMatrix[MAX_CITIES][MAX_CITIES];
    int numCities;
    char cityNames[MAX_CITIES];

public:
    Graph();
    bool loadFromFile(const string& filename);
    void displayMatrix() const;
    int getNumCities() const;
    int getDistance(int from, int to) const;
    char getCityName(int index) const;
    bool isValid() const;
    int getMemoryUsage() const;
};

#endif
#pragma once
