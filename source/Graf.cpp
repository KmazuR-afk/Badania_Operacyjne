#include "../include/Graf.h"

using namespace std;

//konstruktory
Graf::Graf(){}
Graf::Graf(int vertices,bool directed): numVertices(vertices),isDirect(directed)
{
    neigh_Matr.resize(vertices, vector<int>(vertices,0));
}

//dodwanie wierzchołków - w zasadzie wykorzystywany dla listy sąsiedztwa
//ale jeśli numer wierzchołku większy niż initial utworzony rozmiar 
//macierzy to rozszerzamy macierz sąsiedztwa
void Graf::addVertex(size_t v) {
    if (v >= neigh_Matr.size()) {
        neigh_Matr.resize(v+1, vector<int>(v, 0));
        for (auto& row : neigh_Matr) {
            row.resize(v+1, 0);
        }
        numVertices++;
    }
    if (adj_List.find(v) == adj_List.end()) {
        adj_List[v] = list<pair<int, int>>();
        cout << "Dodano wierzchołek: " << v << endl;
    }
}

//dodawanie krawędzi
void Graf::addEdge(int v1,int v2,int value){
    addVertex(v1);
    addVertex(v2);

    adj_List[v1].push_back({v2,value});
    neigh_Matr[v1][v2]=value;
    if(!isDirect){
        adj_List[v2].push_back({v1,value});
        neigh_Matr[v2][v1]=value;
    }
}

//usuwanie krawędzi
void  Graf::removeEdge(int v1,int v2){
    neigh_Matr[v1][v2]=0;
    adj_List[v1].remove_if([v2](const pair<int,int>& edge){
        return edge.first ==v2;
    });
    if(!isDirect){
        adj_List[v2].remove_if([v1](const pair<int,int>& edge){
            return edge.first ==v1;
        });
        neigh_Matr[v2][v1]=0;
    }
}

//wyświetlanie grafu w zależności od wyboru 1-macierz 2-lista sąsiedztwa 3-oba
void Graf::display(int choice) const{
    switch (choice) {
        case 1:
            cout << "Macierz sąsiedztwa:" << endl;
            for (const auto& row : neigh_Matr) {
                for (int val : row) {
                    cout << val << " ";
                }
                cout << endl;
            }
            break;
        case 2:
            cout << "Lista sąsiedztwa:" << endl;
            for (const auto& pair : adj_List) {
                cout << pair.first << " -> ";
                for (const auto& neighbor: pair.second) {
                    cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
                }
                cout << endl;
            }
            break;
        case 3:
            display(1);
            cout << endl;
            display(2);
            break;
        default:
            cout << "Niepoprawna opcja. Wybierz 1 (Macierz), 2 (Lista), lub 3 (Obie)." << endl;
    }
}

//przejscie wszerz
vector<int> Graf::BFS(int v){
    queue<int> Q;//kolejka
    int c=v;
    auto pair=adj_List[c];
    Q.push(c);
    vector<int> road;
    vector<bool> visited(numVertices,false);
    visited[c]=true;
    while(!Q.empty())
    {
        c=Q.front();
        Q.pop();
        road.push_back(c);
        pair=adj_List[c];
        for(const auto& lis:pair){
            if(!visited[lis.first]){
                Q.push(lis.first);
                visited[lis.first]=true;

            }
        }
    }
    return road;
}

//czy jest cykliczny
bool Graf::isCyclic(int v) {
    stack<pair<int, int>> S; 
    vector<bool> visited(numVertices, false);
    S.push({v, -1}); 
    while (!S.empty()) {
        auto [current, parent] = S.top(); S.pop();
        if (!visited[current]) {
            visited[current] = true;
        }
        for (const auto& pair : adj_List[current]) {
            int neighbor = pair.first;
            if (!visited[neighbor]) {
                S.push({neighbor, current}); 
            } else if (neighbor != parent) {
                return true;
            }
        }
    }
    return false;
}


