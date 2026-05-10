//TSP.cpp
#include "TSP.h"
#include <iostream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

TSP::TSP(const Graph& g) : graph(g) {}

void TSP::swapInt(int& a, int& b) {
    int temp = a; a = b; b = temp;
}

bool TSP::isVisited(int city, int visited[], int count) const {
    for (int i = 0; i < count; i++) {
        if (visited[i] == city) return true;
    }
    return false;
}

int TSP::calculateCost(int route[], int n) const {
    int totalCost = 0;
    for (int i = 0; i < n - 1; i++) {
        int distance = graph.getDistance(route[i], route[i + 1]);
        if (distance == 0) return INT_MAX;
        totalCost += distance;
    }
    int returnDistance = graph.getDistance(route[n - 1], route[0]);
    if (returnDistance == 0) return INT_MAX;
    totalCost += returnDistance;
    return totalCost;
}

void TSP::permute(int arr[], int start, int end, int& minCost, int bestRoute[]) {
    if (start == end) {
        int cost = calculateCost(arr, end + 1);
        if (cost < minCost) {
            minCost = cost;
            for (int i = 0; i <= end; i++) bestRoute[i] = arr[i];
        }
        return;
    }
    for (int i = start; i <= end; i++) {
        swapInt(arr[start], arr[i]);
        permute(arr, start + 1, end, minCost, bestRoute);
        swapInt(arr[start], arr[i]);
    }
}

TSPResult TSP::bruteForce() {
    TSPResult result;
    result.totalCost = INT_MAX;
    int n = graph.getNumCities();
    if (n <= 0) return result;

    // FIXED: High resolution clock for accurate timing
    auto start = high_resolution_clock::now();

    int cities[MAX_CITIES];
    int bestRoute[MAX_CITIES];
    for (int i = 0; i < n; i++) cities[i] = i;
    int minCost = INT_MAX;
    permute(cities, 1, n - 1, minCost, bestRoute);

    result.totalCost = minCost;
    for (int i = 0; i < n; i++) result.route[i] = bestRoute[i];
    result.route[n] = bestRoute[0];
    result.routeLength = n + 1;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    result.executionTime = duration.count() / 1000.0; // Convert to milliseconds

    result.memoryUsed = graph.getMemoryUsage();
    return result;
}

TSPResult TSP::greedyNearestNeighbor() {
    TSPResult result;
    result.totalCost = 0;
    int n = graph.getNumCities();
    if (n <= 0) return result;

    // FIXED: High resolution clock
    auto start = high_resolution_clock::now();

    int visited[MAX_CITIES];
    int visitCount = 0;
    int currentCity = 0;
    visited[visitCount++] = 0;
    result.route[0] = 0;

    while (visitCount < n) {
        int nearestCity = -1;
        int minimumDistance = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!isVisited(i, visited, visitCount)) {
                int distance = graph.getDistance(currentCity, i);
                if (distance > 0 && distance < minimumDistance) {
                    minimumDistance = distance;
                    nearestCity = i;
                }
            }
        }
        if (nearestCity == -1) {
            result.totalCost = INT_MAX;
            return result;
        }
        result.totalCost += minimumDistance;
        currentCity = nearestCity;
        visited[visitCount++] = currentCity;
        result.route[visitCount - 1] = currentCity;
    }

    int returnDistance = graph.getDistance(currentCity, 0);
    if (returnDistance == 0) {
        result.totalCost = INT_MAX;
        return result;
    }
    result.totalCost += returnDistance;
    result.route[visitCount] = 0;
    result.routeLength = visitCount + 1;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);  // Nanoseconds for more precision
    result.executionTime = duration.count() / 1000000.0;  // Convert to milliseconds

    result.memoryUsed = graph.getMemoryUsage();
    return result;
}

TSPResult TSP::customImprovement() {
    TSPResult result = greedyNearestNeighbor();
    int n = graph.getNumCities();
    if (result.totalCost == INT_MAX) return result;

    // FIXED: High resolution clock
    auto start = high_resolution_clock::now();

    int route[MAX_CITIES];
    for (int i = 0; i < n; i++) route[i] = result.route[i];

    bool improved = true;
    int iterations = 0;
    while (improved && iterations < 100) {
        improved = false;
        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int oldCost = graph.getDistance(route[i - 1], route[i]) +
                    graph.getDistance(route[j], route[(j + 1) % n]);
                int newCost = graph.getDistance(route[i - 1], route[j]) +
                    graph.getDistance(route[i], route[(j + 1) % n]);

                if (newCost < oldCost) {
                    int left = i, right = j;
                    while (left < right) {
                        int temp = route[left];
                        route[left] = route[right];
                        route[right] = temp;
                        left++;
                        right--;
                    }
                    improved = true;
                }
            }
        }
        iterations++;
    }

    result.totalCost = calculateCost(route, n);
    for (int i = 0; i < n; i++) result.route[i] = route[i];
    result.route[n] = route[0];
    result.routeLength = n + 1;

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(end - start);
    result.executionTime = duration.count() / 1000000.0;

    result.memoryUsed = graph.getMemoryUsage();
    return result;
}

void TSP::displayResult(const TSPResult& result, const string& algorithmName) const {
    cout << "\n========================================\n";
    cout << " RESULT: " << algorithmName << endl;
    cout << "========================================\n";
    if (result.totalCost == INT_MAX) {
        cout << "\n NO VALID ROUTE FOUND.\n";
        return;
    }
    cout << "\n ROUTE: ";
    for (int i = 0; i < result.routeLength; i++) {
        cout << graph.getCityName(result.route[i]);
        if (i < result.routeLength - 1) cout << " -> ";
    }
    cout << "\n\n COST: " << result.totalCost;

    // FIXED: Show micro/nano seconds if too small
    if (result.executionTime < 0.001) {
        cout << "\n TIME: " << fixed << setprecision(3) << result.executionTime * 1000 << " µs";
    }
    else {
        cout << "\n TIME: " << fixed << setprecision(3) << result.executionTime << " ms";
    }

    cout << "\n MEMORY: " << result.memoryUsed << " bytes";
    cout << "\n========================================\n";
}

void TSP::compareResults(const TSPResult& r1, const string& name1,
    const TSPResult& r2, const string& name2,
    const TSPResult& r3, const string& name3) const {
    cout << "\n========================================\n";
    cout << "         PERFORMANCE COMPARISON\n";
    cout << "========================================\n\n";
    cout << left << setw(25) << "Algorithm" << setw(15) << "Cost"
        << setw(20) << "Time(ms)" << setw(15) << "Memory" << endl;
    cout << "------------------------------------------------------------\n";

    // For time display
    string t1 = (r1.executionTime < 0.001) ? to_string(r1.executionTime * 1000) + " µs" : to_string(r1.executionTime) + " ms";
    string t2 = (r2.executionTime < 0.001) ? to_string(r2.executionTime * 1000) + " µs" : to_string(r2.executionTime) + " ms";
    string t3 = (r3.executionTime < 0.001) ? to_string(r3.executionTime * 1000) + " µs" : to_string(r3.executionTime) + " ms";

    cout << left << setw(25) << name1 << setw(15) << r1.totalCost
        << setw(20) << t1
        << setw(15) << r1.memoryUsed << endl;
    cout << left << setw(25) << name2 << setw(15) << r2.totalCost
        << setw(20) << t2
        << setw(15) << r2.memoryUsed << endl;
    cout << left << setw(25) << name3 << setw(15) << r3.totalCost
        << setw(20) << t3
        << setw(15) << r3.memoryUsed << endl;
    cout << "\n========================================\n";
}