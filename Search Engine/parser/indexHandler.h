#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include <string>
#include <iostream>
#include <vector>
#include "dochandler.h"
#include "search.h"
#include "queryengine.h"
using namespace std;


class IndexHandler {
public:
	IndexHandler();
    int useQueryWords(queryEngine& getMyQueries, Search& myPageFinder, dochandler& myWordFinder);
	~IndexHandler();


private:
    Search myPageFinder;
    queryEngine getMyQueries;

    vector<string> oneQuery;
    vector<string> andQuery;
    vector<string> orQuery;
    vector<string> notQuery;

    vector< vector<char*> >theOnePageNums;
    vector< vector<char*> >theAndPageNums;
    vector< vector<char*> >theOrPageNums;
    vector< vector<char*> >theNotPageNums;

};
#endif // INDEXHANDLER_H
