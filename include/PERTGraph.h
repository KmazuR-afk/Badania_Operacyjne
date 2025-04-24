#ifndef PERTGRAPH_H
#define PERTGRAPH_H
#include<vector>
#include<iostream>
#include<map>
#include <iomanip>
#include <math.h>  
#include <algorithm>  
#include <sstream>
#include <fstream>

class PERTGraph {
    private:
        struct Activity {
            int from, to;
            double a, m, b;
            double te, variance;
        };
    
        std::vector<Activity> activities;
        std::map<int, std::vector<int>> adjList;
        std::map<int, double> ES, EF, LS, LF, slack;
        double projectDuration;
        std::vector<int> criticalPath;
    
    public:
        void addActivity(int from, int to, double a, double m, double b);
        void compute();
        void printResults();
        void exportGantt(); 
};
#endif