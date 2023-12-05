// HuffmanCodes.h
#include <queue>
#include <fstream>
#ifndef HUFFMAN_H
#define HUFFMAN_H
using namespace std;
class HuffmanTreeNode {
public:
    char data;
    int freq;
    HuffmanTreeNode* left;
    HuffmanTreeNode* right;

    HuffmanTreeNode(char character, int frequency);
};

class Compare {
public:
    bool operator()(HuffmanTreeNode* a, HuffmanTreeNode* b);
};

class Huffman{
public:
    HuffmanTreeNode* tree;

    HuffmanTreeNode* generateTree(std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, Compare> pq);

    void printCodes();
    void printCodes2(HuffmanTreeNode* root, int arr[], int top);


    void buildHuffmanTree(char data[], int freq[], int size);

    void decodeText(const char* filename);
};


#endif // HUFFMAN_H

