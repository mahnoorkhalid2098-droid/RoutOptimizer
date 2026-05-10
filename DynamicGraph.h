//DynamicGraph.h
#ifndef DYNAMICGRAPH_H
#define DYNAMICGRAPH_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct AdjNode {
    int destCity;
    int weight;
    AdjNode* next;
    AdjNode(int d, int w) : destCity(d), weight(w), next(nullptr) {}
};

class DynamicGraph {
private:
    AdjNode* adjList[10];
    int numCities;
    char cityNames[10];

public:
    DynamicGraph();
    ~DynamicGraph();
    bool loadFromFile(const string& filename);
    void displayList() const;
    int getNumCities() const;
    int getDistance(int from, int to) const;
    char getCityName(int index) const;
    bool isValid() const;
    int getMemoryUsage() const;
};

#endif
#pragma once