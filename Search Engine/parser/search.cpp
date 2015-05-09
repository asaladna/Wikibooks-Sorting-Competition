#include "search.h"
#include "indexHandler.h"
using namespace std;

//Janie Pascoe has ownership over this class

//It recieves up to 4 vectors of vectors and, using different
//conditions depending upon the search from the user, it combines //them into one ending vector that satisfies the query that can
//then be used to calculate relevancy and output the correct
//documents to the user
Search::Search() {

}

int Search::comparePages(vector< vector<char*> > theQueryWordPageNums,vector< vector<char*> > andQueryWordPageNums,vector< vector<char*> > orQueryWordPageNums,vector< vector<char*> > notQueryWordPageNums,dochandler& myWordFinder) {
    //Recieves 4 vector of vectors containing page numbers to be used
    //depending on different conditions throughout this function
    if(!theQueryWordPageNums.empty() && !notQueryWordPageNums.empty() && andQueryWordPageNums.empty() && orQueryWordPageNums.empty()){
        //this block of code only runs if the only two vectors populated
        //are the THE one and the NOT one
        for(unsigned int i = 0; i < theQueryWordPageNums.size(); i++){
            for(unsigned int j = 0; j < theQueryWordPageNums[i].size(); j++){
                theFinalVector.push_back(theQueryWordPageNums[i][j]);
            }
        }
        //this populates a 1 dimensional vector with all the contents of //the 2 dimensional THE vector of vectors conatining page numbers
        if(theFinalVector.size() == 0){
            return 0;
        }
        //this if block runs if the vector is empty, therefore meaning
        //that the search does not exist and the whole program starts //over

        for(unsigned int i = 0; i < theFinalVector.size(); i++){
           for(unsigned int j = 0; j < notQueryWordPageNums.size(); j++){
              for(unsigned int k = 0; k < notQueryWordPageNums[j].size(); k++){
                 if(theFinalVector[i] == notQueryWordPageNums[j][k]){
                     theFinalVector.erase(theFinalVector.begin() + i);
                 }
              }
           }
        }
        //this block then compares the first vector created with the 2-D
        //NOT vector and if any of the documents in the first are also in
        //the second then that document number is deleted out of //theFinalVector
        if(theFinalVector.size() == 0){
            return 0;
        }
        //this if block runs if the vector is empty, therefore meaning
        //that the search does not exist and the whole program starts //over
        myCalculator.calculateMostRelevant(theFinalVector,myWordFinder);
        //the final vector created that satisifies the search is then
        //send to the calculateMostRelevant function within relevancy.cpp
        //where it is used to calculate relevancy and output the top 15
     }
  else
   if(!theQueryWordPageNums.empty() && notQueryWordPageNums.empty() && andQueryWordPageNums.empty() && orQueryWordPageNums.empty()){
       //this block of code only runs if the only vector populated
       //is the THE one
       for(unsigned int i = 0; i < theQueryWordPageNums.size(); i++){
           for(unsigned int j = 0; j < theQueryWordPageNums[i].size(); j++){
               theFinalVector.push_back(theQueryWordPageNums[i][j]);
           }
       }
        //this populates a 1 dimensional vector with all the contents of //the 2 dimensional THE vector of vectors conatining page numbers
       if(theFinalVector.size() == 0){
           return 0;
       }
       //this if block runs if the vector is empty, therefore meaning
       //that the search does not exist and the whole program starts //over
        myCalculator.calculateMostRelevant(theFinalVector, myWordFinder);
       //the final vector created that satisifies the search is then
       //send to the calculateMostRelevant function within relevancy.cpp
       //where it is used to calculate relevancy and output the top 15
   }
   else
       if(theQueryWordPageNums.empty() && !notQueryWordPageNums.empty() && !andQueryWordPageNums.empty() && orQueryWordPageNums.empty()){
           //this block of code only runs if the only two vectors populated
           //are the AND one and the NOT one
           for(unsigned int i = 0; i < andQueryWordPageNums[0].size(); i++){
               firstAndVector.push_back(andQueryWordPageNums[0][i]);
           }
           //this creates a 1-D vector conatining the contents of the vector //at index 0 of the 2-D AND vector in order to be compared //against the rest
           if(firstAndVector.size() == 0){
               return 0;
           }
           //this if block runs if the vector is empty, therefore meaning
           //that the search does not exist and the whole program starts //over

           for(unsigned int i = 0; i < firstAndVector.size(); i++){
               for(unsigned int j = 1; j < andQueryWordPageNums.size(); j++){
                   for(unsigned int k = 0; k < andQueryWordPageNums[j].size(); k++){
                       if(firstAndVector[i + 1] != firstAndVector[i] && firstAndVector[i] == andQueryWordPageNums[j][k]){
                               theFinalAndVector.push_back(firstAndVector[i]);
                       }
                   }
                }
            }
           //this block takes the first AND vector created and compares it
           //to the remaining indices of the 2-D AND vector of vectors
           //and if the document occurs in both then that document number is //added to a new empty vector
           if(theFinalAndVector.size() == 0){
               return 0;
           }

           //this if block runs if the vector is empty, therefore meaning
           //that the search does not exist and the whole program starts //over
            for(unsigned int i = 0; i < theFinalAndVector.size(); i++){
                for(unsigned int j = 0; j < notQueryWordPageNums.size(); j++){
                    for(unsigned int k = 0; k < notQueryWordPageNums[j].size(); k++){
                        if(theFinalAndVector[i] == notQueryWordPageNums[j][k]){
                            theFinalAndVector.erase(theFinalAndVector.begin() + i);

                        }
                    }
                }
            }
            //the final AND 1-D vector is then compared to the NOT vector of //vectors and for any numbers in the AND vector that also appear //in the NOT vector that specific document is then deleted
            //from the final AND vector
            if(theFinalAndVector.size() == 0){
                return 0;
            }

            //this if block runs if the vector is empty, therefore meaning
            //that the search does not exist and the whole program starts //over

            myCalculator.calculateMostRelevant(theFinalAndVector, myWordFinder);
            //the final vector created that satisifies the search is then
            //send to the calculateMostRelevant function within relevancy.cpp
            //where it is used to calculate relevancy and output the top 15
       }
   else
           if(theQueryWordPageNums.empty() && notQueryWordPageNums.empty() && !andQueryWordPageNums.empty() && orQueryWordPageNums.empty()){
               //this block of code only runs if the only vector populated
               //is the AND one
                for(unsigned int i = 0; i < andQueryWordPageNums[0].size(); i++){
                    firstAndVector.push_back(andQueryWordPageNums[0][i]);
           }
               //this creates a 1-D vector conatining the contents of the vector //at index 0 of the 2-D AND vector in order to be compared //against the rest
                if(firstAndVector.size() == 0){
                    return 0;
                }
            //this if block runs if the vector is empty, therefore meaning
            //that the search does not exist and the whole program starts //over
            for(unsigned int i = 0; i < firstAndVector.size(); i++){
               for(unsigned int j = 0; j < andQueryWordPageNums.size(); j++){
                   for(unsigned int k = 0; k < andQueryWordPageNums[j].size(); k++){
                       if(firstAndVector[i + 1] != firstAndVector[i] && firstAndVector[i] == andQueryWordPageNums[j][k]){
                               theFinalAndVector.push_back(firstAndVector[i]);
                       }
                   }
                }
            }
            //this block takes the first AND vector created and compares it
            //to the remaining indices of the 2-D AND vector of vectors
            //and if the document occurs in both then that document number is //added to a new empty vector
           if(theFinalAndVector.size() == 0){
               return 0;
           }
           //this if block runs if the vector is empty, therefore meaning
           //that the search does not exist and the whole program starts //over
            myCalculator.calculateMostRelevant(theFinalAndVector, myWordFinder);
            //the final vector created that satisifies the search is then
            //send to the calculateMostRelevant function within relevancy.cpp
            //where it is used to calculate relevancy and output the top 15
           }
   else
               if(theQueryWordPageNums.empty() && !notQueryWordPageNums.empty() && andQueryWordPageNums.empty() && !orQueryWordPageNums.empty()){
                   //this block of code only runs if the only two vectors populated
                   //are the NOT one and the OR one
                    for(unsigned int i = 0; i < orQueryWordPageNums.size(); i++){
                       for(unsigned int j = 0; j < orQueryWordPageNums[i].size(); j++){
                           theFinalOrVector.push_back(orQueryWordPageNums[i][j]);
                      }
                   }
                    //This creates a 1-D vector that is populated with all of the //contents of every index vector in the 2-D OR vector
                    if(theFinalOrVector.size() == 0){
                        return 0;
                    }
                    //this if block runs if the vector is empty, therefore meaning
                    //that the search does not exist and the whole program starts //over

                   for(unsigned int i = 0; i < theFinalOrVector.size(); i++){
                       for(unsigned int j = 0; j < notQueryWordPageNums.size(); j++){
                           for(unsigned int k = 0; k < notQueryWordPageNums[j].size(); k++){
                               if(theFinalOrVector[i] == notQueryWordPageNums[j][k]){
                                   theFinalOrVector.erase(theFinalOrVector.begin() + i);
                               }
                           }
                       }
                   }
                   //this takes the OR vector that was just made and compares
                   //it to every index vector of the 2-D NOT vector and if the
                   //document appears in both then it is deleted from the OR vector
                   if(theFinalOrVector.size() == 0){
                       return 0;
                   }
                   //this if block runs if the vector is empty, therefore meaning
                   //that the search does not exist and the whole program starts //over
                   myCalculator.calculateMostRelevant(theFinalOrVector, myWordFinder);
                   //the final vector created that satisifies the search is then
                   //send to the calculateMostRelevant function within relevancy.cpp
                   //where it is used to calculate relevancy and output the top 15
               }
   else
                   if(theQueryWordPageNums.empty() && notQueryWordPageNums.empty() && andQueryWordPageNums.empty() && !orQueryWordPageNums.empty()){
                       //this block of code only runs if the only vector populated
                       //is the OR one
                        for(unsigned int i = 0; i < orQueryWordPageNums.size(); i++){
                            for(unsigned int j = 0; j < orQueryWordPageNums[i].size(); j++){
                                theFinalOrVector.push_back(orQueryWordPageNums[i][j]);
                            }
                        }
                        //this makes a 1-D vector that conatains every element from every
                        //index vector in the 2-D OR vector
                        if(theFinalOrVector.size() == 0){
                            return 0;
                        }
                        //this if block runs if the vector is empty, therefore meaning
                        //that the search does not exist and the whole program starts //over

                    myCalculator.calculateMostRelevant(theFinalOrVector, myWordFinder);
                    //the final vector created that satisifies the search is then
                    //send to the calculateMostRelevant function within relevancy.cpp
                    //where it is used to calculate relevancy and output the top 15
                    }
    else
                      if(theQueryWordPageNums.empty() && !notQueryWordPageNums.empty() && !andQueryWordPageNums.empty() && !orQueryWordPageNums.empty()){
                      //this block of code only runs if the only three vectors //populated are the AND one, the NOT one, and the OR one

                          for(unsigned int i = 0; i < orQueryWordPageNums.size(); i++){
                            for(unsigned int j = 0; j < orQueryWordPageNums[i].size(); j++){
                                theFinalOrVector.push_back(orQueryWordPageNums[i][j]);
                            }
                          }
                          //this makes a 1-D vector that conatains every element from every
                          //index vector in the 2-D OR vector
                          if(theFinalOrVector.size() == 0){
                              return 0;
                          }
                          //this if block runs if the vector is empty, therefore meaning
                          //that the search does not exist and the whole program starts //over
                          for(unsigned int i = 0; i < theFinalOrVector.size(); i++){
                            for(unsigned int j = 1; j < andQueryWordPageNums.size(); j++){
                              for(unsigned int k = 0; k < andQueryWordPageNums[j].size(); k++){
                                if(theFinalOrVector[i + 1] != theFinalOrVector[i] && theFinalOrVector[i] == andQueryWordPageNums[j][k]){
                                  theFinalAndVector.push_back(firstAndVector[i]);
                                }
                              }
                            }
                          }
                          //this takes the final OR vector that encompases all documents //and compares it to every element in every index vector of the //2-D AND vector and if the document is in both then it is addded
                          //to the final vector to be compared to the NOT one
                            if(theFinalAndVector.size() == 0){
                                return 0;
                            }
                          //this if block runs if the vector is empty, therefore meaning
                          //that the search does not exist and the whole program starts //over
                          for(unsigned int i = 0; i < theFinalAndVector.size(); i++){
                            for(unsigned int j = 0; j < notQueryWordPageNums.size(); j++){
                              for(unsigned int k = 0; k < notQueryWordPageNums[j].size(); k++){
                                if(theFinalAndVector[i] == notQueryWordPageNums[j][k]){
                                  theFinalAndVector.erase(theFinalAndVector.begin() + i);
                                }
                              }
                            }
                          }
                          //this takes the final vector that was made from the AND
                          //and the OR ones and compares it to the NOT one and if the
                          //document appears in both then it is deleted from the original
                          //final one
                            if(theFinalAndVector.size() == 0){
                                return 0;
                            }
                          //this if block runs if the vector is empty, therefore meaning
                          //that the search does not exist and the whole program starts //over
                            myCalculator.calculateMostRelevant(theFinalAndVector, myWordFinder);
                          //the final vector created that satisifies the search is then
                          //send to the calculateMostRelevant function within relevancy.cpp
                          //where it is used to calculate relevancy and output the top 15
                      }
      else
                              if(theQueryWordPageNums.empty() && notQueryWordPageNums.empty() && !andQueryWordPageNums.empty() && !orQueryWordPageNums.empty()){
                                for(unsigned int i = 0; i < orQueryWordPageNums.size(); i++){
                                  for(unsigned int j = 0; j < orQueryWordPageNums[i].size(); j++){
                                    theFinalOrVector.push_back(orQueryWordPageNums[i][j]);
                                  }
                                }

                                if(theFinalOrVector.size() == 0){
                                    return 0;
                                }
                                //this block of code only runs if the only two vectors populated
                                //are the AND one and the OR one
                                for(unsigned int i = 0; i < theFinalOrVector.size(); i++){
                                  for(unsigned int j = 1; j < andQueryWordPageNums.size(); j++){
                                    for(unsigned int k = 0; k < andQueryWordPageNums[j].size(); k++){
                                      if(theFinalOrVector[i + 1] != theFinalOrVector[i] && theFinalOrVector[i] == andQueryWordPageNums[j][k]){
                                        theFinalAndVector.push_back(theFinalOrVector[i]);
                                      }
                                    }
                                  }
                                }
                                //this takes the final OR vector that encompases all documents //and compares it to every element in every index vector of the //2-D AND vector and if the document is in both then it is addded
                                //to the final vector


                                if(theFinalAndVector.size() == 0){
                                    return 0;
                                }
                                //this if block runs if the vector is empty, therefore meaning
                                //that the search does not exist and the whole program starts //over
                                myCalculator.calculateMostRelevant(theFinalAndVector, myWordFinder);
                                //the final vector created that satisifies the search is then
                                //send to the calculateMostRelevant function within relevancy.cpp
                                //where it is used to calculate relevancy and output the top 15
                              }
    return 1;



                  

}


Search::~Search() {

}
