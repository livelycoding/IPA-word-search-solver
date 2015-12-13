//
//  WordSearch.cpp
//  IPA Word Search Solver
//
//  Created by Taylor Hamermesh on 12/12/15.
//  Copyright © 2015 Taylor Hamermesh. All rights reserved.
//

#include <stdio.h>
#include "WordSearch.h"

WordSearch::WordSearch() {
    n_rows_ = 0;
    n_columns_ = 0;
    search_array_ = nullptr;
}