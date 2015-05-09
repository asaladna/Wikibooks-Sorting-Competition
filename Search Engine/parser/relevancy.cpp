#include "relevancy.h"
#include "search.h"
#include <vector>
#include "math.h"
#include <algorithm>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <map>
using namespace std;
//Janie Pascoe has ownership of this class

//This class takes in a final vector that is 1-D that completely //satisfies the query and calculates the relevancy for each
//document once, stores the tf-idf number parallel to the
//document number, and then prints out the top 15 documents to
//the user with correct information where the text for each //document can also be printed

Relevancy::Relevancy() {
	//constructor
}


void Relevancy::calculateMostRelevant(vector <char*> finalVector, dochandler& myWordFinder){
    //this funtions recieves the final vector that satisfies the
    //query and an object of dochandler in order to execture and
    //access the titles and the text of the top 15 documents because
    //that information is stored in a struct in dochandler.cpp
    totalDocumentCount = 170000;//how many documents total... should be 170,000
    //in the wiki file
    spot = 0;
    termDocumentCount = 1;//how many documents the word is in (not with duplicates)
    currentPage = 0;


    tempDocuments.push_back(finalVector[0]);
    //fills tempDocuments
    //with the first document number so that there is something to be
    //compared to in the for loop on whether or not the number is a
    //duplicate and if it should be added or not

    duplicate = 0;
    for(int i = 0; i < finalVector.size(); i++){
        if(find(tempDocuments.begin(), tempDocuments.end(), finalVector[i]) != tempDocuments.end()){
            continue;
        }
        //if the document already exists in tempDocuments then
        //it goes back to the begining of the for loop and check with the
        //next document number
            else {
            termDocumentCount++;
            //how many documents the word is in not including duplicates
            }
    }



    idfWeight = log((1+totalDocumentCount)/(1+termDocumentCount));
    //and calculates the idfWeight, which is a pre determined
    //calculations based off of these numbers which is then used in
    //calculating the relevancy. idfWeight is the comparison of how
    //many documents the word is in vs how many documents there are
    //total
    for(int i = 0; i < termDocumentCount; i++){
        //through the vector of no duplicates so that each document only
        //has relevancy calculated for it once
        termWeight = recurCalculation(finalVector[i], finalVector);
        //returned from the recurCalculation function
        tfIdf = termWeight * idfWeight;
        //weight in one specific document to the idfWeight which takes
        //into account how many documents it actually occurs in
        relevantDocuments.insert(pair<char*, float>(finalVector[i],tfIdf));
        //number that relevancy was just calculated for as the key value
        //and the tf-idf number for that document as the mapped value
    }



    multimap<float, char*> reverseMap = flip_map(relevantDocuments);
    //this flips the map and creates a new one named reverseMap which
    //is full of the same contents but the tf-idf number is the key
    //value and the document number is the mapped value
    vector <string> textStorage;



//    for(auto rit = reverseMap.rbegin(); rit != reverseMap.rend(); ++rit){
//        cout << "flipped map" << endl << rit->first << " -> " << rit->second << endl;
//    }
    //this iterates through the map from end to begining so that
    //the output is in descending order and prints the information
    //for each document number of the top 15 by accessing rit->second
    //which is the document number in the map
    cout<<endl;
    cout<<"1-------------------------------------"<<endl;
    int counter = 0;
    for(auto rit = reverseMap.rbegin(); rit != reverseMap.rend(); ++rit){

        cout<<"Title: "<<myWordFinder.searchTitle(rit->second)<<endl;
        cout<<"Author: "<<myWordFinder.searchAuthor(rit->second)<<endl;
        cout<<"PageNumber: "<<rit->second<<endl;
        cout<<"Date: "<<myWordFinder.searchDate(rit->second)<<endl;
        cout<<"Relavency: "<<rit->first<<endl;


        cout<<endl;
        cout<<counter+2<<"-------------------------------------"<<endl;


        textStorage.push_back(myWordFinder.searchText(rit->second));
        //stores the text for each of the top 15 documents as //one long string in index 0-14 so that the user can access the
        //text if they want to

        counter++;
        if(counter == 15)
            break;
        //only allows the top 15 documents to be accessed and
        //printed and no more than that
        }
    int page;
    char choice;
    cout<<"Would you like to display Article Contents (Y/N)"<<endl;
    cin >> choice;
    while(choice != 'Y' && choice != 'N')
    {
        //makes sure the new
        //input is still valid by the user and if it isnt it prints the
        //following code and if it is then the process begins again up at
        //the top
        cout<<"Invalid entry please enter Y/N!"<<endl;
        cin >> choice;
        cout<<endl;
    }
    while(choice == 'Y')
    {
        cout<<"Please enter which document choice (1,2,3...,15): ";
        cin >>page;
        while(page > 15 || page < 1)
        {
            cout<<"Invalid entry please enter a value from 1 to 15!"<<endl;
            cin >> page;
            cout<<endl;
        }
        cout<<textStorage[page - 1]<<endl;
        cout<<endl;

        cout<<"Would you like to display any other texts? (Y/N) ";
        cin >> choice;
        cout<<endl;
        while(choice != 'Y' && choice != 'N')
        {
            cout<<"Invalid entry please enter Y/N!"<<endl;
            cin >> choice;
            cout<<endl;
        }
    }




}



int Relevancy::recurCalculation(char* currentPage, vector <char*> recurVector){
    theTermWeight = 0;//the amount of times the word occurs in one specific document
    //this function takes in the current page from the no duplicate
    //vector and the vector that does have the duplicates in it
    //this is so that it can count how many times it occurs in one
    //specific document thus giving the termWeight for that
    //specific document
    for(unsigned int i = 0; i < recurVector.size(); i++){
        if(currentPage == recurVector[i]){
            theTermWeight++;
        }
    }
    return theTermWeight;
    //runs through the whole vector with the duplicates and if the
    //document number passed in is the same as any more documents
    //in the vector then the termWeight is incremented and once
    //it is done iterating through the vector it returns the number
    //which is then used to calculate the tf-idf
}

multimap<float, char*> Relevancy::flip_map(map<char*,float> & source){
    multimap<float, char*> flipped;

    for(auto it = source.begin(); it != source.end(); it++)
        flipped.insert(pair<float, char*>(it->second, it->first));

    return flipped;
    //takes in the original map and while iterating through it
    //stores the values opposite from the original by flipping them
    //yet keeping them in the same index location and then returns it
    //back to the original function
}

Relevancy::~Relevancy() {
	//destructor
}
