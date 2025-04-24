#include "../include/PERTGraph.h"

void PERTGraph::addActivity(int from, int to, double a, double m, double b) {
    double te = (a + 4 * m + b) / 6.0;
    double variance = pow((b - a) / 6.0, 2);
    Activity act = {from, to, a, m, b, te, variance};
    activities.push_back(act);
    adjList[from].push_back(to);
}

void PERTGraph::compute() {
    // 1. Topologiczne sortowanie (dla DAG)
    std::map<int, int> in_degree;
    // Liczenie stopnia wejściowego (ile wierzchołków prowadzi do każdego)
    for (const auto& [u, neighbors] : adjList) {
        for (int v : neighbors) {
            in_degree[v]++;
        }
        if (in_degree.find(u) == in_degree.end())
            in_degree[u] = 0; // Upewniamy się, że wszystkie wierzchołki są uwzględnione
    }
    // Inicjalizacja kolejki wierzchołków o zerowym stopniu wejściowym
    std::vector<int> topo;
    std::vector<int> queue;
    for (const auto& [v, deg] : in_degree) {
        if (deg == 0) queue.push_back(v);
    }
    // Sortowanie topologiczne
    while (!queue.empty()) {
        int node = queue.back();
        queue.pop_back();
        topo.push_back(node);
        for (int neigh : adjList[node]) {
            if (--in_degree[neigh] == 0) queue.push_back(neigh);
        }
    }
    // 2. Obliczanie ES i EF (najwcześniejsze czasy)
    for (int node : topo) {
        double max_ef = 0.0;
        for (const auto& act : activities) {
            if (act.to == node) {
                max_ef = std::max(max_ef, EF[act.from] + act.te);
            }
        }
        ES[node] = max_ef;
        EF[node] = max_ef;
    }
    projectDuration = std::max_element(EF.begin(), EF.end(),
    [](const auto& a, const auto& b) { return a.second < b.second; })->second;
    // Idziemy wstecz (od końca do początku)
    for (auto it = topo.rbegin(); it != topo.rend(); ++it) {
        int node = *it;
        double min_ls = projectDuration;
        bool has_succ = false;
        for (const auto& act : activities) {
            if (act.from == node) {
                has_succ = true;
                min_ls = std::min(min_ls, LS[act.to] - act.te);
            }
        }
        if (!has_succ) min_ls = EF[node]; // jeśli to ostatni węzeł
        LF[node] = min_ls;
        LS[node] = min_ls;
    }
    // 4. Obliczanie zapasu czasu (Slack) i ścieżki krytycznej
    for (const auto& [v, es] : ES) {
        slack[v] = LS[v] - es;
        if (slack[v] == 0) {
            criticalPath.push_back(v); // Wierzchołek leży na ścieżce krytycznej
        }
    }
}

void PERTGraph::printResults() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Wierzcholek\tES\tEF\tLS\tLF\tSlack\n";
    for (const auto& [v, es] : ES) {
        std::cout << v << "\t\t"
                  << ES[v] << "\t"
                  << EF[v] << "\t"
                  << LS[v] << "\t"
                  << LF[v] << "\t"
                  << slack[v] << "\n";
    }
    std::cout << "\nCzas trwania projektu: " << projectDuration << "\n";
    std::cout << "Ścieżka krytyczna: ";
    for (size_t i = 0; i < criticalPath.size(); ++i) {
        std::cout << criticalPath[i];
        if (i != criticalPath.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n";
}

void PERTGraph::exportGantt(){
    std::string filename="../GANTT.csv";
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Nie można otworzyć pliku do zapisu!\n";
        return;
    }

    // Nagłówki
    file << "Od;Do;Start;Czas;Krytyczny\n";
for (const auto& act : activities) {
    double start = EF.at(act.from);
    double czas = act.te;
    bool critical = (LS.at(act.to) - ES.at(act.to) == 0) && (LS.at(act.from) - ES.at(act.from) == 0);

    std::ostringstream sStart, sCzas;
    sStart << std::fixed << std::setprecision(2) << start;
    sCzas << std::fixed << std::setprecision(2) << czas;

    std::string startStr = sStart.str(); std::replace(startStr.begin(), startStr.end(), '.', ',');
    std::string czasStr = sCzas.str(); std::replace(czasStr.begin(), czasStr.end(), '.', ',');

    file << act.from << ";" << act.to << ";" << startStr << ";" << czasStr << ";" << (critical ? "TAK" : "") << "\n";
}
    file.close();
    std::cout << "Zapisano dane do pliku: " << filename << std::endl;
    std::cout << "Generowanie wykresu Gantta w Pythonie...\n";
    
    //TE LINIE KODU NALEŻY ZMIENIĆ I DOSTARCZYĆ WŁASNĄ ŚCIEZKĘ DO KATALOGU PYTHON.EXE
    std::string pythonPath = "\"C:\\Program Files\\Python39\\python.exe\"";
    std::string command = pythonPath + " ../source/generate_gantt.py";
    int result = system(command.c_str());
    std::cout << "Kod zakończenia: " << result << "\n";
    if (result != 0) {
        std::cerr << "Nie udało się wygenerować wykresu Gantta!\n";
    } else {
        std::cout << "Wykres Gantta zapisany jako ../GANTT.png\n";
    }
}
