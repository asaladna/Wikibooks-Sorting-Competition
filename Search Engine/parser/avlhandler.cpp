#include "avlhandler.h"



using namespace std;


avlhandler::avlhandler()
{
    t = new AvlTree<string, char*, vector<char*>>;
}
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

void avlhandler::assignValues(string inputWord, char* pageNum)
{

    //inserts word and page num into AVL tree
    t->insert(inputWord,pageNum, pageNumList);

}

//searches tree for word and returns
//vector of pages where word is contained
std::vector<char*> avlhandler::search(string word)
{
    return t->contains(word);
}

//outputs entire tree
void avlhandler::output(bool flag)
{
    t->printTree();
}

//clears AVLtree of contents
void avlhandler::clearStruct()
{
    t->makeEmpty();
}

avlhandler::~avlhandler()
{


}

















