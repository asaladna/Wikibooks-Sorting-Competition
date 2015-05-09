#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <iostream>
#include "relevancy.h"
using namespace std; 

class Search {
public:
	Search();
    int comparePages(vector< vector<char*> > theQueryWordPageNums,vector< vector<char*> > andQueryWordPageNums,vector< vector<char*> > orQueryWordPageNums,vector< vector<char*> > notQueryWordPageNums,dochandler& myWordFinder);
	~Search();
    Relevancy myCalculator;
private:
    vector <char*> theFinalVector;
    vector <char*> theFinalAndVector;
    vector <char*> firstAndVector;
    vector <char*> theFinalOrVector;

};
#endif //SEARCH_H
