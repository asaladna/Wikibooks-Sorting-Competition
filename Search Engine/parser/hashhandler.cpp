#include "hashhandler.h"

hashhandler::hashhandler()
{
    hash = new HashTable();
}

//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items

void hashhandler::assignHashValues(string inputWord, char* pageNum)//populates hash table with words and page nums
{
    hash->addWord(inputWord, pageNum );
}


//returns vector of pageNums
vector<char*> hashhandler::search(string word)
{

    const std::unordered_map<std::string,std::vector<char*>>* myList;
    myList = hash->getReference();

    cout<<myList->size()<<"map size"<<endl;


    try
    {
        pages = myList->at(word);
    }
    catch(std::out_of_range e)
    {

    }
    return pages;



}

//clears hash table of contents
void hashhandler::clearStruct()
{
    hash->clear();
}

//outputs hash tables contents
void hashhandler::output(bool flag)
{
    hash->output(flag);
}


hashhandler::~hashhandler()
{

}

