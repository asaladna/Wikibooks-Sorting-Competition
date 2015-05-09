#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <streambuf>
//#include <vector>
//#include "userinterface.h"
#include "dochandler.h"
#include "indexHandler.h"
#include "rapidxml-1.13/rapidxml.hpp"
#include "hashhandler.h"
#include "queryengine.h"
#include "search.h"
//Ziga Cerkovnik
class userInterface
{
    public:
        userInterface();
        virtual ~userInterface();
        bool userInput(); //initial prompt; choose between Maintenance and Interactive Mode
        bool maintenanceMode(); //interface of Maintenance Mode
        bool interactiveMode(); //interface of Interactive Mode
        void display(); //displays results
        bool prompt();

        void setDataStruct(int);
        bool getDataStruct();

        void setQuery(std::string);
        std::string getQuery();

    protected:
    private:
        Search s1;
        dochandler xml;

        char mode;
        char maintenanceQuery;
        char interactiveQuery;
        std::string query;
       // std::string y;
        bool dataStruct;
};
#endif // USERINTERFACE



