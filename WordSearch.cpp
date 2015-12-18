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
    //big idea:
    //Loop through lines,
    
    /*
    
    
    
    n_columns = charCount;
    searchArray = new string*[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        searchArray[i] = new string[n_columns];
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    for (int n=0; n < n_rows; n++)
    {
        currentLine = linesInputted.front();
        charCount = 0;
        for (int i = 0; i<currentLine.length();i++)
        {
            switch (currentLine[i])
            {
                case ' ':
                    continue;
                case 'p':
                case 'b':
                case 't':
                case 'd':
                case 'k':
                case 'g':
                case 'f':
                case 'v':
                case 's':
                case 'z':
                case 'h':
                case 'm':
                case 'n':
                case 'l':
                case 'w':
                case 'i':
                case 'I':
                case 'u':
                case 'e':
                case 'o':
                case 'a':
                {
                    if (charCount == n_columns)
                    {
                        cout << "Excess characters in row " << n+1;
                        exit(4);
                    }
                    
                    searchArray[n][charCount] = currentLine[i];
                    charCount++;
                    break;
                }
                case ':':
                {
                    if (charCount == n_columns)
                    {
                        cout << "Excess characters in row " << n+1;
                        exit(4);
                    }
                    
                    i++;
                    //build the character until you hit the next ':'
                    string escapedChar;
                    while (i < currentLine.length())
                    {
                        if (currentLine[i]==':')
                        {
                            //check if what was escaped was valid
                            if (escapedChar == "theta" || escapedChar == "delta" || escapedChar == "integral" ||
                                escapedChar == "ezh" || escapedChar == "t-integral" || escapedChar == "d-ezh" ||
                                escapedChar == "n-hook" || escapedChar == "r-flipped" || escapedChar == "w-flipped" ||
                                escapedChar == "omega" || escapedChar == "epsilon" || escapedChar == "shwa" ||
                                escapedChar == "v-flipped" || escapedChar == "c-flipped" || escapedChar == "theta" ||
                                escapedChar == "ae")
                            {
                                searchArray[n][charCount] = escapedChar;
                                charCount++;
                                break;
                            }
                            else
                            {
                                cout << "Invalid escaped character on line" << n+1;
                                exit(4);
                            }
                        }
                        escapedChar += currentLine[i];
                        i++;
                    }
                    
                    if (i == currentLine.length())
                    {
                        cout << "Escape terminator missing on line " << n+1;
                        exit(3);
                    }
                    break;
                }
                default:
                {
                    cout << "Invalid character in search on line " << n+1;
                    exit(4);
                }
            }
        }
        
        //ensure there are enough letters in the row
        if (charCount!=n_columns)
        {
            cout << "Too few characters in row " << n+1;
            exit(4);
        }
        
        //remove a line so the next one analyzed is correct.
        linesInputted.pop();
    }
     */
    return 0;
}

int WordSearch::getLineWidth(string line) {
    //checks the width of line.
    //This function assumes valid input.
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

