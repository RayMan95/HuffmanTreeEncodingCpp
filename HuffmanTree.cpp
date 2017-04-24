// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include <fstream>
#include <iostream>
#include "huffencode.h"

using namespace std;
using HTree = FKRRAY001::HuffmanTree;
using HNode = FKRRAY001::HuffmanNode;
typedef std::shared_ptr<FKRRAY001::HuffmanNode> nodePtr;

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
        vector<shared_ptr<HNode>> nodeVec;
        for (auto c : this->charFreqs){
            nodePtr newNodePtr = shared_ptr<HNode>(new HNode(c.first, c.second));
            nodeVec.push_back(newNodePtr);
        }

        // is a min-queue
        priority_queue<shared_ptr<HNode>, vector<shared_ptr<HNode>>, HNode::compare> myQueue;
        for (shared_ptr<HNode> v : nodeVec){
            myQueue.push(v);
        }

        // TODO: possibly change parent val
        const char headChar[] = "~"; // char identifying parent nodes

        while(myQueue.size() != 1){

            shared_ptr<HNode> left = myQueue.top();
            myQueue.pop();
    //        cout << "right: " << left->get() << " popped." << endl; 
            shared_ptr<HNode> right = myQueue.top();
            myQueue.pop();
    //        cout << "left: " << right->get() << " popped." << endl;

            nodePtr parent = shared_ptr<HNode>(new HNode(headChar[0], left->f+right->f));
            // assign family links
            parent->setChildren(left, right);
            left->setParent(parent);
            right->setParent(parent);
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

nodePtr HTree::getRoot(void){
    return this->root;
}

void HTree::buildCodes(nodePtr root, string str, const char head){
    if (!root) // null
        return;
    
    if (root->get() == head){ // parent node
        buildCodes(root->left, str + "0", head);
        buildCodes(root->right, str + "1", head);
    }
    else{
        cout << root->get() << ": " << str << endl;
        codeTable[root->get()] = str;
        // TODO: check is inorder
        // inorder traversal
        buildCodes(root->left, str + "0", head);
        buildCodes(root->right, str + "1", head);
    }
}

bool HTree::compress(string fileInName, string fileOutName){
    ifstream ifile(fileInName);
    if (!ifile.is_open())
        return false;
    
    char c;
    string s = "";
    while (ifile >> c){
        s += codeTable[c];
    }
    
    ifile.close();
    
    ofstream ofile(fileOutName + ".hdr");
    ofile << uniqueChars << endl;
    for (auto p : codeTable){
        ofile << p.first << ": " << p.second << endl;
    }
    ofile.close();
    
    // TODO: check if must be binary
    ofile.open(fileOutName);
    ofile << s; // << endl; TODO: check if endl valid
    ofile.close();
    
    return true;
}