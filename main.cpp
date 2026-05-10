//main.cpp
#include <iostream>
#include <string>
#include "Graph.h"
#include "DynamicGraph.h"
#include "TSP.h"

using namespace std;

void printMenu() {
    cout << "\n========================================\n";
    cout << "            ROUTE OPTIMIZATION\n";
    cout << "========================================\n";
    cout << " 1. Load Graph from File\n";
    cout << " 2. Display Matrix (Static)\n";
    cout << " 3. Display List (Dynamic)\n";
    cout << " 4. Brute Force (O(n!))\n";
    cout << " 5. Greedy Nearest Neighbor (O(n^2))\n";
    cout << " 6. 2-Opt Improvement (O(n^3))\n";
    cout << " 7. Run All + Compare\n";
    cout << " 8. Memory Analysis\n";
    cout << " 9. Static vs Dynamic\n";
    cout << "10. Exit\n";
    cout << "Choice: ";
}

int main() {
    Graph g;
    DynamicGraph dg;
    TSP* tsp = nullptr;
    bool graphLoaded = false;
    int choice;
    string filename;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nFilename: ";
            cin >> filename;
            if (g.loadFromFile(filename) && dg.loadFromFile(filename)) {
                graphLoaded = true;
                if (tsp != nullptr) delete tsp;
                tsp = new TSP(g);
                cout << "\n[SUCCESS] Graph loaded.\n";
            }
            else {
                cout << "\n[ERROR] Failed to load.\n";
            }
            break;

        case 2:
            if (!graphLoaded) cout << "\nLoad graph first.\n";
            else g.displayMatrix();
            break;

        case 3:
            if (!graphLoaded) cout << "\nLoad graph first.\n";
            else dg.displayList();
            break;

        case 4:
            if (tsp == nullptr) cout << "\nLoad graph first.\n";
            else tsp->displayResult(tsp->bruteForce(), "Brute Force");
            break;

        case 5:
            if (tsp == nullptr) cout << "\nLoad graph first.\n";
            else tsp->displayResult(tsp->greedyNearestNeighbor(), "Greedy");
            break;

        case 6:
            if (tsp == nullptr) cout << "\nLoad graph first.\n";
            else tsp->displayResult(tsp->customImprovement(), "2-Opt Improvement");
            break;

        case 7:
            if (tsp == nullptr) cout << "\nLoad graph first.\n";
            else {
                TSPResult brute = tsp->bruteForce();
                TSPResult greedy = tsp->greedyNearestNeighbor();
                TSPResult custom = tsp->customImprovement();
                tsp->displayResult(brute, "Brute Force");
                tsp->displayResult(greedy, "Greedy");
                tsp->displayResult(custom, "2-Opt");
                tsp->compareResults(brute, "Brute Force", greedy, "Greedy", custom, "2-Opt");
            }
            break;

        case 8:
            if (!graphLoaded) cout << "\nLoad graph first.\n";
            else {
                cout << "\n========================================\n";
                cout << "           MEMORY ANALYSIS\n";
                cout << "========================================\n";
                cout << "Static Graph Memory:  " << g.getMemoryUsage() << " bytes\n";
                cout << "Dynamic Graph Memory: " << dg.getMemoryUsage() << " bytes\n";
            }
            break;

        case 9:
            if (!graphLoaded) cout << "\nLoad graph first.\n";
            else {
                g.displayMatrix();
                dg.displayList();
            }
            break;

        case 10:
            cout << "\nExiting...\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }
    } while (choice != 10);

    if (tsp != nullptr) delete tsp;
    return 0;
}