#ifndef HASHHANDLER_H
#define HASHHANDLER_H

#include <string>
#include <vector>

#include <iostream>
#include "hashtable.h"
#include "indexinput.h"

//ALEX SALADNA


class hashhandler
{
public:
    hashhandler();
    ~hashhandler();
    void assignHashValues(string inputWord, char* pageNum);
    vector<char*>search(string word);
    void clearStruct();
    void output(bool flag);
private:
    HashTable* hash;
    vector<char*> pages;
};

#endif // HASHHANDLER_H
