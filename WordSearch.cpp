//
//  WordSearch.cpp
//  IPA Word Search Solver
//
//  Created by Taylor Hamermesh on 12/12/15.
//  Copyright © 2015 Taylor Hamermesh. All rights reserved.
//

#include <iostream>
#include "WordSearch.h"
using namespace std;

WordSearch::WordSearch() {
    n_rows_ = 0;
    n_columns_ = 0;
    search_array_ = nullptr;
}

void WordSearch::storeLine(string line) {
        n_rows_++;
        lines_inputted_.push(line);
}

int generateWordSearch() {
    cout << "getLineWidth called";
    return 0;
}

int WordSearch::setLineWidth() {
    cout << "setLineWidth called";
    return 0;
}

