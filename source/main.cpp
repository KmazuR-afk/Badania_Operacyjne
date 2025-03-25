#include <iostream>
#include "../include/Graf.h"

int main() {
    Graf g1(6);
    std::srand(std::time(0));
    g1.addEdge(0, 1, 3);
g1.addEdge(0, 4, 3);
g1.addEdge(0, 5, 6);

g1.addEdge(1, 2, 1);
g1.addEdge(1, 3, 3);

g1.addEdge(2, 3, 3);
g1.addEdge(2, 5, 1);

g1.addEdge(5, 3, 1);
g1.addEdge(4, 5, 2);
    /*auto randomWeight = []() { return std::rand() % 10 + 1; };
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
    g1.addEdge(8, 9, randomWeight());*/
    g1.display(3);
    /*std::vector<int> bfs1=g1.BFS(3);
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
    std::vector<std::vector<int>> d=g1.Dijkstra();
        for(int j=0;j<6;j++){
            std::cout<<"poprzednik "<<d[0][j]<<" waga "<<d[1][j]<<std::endl;
        }*/
    std::vector<int> heur=g1.countHeuristicDijkstra(3);
    for(int u:heur){
        std::cout<<u<<" - ";
    }
    std::cout<<std::endl;
    std::vector<std::vector<int>> ast=g1.Astar(0,3,heur);
    for(int i=0;i<(int)ast[0].size();i++)
    {
        std::cout<<"poprzednik "<<ast[0][i]<<" aktualny koszt "<<ast[1][i]<<std::endl;
    }
    return 0;
}