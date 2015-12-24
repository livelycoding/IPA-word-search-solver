//
//  Prompter.cpp
//  IPA Word Search Solver
//
//  Created by Taylor Hamermesh on 12/12/15.
//  Copyright © 2015 Taylor Hamermesh. All rights reserved.
//

#include <iostream>
#include "Prompter.h"
using namespace std;
    
/*
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
};*/

Prompter::Prompter() {
    cout << "Welcome to the IPA word search solver!" << endl << endl;
    printIntro();
    allowInput();
}

void Prompter::allowInput() {
    string input;
    getline(cin, input);
    parseInput(input);
}

void Prompter::parseInput(std::string input){
    if (input == "HELP") {
        printHelp();
        allowInput();
    }
    else if (input == "LIST") {
        printCharacterList();
        allowInput();
    }
    else if (input == "END") {
        
    }
    else {
        
    }
        
}

void Prompter::saveInput() {
    cout << "saveInput ran";
}

void Prompter::rejectInput() {
    cout << "rejectInput ran";
}


//Exposition interface blocks below

void Prompter::printIntro() {
    cout << "Enter characters to be inserted into the wordsearch one row at a time." << endl;
    cout << "Type END when the word search is fully generated." << endl;
    cout << "Type HELP for further instructions on input, if needed" << endl;
    cout << "Type DELETE to remove a single mistyped line and RESET if you would like to fully start over." << endl << endl;
}

void Prompter::printHelp() {
    cout << "This program is designed around standard english IPA pronunciations as defined by University of Arizona at the following link:\n http://ic-migration.webhost.uits.arizona.edu/icfiles/ic/lsp/site/IPA/SSAE.html " << endl << endl;
    cout << "Any character with a standard representation with a letter is written with that letter." << endl << endl;
    cout << "for nonstandard character such as the schwa, enter the escape character :, type an approximate " <<
    "description of the character, then another :. For example tS, the unvoiced alveopalatal fricative," <<
    "is written :t-integral:" << endl <<endl;
    cout << "Any character which appears to be another character flipped or rotated is" << endl;
    cout << "written as :r-flipped: (voiced alveolar retroflex approximant)." << endl << endl;
    cout << "For a full list of such commands, type LIST." << endl;
    cout << "Spaces are omitted automatically, but may be used to help format." << endl << endl;
}

void Prompter::printCharacterList() {
    cout << "characters list: " << endl << endl;
    cout << "consonants: " << endl;
    cout << "p b t d k g f v"  << endl;
    cout << ":theta:" << "- voiceless interdental fricative" << endl;
    cout << ":delta:" << "- voiced interdental fricative" << endl;
    cout << " s z" << endl;
    cout << ":integral:" << "- voiceless alveopalatal fricative" << endl;
    cout << ":ezh:" << "- voiced alveopalatal fricative" << endl;
    cout << "h"  << endl;
    cout << ":t-integral:" << "- voiceless alveopalatal affricate" << endl;
    cout << ":d-ezh:" << "- voiced alveopalatal affricate" << endl;
    cout << "m n"  << endl;
    cout << ":n-hook:" << "- voiced nasal velar" << endl;
    cout << "l" << endl;
    cout << ":r-flipped:" << "- voiced alveolar retroflex approximant" << endl;
    cout << ":w-flipped:" << "- unvoiced bilabial glide" << endl;
    cout << "w j" << endl << endl;
    cout << "vowels:" << endl;
    cout << "i I u :omega: e :epsilon: :shwa: :v-flipped: :c-flipped: o :ae: a" << endl << endl;
}

