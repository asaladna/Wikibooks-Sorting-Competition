#ifndef DOCHANDLER_H
#define DOCHANDLER_H

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "cleantext.h"
#include "avlhandler.h"
#include "hashhandler.h"

#include "rapidxml-1.13/rapidxml.hpp"

//ALEX SALADNA


class dochandler
{
public:
    dochandler();
    ~dochandler();

    void parser(std::string file, bool chosenStruct);

    void chooseDataStruct(bool flag);
    std::vector <char*> search(std::string word);
    void writeToDisk();
    void readFromIndex();
    std::string searchAuthor(char* pageNum);
    std::string searchDate(char* pageNum);
    std::string searchTitle(char* pageNum);
    std::string searchText(char* pageNum);

    void outputInfo();
    void clear();

//    void setAddWord(std::vector<input> const &addDoc);
//    vector<input> const &getAddWord() const;
private:

    struct input
    {
        std::string author;
        //char* page;
        std::string word;
        std::string date;
        std::string title;
        std::string text;
    }pageInfo, temp;


    avlhandler* avlTree;
    hashhandler* hash;
    cleantext* clean;

    std::unordered_map<char*,input>pageInfoList;

    std::vector<input> addingDoc;
    std::string storeWord;
    int storePageNum;
    bool dataStructure;
};

#endif // DOCHANDLER_H
