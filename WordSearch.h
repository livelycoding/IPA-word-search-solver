//
//  WordSearch.h
//  IPA Word Search Solver
//
//  Created by Taylor Hamermesh on 12/12/15.
//  Copyright © 2015 Taylor Hamermesh. All rights reserved.
//

#ifndef wordSearch_h
#define wordSearch_h
#include <string>
#include <queue>



class WordSearch {
public:
    WordSearch();
    void storeLine(std::string line);
    int generateWordSearch();
private:
    int getLineWidth();
    int setLineWidth();
    int n_rows_;
    int n_columns_;
    int depth_;
    int line_width_;
    std::string** search_array_;
    std::queue<std::string> lines_inputted_;
};







#endif /* wordSearch_h */
