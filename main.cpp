//
//  main.cpp
//  IPA word search bruteforcer
//
//  Created by Taylor Hamermesh on 4/9/15.
//  Copyright (c) 2015 Taylor Hamermesh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
using namespace std;


void buildIPADictionary(unordered_map<string, vector<string> > soundList);
void addLineToArray(string toAppend);

int main() {
    
    //build english dictionary in c++
    
    unordered_set<string> dictionary;
    
    ifstream dictFile;
    dictFile.open("words.txt");
    if (dictFile.is_open())
    {
        string currentWord;
        
        //read all lines
        while (getline(dictFile,currentWord))
        {
            dictionary.insert(currentWord);
        }
        
        dictFile.close();
    }
    else
    {
        cout << "The dictionary could not be loaded";
        exit(2);
    }
    
    //build the IPA dictionary
    
    unordered_map<string, vector<string> > soundList;
    buildIPADictionary(soundList);
    
    //needed declarations
    
    int n_rows;
    int n_columns;
    int depth;
    
    string** searchArray = nullptr;
    queue<string> linesInputted;
    string currentLine;
    
    //used for deletion
    queue<string> emptyQueue;

    
    cout << "Welcome to the IPA word search solver!" << endl << endl;
    cout << "Enter maximal word character length to search for: ";
    cin >> depth;
    cin.ignore(10000,'\n');
    cout << endl;
    if (depth <= 0)
    {
        cout << "Invalid depth  ";
        exit(1);
    }
    
    bool inputComplete = false;
    
    cout << "Enter characters to be inserted into the wordsearch one row at a time." << endl;
    cout << "Type END on a new line when the word search is fully generated." << endl;
    cout << "Type HELP for further instructions on input, if needed" << endl;
    cout << "Type RESET if you input your result incorrectly or would like to start over." << endl << endl;
    while (inputComplete==false)
    {
        getline(cin, currentLine);
        if (currentLine == "HELP")
        {
            cout << "This program is designed around standard english IPA pronunciations." << endl << endl <<
            "Any character with a standard representation with a letter is written with that letter." << endl << endl;
            cout << "for nonstandard character such as the schwa, enter the escape character :, type an approximate " <<
            "description of the character, then another :. For example tS, the unvoiced alveopalatal fricative," <<
            "is written :t-integral: ." << endl <<endl;
            cout << "Any character which appears to be another character flipped or rotated is" << endl;
            cout << "written as :r-flipped: (voiced alveolar retroflex approximant)." << endl << endl;
            cout << "For a full list of such commands, type LIST." << endl;
            cout << "Spaces are omitted automatically, but may be used to help format." << endl << endl;
            continue;
        }
        
        if (currentLine == "RESET")
        {
            linesInputted = emptyQueue;
            cout << "Characters stored deleted." << endl;
            cout << "Type END on a new line when the word search is fully generated." << endl;
            cout << "Type HELP for further instructions on input, if needed" << endl;
            cout << "Type RESET if you input your result incorrectly or would like to start over." << endl << endl;
            continue;
        }
        
        if (currentLine == "LIST")
        {
            cout << "characters list: " << endl << endl;
            cout << "consonants: " << endl;
            
            cout << "p b t d k g f v"  << endl <<
            
            ":theta:" << "- voiceless interdental fricative" << endl <<
            ":delta:" << "- voiced interdental fricative" << endl <<
            
            " s z" << endl <<
            
            ":integral:" << "- voiceless alveopalatal fricative" << endl <<
            ":ezh:" << "- voiced alveopalatal fricative" << endl <<
            
            "h"  << endl <<

            ":t-integral:" << "- voiceless alveopalatal affricate" << endl <<
            ":d-ezh:" << "- voiced alveopalatal affricate" << endl <<
            
            "m n"  << endl <<
            
            ":n-hook:" << "- voiced nasal velar" << endl <<
            
            "l" << endl <<
            
            ":r-flipped:" << "- voiced alveolar retroflex approximant" << endl <<
            ":w-flipped:" << "- unvoiced bilabial glide" << endl <<
            
            "w" << endl << endl <<
            
            "vowels:" << endl <<
            "i I u :omega: e :epsilon: :shwa: :v-flipped: :c-flipped: o :ae: a" << endl << endl;
        
            continue;
        }
        if (currentLine == "END")
        {
            // parse text in the queue to put in a 2D array
            int columnsInPrevRow = 0;
            
            //parse until no lines remain
            while (!linesInputted.empty())
            {
                currentLine = linesInputted.front();
                for (int i = 0; i<currentLine.length();i++)
                {
                    
                }
            
            }
        
        }
        
        //store the line in the queue
        else
        {
            linesInputted.push(currentLine);
            continue;
        }
    }
    
    if (n_rows <= 0)
    {
        cout << "Invalid row number ";
        exit(1);
    }
    if (n_rows <= 0)
    {
        cout << "Invalid column number ";
        exit(1);
    }
    
    
    
    
    
    
    return 0;
}


