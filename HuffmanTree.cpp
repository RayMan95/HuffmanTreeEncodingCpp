// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include "huffencode.h"
using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef std::shared_ptr<FKRRAY001::HuffmanNode> nodePtr;


nodePtr root;

bool HTree::insert(char* cptr, int freq){
    nodePtr n(new HNode(*cptr, freq));
    if (root == nullptr){
        root = move(n);
        return true;
    }
    
    return false;
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