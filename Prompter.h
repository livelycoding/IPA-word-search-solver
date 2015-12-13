//
//  Prompter.hpp
//  IPA Word Search Solver
//
//  Created by Taylor Hamermesh on 12/12/15.
//  Copyright © 2015 Taylor Hamermesh. All rights reserved.
//

#ifndef Prompter_h
#define Prompter_h

#include <string>

class Prompter {
public:
    Prompter();
    void allowInput();
    void parseInput(std::string input);
private:
    void saveInput();
    void rejectInput();
    void printIntro();
    void printHelp();
    void printCharacterList();
    std::string input_;
};


#endif /* Prompter_h */
