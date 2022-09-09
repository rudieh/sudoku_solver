#include "../include/subgrid.h"
#include <algorithm>
#include <iostream>

Subgrid::Subgrid(std::vector<int*> initVector) {
    for (int i = 0; i < 9; i++) {
        v.push_back(initVector[i]);
    }
}

Subgrid::Subgrid(std::vector<int>& initVector) {
    for (int i = 0; i < 9; i++) {
        v.push_back(&initVector[i]);
    }
}

Subgrid::~Subgrid() {

}

bool Subgrid::hasNum(int number) const {
    for (auto e : v) {
        if (*e == number) {
            return true;
        }
    }
    return false;
}

bool Subgrid::isValid() const {
    std::vector<int> counter(9, 0);
    for (int i = 0; i < 9; i++) {
        int k = *v[i];
        if (k >= 1 && k <= 9) {
            counter.at(k-1)++;
        }
    }
    int max = *max_element(counter.begin(), counter.end());
    return (max < 2);
}

void Subgrid::print() const {
    for (auto e : v) {
        std::cout << *e << ' ';
    }
    std::cout << std::endl;
}

void Subgrid::markNoNumCells(int number) {
    if (hasNum(number)) {
        for (auto e : v) {
            if (*e == c_EMPTY) {
                *e = c_FORBID;
            }
        }
    }
}

void Subgrid::resetCells() {
    for (auto e : v) {
        if (*e == c_FORBID) {
            *e = c_EMPTY;
        }
    }
}

bool Subgrid::setNum(int number) {
    if (hasNum(number) || !isValid()) {
        return false;
    }

    // For more control, this should be a separate step outside this function:
    // markNoNumCells(number);

    int index = -1;
    for (int i = 0; i < v.size(); i++) {
        if (*v[i] == c_EMPTY) {
            if (index >= 0) {
                return false;
            }
            else {
                index = i;
            }
        }
    }
    *v[index] = number;
    resetCells();
    return true;
}