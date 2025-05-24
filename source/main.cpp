#include <iostream>
#include "../include/Graf.h"
#include "../include/PERTGraph.h"

int main() {
    PERTGraph g;
    g.addActivity(1, 3, 3, 5, 6);
    g.addActivity(1, 4, 3, 5, 8);
    g.addActivity(1, 6, 3, 4, 5);
    g.addActivity(1, 7, 4, 4, 7);
    g.addActivity(2, 3, 3, 5, 6);
    g.addActivity(2, 6, 4, 7, 10);
    g.addActivity(3, 5, 4, 6, 6);
    g.addActivity(3, 6, 3, 3, 3);
    g.addActivity(3, 9, 2, 3, 5);
    g.addActivity(4, 7, 3, 4, 6);
    g.addActivity(4, 8, 3, 5, 6);
    g.addActivity(4, 10, 4, 5, 7);
    g.addActivity(5, 6, 3, 6, 7);
    g.addActivity(5, 7, 3, 3, 6);
    g.addActivity(6, 7, 2, 3, 4);
    g.addActivity(6, 9, 4, 7, 9);
    g.addActivity(7, 9, 2, 2, 2);
    g.addActivity(8, 9, 1, 1, 3);
    g.addActivity(8, 9, 4, 6, 9);  // uwaga: powtarzająca się krawędź – możesz pominąć jedną
    g.addActivity(9, 10, 2, 4, 7);
    
    // Obliczamy algorytm PERT
    g.compute();

    // Wyświetlamy wyniki
    g.printResults();
    g.exportGantt();
    return 0;
}