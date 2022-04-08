// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <io/console.h>
#include <io/filelib.h>
#include <collections/grid.h>
#include <graphics/gwindow.h>
#include <io/simpio.h>
#include <util/strlib.h>
#include "lifegui.h"

class LifeGrid: public Grid<state> {
public:
    LifeGrid(int nRows, int nCols) : Grid<state>(nRows, nCols){

    }
    std::vector<std::pair<int, int>> getNeighbors(int x, int y) const{
        std::vector<std::pair<int, int>> retVec;
        if (x < 0 || y < 0 || x >= numRows() || y >= numCols()) {
            return retVec;
        }
        if (x+1 < numRows()) {
            if (y+1 < numCols()) {
                retVec.emplace_back(x+1, y+1);
                retVec.emplace_back(x, y+1);
            }
            if (y-1 >= 0) {
                retVec.emplace_back(x+1, y-1);
                retVec.emplace_back(x, y-1);
            }
            retVec.emplace_back(x+1, y);
        }
        if (x-1 >= 0) {
            if (y+1 < numCols()) {
                retVec.emplace_back(x-1, y+1);
            }
            if (y-1 >= 0) {
                retVec.emplace_back(x-1, y-1);
            }
            retVec.emplace_back(x-1, y);
        }
        return retVec;
    }
    bool isAlive(int x, int y) const {
        return get(x, y) == alive;
    }
    bool willAlive(int x, int y) const {
        int aliveNeighborNum = 0;
        auto neighbors = getNeighbors(x, y);
        for (auto &item:neighbors) {
            if (isAlive(item.first, item.second)) aliveNeighborNum++;
        }
        /**rule1*/
        if (aliveNeighborNum < 2) {
            return false;
        }
        /**rule3*/
        if (aliveNeighborNum >= 4) {
            return false;
        }
        return true;
    }
};

void simulation(LifeGrid &grid);

int main() {
    // TODO: Finish the program!
    auto startFileStr = "start.txt";
    std::string outStr;
    std::string inStr;
    std::ifstream is;
    if (readEntireFile(startFileStr, outStr)) {
        std::cout << outStr;
        std::cin >> inStr;
        if (!openFile(is, inStr)) {
            std::cout << "Please give the correct file path." << std::endl;
        }
        getLine(is, outStr);
        auto gridHeight = stringToInteger(outStr);
        getLine(is,outStr);
        auto gridWidth = stringToInteger(outStr);
        LifeGrid grid(gridHeight, gridWidth);

        LifeGUI lifeGui;
        lifeGui.resize(gridHeight + 1, gridWidth);

        //initialize
        for (int i = 0; i < gridHeight; ++i) {
            getLine(is, outStr);
            for (int j = 0; j < gridWidth; ++j) {
                if (outStr.at(j) == 'X') {
                    grid[i][j] = alive;
                } else {
                    grid[i][j] = dead;
                }
            }
        }
        //display
        lifeGui.display(grid);

        //update
        for (int i = 0; i < 1000; ++i) {
            simulation(grid);
            lifeGui.display(grid);
        }
        std::cout << "Have a nice Life!" << std::endl;

    }

    return 0;
}


/**
 *  Rules:
 *  A location that has zero or one neighbors will be empty in the next generation. If a cell was there, it dies.
 *  A location with two neighbors is stable. If it had a cell, it still contains a cell. If it was empty, it's still empty.
 *  A location with three neighbors will contain a cell in the next generation. If it was unoccupied before, a new cell is born. If it currently contains a cell, the cell remains.
 *  A location with four or more neighbors will be empty in the next generation. If there was a cell in that location, it dies of overcrowding.
 */
void simulation(LifeGrid &grid) {
    for (int i = 0; i < grid.height(); ++i) {
        for (int j = 0; j < grid.width(); ++j) {
            if (!grid.isAlive(i, j) && grid.willAlive(i, j)) {
                grid[i][j] = alive;
            } else if (grid.isAlive(i, j) && !grid.willAlive(i, j)){
                grid[i][j] = dead;
            }
        }
    }
}




