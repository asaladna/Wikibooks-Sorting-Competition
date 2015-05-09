#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <map>
#include <fstream>
using namespace std;

//ALEX SALADNA


// SeparateChaining Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

class HashTable
{
    public:
        HashTable();
        ~HashTable();

        void addWord(string word, char* page);
        std::vector<char*> search(std::string searchWord);
        void output(bool flag);
        void cleanStruct();
        void clear();
        const std::unordered_map<std::string,std::vector<char*>>* getReference()
        {
            return &wordList;
        }

    private:


        std::vector<char*> pageNums;

        std::unordered_map<std::string,std::vector<char*>>wordList;
};




#endif // HASHTABLE_H




