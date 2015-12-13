//
//  WordInProg.h
//  IPA Word Search Solver
//
//  Created by Taylor Hamermesh on 12/12/15.
//  Copyright © 2015 Taylor Hamermesh. All rights reserved.
//

#ifndef WordInProg_h
#define WordInProg_h

#include <string>


class wordInProg
{
    enum Direction {
        Up, Up_right, Right, Down_right, Down, Down_left, Left, Up_left
    };
    Direction currDirection;
    std::string possibleWord;
    std::string phonemes;
    int phonemeCount;
};


#endif /* WordInProg_h */
