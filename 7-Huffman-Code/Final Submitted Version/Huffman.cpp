//
// Created by Jo Harper on 11/29/23.
//
// C++ Program for Huffman Coding
// using Priority Queue
#include <iostream>
#include <queue>
#include<string>
#include "Huffman.h"
using namespace std;

// Maximum Height of Huffman Tree.
#define MAX_SIZE 100

//class HuffmanTreeNode {
//public:
//    // Stores character
//    char data;
//
//    // Stores frequency of
//    // the character
//    int freq;
//
//    // Left child of the
//    // current node
//    HuffmanTreeNode* left;
//
//    // Right child of the
//    // current node
//    HuffmanTreeNode* right;
//
//    // Initializing the
//    // current node
//    HuffmanTreeNode(char character,
//                    int frequency)
//    {
//        data = character;
//        freq = frequency;
//        left = right = NULL;
//    }
//};
HuffmanTreeNode::HuffmanTreeNode(char character,
                    int frequency)
    {
        data = character;
        freq = frequency;
        left = right = NULL;
    }


// Custom comparator class
//class Compare {
//public:
//    bool operator()(HuffmanTreeNode* a,
//                    HuffmanTreeNode* b)
//    {
//        // Defining priority on
//        // the basis of frequency
//        return a->freq > b->freq;
//    }
//};

bool Compare::operator()(HuffmanTreeNode* a,
                HuffmanTreeNode* b)
{
    // Defining priority on
    // the basis of frequency
    return a->freq > b->freq;
}


// Function to generate Huffman
// Encoding Tree
HuffmanTreeNode* Huffman::generateTree(priority_queue<HuffmanTreeNode*,vector<HuffmanTreeNode*>, Compare> pq) {
    while (pq.size() != 1) {
    HuffmanTreeNode* left = pq.top();

    pq.pop();
    HuffmanTreeNode* right = pq.top();

    pq.pop();

    HuffmanTreeNode* node = new HuffmanTreeNode('$',
                                                left->freq + right->freq);
    node->left = left;
    node->right = right;

    pq.push(node);
    }
    return pq.top();
}
void Huffman::printCodes() {
    int arr[MAX_SIZE], top = 0;
    printCodes2(this->tree, arr, top);
}
// Function to print the
// huffman code for each
// character.

// It uses arr to store the codes
void Huffman::printCodes2(HuffmanTreeNode* root, int arr[], int top)
{

    // Assign 0 to the left node
    // and recur
    if (root->left) {
        arr[top] = 0;
        printCodes2(root->left,
                   arr, top + 1);
    }

    // Assign 1 to the right
    // node and recur
    if (root->right) {
        arr[top] = 1;
        printCodes2(root->right, arr, top + 1);
    }

    // If this is a leaf node,
    // then we print root->data

    // We also print the code
    // for this character from arr
    if (!root->left && !root->right) {
        cout << root->data << " ";
        for (int i = 0; i < top; i++) {
            cout << arr[i];
        }
        cout << endl;
    }
}



void Huffman::buildHuffmanTree(char data[],
                  int freq[], int size)
{

    // Declaring priority queue
    // using custom comparator
    priority_queue<HuffmanTreeNode*,
            vector<HuffmanTreeNode*>,
            Compare>
            pq;

    // Populating the priority
    // queue
    for (int i = 0; i < size; i++) {
        HuffmanTreeNode* newNode
                = new HuffmanTreeNode(data[i], freq[i]);
        pq.push(newNode);
    }

    // Generate Huffman Encoding
    // Tree and get the root node
    HuffmanTreeNode* root = generateTree(pq);
    this->tree = root;

    // Print Huffman Codes
//    int arr[MAX_SIZE], top = 0;
//    printCodes(root, arr, top);
}

void Huffman::decodeText(const char* fileName) {
    ifstream inputFile(fileName, ios::binary);
    if (!inputFile) {
        cerr << "Error opening file: " << fileName << endl;
        return;
    }

    ofstream outputFile("decoded_text.txt", ios::out);
    string result = "";
    HuffmanTreeNode* current = this->tree;

    char bit;
    while (inputFile.get(bit)) {
        if (bit == '0') {
            // Move to the left child for '0'
            current = current->left;
        } else if (bit == '1') {
            // Move to the right child for '1'
            current = current->right;
        }

        // If it's a leaf node, print the character and reset to the root
        if (current && !current->left && !current->right) {
            result +=current->data;
            current = this->tree; // Reset to the root
        }
    }
    cout << endl;
    cout << result << endl;
    inputFile.close();
    outputFile.close();
}


