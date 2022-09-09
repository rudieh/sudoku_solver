#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

#include "include/grid.h"

// using namespace std;

int main (int argc, char* argv[]){
    std::cout << "Starting program." << std::endl;

    std::string textfile;
    if (argc > 1) {
        textfile = argv[1];
    }
    else {
        textfile = "examples/hard.txt";
    }

    Grid g(textfile);

    const int maxTries = 100;
    for (int tries = 0; tries < maxTries; tries++) {
        if (g.isFinished()) {
            std::cout << "Finished after " << tries+1 << " tries!" << std::endl;
            break;
        }

        bool simpleCheck = false;
        bool advancedCheck = false;

        // Check if a number has one single valid cell per subgrid
        for (int k = 1; k <= 9; k++) {
            simpleCheck = simpleCheck || g.setNumGrid(k);
            if (!g.validateGrid()) {
                g.printGrid();
                std::cout << "Failed validation in try: " << tries << " number: " << k << std::endl;
                return -1;
            }
        }

        // Check for cells that only can be occupied by a single value
        advancedCheck = g.checkCellSingleNum();
        if (!g.validateGrid()) {
            g.printGrid();
            std::cout << "Failed validation in try: " << tries << std::endl;
            return -1;
        }
        if ((!simpleCheck) && (!advancedCheck)) {
            std::cout << "No progress in try: " << tries << std::endl;
            break;
        }
    }
    g.printGrid();

    std::cout << "Program finished." << std::endl;
    return 0;
}