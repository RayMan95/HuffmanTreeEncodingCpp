// Author: Rayaan Fakier FKRRAY001
// Date: 21-04-2017
// Driver class

#include "huffencode.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv){
    if (argc != 3){
        FKRRAY001::say("Well then get your shit together, get it all together and put it in a back pack, "
        "all your shit, so it's together.\n[pause].\nAnd if you gotta take it some where, take it"
        " somewhere, you know, take it to the shit store and sell it, or put it in the shit museum. I don't care what you do, you just gotta get it together.");
    }
    else{
        string inFileName = string(argv[1]);
        string outFileName = string(argv[2]);

        FKRRAY001::say(inFileName + " " + outFileName);
        FKRRAY001::HuffmanTree * ht = new FKRRAY001::HuffmanTree();
        char c[] = "kill";
        char& cref = c[0];
        ht->insert(cref);

    }

    return 0;
}

// Basic printing method
void FKRRAY001::say(string s){
    cout << s << endl;
}