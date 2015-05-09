#include "indexHandler.h"
#include "avlhandler.h"
#include <vector>
using namespace std;

IndexHandler::IndexHandler() {
	//constructor
}

int IndexHandler::useQueryWords(queryEngine& getMyQueries, Search& myPageFinder, dochandler& myWordFinder) {
    oneQuery = getMyQueries.getWords();
    andQuery = getMyQueries.getAndWords();
    orQuery = getMyQueries.getOrWords();
    notQuery = getMyQueries.getNotWords();

    for(unsigned int i = 0; i < oneQuery.size(); i++){
        theOnePageNums.push_back(myWordFinder.search(oneQuery[i]));
    }
    for(unsigned int i = 0; i < andQuery.size(); i++){
        theAndPageNums.push_back(myWordFinder.search(andQuery[i]));
    }
    for(unsigned int i = 0; i < orQuery.size(); i++){
        theOrPageNums.push_back(myWordFinder.search(orQuery[i]));
    }
    for(unsigned int i = 0; i < notQuery.size(); i++){
        theNotPageNums.push_back(myWordFinder.search(notQuery[i]));
    }

    int i = myPageFinder.comparePages(theOnePageNums, theAndPageNums, theOrPageNums, theNotPageNums,myWordFinder);
    return i;
}

IndexHandler::~IndexHandler() {
	//destructor
}


