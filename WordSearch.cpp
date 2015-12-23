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
    buildIPADictionary();
}

void WordSearch::storeLine(string line) {
        n_rows_++;
        lines_inputted_.push(line);
}

void WordSearch::removeTopLine() {
    if (n_rows_==0)
        return;
    n_rows_--;
    lines_inputted_.pop();
}

int generateWordSearch() {
        //create an array of strings:
        //Plan:
        /*
         Loop through each line and convert the string into a bunch of strings with each character
         so search_array_[0][0] is the first character string, search_array_[0][1] is the second, etc:
         
         for queue
         
         [0][0], [0][1], ....   [0][m]
         [1][0],
         [2][0],    ...          ...
         ...
         [n][0]     ...         [n][m]
         
         
         1. Use a new to declare such an array of strings
         2. Parse line by line:
            a. if it's a character on the list of valid single characters, edit the search array at that spot to the character
            b. otherwise declare "invalid character starting at row i, column j. Replace (C)haracter, (L)ine, or (Q)uit?"
         
         
         */
    return 0;
}

int WordSearch::getLineWidth(string line) {
    //checks the width of line.
    //This function assumes validly formed input.
    int count=0;
    
    bool inEscape = false;
    if (line == "")
        return 0;
    
    //ignore spaces, count concluded escaped characters, count all other characters
    for (int i=0;i<=line.length();i++) {
        switch (line[i]) {
            case ' ':
                continue;
            case ':':
                inEscape= !inEscape;
                if (inEscape==false)
                    count++;
                continue;
            default:
                if (inEscape==false)
                {
                    count++;
                    continue;
                }
                else
                    continue;
        }
    }
    
    return count;
}

void WordSearch::buildIPADictionary(){

}

