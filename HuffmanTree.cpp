// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include <fstream>

#include "huffencode.h"

using namespace std;
using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef std::shared_ptr<FKRRAY001::HuffmanNode> nodePtr;

unordered_map<char, int> charFreqs;
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
    vector<shared_ptr<HNode>> nodeVec;
    for (auto c : charFreqs){
        nodePtr newNodePtr = shared_ptr<HNode>(new HNode(c.first, c.second));
        nodeVec.push_back(newNodePtr);
    }
    
    priority_queue<shared_ptr<HNode>, vector<shared_ptr<HNode>>, HNode::compare> myQueue;
    for (shared_ptr<HNode> v : nodeVec){
        myQueue.push(v); // TODO: not properly ordered
    }
    // for debug
//    while(!myQueue.empty()){
//        myQueue.top();
//        myQueue.pop();
//    }
    ifile.close();
}

HNode* HTree::getRoot(void){
    return &(*root);
}