void buildIPADictionary(unordered_map<string, vector<string> > soundList)
{
    //declare sound approximations for Standard American English q
    
    //consonants
    soundList["p"].push_back("p");
    soundList["p"].push_back("pp");
    
    soundList["b"].push_back("b");
    soundList["b"].push_back("bb");
    
    soundList["t"].push_back("t");
    soundList["t"].push_back("tt");
    
    soundList["d"].push_back("d");
    soundList["d"].push_back("dd");
    
    soundList["k"].push_back("k");
    soundList["k"].push_back("ke");
    soundList["k"].push_back("ck");
    soundList["k"].push_back("c");
    soundList["k"].push_back("ch");
    soundList["k"].push_back("q");
    
    soundList["g"].push_back("g");
    soundList["g"].push_back("gg");
    
    //no velar stop: doesn't really ever add to words.
    
    soundList["f"].push_back("f");
    soundList["f"].push_back("gh");
    soundList["f"].push_back("ff");
    soundList["f"].push_back("ph");
    
    soundList["v"].push_back("v");
    soundList["v"].push_back("ve");
    soundList["v"].push_back("f");
    
    //voiceless interdental fricative
    soundList["theta"].push_back("th");
    
    //voiced interdental fricative
    soundList["delta"].push_back("th");
    soundList["delta"].push_back("the");
    
    soundList["s"].push_back("s");
    soundList["s"].push_back("ss");
    soundList["s"].push_back("c");
    
    soundList["z"].push_back("z");
    soundList["z"].push_back("s");
    soundList["z"].push_back("zz");
    
    //voiceless alveopalatal fricative
    soundList["integral"].push_back("sh");
    soundList["integral"].push_back("s");
    soundList["integral"].push_back("ss");
    soundList["integral"].push_back("ti");
    
    //voiced alveopalatal fricative
    soundList["ezh"].push_back("su");
    soundList["ezh"].push_back("ge");
    soundList["ezh"].push_back("ti");
    soundList["ezh"].push_back("zu");
    
    soundList["h"].push_back("h");
    soundList["h"].push_back("wh");
    
    //voiceless alveopalatal affricate
    soundList["t-integral"].push_back("ch");
    soundList["t-integral"].push_back("t");
    soundList["t-integral"].push_back("tch");
    
    //voiced alveiopalatal affricate
    soundList["d-ezh"].push_back("j");
    soundList["d-ezh"].push_back("ge");
    soundList["d-ezh"].push_back("gi");
    soundList["d-ezh"].push_back("g");
    soundList["d-ezh"].push_back("dj");
    soundList["d-ezh"].push_back("dge");
    
    soundList["m"].push_back("m");
    
    soundList["n"].push_back("n");
    
    //voiced nasal velar
    soundList["n-hook"].push_back("ng");
    
    soundList["l"].push_back("l");
    soundList["l"].push_back("ll");
    
    //voiced alveolar retroflex approximant
    soundList["r-flipped"].push_back("r");
    
    //unvoiced bilabial glide
    soundList["w-flipped"].push_back("wh");
    
    //voiced bilabial glide
    soundList["w"].push_back("w");
    soundList["w"].push_back("wh");
    
    
    //VOWELS
    soundList["i"].push_back("i");
    soundList["i"].push_back("e");
    soundList["i"].push_back("ea");
    soundList["i"].push_back("ee");
    soundList["i"].push_back("ei");
    soundList["i"].push_back("ie");
    
    soundList["I"].push_back("i");
    soundList["I"].push_back("y");
    soundList["I"].push_back("e");
    soundList["I"].push_back("o");
    soundList["I"].push_back("ui");
    
    soundList["u"].push_back("u");
    soundList["u"].push_back("ew");
    soundList["u"].push_back("o");
    soundList["u"].push_back("oo");
    soundList["u"].push_back("ou");
    soundList["u"].push_back("ue");
    soundList["u"].push_back("ui");
    
    soundList["omega"].push_back("o");
    soundList["omega"].push_back("oo");
    soundList["omega"].push_back("ou");
    soundList["omega"].push_back("u");
    
    soundList["e"].push_back("e");
    soundList["e"].push_back("ea");
    
    soundList["epsilon"].push_back("e");
    
    soundList["shwa"].push_back("a");
    soundList["shwa"].push_back("e");
    soundList["shwa"].push_back("o");
    soundList["shwa"].push_back("u");
    
    soundList["v-flipped"].push_back("u");
    soundList["v-flipped"].push_back("o");
    soundList["v-flipped"].push_back("oo");
    soundList["v-flipped"].push_back("ou");
    soundList["v-flipped"].push_back("ough");
    
    soundList["c-flipped"].push_back("oa");
    soundList["c-flipped"].push_back("ough");
    soundList["c-flipped"].push_back("a");
    soundList["c-flipped"].push_back("aw");
    soundList["c-flipped"].push_back("au");
    
    soundList["o"].push_back("o");
    soundList["o"].push_back("oa");
    soundList["o"].push_back("oe");
    soundList["o"].push_back("ow");
    soundList["o"].push_back("ou");
    
    soundList["ae"].push_back("a");
    
    soundList["a"].push_back("a");
    soundList["a"].push_back("au");
    soundList["a"].push_back("augh");
    soundList["a"].push_back("o");
}

















