#include "../include/grid.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

Grid::Grid(std::string fn): mGrid(81, c_EMPTY), mFilename(fn) {
    loadGrid();
    initRows();
    initCols();
    initFields();
}

Grid::~Grid() {

}

bool Grid::isFinished() const {
    if (std::count(mGrid.begin(), mGrid.end(), c_FORBID) ||
        std::count(mGrid.begin(), mGrid.end(), c_EMPTY)) {
            return false;
        }
    return true;
}

bool Grid::validateGrid() const {
    bool bRows = true;
    for ( auto r : mRows) {
        bRows = bRows && r.isValid();
    }

    bool bCols = true;
    for ( auto c : mCols) {
        bCols = bCols && c.isValid();
    }

    bool bFields = true;
    for ( auto f : mFields) {
        bFields = bFields && f.isValid();
    }

    return bRows && bCols && bFields;
}

void Grid::printGrid() const {
    std::string divider(33, '*');

    std::cout << divider << std::endl;

    for (int cell = 0; cell < mGrid.size(); cell++) {

        if ((cell != 0) && (cell%3 == 0)) {
            if (cell%9 == 0) {
                std::cout << std::endl;
            }
            else {
                std::cout << ' ' << '|';
            }

            if (cell%27 == 0) {
                std::cout << ' ' << std::string(31, '-') << ' ' << std::endl;
            }
        }
        if (mGrid[cell] == c_EMPTY) {
            std::cout << ' ' << std::setw(2) << '.';
        }
        else {
            std::cout << ' ' << std::setw(2) << mGrid[cell];
        }
    }

    std::cout << std::endl << divider << std::endl;
}

void Grid::loadGrid() {
    std::ifstream iFile;
    iFile.open(mFilename);
    if (!iFile) {
        std::cerr << "Cannot find/reach: " << mFilename << std::endl;
    }
    else {
        std::string line;
        int lineNumber = 0;
        while (getline(iFile, line)) {
            int column = 0;
            for (auto &ch : line) {
                if ((ch >= '1') && (ch <= '9')) {
                    mGrid[9*lineNumber+column] = ch - '0';
                    column++;
                }
                else if ((ch == 'x') || (ch == '0')) {
                    mGrid[9*lineNumber+column] = c_EMPTY;
                    column++;
                }
            }
            lineNumber++;
        }
    }
    iFile.close();
}

void Grid::initRows() {
    for (int row = 0; row < 9; row++) {
        std::vector<int*> v;
        for (int col = 0; col < 9; col++) {
            v.push_back(&(mGrid[row*9+col]));
        }
        mRows.push_back(Subgrid(v));
    }
}

void Grid::initCols() {
    for (int col = 0; col < 9; col++) {
        std::vector<int*> v;
        for (int row = 0; row < 9; row++) {
            v.push_back(&(mGrid[row*9+col]));
        }
        mCols.push_back(Subgrid(v));
    }
}

void Grid::initFields() {
    int a = -1;
    int b = -1;
    int row = -1;
    int col = -1;

    for (int field = 0; field < 9; field++) {
        a = field/3;
        b = field%3;
        std::vector<int*> v;
        for (int k = 0; k < 9; k++) {
            row = a*3 + k/3;
            col = b*3 + k%3;
            v.push_back(&(mGrid[row*9+col]));
        }
        mFields.push_back(Subgrid(v));
    }
}

bool Grid::setNumGrid(int number) {
    // Prepare by marking everything
    markNoNumCellsGrid(number);

    // Set numbers if possible
    bool bRows = false;
    bool bCols = false;
    bool bFields = false;

    for ( auto r : mRows) {
        // Check if empty cells exists
        if (r.hasNum(c_EMPTY)) {
            bRows = bRows || r.setNum(number);
        }
    }

    // Mark again because of the changed cells
    if (bRows) {
        markNoNumCellsGrid(number);
    }

    for ( auto c : mCols) {
        // Check if empty cells exists
        if (c.hasNum(c_EMPTY)) {
            bCols = bCols || c.setNum(number);
        }
    }

    // Mark again because of the changed cells
    if (bCols) {
        markNoNumCellsGrid(number);
    }

    for ( auto f : mFields) {
        // Check if empty cells exists
        if (f.hasNum(c_EMPTY)) {
            bFields = bFields || f.setNum(number);
        }
    }

    resetGrid();

    return bRows || bCols || bFields;
}

void Grid::markNoNumCellsGrid(int number) {
    for ( auto r : mRows) {
        r.markNoNumCells(number);
    }

    for ( auto c : mCols) {
        c.markNoNumCells(number);
    }

    for ( auto f : mFields) {
        f.markNoNumCells(number);
    }
}

bool Grid::checkCellSingleNum() {
    bool setCell = false;

    for (int i = 0; i < mGrid.size(); i++) {
        // Only check empty cells
        if (mGrid[i] != 0) {
            continue;
        }

        // Calculate positions in subgrids
        int row = i/9;
        int col = i%9;
        int field = 3*(row/3) + col/3;

        int foundNumber = 0;
        for (int number = 1; number <= 9; number++) {
            if ((!mRows[row].hasNum(number)) &&
                (!mCols[col].hasNum(number)) &&
                (!mFields[field].hasNum(number))) {

                     /*
                     std::cout << "Cell: " << i 
                            << " Found number: " << foundNumber 
                            << " Number: " << number 
                            << " Row: " << row
                            << " Col: " << col
                            << " Field: " << field
                            << std::endl;
                    */
                    // Break if more than one number are valid in this cell
                    if (foundNumber > 0) {
                        foundNumber = 0;
                        break;
                    }
                    foundNumber = number;
                }
        }
        if (foundNumber > 0) {
            mGrid[i] = foundNumber;
            setCell = true;
            /*
            std::cout << "Found number: " << foundNumber 
                    << " Cell: " << i 
                    << " Row: " << row
                    << " Col: " << col
                    << " Field: " << field
                    << std::endl;
            */
        }
    }

    return setCell;
}

void Grid::resetGrid() {
    for (auto r : mRows) {
        r.resetCells();
    }
}