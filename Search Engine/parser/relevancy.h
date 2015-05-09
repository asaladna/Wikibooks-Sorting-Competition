#ifndef RELEVANCY_H
#define RELEVANCY_H

#include <iostream>
#include <vector>
#include <map>
#include "dochandler.h"
using namespace std;

class Relevancy {
	public:
    Relevancy();
    void calculateMostRelevant(vector <char*> finalVector, dochandler& myWordFinder);
    int recurCalculation(char* currentPage, vector <char*> recurVector);
    multimap<float, char*> flip_map(map<char*,float> & source);
    ~Relevancy();

	private:


    vector <char*> finalVector;
    vector <char*> tempDocuments;
    map <char*, float> relevantDocuments;
    int totalDocumentCount;
    int spot;
    int termDocumentCount;
    int termWeight;
    int theTermWeight;
    char* currentPage;
    int thePage;
    float idfWeight;
    float tfIdf;
    //vector <float> relevantDocuments;
    int i;
    int temp;
    int duplicate;

};
#endif //RELEVANCY_H
