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
#include <unordered_set>
#include <unordered_map>


class WordSearch {
public:
    WordSearch();
    void storeLine(std::string line);
    void searchForWords();
    int generateWordSearch();
private:
    int getLineWidth(std::string line);
    void removeTopLine();
    void buildIPACharacterList();
    void buildIPAToSoundsList();
    
    int n_rows_;
    int n_columns_;
    int depth_;
    int line_width_;
    std::string** search_array_;
    std::queue<std::string> lines_inputted_;
    std::unordered_set<std::string> IPA_characters_;
    std::unordered_map<std::string, std::vector<std::string> > IPA_sounds_;
    
    
    //inlines
    inline void setLineWidth(int newLength) {
        line_width_ = newLength;
    }
};







#endif /* wordSearch_h */
