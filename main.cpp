//
//  main.cpp
//  IPA word search bruteforcer
//
//  Created by Taylor Hamermesh on 4/9/15.
//  Copyright (c) 2015 Taylor Hamermesh. All rights reserved.
//

#include <iostream>
#include <cctype>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>
#include "Prompter.h"
#include "WordSearch.h"
using namespace std;


void buildIPADictionary(unordered_map<string, vector<string> >& soundList);


void branchOffOf(string** grid, const unordered_set<string>& dictionary, const unordered_map<string, vector<string> >& sounds,  int startY,
                 int startX,int n_rows,int n_cols, int maxdepth);

int main() {
    //DEBUG
    //Prompter prompt;
    //WordSearch search;
    
    
    //build english dictionary in c++
    
    unordered_set<string> dictionary;
    
    ifstream dictFile;
    dictFile.open("./words/words.txt");
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
        cout << "The dictionary could not be loaded\n";
        exit(2);
    }
    
    //build the IPA dictionary
    
    unordered_map<string, vector<string> > soundList;
    buildIPADictionary(soundList);
    
    //needed declarations
    
    int n_rows = 0;
    int n_columns = 0;
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
    
    cout << "Enter characters to be inserted into the wordsearch one row at a time." << endl;
    cout << "Type END when the word search is fully generated." << endl;
    cout << "Type HELP for further instructions on input, if needed" << endl;
    cout << "Type DELETE to remove a single mistyped line and RESET if you would like to fully start over." << endl << endl;
    for(;;)
    {
        getline(cin, currentLine);
        if (currentLine == "HELP")
        {
            cout << "This program is designed around standard english IPA pronunciations as defined by University of Arizona at the following link:\n http://ic-migration.webhost.uits.arizona.edu/icfiles/ic/lsp/site/IPA/SSAE.html " << endl << endl <<
            "Any character with a standard representation with a letter is written with that letter." << endl << endl;
            cout << "for nonstandard character such as the schwa, enter the escape character :, type an approximate " <<
            "description of the character, then another :. For example tS, the unvoiced alveopalatal fricative," <<
            "is written :t-integral:" << endl <<endl;
            cout << "Any character which appears to be another character flipped or rotated is" << endl;
            cout << "written as :r-flipped: (voiced alveolar retroflex approximant)." << endl << endl;
            cout << "For a full list of such commands, type LIST." << endl;
            cout << "Spaces are omitted automatically, but may be used to help format." << endl << endl;
            continue;
        }
        
        if (currentLine == "RESET")
        {
            n_rows = 0;
            linesInputted = emptyQueue;
            cout << "Characters stored deleted." << endl;
            cout << "Type END on a new line when the word search is fully generated." << endl;
            cout << "Type HELP for further instructions on input, if needed" << endl;
            cout << "Type DELETE to remove a single mistyped line and RESET if you would like to fully start over." << endl << endl;
            continue;
        }
        
        if (currentLine == "DELETE")
        {
            if (n_rows <= 0)
            {
                cout << "Nothing to delete." << endl;
                continue;
            }
            linesInputted.pop();
            n_rows--;
            cout << "Line deleted." << endl;
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
            if (linesInputted.empty())
            {
                cout << "No lines inputted";
                exit(2);
            }
            
            //count the number of columns we expect for the remainder of execution using line one and generate the grid.
            //slight code smell to improve usability, we have to do character detection to figure out the character count.
            currentLine = linesInputted.front();
            int charCount = 0;
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
                        charCount++;
                        break;
                    case ':':
                        i++;
                        //check until you hit the next ':'
                        while (i < currentLine.length())
                        {
                            if (currentLine[i]==':')
                            {
                                charCount++;
                                break;
                            }
                            i++;
                        }
                        
                        if (i == currentLine.length())
                        {
                            cout << "Escape missing";
                            exit(3);
                        }
                        break;
                    default:
                    {
                        cout << "Invalid character in search.";
                        exit(4);
                    }
                }
            }
            
            //using the character count, generate the 2D array to be used for the remainder of production.
            
            n_columns = charCount;
            searchArray = new string*[n_rows];
            for (int i = 0; i < n_rows; i++)
            {
                searchArray[i] = new string[n_columns];
            }
            
            //loop through all letters given in the queue, and add them to the grid.
            
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
            
            
            break;
        }
        
        //store the line in the queue
        else
        {
            n_rows++;
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
    
    //print wordsearch
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_columns; j++)
        {
            cout << searchArray[i][j] << " ";
        }
        cout << endl;
    }
    
    //find words
    for (int i = 0; i < n_rows; i++)
    {
        for (int j = 0; j < n_columns; j++)
        {
            branchOffOf(searchArray, dictionary, soundList, i, j, n_rows, n_columns, depth);
        }
        cout << endl;
    }
    
    
    
    //clean up allocated grid memory.
    
    for (int i = 0; i <n_columns; i++)
    {
        delete [] searchArray[i];
    }
    
    delete [] searchArray;
    return 0;
}


