// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include <fstream>
#include <iostream>
#include <sstream>
#include "huffencode.h"

using namespace std;
using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef shared_ptr<HNode> nodeSPtr;

HTree::~HuffmanTree(){
    root = nullptr;
}

// Move constructor
HTree::HuffmanTree(HTree && rhs){
    root = move(rhs.root);
    rhs.root = nullptr;
    
    uniqueChars = move(rhs.getUniqueChars());
    codeTable = move(*rhs.getCodeTable());
    charFreqs = move(*rhs.getFreqMap());
    myQueue = move(*rhs.getPQueue());
}

// TODO: review these 2
// CopyAss op
HTree& HTree::operator =(HuffmanTree& rhs){
    root = rhs.root;
    uniqueChars = rhs.getUniqueChars();
    codeTable = *rhs.getCodeTable();
    charFreqs = *rhs.getFreqMap();
    myQueue = *rhs.getPQueue();
    
    rhs.root = nullptr;
    
    return *this;
}

// MoveAss op
HTree& HTree::operator =(HuffmanTree&& rhs){
    root = move(rhs.root);
    uniqueChars = move(rhs.getUniqueChars());
    codeTable = move(*rhs.getCodeTable());
    charFreqs = move(*rhs.getFreqMap());
    myQueue = move(*rhs.getPQueue());
    
    rhs.root = nullptr;
    
    return *this;
}

int HTree::buildTree(string fileInName){
    ifstream ifile;
    ifile.open(fileInName);
    if (ifile.is_open()){
        char c;
        while (ifile >> c){
            if (this->charFreqs.find(c) == this->charFreqs.end()) // not yet added
                this->charFreqs[c] = 1;
            else
                this->charFreqs[c] = this->charFreqs[c]+1;
        }
        vector<nodeSPtr> nodeVec;
        for (auto c : this->charFreqs){
            nodeSPtr newNodePtr = shared_ptr<HNode>(new HNode(c.first, c.second));
            nodeVec.push_back(newNodePtr);
        }

        
        for (shared_ptr<HNode> v : nodeVec){
            myQueue.push(v);
        }

        // TODO: possibly change parent val
        const char headChar[] = "~"; // char identifying parent nodes

        while(myQueue.size() != 1){

            shared_ptr<HNode> left = myQueue.top();
            myQueue.pop();
    //        cout << "left: " << left->get() << " popped." << endl; 
            shared_ptr<HNode> right = myQueue.top();
            myQueue.pop();
    //        cout << "right: " << right->get() << " popped." << endl;

            nodeSPtr parent = shared_ptr<HNode>(new HNode(headChar[0], left->f+right->f));
            // assign family links
            parent->setChildren(left, right);
            myQueue.push(parent);
        }
        this->root = myQueue.top();
        myQueue.pop();
        ifile.close();
        this->buildCodes(this->root,"", headChar[0]);
        
        uniqueChars = codeTable.size();
        return uniqueChars;
    }
    return -1; // file didn't open
}

nodeSPtr HTree::getRoot(void){
    return this->root;
}

void HTree::buildCodes(nodeSPtr root, string str, const char head){
    if (!root) // null
        return;
    
    if (root->get() == head){ // parent node
        buildCodes(root->left, str + "0", head);
        buildCodes(root->right, str + "1", head);
    }
    else{
//        cout << root->get() << ": " << str << endl;
        codeTable[root->get()] = str;
        // inorder traversal
        buildCodes(root->left, str + "0", head);
        buildCodes(root->right, str + "1", head);
    }
}

bool HTree::encode(string fileInName, string fileOutName){
    int inSize = 0,outSize = 0;
    ifstream ifile(fileInName);
    if (!ifile.is_open())
        return false;
    
    char c;
    string s = "", line;
    while (getline(ifile,line)){
        istringstream iss(line);
        while(iss >> c){
            s += codeTable[c]; // build output from codetable
            outSize += codeTable[c].length();
            inSize++;
        }
        s+="\n";
    }
    ifile.close();
    
    compression = outSize/inSize;
    
    ofstream ofile(fileOutName);
    ofile << s;
    ofile.close();
    
    ofile.open(fileOutName + ".hdr");
    ofile << uniqueChars << endl;
    for (auto p : codeTable){
        ofile << p.first << ": " << p.second << endl;
    }
    ofile.close();
    
    return true;
}

int HTree::getUniqueChars(){
    return uniqueChars;
}

// TODO: review returning references
unordered_map<char, int>* HTree::getFreqMap(){
    return &charFreqs;
}

unordered_map<char, string>* HTree::getCodeTable(){
    return &codeTable;
}

priority_queue<nodeSPtr, vector<nodeSPtr>, HNode::compare>* HTree::getPQueue(){
    return &myQueue;
}

int HTree::getCompressionRatio(){
    return compression;
}
