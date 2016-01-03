//
//  WordSearch.cpp
//  IPA Word Search Solver
//
//  Created by Taylor Hamermesh on 12/12/15.
//  Copyright © 2015 Taylor Hamermesh. All rights reserved.
//

#include <iostream>
#include <string>
#include "WordSearch.h"
using namespace std;

WordSearch::WordSearch() {
    n_rows_ = 0;
    n_columns_ = 0;
    search_array_ = nullptr;
    buildIPACharacterList();
    buildIPAToSoundsList();
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

int WordSearch::generateWordSearch() {
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
    
    //Exit if the queue is empty
    if (n_rows_<=0) {
        cout << "Error: No lines given.";
        return 4;
    }
    
    //initialize rows of string arrays
    search_array_ = new string*[n_rows_];
    
    //initialize the columns
    for (int i=0; i<n_columns_; i++) {
        search_array_[i] = new string[n_columns_];
    }
    
    //loop through the rows and insert things into their correct column
    for (int i=0; i<n_rows_;i++) {
        string current_row = lines_inputted_.front();
        lines_inputted_.pop();
        //handleLine(current_row);
    }
    
    
    return 0;
}

void WordSearch::handleLine(string line, int row, int& expectedLength) {
    //handles a line by counting the number of characters in it while saving it into the search.
    //breaks if the number of characters is wrong
    //if expected length is -1, changes the expected length to the count. Otherwise, uses it to check the result.
    int count=0;
    bool inEscape = false;
    
    string buildingString;
    
    if (line == "") {
        cout << "Empty line";
        exit(4);
    }
    
    for (int i=0;i<line.length();i++) {
        switch (line[i]) {
            //ignore whitespace
            case ' ':
                continue;
            case ':':
                //Exit running escapes if inside, enter one if not
                inEscape= !inEscape;
                
                //if we just exited an escape, We've completed a new character. Add to count and append the running character
                if (inEscape==false) {
                    
                    //ensure count validity then append the character if it is valid
                    checkCountValid(count, row, expectedLength);
                    checkIfIpa(count, row, buildingString);
                    
                    //append the string
                    search_array_[row][count]=buildingString;
                    count++;
                    continue;
                }
                //we've entered an escape. wipe the current string and continue.
                else {
                    buildingString="";
                    continue;
                }
            default:
                //If not in an escape, append the character after validity checking
                if (inEscape==false)
                {
                    checkCountValid(count, row, expectedLength);
                    string singleChar;
                    singleChar+=line[i];
                    checkIfIpa(count, row, singleChar);
                    
                    //append the character
                    search_array_[row][count]+=line[i];
                    count++;
                    continue;
                }
                //We are in an escape. Append the current character to the building string and move on.
                else {
                    buildingString+=line[i];
                    continue;
                }
        }
    }
    
    //We've completed looping a string, completing a line. Final correctness checks:
    //An escape left unclosed
    if (inEscape) {
        cout << "An escape in line " << row << " was not terminated";
        exit(4);
    }
    
    //We have the expected number of IPA characters, or if no number is set yet, we make this the expected number
    if (expectedLength == -1)
        expectedLength = count;
    else if (expectedLength < count) {
        cout << "Line " << row << " is " << (expectedLength-count) << " characters short.";
        exit(4);
    }
}


//Helper function:

//if maxNum = -1, return.
//Otherwise, enforces max line width to prevent array index errors.

void WordSearch::checkCountValid(int currentCount, int row, int maxNum) {
    if (maxNum==-1)
        return;
    //equal to or greater than because c
    if (currentCount>=maxNum)
    {
        cout << "Too many characters in row " << row;
        exit(4);
    }
}

//returns if a string is a valid IPA character
void WordSearch::checkIfIpa(int currentCount, int row, string input) {
    unordered_set <string>::const_iterator ipaChar;
    ipaChar=IPA_characters_.find(input);
    if (ipaChar==IPA_characters_.end()){
        cout << "invalid character in row " << row << " at index " << currentCount;
        exit(4);
    }
}




void WordSearch::buildIPACharacterList() {
//list of all valid IPA Characters. If yours is missing, add it.

    IPA_characters_.insert("p");
    IPA_characters_.insert("b");
    IPA_characters_.insert("t");
    IPA_characters_.insert("d");
    IPA_characters_.insert("k");
    IPA_characters_.insert("g");
    IPA_characters_.insert("f");
    IPA_characters_.insert("v");
    IPA_characters_.insert("theta");
    IPA_characters_.insert("delta");
    IPA_characters_.insert("s");
    IPA_characters_.insert("z");
    IPA_characters_.insert("integral");
    IPA_characters_.insert("ezh");
    IPA_characters_.insert("h");
    IPA_characters_.insert("t-integral");
    IPA_characters_.insert("d-ezh");
    IPA_characters_.insert("m");
    IPA_characters_.insert("n");
    IPA_characters_.insert("n-hook");
    IPA_characters_.insert("l");
    IPA_characters_.insert("r-flipped");
    IPA_characters_.insert("w-flipped");
    IPA_characters_.insert("j");
    IPA_characters_.insert("i");
    IPA_characters_.insert("I");
    IPA_characters_.insert("u");
    IPA_characters_.insert("omega");
    IPA_characters_.insert("e");
    IPA_characters_.insert("epsilon");
    IPA_characters_.insert("shwa");
    IPA_characters_.insert("v-flipped");
    IPA_characters_.insert("c-flipped");
    IPA_characters_.insert("o");
    IPA_characters_.insert("ae");
    IPA_characters_.insert("a");
}

void WordSearch::buildIPAToSoundsList() {
//Sounds associated with IPA characters in english. If you add sounds, add how they could be translated into english
    IPA_sounds_["p"].push_back("p");
    IPA_sounds_["p"].push_back("pp");
    
    IPA_sounds_["b"].push_back("b");
    IPA_sounds_["b"].push_back("bb");
    
    IPA_sounds_["t"].push_back("t");
    IPA_sounds_["t"].push_back("tt");
    
    IPA_sounds_["d"].push_back("d");
    IPA_sounds_["d"].push_back("dd");
    
    IPA_sounds_["k"].push_back("k");
    IPA_sounds_["k"].push_back("ke");
    IPA_sounds_["k"].push_back("ck");
    IPA_sounds_["k"].push_back("c");
    IPA_sounds_["k"].push_back("ch");
    IPA_sounds_["k"].push_back("q");
    
    IPA_sounds_["g"].push_back("g");
    IPA_sounds_["g"].push_back("gg");
    
    //no velar stop: doesn't really ever add to words.
    
    IPA_sounds_["f"].push_back("f");
    IPA_sounds_["f"].push_back("gh");
    IPA_sounds_["f"].push_back("ff");
    IPA_sounds_["f"].push_back("ph");
    
    IPA_sounds_["v"].push_back("v");
    IPA_sounds_["v"].push_back("ve");
    IPA_sounds_["v"].push_back("f");
    
    //voiceless interdental fricative
    IPA_sounds_["theta"].push_back("th");
    
    //voiced interdental fricative
    IPA_sounds_["delta"].push_back("th");
    IPA_sounds_["delta"].push_back("the");
    
    IPA_sounds_["s"].push_back("s");
    IPA_sounds_["s"].push_back("ss");
    IPA_sounds_["s"].push_back("c");
    
    IPA_sounds_["z"].push_back("z");
    IPA_sounds_["z"].push_back("s");
    IPA_sounds_["z"].push_back("zz");
    
    //voiceless alveopalatal fricative
    IPA_sounds_["integral"].push_back("sh");
    IPA_sounds_["integral"].push_back("s");
    IPA_sounds_["integral"].push_back("ss");
    IPA_sounds_["integral"].push_back("ti");
    
    //voiced alveopalatal fricative
    IPA_sounds_["ezh"].push_back("su");
    IPA_sounds_["ezh"].push_back("ge");
    IPA_sounds_["ezh"].push_back("ti");
    IPA_sounds_["ezh"].push_back("zu");
    
    IPA_sounds_["h"].push_back("h");
    IPA_sounds_["h"].push_back("wh");
    
    //voiceless alveopalatal affricate
    IPA_sounds_["t-integral"].push_back("ch");
    IPA_sounds_["t-integral"].push_back("t");
    IPA_sounds_["t-integral"].push_back("tch");
    
    //voiced alveiopalatal affricate
    IPA_sounds_["d-ezh"].push_back("j");
    IPA_sounds_["d-ezh"].push_back("ge");
    IPA_sounds_["d-ezh"].push_back("gi");
    IPA_sounds_["d-ezh"].push_back("g");
    IPA_sounds_["d-ezh"].push_back("dj");
    IPA_sounds_["d-ezh"].push_back("dge");
    
    IPA_sounds_["m"].push_back("m");
    
    IPA_sounds_["n"].push_back("n");
    
    //voiced nasal velar
    IPA_sounds_["n-hook"].push_back("ng");
    
    IPA_sounds_["l"].push_back("l");
    IPA_sounds_["l"].push_back("ll");
    
    //voiced alveolar retroflex approximant
    IPA_sounds_["r-flipped"].push_back("r");
    
    //unvoiced bilabial glide
    IPA_sounds_["w-flipped"].push_back("wh");
    
    //voiced bilabial glide
    IPA_sounds_["w"].push_back("w");
    IPA_sounds_["w"].push_back("wh");
    
    //voiced palatal glide
    IPA_sounds_["j"].push_back("y");
    
    //VOWELS
    IPA_sounds_["i"].push_back("i");
    IPA_sounds_["i"].push_back("e");
    IPA_sounds_["i"].push_back("ea");
    IPA_sounds_["i"].push_back("ee");
    IPA_sounds_["i"].push_back("ei");
    IPA_sounds_["i"].push_back("ie");
    
    IPA_sounds_["I"].push_back("i");
    IPA_sounds_["I"].push_back("y");
    IPA_sounds_["I"].push_back("e");
    IPA_sounds_["I"].push_back("o");
    IPA_sounds_["I"].push_back("ui");
    
    IPA_sounds_["u"].push_back("u");
    IPA_sounds_["u"].push_back("ew");
    IPA_sounds_["u"].push_back("o");
    IPA_sounds_["u"].push_back("oo");
    IPA_sounds_["u"].push_back("ou");
    IPA_sounds_["u"].push_back("ue");
    IPA_sounds_["u"].push_back("ui");
    
    IPA_sounds_["omega"].push_back("o");
    IPA_sounds_["omega"].push_back("oo");
    IPA_sounds_["omega"].push_back("ou");
    IPA_sounds_["omega"].push_back("u");
    
    IPA_sounds_["e"].push_back("e");
    IPA_sounds_["e"].push_back("ea");
    
    IPA_sounds_["epsilon"].push_back("e");
    
    IPA_sounds_["shwa"].push_back("a");
    IPA_sounds_["shwa"].push_back("e");
    IPA_sounds_["shwa"].push_back("o");
    IPA_sounds_["shwa"].push_back("u");
    
    IPA_sounds_["v-flipped"].push_back("u");
    IPA_sounds_["v-flipped"].push_back("o");
    IPA_sounds_["v-flipped"].push_back("oo");
    IPA_sounds_["v-flipped"].push_back("ou");
    IPA_sounds_["v-flipped"].push_back("ough");
    
    IPA_sounds_["c-flipped"].push_back("oa");
    IPA_sounds_["c-flipped"].push_back("ough");
    IPA_sounds_["c-flipped"].push_back("a");
    IPA_sounds_["c-flipped"].push_back("aw");
    IPA_sounds_["c-flipped"].push_back("au");
    
    IPA_sounds_["o"].push_back("o");
    IPA_sounds_["o"].push_back("oa");
    IPA_sounds_["o"].push_back("oe");
    IPA_sounds_["o"].push_back("ow");
    IPA_sounds_["o"].push_back("ou");
    
    IPA_sounds_["ae"].push_back("a");
    
    IPA_sounds_["a"].push_back("a");
    IPA_sounds_["a"].push_back("au");
    IPA_sounds_["a"].push_back("augh");
    IPA_sounds_["a"].push_back("o");
}