void Graf::unDirectify() {
    for (int i = 0; i < numVertices; i++) {
        for (int j = i; j < numVertices; j++) {
            if (neigh_Matr[i][j] != neigh_Matr[j][i]) {
                int maxWeight = max(neigh_Matr[i][j], neigh_Matr[j][i]);
                neigh_Matr[i][j] = maxWeight;
                neigh_Matr[j][i] = maxWeight;
            }
        }
    }
    for (int i = 0; i < numVertices; i++) {
        for (auto& j : adj_List[i]) {
            int u = i;
            int v = j.first;
            int w = j.second;
            bool exists = false;
            for (auto& other_way : adj_List[v]) {
                if (other_way.first == u) {
                    exists = true;
                    if (other_way.second != w) {
                        int m = max(w, other_way.second);
                        j.second = m;
                        other_way.second = m;
                    }
                    break; 
                }
            }
            if (!exists) {
                adj_List[v].push_back({u, w});
            }
        }
    }
    isDirect = false;
}

//badamy spójność grafu
bool Graf::isConnected(){
    if(!isDirect){
        if(numVertices==(int)BFS(0).size()){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        unDirectify();
        display(3);
        return isConnected();
    }
}

//algorytm Prima bazowany na AISD I LO i Abdul Bari 3.5 Prims and Kruskals ...
vector<Edge> Graf::Prim(){
    srand(time(0));
    int r_ver=0;//rand()%numVertices;
    vector<Edge> ret;
    vector<bool> visited(numVertices,false);
    visited[r_ver]=true;
    priority_queue<Edge,vector<Edge>,greater<Edge>> Q;
    for(const auto& u: adj_List[r_ver])
    {
        if(!visited[u.first]){
            Q.push({u.second,r_ver,u.first});  
        }
    }
    while(!Q.empty()){
        auto [weight,from,to]=Q.top();
        Q.pop();
        if(visited[to]) continue;

        ret.push_back({weight,from,to});
        visited[to]=true;
        for(const auto& u: adj_List[to])
        {
            if(!visited[u.first]){
                Q.push({u.second,to,u.first});  
            }
        }
    }
    return ret;
}

//algorytm Dijkstry bazowany na stronie Algorytmy i struktury danych i Algorytm.edu.pl
vector<vector<int>> Graf::Dijkstra(int start){
    const int INF = __INT_MAX__;
    priority_queue<Edge,vector<Edge>,greater<Edge>> Q;
    vector<int> dist(numVertices, INF);
    std::vector<int> prev(numVertices, -1);
    std::vector<bool> visited(numVertices, false);
    dist[start] = 0;
    prev[start]= -1;
    Q.push({0,-1,start});
    while(!Q.empty()){
        auto [weight,p,u]=Q.top();
        Q.pop();
        if (visited[u]) continue;
        visited[u]=true;
        prev[u] = p;
        for (const auto& [neighbor, edgeWeight] : adj_List[u]) {
            if (!visited[neighbor] && dist[u] + edgeWeight < dist[neighbor]) {
                dist[neighbor] = dist[u] + edgeWeight;
                Q.push({dist[neighbor], u, neighbor});
            }
        }
    }
    return {prev,dist};
}

vector<int> Graf::countHeuristicDijkstra(int goal){
    std::vector<int> h(numVertices, INT_MAX);
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<>> Q;

    h[goal] = 0;
    Q.push({0, goal});

    while (!Q.empty()) {
        auto [dist, u] = Q.top();
        Q.pop();

        for (const auto& [v, w] : adj_List[u]) {
            if (h[u] + w < h[v]) {
                h[v] = h[u] + w;
                Q.push({h[v], v});
            }
        }
    }

    return h;
}

vector<vector<int>> Graf::Astar(int start,int goal,const vector<int>& h)
{
    vector<int> gScore(numVertices,__INT_MAX__);
    vector<int> prev(numVertices,-1);
    vector<bool> visited(numVertices,false);
    priority_queue<Edge,vector<Edge>,greater<Edge>> Q;
    vector<int> f(numVertices,0);
    gScore[start]=0;
    prev[start]=-1;
    int tg=0;
    Q.push({h[start],0,start});//recykling edge teraz f,g,vertex
    while(!Q.empty()){
        auto [f,g,u]=Q.top();
        Q.pop();
        if (visited[u]) continue;
        visited[u]=true;
        if(u==goal) break;
        for(const auto& [v,edgeWeight]:adj_List[u])
        {
            tg=gScore[u]+edgeWeight;
            if(tg<gScore[v] ){
                gScore[v]=tg;
                prev[v]=u;
                Q.push({tg+h[v],tg,v});
            }
        }
    }
    vector<int>path_cost;
    vector<int>road;
    vector<int>rpath_cost;
    vector<int>rroad;
    for(int c=goal;c!=-1;c=prev[c])
    {
        path_cost.push_back(gScore[c]);
        road.push_back(prev[c]);
    }
    for(int i=road.size()-2;i>-1;i--){
        rpath_cost.push_back(path_cost[i]);
        rroad.push_back(road[i]);
    }
    return {rroad,rpath_cost};
}
 //Christfides funcs
 vector<int> Graf::isOdd(const vector<Edge>& mst){
    vector<int> degree(numVertices);
    for(const auto& [weigh,to,from]:mst){
        degree[from]++;
        degree[to]++;
    }
    vector<int> odd;
    for(int i =0;i<numVertices;i++){
        if(degree[i]%2==1){
            odd.push_back(i);
        }
    }
    return odd;
 }
 vector<Edge> Graf::findMinimumMatching(vector<int> odd)
 {
    vector<Edge> match;
    vector<bool> used(numVertices,false);
    vector<int>unmatched=odd;
    int best_f=-1;
    int min_weight=INT_MAX;
    int u;
    while(!unmatched.empty()){
        u=unmatched.back();
        unmatched.pop_back();
        if(used[u]) continue;

        best_f=-1;
        min_weight=INT_MAX;
        for (int v:unmatched){
            if(!used[v] && neigh_Matr[u][v]<min_weight && neigh_Matr[u][v]!=0){
                min_weight = neigh_Matr[u][v];
                best_f = v;
            }
        }
        if(best_f!=-1){
            match.push_back({min_weight,u,best_f});//waga,z,do
            used[u]=true;
            used[best_f]=true;
        }
    }
    return match;
 }
 
 vector<Edge> Graf::mergeGraphs(const vector<Edge>& mst, const vector<Edge>& matching)
 {
    vector<Edge> merged=mst;

    for (const auto& edge:matching)
    {
        merged.push_back(edge);
    }
    return merged;
 }
 //Hierholzer
 vector<int> Graf::findEulerianTour(const vector<Edge>& multigraph){
    unordered_map<int, vector<int>> tempAdj;

    for (const auto& [weight, u, v] : multigraph) {
        tempAdj[u].push_back(v);
        tempAdj[v].push_back(u);
    }

    vector<int> tour;
    stack<int> stack;
    stack.push(multigraph.empty() ? 0 : get<1>(multigraph[0]));

    while (!stack.empty()) {
        int u = stack.top();
        if (!tempAdj[u].empty()) {
            int v = tempAdj[u].back();
            tempAdj[u].pop_back();

            // Usuń odwrotną krawędź (v → u)
            auto& neighbors = tempAdj[v];
            auto it = std::find(neighbors.begin(), neighbors.end(), u);
            if (it != neighbors.end()) {
                neighbors.erase(it);
            }

            stack.push(v);
        } else {
            tour.push_back(u);
            stack.pop();
        }
    }

    std::reverse(tour.begin(), tour.end());
    return tour;
 }
 vector<int> Graf::shortcutEulerianTour(const vector<int>& eulerTour)
 {
    unordered_set<int> visited;
    vector<int> hamiltonianPath;

    for (int v : eulerTour) {
        if (visited.find(v) == visited.end()) {
            visited.insert(v);
            hamiltonianPath.push_back(v);
        }
    }

    if (!hamiltonianPath.empty()) {
        hamiltonianPath.push_back(hamiltonianPath[0]);
    }

    return hamiltonianPath;
 }
 pair<vector<int>, int> Graf::christofidesTSP() {
    vector<Edge> mst = Prim();
    vector<int> oddVertices = isOdd(mst);
    vector<Edge> matching = findMinimumMatching(oddVertices);
    vector<Edge> multigraph = mergeGraphs(mst, matching);
    vector<int> eulerTour = findEulerianTour(multigraph);
    vector<int> tspPath = shortcutEulerianTour(eulerTour);
    int length=0;
    for(size_t i=0;i<tspPath.size()-1;i++){
        length+=neigh_Matr[tspPath[i]][tspPath[i+1]];
    }

    return {tspPath,length};
}

