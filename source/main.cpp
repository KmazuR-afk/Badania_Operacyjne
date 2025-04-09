#include <iostream>
#include "../include/Graf.h"

int main() {
    Graf g(10);  // Graf z 10 wierzchołkami

// Dodawanie krawędzi (pełny graf symetryczny)
    int dist[10][10] = {
        {0,4,7,3,6,8,5,9,6,4},
        {4,0,5,6,3,7,6,4,8,5},
        {7,5,0,4,6,5,7,8,3,6},
        {3,6,4,0,5,9,4,6,7,8},
        {6,3,6,5,0,4,6,7,8,5},
        {8,7,5,9,4,0,6,8,5,6},
        {5,6,7,4,6,6,0,3,7,5},
        {9,4,8,6,7,8,3,0,4,6},
        {6,8,3,7,8,5,7,4,0,4},
        {4,5,6,8,5,6,5,6,4,0}
    };

    for (int i = 0; i < 10; ++i) {
        for (int j = i + 1; j < 10; ++j) {
            g.addEdge(i, j, dist[i][j]);
        }
    }

    // Wywołanie algorytmu Christofidesa
    auto [tsp,len] = g.christofidesTSP();
    std::cout << "Sciezka TSP (Christofides): ";
    for (int v : tsp) std::cout << v << " => ";
    std::cout<< " (powrot)" << std::endl<<"dlugosc "<<len<<std::endl;
    return 0;
}