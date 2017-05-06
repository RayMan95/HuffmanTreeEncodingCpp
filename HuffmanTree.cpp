// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include <fstream>
#include <iostream>
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
    charFreqs = move(*rhs.getFreqtable());
    myQueue = move(*rhs.getPQueue());
}
// CopyAss op
HTree& HTree::operator =(HuffmanTree& rhs){
    root = rhs.root;
    uniqueChars = rhs.getUniqueChars();
    codeTable = *rhs.getCodeTable();
    charFreqs = *rhs.getFreqtable();
    myQueue = *rhs.getPQueue();
    
    rhs.root = nullptr;
    
    return *this;
}

// TODO: review
// MoveAss op
HTree& HTree::operator =(HuffmanTree&& rhs){
    root = move(rhs.root);
    uniqueChars = move(rhs.getUniqueChars());
    codeTable = move(*rhs.getCodeTable());
    charFreqs = move(*rhs.getFreqtable());
    myQueue = move(*rhs.getPQueue());
    
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
    //    cout << endl;
    //    for (auto p : codeTable){
    //        cout << p.first << ": " << p.second << endl;
    //    }
        
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
        cout << root->get() << ": " << str << endl;
        codeTable[root->get()] = str;
        // inorder traversal
        buildCodes(root->left, str + "0", head);
        buildCodes(root->right, str + "1", head);
    }
}

bool HTree::encode(string fileInName, string fileOutName){
    ifstream ifile(fileInName);
    if (!ifile.is_open())
        return false;
    
    char c;
    string s = "";
    while (ifile >> c){
        s += codeTable[c]; // build output from codetable
    }
    ifile.close();
    
    ofstream ofile(fileOutName);
    ofile << s; // << endl; TODO: check if endl valid
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

unordered_map<char, int>* HTree::getFreqtable(){
    return &charFreqs;
}

unordered_map<char, string>* HTree::getCodeTable(){
    return &codeTable;
}

priority_queue<nodeSPtr, vector<nodeSPtr>, HNode::compare>* HTree::getPQueue(){
    return &myQueue;
}