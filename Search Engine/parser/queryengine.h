#ifndef QUERYENGINE
#define QUERYENGINE
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "userinterface.h"
#include "cleantext.h"
//Ziga Cerkovnik

class queryEngine
{
    public:
        queryEngine();
        virtual ~queryEngine();

        void setQ(std::string);
        std::string getQ();

        bool breakWords(std::string query); //main function for sorting query words
        bool nestedCheck(std::string); //checks for nested expression
        bool nestedCheckBegin(std::string); // checks for "("
        bool nestedCheckEnd(std::string); // checks for ")"
        bool wrongCheck(std::string); //checks if a word is misspelled

        void setWords( std::vector<std::string> &w);
        void setAndWords( std::vector<std::string> &a);
        void setOrWords( std::vector<std::string> &o);
        void setNotWords( std::vector<std::string> &n);
        std::vector<std::string> getWords();
        std::vector<std::string> getAndWords();
        std::vector<std::string> getOrWords();
        std::vector<std::string> getNotWords();

        void setW(std::vector<std::string> &x);
        std::vector<std::string> getW();

    protected:
    private:
         std::string q;
         std::string temp;
         std::string tempWord;
         std::vector<std::string> words;
         std::vector<std::string> andWords;
         std::vector<std::string> orWords;
         std::vector<std::string> notWords;
         std::vector<std::string> stopWords;
         std::vector<std::string> misspelled;
         std::stringstream input;
         //userInterface u1;
         cleantext ct1;
         std::vector<std::string> testw;
};


#endif // QUERYENGINE