void buildIPADictionary(unordered_map<string, vector<string> >& soundList)
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



void branchInDirection(string** grid, const unordered_set<string>& dictionary, const unordered_map<string, vector<string> >& sounds, int n_rows, int n_cols, int x, int y,
                       int dirX, int dirY, int depthLeft, string phonemes, string possibleWord)
{
    //stop if max depth hit
    if (depthLeft <= 0)
        return;
    
    unordered_map <string, vector<string> >::const_iterator sound = sounds.find(grid[y][x]);
    
    //check for a word build up till this point.
    unordered_set<string>::const_iterator word = dictionary.find(possibleWord);
    
    if (possibleWord!="")
    {
        if (word != dictionary.end())
            cout << "Potential match for " << phonemes << " : " << possibleWord  << "" << endl;
    }
    
    
    //for every case of the consonant we're currently on, append the current sound to the string and try it in all directions.
    for (int i = 0; i < sound->second.size(); i++)
    {
        if ( (x + dirX >= 0) && (x + dirX < n_cols) && (y + dirY >= 0 && y + dirY < n_rows) )
        {
            branchInDirection(grid, dictionary, sounds, n_rows, n_cols, x+dirX, y+dirY, dirX, dirY, depthLeft-1,
                              possibleWord+sound->second[i],phonemes+grid[y][x]);
        }
    }
}

void branchOffOf(string** grid, const unordered_set<string>& dictionary, const unordered_map<string, vector<string> >& sounds,  int startY,
                 int startX,int n_rows,int n_cols, int maxdepth)
{
    unordered_map <string, vector<string> >::const_iterator sound = sounds.find(grid[startY][startX]);
    
    //for every case of the consonant we're currently on, append the current sound to the string and try it in all directions.
    for (int i = 0; i < sound->second.size(); i++)
    {
        //in all eight cardinal directions rereun the function
        for (int y=-1; y<=1; y++)
        {
            for (int x=-1; x<=1; x++)
            {
                if ( (startX + x >= 0) && (startX + x < n_cols) && (startY + y >= 0 && startY + y < n_rows) )
                {
                    branchInDirection(grid, dictionary, sounds, n_rows, n_cols, startX, startY, x, y, maxdepth,"","");
                }
            }
        }
    }
}

/*
 //recursively run build word on every letter to find words in english that match
 void buildWord(string** grid, const unordered_set<string>& dictionary, const unordered_map<string, vector<string> >& sounds,  int currx,
 int curry,int n_rows,int n_cols, int horzPicked, int vertPicked, int depth,int maxdepth,string curr_string, string phonemes)
 {
 {
 //check for word at the current depth
 unordered_set<string>::const_iterator word = dictionary.find(curr_string);
 if (word != dictionary.end())
 cout << "Potential match for " << phonemes << " : " << curr_string  << "" << endl;
 
 //exit if out of bounds
 if (currx < 0 || currx >=n_cols || curry < 0 || curry >= n_rows)
 return;
 
 //exit if we've hit maximal depth.
 if (depth>maxdepth)
 return;
 
 //find the sound we're on
 string currChar = grid[currx][curry];
 unordered_map <string, vector<string> >::const_iterator sound = sounds.find(currChar);
 
 //branch out in all directions if directions are not picked.
 if (horzPicked == 0 && vertPicked == 0)
 {
 //for every case of the consonant we're currently on, append the current sound to the string and try it in all directions.
 for (int i = 0; i < sound->second.size(); i++)
 {
 //in all eight cardinal directions rereun the function
 for (int j=-1; j<=1; j++)
 {
 for (int k=-1; k<=1; k++)
 {
 //don't build words that are out of bounds
 if (!(j==k && j == 0) && currx+j>=0 && currx+j<n_cols && curry+k>=0 && curry+k < n_rows)
 {
 buildWord(grid, dictionary, sounds, currx + j, curry+k, n_rows, n_cols, j, k, depth+1, maxdepth,curr_string+sound->second[i],  phonemes+grid[currx+j][curry+k]);
 }
 }
 }
 }
 }
 //go deeper in a fixed direction
 else
 {
 //for every case of the consonant we're currently on, append the current sound to the string and try it in all directions.
 for (int i = 0; i < sound->second.size(); i++)
 {
 {
 if (!(currx + horzPicked == curry + vertPicked && currx + horzPicked == 0)
 &&  currx + horzPicked>=0
 && currx + horzPicked<n_cols
 && curry + vertPicked>=0
 && curry + vertPicked < n_rows)
 {
 buildWord(grid, dictionary, sounds, currx + horzPicked, curry+vertPicked, n_rows, n_cols, horzPicked, vertPicked, depth+1, maxdepth,curr_string+sound->second[i],  phonemes+grid[currx+horzPicked][curry+vertPicked]);
 }
 }
 }
 }
 }
 }
 
 */










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