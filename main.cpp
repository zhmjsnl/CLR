#include <iostream>
#include <ctime>
#include <vector>
#include "ts.h"
#include "ps.h"
#include "graph.h"
#include "constant.h"

using namespace std;

string constant::instanceFileName = "";
bool constant::plusDelta = true;
bool constant::openLog = false;
bool constant::shortCutInPS = true;
bool constant::shortCutCycleInPS = false;
double constant::greedyAlpha = 1;
bool constant::usingLKH = true;
bool constant::psLKH = false;

int main(int argc, char *argv[]) {
    if (argc != 5) {
        cout << "./clr.exe filename greedyAlpha usingLKH psLKH" << endl;
        exit(1);
    }
    string fileName = argv[1];
    double alpha = atoi(argv[2]);
    constant::usingLKH = atoi(argv[3]) == 1;
    constant::psLKH = atoi(argv[4]) == 1;
    constant::instanceFileName = "./instance/" + fileName;
    constant::greedyAlpha = alpha;
    cout << fileName << "\t";
    int n;
    int cliNum, depNum;
    int capacity;
    vector<int> demand;
    vector<double> openCost;
    double **dist = graph::buildGraphFromInstance(
            n, cliNum, depNum, capacity, demand, openCost);

    clock_t st = clock();
    ts tsSolver;
    tsSolver.solve(n, cliNum, depNum, capacity, demand, openCost, dist);
    ps psSolver;
    psSolver.solve(n, cliNum, depNum, capacity, demand, openCost, dist);
    clock_t et = clock();
    cout << et - st << endl;

    return 0;
}