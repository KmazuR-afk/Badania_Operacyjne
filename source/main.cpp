#include <iostream>
#include "../include/Graf.h"

int main() {
    Graf g(6);
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 7);
    g.addEdge(0, 3, 3);
    g.addEdge(0, 4, 2);
    g.addEdge(0, 5, 8);
    g.addEdge(0, 6, 4);
    
    g.addEdge(1, 2, 6);
    g.addEdge(1, 3, 1);
    g.addEdge(1, 7, 7);
    g.addEdge(1, 8, 2);
    
    g.addEdge(2, 3, 3);
    g.addEdge(2, 6, 5);
    g.addEdge(2, 9, 8);
    
    g.addEdge(3, 4, 4);
    g.addEdge(3, 7, 6);
    
    g.addEdge(4, 5, 1);
    g.addEdge(4, 8, 5);
    
    g.addEdge(5, 6, 9);
    g.addEdge(5, 9, 3);
    
    g.addEdge(6, 7, 2);
    g.addEdge(6, 8, 6);
    
    g.addEdge(7, 8, 4);
    g.addEdge(7, 9, 7);
    
    g.addEdge(8, 9, 2);
    
    g.addEdge(1, 9, 3);
    g.addEdge(0, 9, 4);
    g.addEdge(4, 6, 5);
    g.addEdge(3, 5, 6);
    g.addEdge(2, 8, 7);
    
    /*auto randomWeight = []() { return std::rand() % 10 + 1; };*/
    g.display(3);
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
    std::vector<int> heur=g.countHeuristicDijkstra(7);
    std::cout<<"heurystyka:"<<std::endl;
    for(int u:heur){
        std::cout<<u<<" - ";
    }
    std::cout<<std::endl;
    std::vector<std::vector<int>> ast=g.Astar(0,7,heur);
    for(int i=0;i<(int)ast[0].size();i++)
    {
        std::cout<<"poprzednik "<<ast[0][i]<<" aktualny koszt "<<ast[1][i]<<std::endl;
    }
    return 0;
}