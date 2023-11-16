/*
 * Homework 6 Coding Question Prompt
 * [BIG DATA]
 *
This problem involves finding information in a very large data file, BigData.txt,
similar to what you might find from the dump of a hard drive. The file can be
obtained from eng grid: /ad/eng/courses/ec/ec330/BigData.txt or
https://drive.google.com/file/d/0B2H-ZCNPqkX2bzhxUlRVdHg4cVE/view?usp=sharing&resourcekey=0-feWTz4uAWol9e5qOz6_b7w

We also provide, on Blackboard, a TinyData.txt file, which is useful for initial tests of
your code.
Within this file, determine:
-----------------------------------------------------------------------------------
## Part A ## fiveA
The number of BU-IDs in the file whose digits add to a number greater than 28. A
BU ID is defined as anything starting with a U and followed by exactly eight
digits and then a non-digit.

## Part B ## fiveB
The number of English words (from the dictionary.txt file) that appear in the file
that do not end with the same letter of the alphabet as your last name (for
example, if your last name ends with the letter ‘t’, then you should exclude
EC330 Applied Algorithms and Data Structures for Engineers, Fall 2023
dictionary words that end with ‘t’). The words do not need to be delimited by
spaces (or other punctuation) in the file, and may overlap. The words must be
contiguous e.g: door$knob or door knob will not find doorknob, but will still find
door, and knob. Duplicates do count. For example, the word “a”, which is a
dictionary word, appears in the data more than once, and should be counted
accordingly.

## Part C ## fiveC
The length of the longest palindrome (i.e. a string that equals its reverse) you can
find within the text. When finding palindromes, consider ALL characters (spaces
should count).
-----------------------------------------------------------------------------------
Your code must be submitted in a single file named Problem5.cpp. Your code should
include three functions, fiveA, fiveB, and fiveC. These functions must have the same
declarations as the function declarations in Problem5.h, and when run in the same
directory as BigData.txt they should analyze this file. To receive full credit, your
solution needs to be efficient. Your code should be compiled as follows:

 to run this code, run these line in the terminal (make sure to have dictionary.txt and
 Big Data.txt and .h file on the same path):
> scl enable devtoolset-10 bash
> g++ -std=c++17 -o hw5 Problem5.cpp main.cpp
> ./hw5
 */


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include <cctype>
#include "Problem5.h"
using namespace std;
/* --------------------------------------------------------------------------------------------------------------------
#### Part A ####
First I open the file and read line by line.
I use a for-loop that goes through each character and check for "U"
Then I check to make sure the following 8 element is digit followed by a non-digit at the end
Increment every time when sum of the digits is > 28
 */
int fiveA(){
    int count = 0;
    //---- read file line by line -----
    ifstream textFile;
    textFile.open("BigData.txt");
    int lineCt;
    string text;
    //---------------------------------

    while(getline(textFile,text)) {
        lineCt++;
        for (int i = 0; i < text.size(); i++) {
            if (text[i] == 'U' && !isdigit(text[i + 9])) {
                int sum = 0;
                for (int j = 1; j <= 8; j++) {
                    if (isdigit(text[i + j])) {
                        sum += static_cast<int>(text[i + j]) - 48;
                    } else {
                        goto endLoops;
                    }
                }
                if (sum > 28) {
                    count++;
                }
            }
            endLoops:
            int n = 0;
        }
    }
    return count;
}



/*----------------------------------------------------------------------------------------------------------------------
#### Part B ####
I used a trie (referenced from https://www.geeksforgeeks.org/trie-insert-and-search/)
I first add all the word (excluding the ones ends in "i" per requirement) to the Trie
Then I go through the text file by character with slow iterator (i) as the starting index
fast iterator (j) that starts at i and increment as long as the element is a letter in the alphabet.
check all the substring (substr(i,j-i+1)) is a word in Trie. Increment if it is.
 */
// Trie Implementation ------------------------------------------------------
// C++ implementation of search and insert
// operations on Trie
const int ALPHABET_SIZE = 58;

// trie node
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;
};

// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;
    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        char currentChar = key[i];
        int index;
        if(isalpha(currentChar)){
            index = key[i] - 'A';
        }
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode(); //

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}

// Returns true if key presents in trie, else
// false
bool isWord(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        char currentChar = key[i];
        int index;
        if(isalpha(currentChar)){
            index = key[i] - 'A';
        }
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->isEndOfWord);
}

bool searchInTrie(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    for (int i = 0; i < key.length(); i++)
    {
        char currentChar = key[i];
        int index;

        if(isalpha(currentChar)){
            index = key[i] - 'A';
        }
        else{

        }
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return true;
}
//End of Trie Implementation --------------------------------------------------
int fiveB(){
//input words from text into trie
    TrieNode* root = new TrieNode();
    ifstream dicFile;
    dicFile.open("dictionary.txt");
    string text;

    while(getline(dicFile,text)){
        if(text.back() != 'i'){
            insert(root,text);
        }
    }
    dicFile.close();
    ifstream findTextFile;
    findTextFile.open("BigData.txt");
    string allText((istreambuf_iterator<char>(findTextFile)), (istreambuf_iterator<char>()));

    string subString;
    int countWord = 0;
    for(int i = 0; i < allText.size();i++){
        int Jay = i;
        //cout << "("<<Jay<< ")";
        if(isalpha(allText[i])){
            int j = i;
            while(isalpha(allText[j])){
                int word_length = j-i+1;
                subString = allText.substr(Jay,word_length);
                if(searchInTrie(root,subString)){
                    if(isWord(root,subString)){
                        countWord++;
                    }
                }
                j++;
            }
        }
    }

    return countWord;

}
//----------------------------------------------------------------------------------------------------------------------
/*#### Part C ####*/
/*
Initialize a int variable named max = 1;
go through each character c in the text file,
check the letters of current max index left and right to the character,
if they are equal, then grab the substring (substr starting from c-max  to c+max)
reverse it, and check each character to see if it is equal to original
if completely equal, increment max by 2 and keep going.
 */

// helper function that read File text into a string variable "text" --------------------
string readData(){
    ifstream textFile;
    textFile.open("BigData.txt");
    //adding each "line" (of text) into a big string "text"
    string line;
    string text;
    if(textFile.is_open()){
        while(!textFile.eof()){
            textFile >> line;
            text+=line;
        }
    }
    else{
        cout << "fail to open" << endl;
    }
    return text;
}//---------------------------------------------------------------------------------------

int fiveC(){
    string text = readData();
    int max = 1;
    for(int i = 1; i < text.size();i++){
        if(text[i-max/2-1] == text[i+max/2+1]){
            string backward_testString = text.substr(i-(max/2)-1,max+2);
            string testString = backward_testString;
            reverse(backward_testString.begin(),backward_testString.end());
            for(int j = 0; j < testString.size();j++){
                if(testString[j] != backward_testString[j]){
                    goto endLoop2;
                }
            }
            max+=2;
        }
        endLoop2:
        int n = 0;
    }
    return max;
}