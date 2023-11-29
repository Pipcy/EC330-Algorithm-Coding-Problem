//
// Created by ppp on 11/28/23.
//
#include<iostream>
using namespace std;

#ifndef HW7_HUFFMAN_H
#define HW7_HUFFMAN_H

class Huffman{
private:
    int frequency;
    int size;
public:
    Huffman();
    void buildHuffmanTree(int frequency[], int size);
    void printCodes();
    void decodeText(string* filename);
};
#endif //HW7_HUFFMAN_H
