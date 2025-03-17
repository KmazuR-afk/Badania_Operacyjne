#include <iostream>
#include "../include/Graf.h"

int main() {
    Graf g1(10);
    std::srand(std::time(0));
    auto randomWeight = []() { return std::rand() % 10 + 1; };
    g1.addEdge(0, 1, randomWeight());
    g1.addEdge(1, 2, randomWeight());
    g1.addEdge(2, 3, randomWeight());
    g1.addEdge(3, 0, randomWeight());
    g1.addEdge(0, 2, randomWeight());
    g1.addEdge(1, 3, randomWeight());
    g1.addEdge(0, 4, randomWeight());
    g1.addEdge(4, 2, randomWeight());
    g1.addEdge(1, 4, randomWeight());
    g1.addEdge(3, 4, randomWeight());
    g1.addEdge(4, 5, randomWeight());
    g1.addEdge(3, 7, randomWeight());
    g1.addEdge(5, 6, randomWeight());
    g1.addEdge(6, 7, randomWeight());
    g1.addEdge(7, 8, randomWeight());
    g1.addEdge(8, 5, randomWeight()); // Tworzy cykl 5-6-7-8-5
    g1.addEdge(5, 7, randomWeight());
    g1.addEdge(6, 8, randomWeight());
    g1.addEdge(5, 9, randomWeight());
    g1.addEdge(6, 9, randomWeight());
    g1.addEdge(7, 9, randomWeight());
    g1.addEdge(8, 9, randomWeight());
    g1.display(3);
    std::vector<int> bfs1=g1.BFS(3);
    std::cout<<"BFS:\n";
    for(auto i:bfs1){
        std::cout<<i<<" -> ";
    }
    std::cout<<std::endl;
    std::cout<<"czy graf jest cykliczny? - "<<std::boolalpha<<g1.isCyclic(0)<<std::endl<<std::noboolalpha;
    std::cout<<"czy graf jest spójny? - "<<std::boolalpha<<g1.isConnected()<<std::endl<<std::noboolalpha;
    std::vector<Edge> prim=g1.Prim();
    std::cout << "Drzewo rozpinające (waga, skąd, dokąd):\n";
    for (const auto& [weight, from, to] : prim) {
        std::cout << "(" << weight << ", " << from << ", " << to << ")\n";
    }
    /*Graf g2(10);

    // Komponent 1 (cykl i dodatkowe krawędzie)
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.addEdge(3, 0); // Tworzy cykl 0-1-2-3-0
    g2.addEdge(0, 2);
    g2.addEdge(1, 3);
    g2.addEdge(0, 4);
    g2.addEdge(4, 2);
    g2.addEdge(1, 4);
    g2.addEdge(3, 4);
    // Komponent 2 (cykl i dodatkowe krawędzi)
    g2.addEdge(5, 6);
    g2.addEdge(6, 7);
    g2.addEdge(7, 8);
    g2.addEdge(8, 5); // Tworzy cykl 5-6-7-8-5
    g2.addEdge(5, 7);
    g2.addEdge(6, 8);
    g2.addEdge(5, 9);
    g2.addEdge(6, 9);
    g2.addEdge(7, 9);
    g2.addEdge(8, 9);
    g2.display(3);
    std::vector<int> bfs2=g2.BFS(3);
    std::cout<<"BFS:\n";
    for(auto i:bfs2){
        std::cout<<i<<" -> ";
    }
    std::cout<<std::endl;
    std::cout<<"czy graf jest cykliczny? - "<<std::boolalpha<<g2.isCyclic(0)<<std::endl<<std::noboolalpha;
    std::cout<<"czy graf jest spójny? - "<<std::boolalpha<<g2.isConnected()<<std::endl<<std::noboolalpha;
    Graf g3(10);

    // Spójny, acykliczny graf (drzewo z 10 wierzchołkami)
    g3.addEdge(0, 1);
    g3.addEdge(0, 2);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(2, 5);
    g3.addEdge(2, 6);
    g3.addEdge(3, 7);
    g3.addEdge(4, 8);
    g3.addEdge(5, 9);
    std::vector<int> bfs3=g3.BFS(3);
    std::cout<<"BFS:\n";
    for(auto i:bfs3){
        std::cout<<i<<" -> ";
    }
    std::cout<<std::endl;
    std::cout<<"czy graf jest cykliczny? - "<<std::boolalpha<<g3.isCyclic(0)<<std::endl<<std::noboolalpha;
    std::cout<<"czy graf jest spójny? - "<<std::boolalpha<<g3.isConnected()<<std::endl<<std::noboolalpha;*/
    /*//badanie funkcjonalności isConnected dla grafów skierowanych
    Graf g(5,true);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);  // Powrót do 0 - zapewnia spójność
    g.addEdge(1, 3);  // Dodatkowa krawędź
    g.addEdge(2, 4);  // Dodatkowa krawędź
    g.addEdge(3, 1);  // Dodatkowa krawędź - wprowadza cykl
    g.display(3);
    std::cout<<"czy graf jest spójny? - "<<std::boolalpha<<g.isConnected()<<std::endl<<std::noboolalpha;
    */
    return 0;
}