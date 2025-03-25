#ifndef GRAF_H
#define GRAF_H

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <tuple>
using Edge = std::tuple<int, int, int>;
class Graf{
    private:
        std::vector<std::vector<int>> neigh_Matr;
        std::unordered_map<int,std::list<std::pair<int,int>>> adj_List;
        int numVertices;
        bool isDirect;

    public:
        Graf();
        Graf(int vertices=0,bool directed=false);
        void addVertex(size_t Vertex);
        void addEdge(int v1,int v2,int value=1);
        void removeEdge(int v1,int v2);
        void display(int choice) const;
        std::vector<int> BFS(int v);
        std::vector<std::vector<int>> getMatrix() const;
        std::list<int> getNeighborsList(int vertex) const;
        bool isCyclic(int v);
        bool isConnected();
        void unDirectify();
        std::vector<Edge> Prim();
        std::vector<std::vector<int>> Dijkstra(int start=0);
        std::vector<int> countHeuristicDijkstra(int goal);
        std::vector<std::vector<int>> Astar(int start,int goal,const std::vector<int>& h);
};
#endif