#include "userinterface.h"

using namespace rapidxml;
using namespace std;
userInterface::userInterface()
{
    int x;
    cout<<"Which would you like to do?"<<endl;
    cout<<"1 HashTable or AVL Tree"<<endl;
    cout<<"2 Read from the index"<<endl;
    cin >> x;
    if(x == 1)
    {
        cout<<"Please Enter FileName"<<endl;
        string fileName;
        cin >> fileName;
        interactiveMode();
        string file = fileName;
        xml.parser(file,dataStruct);
        cout<<"Parsing Complete!"<<endl;
    }
    else if(x == 2)
        xml.readFromIndex();

}
userInterface::~userInterface()
{
    //dtor
}

bool userInterface::userInput() //User chooses between Maintenance mode and Interactive mode
{
    cout << " Select a mode: " << endl;
    cout << endl << "(M) Maintenance Mode" << endl;
    cout << "(I) Interactive Mode" << endl;
    cout << "(E) Exit Program"<<endl;
    cin >> mode;

    if(mode != 'M' && mode != 'I' && mode != 'E')
    {
        cout<<"Incorrect Entry!"<<endl;
        userInput();
    }

    if(mode == 'E')
    {
        xml.writeToDisk();
        return false;
    }


    switch(mode)
    {
    case 'M':
        {
            maintenanceMode();
            userInput();
        }
    case 'I':
        {
            string query;
            char choice;
            cout<<"Would you like to search (Y/N): ";
            cin >> choice;

            //if user's input is invalid
            while(choice != 'Y' && choice != 'N')
            {
                cout<<"Invalid entry please enter Y/N!"<<endl;
                cin >> choice;
                cout<<endl;
            }

            cout<<endl;

            //if user decides to search
            while(choice == 'Y')
            {
                cout<<"Enter Query: ";
                cin.ignore();
                getline(cin,query);

                queryEngine q1;
                q1.breakWords(query);

                Search s1;
                IndexHandler myIndexHandler;
                if(myIndexHandler.useQueryWords(q1, s1, xml) == 0)
                {
                    cout<<"Incorrect Entry!!!!!!"<<endl;
                    userInput();
                }

                cout<<"Would you like to enter another Query? (Y/N)"<<endl;
                cin >> choice;
                while(choice != 'Y' && choice != 'N')
                {
                    cout<<"Invalid entry please enter Y/N!"<<endl;
                    cin >> choice;
                    cout<<endl;
                }
                cout<<endl;
            }
            userInput();
        }
    default:
        {
            cout << endl << "Enter 'M' for Maintenance mode or 'I' for Interactive mode! " << endl << endl;
            userInput();

        }
    }
    return false;
}

bool userInterface::maintenanceMode() //Maintenance mode interface
{
    cout << endl << "Choose the action you wish to perform: " << endl;
    cout << endl << "   (A) Manually Add Documents" << endl;
    cout << endl << "   (C) Clear the index" << endl;
    cout << endl << "   (B) Back" << endl;
    cin >> maintenanceQuery;

    while(maintenanceQuery != 'A' && maintenanceQuery != 'B'&& maintenanceQuery != 'C')
    {
        cout<<"Invalid entry please enter:"<<endl;
        cout << endl << "   (A) Manually Add Documents" << endl;
        cout << endl << "   (C) Clear the index" << endl;
        cout << endl << "   (B) Back" << endl;
        cin >> maintenanceQuery;
        cout<<endl;
    }

    switch(maintenanceQuery)
    {

    case 'A':
        {
            string fileName;
            cout<<"Please enter document name: ";
            cin.ignore();

            getline(cin,fileName);


            //addDoc.parser(fileName, dataStruct);
//            cout<<endl;
//            ifstream newFile;
//            newFile.open (fileName);

//            std::string content((std::istreambuf_iterator<char>(newFile)),
//                             std::istreambuf_iterator<char>());
            userInput();

            break;
        }
    case 'C':
        {
            xml.clear();
            cout<<"Data Structure Cleared"<<endl;
            userInput();
        }
    case 'B':
        {
            system("clear");
            userInput();
        }
    default:
        {
            cout << endl << "Please choose a valid response (A to Add Documents or C to clear the index) " << endl;
        }
    }

    return true;
}

bool userInterface::interactiveMode() //Interactive mode interface
{
    cout << endl << "What would you like the index to be loaded into: " << endl;
    cout << endl << "   (1) AVL Structure" << endl;
    cout << endl << "   (2) Hash Table" << endl;
    cout << endl << endl << "   (B) Back" << endl;
    cin >> interactiveQuery;

    setDataStruct(interactiveQuery);

    switch(interactiveQuery)
    {
        case '1': //select AVL Tree
        {
            system("clear");
            setDataStruct(interactiveQuery);
            prompt();
            break;

        }
        case '2': // select Hash Table
        {
            system("clear");
            setDataStruct(interactiveQuery);
            prompt();
            break;

        }
        case 'B':
        {
            system("clear");
            userInput();

            break;
        }
        default:
        {   system("clear");
            cout << endl << "Please select 1 for AVL Structure and 2 for Hash Table!" << endl;
            interactiveMode();
        }
    }

    return false;
}


bool userInterface::prompt()  //Prompt user to enter query and stores it in a String object
{

    /*cout << endl << "Enter your query: \n";
    getline(cin, query);
    setQuery(query);
    cout << getQuery();*/

    //queryEngine q1;
    //q1.breakWords();

    return false;
}


void userInterface::setQuery(string y)
{
    query = y;
}

string userInterface::getQuery()
{
    return query;
}


void userInterface::setDataStruct(int x)
{
    if(x == 1)
    {
        dataStruct = true;
    }
    if(x == 2)
    {
        dataStruct = false;
    }

}

bool userInterface::getDataStruct()
{
    return dataStruct;
}

