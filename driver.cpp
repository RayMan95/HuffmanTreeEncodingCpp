// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include "huffencode.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
    if (argc != 3){
        cout << "Well then get your shit together, get it all together and put it in a back pack,\
 all your shit, so it's together.\n[pause].\nAnd if you gotta take it some where, take it somewhere,\
 you know, take it to the shit store and sell it, or put it in the shit museum. I don't care what you do,\
 you just gotta get it together." << endl;
    }
    else{
        string inFileName = string(argv[1]);
        string outFileName = string(argv[2]);

        
        FKRRAY001::HuffmanTree * ht = new FKRRAY001::HuffmanTree();
        int uCs = ht->buildTree(inFileName);
        if(uCs < 0)
            cout << "File failed to open" << endl;
        else if(uCs == 0)
            cout << "File loaded, but had 0 unique characters" << endl;
        else{
            cout << inFileName << " loaded successfully had " << uCs << " unique chars" << endl;
        }
//        cout << to_string(ht->insert(c,0)) << endl;
//        cout << to_string(ht->getRoot()->get()) << endl;
        
        if(ht->encode(inFileName, outFileName)){
            cout << "File encoded successfully" << endl;
            cout << "Compressed at a ratio of (outputfilesize/inputfilesize): " << ht->getCompressionRatio() << endl;
        }
        else
            cout << "File encode failed" << endl;
        
        delete ht;
        
        cout << outFileName << " built from " << inFileName << endl;

    }

    return 0;
}