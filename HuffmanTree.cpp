// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include <fstream>

#include "huffencode.h"

using namespace std;
using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef std::shared_ptr<FKRRAY001::HuffmanNode> nodePtr;
std::unordered_map<char, int> charFreqs;

nodePtr root;
int uniqueChars;

bool HTree::insert(char* cptr, int freq){
    nodePtr n(new HNode(*cptr, freq));
    if (root == nullptr){
        root = move(n);
        return true;
    }
    
    return false;
}

void HTree::buildTree(string fileInName){
    ifstream ifile;
    ifile.open(fileInName);
    char c;
    while (ifile >> c){
        if (charFreqs.find(c) == charFreqs.end()) // not yet added
            charFreqs[c] = 1;
        else
            charFreqs[c] = charFreqs[c]+1;
    }
    
    ifile.close();
}

bool HTree::compare(const HNode& a, const HNode& b){
    if (a.f < b.f)
        return true; // or > if the algorithm requires that ordering
    else 
        return false;
}

HNode* HTree::getRoot(void){
    return &(*root);
}