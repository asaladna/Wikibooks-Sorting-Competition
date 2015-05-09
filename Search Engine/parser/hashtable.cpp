#include "hashtable.h"
#include <iostream>
using namespace std;


/**
 * Internal method to test if a positive number is prime.
 * Not an efficient algorithm.
 */
HashTable::HashTable()
{
    wordList.reserve(300000);
}

void HashTable::addWord(string word, char* page )
{
    //adds word to hash table only if the word doesnt exist
    wordList.emplace(word,pageNums);

    //push back vector with new page number
    wordList.at(word).push_back(page);
}



//search hash table for desired word
vector<char*> HashTable::search(string searchWord)
{
    cout<<searchWord<<endl;
    return this->wordList.at(searchWord);
}


//outputs hahstable contents to screen or
//store in persitant index
void HashTable::output(bool flag)
{

    if(flag == true)
    {
        ofstream index;
        index.open ("indexContents.txt");

        for (auto& x: wordList)
        {
            index << x.first <<endl;
            for(int i = 0; i <x.second.size(); i++)
            {
                index<<x.second[i]<<endl;
            }
            index<<"|"<<endl;
        }
        index.close();
    }
    else
    {
        for (auto& x: wordList)
        {
            std::cout << x.first << ": ";
            for(int i = 0; i <x.second.size(); i++)
            {
                cout<<x.second[i]<<", ";
            }
            cout<<endl;
        }
    }
}

//clears hash table contents
void HashTable::clear()
{
    wordList.erase ( wordList.begin(), wordList.end() ); // erasing by range
}

HashTable::~HashTable()
{

}
