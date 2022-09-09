#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include "subgrid.h"

/**
 * @brief   Class holding one single, complete sudoku grid.
 * 
 */
class Grid {
public:
    std::string mFilename;

    /// Vector holding the values of the grid.
    std::vector< int > mGrid;

    /// Vector holding subgrids which are references to the rows of the sudoku.
    std::vector< Subgrid > mRows;

    /// Vector holding subgrids which are references to the columns of the sudoku.
    std::vector< Subgrid > mCols;

    /// Vector holding subgrids which are references to the 3x3 grids/fields of the sudoku.
    std::vector< Subgrid > mFields;

public:
    Grid( std::string fn );
    ~Grid();

    /**
     * @brief   Check whether this sudoku is completely filled and finished.
     * 
     * @return true     The sudoku if filled.
     * @return false    The sudoku still has empty or marked cells.
     */
    bool isFinished() const;

    /**
     * @brief   Checks whether every row, column, and 3x3 grid/field is valid.
     * 
     * @return true     Everything is valid.
     * @return false    Something of the above is invalid.
     */
    bool validateGrid() const;

    /**
     * @brief   Displays the grid and the values of the cells.
     * 
     */
    void printGrid() const;

    /**
     * @brief Loads the grid from the specified, saved filename.
     * 
     */
    void loadGrid();

    /**
     * @brief   Initializes the references of the rows of the grid.
     * 
     */
    void initRows();

    /**
     * @brief   Initializes the references of the columns of the grid.
     * 
     */
    void initCols();

    /**
     * @brief   Initializes the references of the 3x3 grids/fields.
     * 
     */
    void initFields();

    /**
     * @brief   Sets the specified number in as many valid cells as possible.
     * 
     * @param number    Number to be set.
     * @return true     At least one cell was set with the number.
     * @return false    No cell was set with the specified number.
     */
    bool setNumGrid( int number );

    /**
     * @brief   Marks every empty cell in the grid with the c_FORBID constant
     *          if the number from the parameter already exists in the respective subgrid.
     * 
     * @param number    Number against whose existence is checked.
     */
    void markNoNumCellsGrid ( int number );

    /**
     * @brief   Checks each cell if it can only be occupied by one single value.
     * 
     * @return true     At least one cell was found and set.
     * @return false    No cell was set.
     */
    bool checkCellSingleNum();

    /**
     * @brief   Resets cells from c_FORBID to c_EMPTY in the entire grid.
     * 
     */
    void resetGrid();
};

#endif