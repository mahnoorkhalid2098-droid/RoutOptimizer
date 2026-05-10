# RoutOptimizer
A Route Optimization System using Travelling Salesperson Problem (TSP) implemented in C++ and Qt with Brute Force, Greedy, and 2-Opt algorithms.
# Route Optimization System using TSP

## Overview
This project implements a Route Optimization System using the Travelling Salesperson Problem (TSP).

The system calculates the shortest possible route between cities using different algorithms and compares their performance.

## Features
- Adjacency Matrix Representation
- Adjacency List Representation
- Brute Force Algorithm
- Greedy Nearest Neighbor
- 2-Opt Improvement Algorithm
- Performance Comparison
- Memory Analysis
- GUI using Qt
- File Handling

## Technologies Used
- C++
- Qt Framework
- Object Oriented Programming
- Data Structures & Algorithms

## Algorithms Implemented

### 1. Brute Force
Checks all possible routes.

Complexity:
O(n!)

### 2. Greedy Nearest Neighbor
Chooses nearest unvisited city.

Complexity:
O(n²)

### 3. 2-Opt Improvement
Improves greedy route using edge swapping.

Complexity:
O(n³)

## Sample Input

4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0

## Sample Output

Optimal Route:
A → B → D → C → A

Cost:
80

## GUI
The project also includes a Qt GUI for:
- Loading graph files
- Running algorithms
- Comparing outputs
- Visualizing results

## Authors
- Mahnoor Khalid
- [Second Member Name]

## Course
Data Structures and Algorithms
Bahria University Islamabad
