#ifndef SUBGRID_H
#define SUBGRID_H

#include <vector>

/// Cell is empty.
const int c_EMPTY = 0;

/// Cell is invalid for a specific number.
const int c_FORBID = -1;

/// Cell can only be occupied by one single number.
const int c_UNAMBI = -2;

/**
 * @brief   Class holding one single sudoku subgrid,
 *          e.g. a row, a column, or one of the 3x3 grids/fields.
 * 
 */
class Subgrid {
public:
    std::vector< int* > v;

public:
    Subgrid( std::vector< int* > initVector );
    Subgrid( std::vector< int >& initVector );
    ~Subgrid();

    /**
     * @brief   Checks whether the number already exists in this subgrid.
     * 
     * @param number    The number which is to be checked.
     * @return true     The number already exists in this subgrid.
     * @return false    The number does not exist in this subgrid.
     */
    bool hasNum( int number ) const;

    /**
     * @brief   Checks if all numbers occur at most once in this subgrid.
     * 
     * @return true     Every number only occurs at most once.
     * @return false    At least one number occurs at least two times.
     */
    bool isValid() const;

    /**
     * @brief   Displays the subgrid.
     * 
     */
    void print() const;

    /**
     * @brief   Marks every empty cell with the c_FORBID constant
     *          if the number from the parameter already exists in this subgrid.   
     * 
     * @param number    Number whose existence is checked in this vector.
     */
    void markNoNumCells( int number );

    /**
     * @brief   Resets previously marked cells to c_EMPTY again.
     * 
     */
    void resetCells();

    /**
     * @brief   Sets the specified number inside this subgrid,
     *          if there is only one valid cell for it.
     * 
     * @param number    The number to set.
     * @return true     The number was successfully set.
     * @return false    The number was not set.
     */
    bool setNum( int number );
};

#endif