//Needs:
//Output english equivalents as one goes. The algorithm for large m and large n will become quite slow with regards to reaching the end. Outputting words as one goes and providing a starting and ending character means the work can be subdivided between multiple computers or started from the leaveoff points
//Arbitrary start and end characters



//ENGLISH HASHTABLE STUFF GOES HERE



//RECURSIVE GENERATION
/*
void buildWord(currx, curry,boundx,boundy,depth,maxdepth,curr_string)
{

//exit if out of bounds
if (currx < 0 || currx > boundx || curry < 0 || curry > boundy)
    return;
 
//exit if we've hit maximal depth.
 if (depth>maxdepth)
    return;
 
//for every case of the consonant we're currently on, append the current sound to the string
 for (int i = 0; i <
 
 
 
//if we're on the right x and y, we're done
if (currx =


}

*/


/*

Workflow:
 
-Load an english dictionary into a hash table.

-create an unordered map of characters representing IPA sounds associated with a vector of possible letter combinations. Populate these vectors.

-Ask for number of rows and columns, n & m. Abort on negatives or 0.

-Ask for a raw string of text representing all characters left to right. :: encloses IPA symbols without english equivalents.

-Generate a 2D array of strings using this data. Abort if fed a nonIPA symbol with an error message of what broke it.

-Ask for a start character and an end character, S and E. Also ask for a max world length to check for, WL. Abort on two.
 
-Create a hash table for found words.
-Create a vector for current word attempts.
-create a current word length
 
-Go through all characters till you hit the end character:

-Have we hit the Wordlength cap? If so, move on to the next letter.
 
 OTHERWISE
-check if current word length in a directions is on or off the chart, starting at top and going clockwise
-if it is on the chart, starting on the present character, create a vector
-Repeat this for the current character until we hit the wordlength cap:
-Check if there's a character (currentlength)
-
 
*/