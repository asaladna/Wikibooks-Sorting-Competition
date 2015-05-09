#ifndef AVLHANDLER_H
#define AVLHANDLER_H

#include <string>
#include <vector>

#include <iostream>
#include "AvlTree.h"



class avlhandler
{
public:
    avlhandler();
    ~avlhandler();


    void assignValues(std::string inputWord, char* pageNum);
    std::vector<char*>search(std::string word);
    void output(bool flag);
    void clearStruct();
private:
    AvlTree<std::string, char*, vector<char*>>* t;

    vector<char*> pageNumList;


};

#endif // AVLHANDLER_H
