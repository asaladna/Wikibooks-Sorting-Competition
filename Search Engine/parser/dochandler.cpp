#include "dochandler.h"

using namespace rapidxml;
using namespace std;

dochandler::dochandler()
{
    pageInfoList.reserve(300000);



    clean = new cleantext();//removes all stop words and stems
    avlTree = new avlhandler();//accesses the avl tree to store data
    hash = new hashhandler();//accesses the hash table to store data
}


void dochandler::parser(string file, bool chosenStruct)
{
    //true= implement AVLTree  False= implement HashTable
    dataStructure = chosenStruct;


    int choice;
    int pageCounter = 0;



    string date;
    string text;
    string word;
    string author;

    cout << "Parsing..." << endl;
    xml_document<> doc;
    xml_node<> * root_node;


    // Read the xml file into a vector

    ifstream theFile;
    theFile.open(file.c_str());

    if(theFile.good())
        cout<<"File is Loaded"<<endl;

    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');



    cout<<"loaded"<<endl;
    // Parse the buffer using the xml file parsing library into doc
    doc.parse<0>(&buffer[0]);


    // Find our root node
    root_node = doc.first_node();

    if(root_node == 0)
        cerr<<"Incorrect XML format"<<endl;

    ofstream data;
    data.open ("pageInfo.txt");
    cout<<"test"<<endl;

    //find the page tag and pull necassary data only
    for (xml_node<> * page_node = root_node->first_node("page"); page_node;
        page_node = page_node->next_sibling())
    {
        pageCounter++;
        //reads in ID (Page Number)
        char* page = (page_node->first_node("id")->value());

        int strLen = strlen(page);

        char* pageToInsert = new char[strLen + 1];
        strcpy(pageToInsert, page);

        string title = page_node->first_node("title")->value();

        xml_node<> * revision_node = page_node->first_node("revision");
        text = revision_node->first_node("text")->value();
        //reads in timestamp (Date)
        date = revision_node->first_node("timestamp")->value();
        xml_node<> * contributor_node = revision_node->first_node("contributor");
        author = contributor_node->first_node()->value();

        pageInfo.author= author;
        pageInfo.title = title;
        pageInfo.text = text;
        pageInfo.date = date;

        //unordered map storing title, author, text, and date and can only be accessed with pageID
        pageInfoList.emplace(pageToInsert,pageInfo);

        //write all needed data onto disk for storage
        data << title << endl<<date<< endl << page << endl;
        data << author<<endl<<"|"<<endl;
        //data << text <<endl;


        stringstream stream(text);
        while (stream >> word)
         {
            //stems words, removes stops words and other uncecessary content
             bool flag = clean->formatText(word);

             if(flag == true)
             {
                 //word to be passed to AVL/Hash table
                 string parsedWord = clean->getWord();

                 if(dataStructure == true)
                     avlTree->assignValues(parsedWord, pageToInsert);
                 else if (dataStructure == false)
                     hash->assignHashValues(parsedWord, pageToInsert);
             }

         }
     }


     data.close();
}



//clears data structure of all contents


void dochandler::readFromIndex()
{
     pageInfoList.clear();

    string currentWord;
    string word;
    char* page;
    page = new char[50];
    std::ifstream ifs2;
    ifs2.open("indexContents.txt");
    while(!ifs2.eof())
    {
        getline(ifs2,word);
        if(word== "|")
        {
            getline(ifs2,word);
            currentWord = word;
        }
        else
        {
            strcpy(page,word.c_str());

            if(dataStructure == true)
                avlTree->assignValues(currentWord, page);
            else if (dataStructure == false)
                hash->assignHashValues(currentWord, page);
        }

    }

    string title;
    char* ID;
    ID = new char[50];
    string tempID;
    string date;
    string author;
    string text = "N/A";
    std::ifstream info;
    info.open("pageInfo.txt");
    while(!info.eof())
    {

        getline(info,title);
        getline(info,date);
        getline(info,tempID);
        getline(info,author);
        getline(info,word);

        strcpy(ID,tempID.c_str());

        pageInfo.author= author;
        pageInfo.title = title;
        pageInfo.text = text;
        pageInfo.date = date;

        pageInfoList.emplace(ID,pageInfo);



    }



    ifs2.close();
    info.close();

}

void dochandler::clear()
{
    int choice;

    cout<<"Do you want to clear data sctructure or persistant index?"<<endl;
    cout<<"1 for data structure"<<endl;
    cout<<"2 for persistant index"<<endl;
    cout<<"3 to go back"<<endl;

    cin>>choice;
    cout<<endl;

    while(choice != 1 && choice != 2 && choice != 3)
    {
        cout<<"Please enter a correct value of 1, 2, or 3"<<endl;
        cin >> choice;
        cout<<endl;
    }

    if(choice == 1)
    {
        if(dataStructure == true)
            avlTree->clearStruct();
        else
            hash->clearStruct();
    }
    else if(choice == 2)
    {
        std::ofstream ofs;
        ofs.open("pageInfo.txt", std::ofstream::out | std::ofstream::trunc);
        ofs.close();

        std::ofstream ofs2;
        ofs2.open("indexContents.txt", std::ofstream::out | std::ofstream::trunc);
        ofs2.close();
    }
    else if(choice == 3)
        return;
}


//stores data structure contents on disk
void dochandler::writeToDisk()
{
    cout<<"Saving Contents To Disk"<<endl;
    bool flag = true;

    if(dataStructure == true)
        avlTree->output(flag);
    else
        hash->output(flag);
}

//take userID and retrieve date
std::string dochandler::searchDate(char* pageNum)
{
    temp = pageInfoList.at(pageNum);
    string date = temp.date;

    return date;
}

//take userID and retrieve Author
std::string dochandler::searchAuthor(char* pageNum)
{
    temp = pageInfoList.at(pageNum);
    string author = temp.author;

    return author;
}

//take userID and retrieve Title
std::string dochandler::searchTitle(char* pageNum)
{
    temp = pageInfoList.at(pageNum);
    string title = temp.title;

    return title;
}

//take userID and retrieve Text
std::string dochandler::searchText(char* pageNum)
{
    temp = pageInfoList.at(pageNum);
    string text = temp.text;

    return text;
}

//retrieves userID from dataStructure
vector <char*> dochandler::search(string word)
{
    vector<char*> output;
    if(dataStructure == true)
    {
        output = avlTree->search(word);
    }
    else
    {
        output =  hash->search(word);
    }
    return output;
}

//outputs all info to screen (Mostly used for testing)
void dochandler::outputInfo()
{
    for (auto& x: pageInfoList)
    {
        std::cout << x.first << ": "<<x.second.title;
        cout<<endl;
        cout<<x.second.text<<endl;
    }
}

dochandler::~dochandler()
{
    delete clean;
}
