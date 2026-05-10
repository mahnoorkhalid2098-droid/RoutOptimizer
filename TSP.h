//TSP.h
#ifndef TSP_H
#define TSP_H

#include "Graph.h"
#include <chrono>
#include <climits>

using namespace std;

struct TSPResult {
    int route[MAX_CITIES + 1];
    int routeLength;
    int totalCost;
    double executionTime;  // in milliseconds
    int memoryUsed;
};

class TSP {
private:
    const Graph& graph;
    void swapInt(int& a, int& b);
    bool isVisited(int city, int visited[], int count) const;
    int calculateCost(int route[], int n) const;
    void permute(int arr[], int start, int end, int& minCost, int bestRoute[]);

public:
    TSP(const Graph& g);
    TSPResult bruteForce();
    TSPResult greedyNearestNeighbor();
    TSPResult customImprovement();
    void displayResult(const TSPResult& result, const string& algorithmName) const;
    void compareResults(const TSPResult& r1, const string& name1,
        const TSPResult& r2, const string& name2,
        const TSPResult& r3, const string& name3) const;
};

#endif