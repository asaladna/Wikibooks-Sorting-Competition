#include "indexHandler.h"
#include "queryengine.h"

using namespace std;

queryEngine::queryEngine()
{
    //ctor
}


void queryEngine::setQ(string x)
{
    q = x;
}

string queryEngine::getQ()
{
    return q;
}

bool queryEngine::breakWords(string query)
{


    q = query;


    stringstream input2(q);
    END:
    while(input2 >> tempWord)
    {
        //if not a nested query
        if(nestedCheck(tempWord) != true) //if not a nested query
        {

            if(tempWord == "AND") //if AND is a prefix boolean
            {
                AND:
                //continue reading the query

                while(input2 >> tempWord)
                {
                    if(tempWord == "AND")
                    {
                       goto AND1;
                    }
                    if(tempWord == "OR")
                    {
                       goto OR1;
                    }
                    if(tempWord == "NOT")
                    {
                        goto NOT1;
                    }
                    //if signs of a nested query is found

                    if(nestedCheck(tempWord) != false) //if nested query, go to NESTED
                    {
                        //NESTED:
                        //gets rid of ( and )
                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), '('), tempWord.end());  //gets rid of ( and )
                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());

                            if(tempWord == "AND") //if AND is a prefix boolean
                            {
                                AND1:
                                while(input2 >> tempWord && tempWord != "NOT" && tempWord != "OR")
                                {
                                    //if signs of a nested query is found
                                    if(nestedCheck(tempWord) != false)
                                    {
                                        //get's read of )
                                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                        andWords.push_back(tempWord);
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                        //break;
                                        goto AND;
                                    }
                                    //if the word is not a stop rord
                                    else if(ct1.formatText(tempWord)!=false) // && (nestedCheck(tempWord) != true))
                                    {
                                        //store to AND vector
                                        andWords.push_back(ct1.getWord());
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                    }
                                }
                            }

                            if(tempWord == "OR")
                            {
                                OR1:
                                while(input2 >> tempWord && tempWord != "NOT")// && tempWord != "AND")
                                {
                                    if(ct1.formatText(tempWord) != false)
                                    {
                                        //if signs of a nested query are found
                                        orWords.push_back(ct1.getWord());
                                        //tempWord.clear();
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                    }
                                    if(nestedCheck(tempWord) != false)
                                    {
                                        //get rid of )
                                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                        orWords.push_back(tempWord);
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                       // break;
                                        goto AND;
                                    }
                                }
                            }

                            if(tempWord == "NOT")
                            {
                                NOT1:
                                while(input2 >> tempWord)
                                {
                                    if(ct1.formatText(tempWord) != false)
                                    {
                                        notWords.push_back(ct1.getWord());
                                        //tempWord.clear();
                                        tempWord.erase(tempWord.begin(), tempWord.end());

                                    }

                                    //if word is not a stop word
                                    if(nestedCheck(tempWord) != false)
                                    {
                                        //store in OR vector
                                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                        notWords.push_back(tempWord);
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                        goto AND;
                                    }

                                }
                                goto END;
                            }
                    }
                          //if not nested, store
                    if((ct1.formatText(tempWord)!=false)) //not a stop word
                    {
                        andWords.push_back(ct1.getWord());
                        tempWord.clear();
                        goto AND;
                    }
               }

            }

            if(tempWord == "OR")
            {
                OR:
                while(input2 >> tempWord)// && tempWord != "AND") // && tempWord != "AND")
                {
                    if(tempWord == "AND")
                    {
                       goto AND;
                    }
                    if(tempWord == "OR")
                    {
                        goto OR;
                    }
                    if(tempWord == "NOT")
                    {
                        goto NOT;
                    }

                    //if it is not a stop word
                    if(ct1.formatText(tempWord)!=false)
                    {
                        if(nestedCheck(tempWord) != false)
                        {
                            //NESTED:
                            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), '('), tempWord.end());  //gets rid of ( and )
                            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());

                                if(tempWord == "AND") //if AND is a prefix boolean
                                {
                                   // AND2:
                                    while(input2 >> tempWord && tempWord != "NOT" && tempWord != "OR")
                                    {
                                        if(nestedCheck(tempWord) != false) //if nested query .end
                                        {
                                            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                            andWords.push_back(tempWord);
                                            tempWord.erase(tempWord.begin(), tempWord.end());
                                            //break;
                                            goto OR;
                                        }
                                        else if(ct1.formatText(tempWord)!=false)
                                        {
                                            andWords.push_back(ct1.getWord());
                                            tempWord.erase(tempWord.begin(), tempWord.end());
                                        }
                                    }
                                }

                                if(tempWord == "OR")
                                {
                                    //OR2:
                                    while(input2 >> tempWord && tempWord != "NOT")// && tempWord != "AND")
                                    {
                                        if(ct1.formatText(tempWord) != false)
                                        {
                                            orWords.push_back(ct1.getWord());
                                            //tempWord.clear();
                                            tempWord.erase(tempWord.begin(), tempWord.end());
                                        }
                                        if(nestedCheck(tempWord) != false)
                                        {
                                            //orWords.push_back(tmp);
                                            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                            orWords.push_back(tempWord);
                                            tempWord.erase(tempWord.begin(), tempWord.end());
                                           // break;
                                            goto OR;
                                        }
                                    }
                                }

                                if(tempWord == "NOT")
                                {
                                    while(input2 >> tempWord)
                                    {
                                        if(ct1.formatText(tempWord) != false)
                                        {
                                            notWords.push_back(ct1.getWord());
                                            //tempWord.clear();
                                            tempWord.erase(tempWord.begin(), tempWord.end());

                                        }
                                        if(nestedCheck(tempWord) != false)
                                        {
                                            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                            notWords.push_back(tempWord);
                                            tempWord.erase(tempWord.begin(), tempWord.end());
                                            goto OR;
                                        }

                                    }
                                    goto END;
                                }
                        }
                        orWords.push_back(ct1.getWord());
                        tempWord.clear();
                        goto OR;
                     }

                    /*if(ct1.formatText(tempWord) != false)
                    {
                        orWords.push_back(ct1.getWord());
                        //tempWord.clear();
                        tempWord.erase(tempWord.begin(), tempWord.end());
                    }*/
                }
            }

            if(tempWord == "NOT")
            {
                NOT:
                while(input2 >> tempWord)
                {
                    /*if(nestedCheck(tempWord) != false)
                    {
                        goto NESTED;
                    }*/
                    if(tempWord == "AND")
                    {
                       goto AND;
                    }
                    if(tempWord == "OR")
                    {
                        goto OR;
                    }
                    if(tempWord == "NOT")
                    {
                        goto NOT;
                    }

                    if(ct1.formatText(tempWord)!=false)
                    {
                    if(nestedCheck(tempWord) != false)
                    {
                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), '('), tempWord.end());  //gets rid of ( and )
                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());

                            if(tempWord == "AND") //if AND is a prefix boolean
                            {
                                AND3:
                                while(input2 >> tempWord && tempWord != "NOT" && tempWord != "OR")
                                {
                                    //if signs of a nested query are found
                                    if(nestedCheck(tempWord) != false)
                                    {
                                        //gets rid of )
                                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                        andWords.push_back(tempWord);
                                        //puts word in lowercase
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                        //break;
                                        goto NOT;
                                    }
                                    else if(ct1.formatText(tempWord)!=false) // && (nestedCheck(tempWord) != true))
                                    {
                                        //puts word in lowercase
                                        andWords.push_back(ct1.getWord());
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                    }
                                }
                            }

                            if(tempWord == "OR")
                            {
                                OR3:
                                while(input2 >> tempWord && tempWord != "NOT")// && tempWord != "AND")
                                {
                                    //if signs of nested query
                                    if(ct1.formatText(tempWord) != false)
                                    {
                                        orWords.push_back(ct1.getWord());
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                    }
                                    if(nestedCheck(tempWord) != false)
                                    {
                                        //orWords.push_back(tmp);
                                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                        orWords.push_back(tempWord);
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                       // break;
                                        goto NOT;
                                    }
                                }
                            }

                            if(tempWord == "NOT")
                            {
                                while(input2 >> tempWord)
                                {
                                    //if not a stop word
                                    if(ct1.formatText(tempWord) != false)
                                    {
                                        notWords.push_back(ct1.getWord());
                                        //tempWord.clear();
                                        tempWord.erase(tempWord.begin(), tempWord.end());

                                    }
                                    if(nestedCheck(tempWord) != false)
                                    {
                                        tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                                        notWords.push_back(tempWord);
                                        tempWord.erase(tempWord.begin(), tempWord.end());
                                        goto NOT;
                                    }
                                }
                              goto END;
                            }
                    }

                        //()()()()()
                      // if(ct1.formatText(tempWord) != false)
                    //{
                        notWords.push_back(ct1.getWord());
                        //tempWord.clear();
                        tempWord.erase(tempWord.begin(), tempWord.end());
                    //}
                        goto NOT;

}
                }
                break;
            }
           if(ct1.formatText(tempWord) != false  && tempWord != "") //if word is not a stop word and no prefix bool
            {

                words.push_back(ct1.getWord());
                //tempWord.clear();
                tempWord.erase(tempWord.begin(), tempWord.end());
            }
           //else
             //  stopWords.push_back(ct1.getWord());
        }

        else //if(nestedCheck(tempWord) == true) //- if nested query is found*************************************************
        {
            NESTED:
            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), '('), tempWord.end());  //gets rid of ( and )
            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());

                if(tempWord == "AND") //if AND is a prefix boolean
                {
                   // AND2:
                    while(input2 >> tempWord && tempWord != "NOT" && tempWord != "OR")
                    {
                        if(nestedCheck(tempWord) != false)
                        {
                            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                            andWords.push_back(tempWord);
                            tempWord.erase(tempWord.begin(), tempWord.end());
                            //break;
                            goto END;
                        }
                        else if(ct1.formatText(tempWord)!=false) // && (nestedCheck(tempWord) != true))
                        {
                            andWords.push_back(ct1.getWord());
                            tempWord.erase(tempWord.begin(), tempWord.end());
                        }
                    }
                }

                if(tempWord == "OR")
                {
                    //OR2:
                    while(input2 >> tempWord && tempWord != "NOT")// && tempWord != "AND")
                    {
                        if(ct1.formatText(tempWord) != false)
                        {
                            orWords.push_back(ct1.getWord());
                            //tempWord.clear();
                            tempWord.erase(tempWord.begin(), tempWord.end());
                        }
                        if(nestedCheck(tempWord) != false)
                        {
                            //orWords.push_back(tmp);
                            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                            orWords.push_back(tempWord);
                            tempWord.erase(tempWord.begin(), tempWord.end());
                           // break;
                            goto END;
                        }
                    }
                }

                if(tempWord == "NOT")
                {
                    while(input2 >> tempWord)
                    {
                        //if nested query is found

                        if(ct1.formatText(tempWord) != false)
                        {
                            //gets rid of )
                            notWords.push_back(ct1.getWord());
                            //tempWord.clear();
                            tempWord.erase(tempWord.begin(), tempWord.end());

                        }
                        //if word is not a stop word and no prefix bool
                        if(nestedCheck(tempWord) != false)
                        {
                            tempWord.erase(std::remove(tempWord.begin(), tempWord.end(), ')'), tempWord.end());
                            notWords.push_back(tempWord);
                            tempWord.erase(tempWord.begin(), tempWord.end());
                            goto END;
                        }
                        //if not a stop word

                    }
                    goto END;
                }

               if(ct1.formatText(tempWord) != false && tempWord != "") //if word is not a stop word and no prefix bool
                {
                    words.push_back(ct1.getWord());
                    tempWord.erase(tempWord.begin(), tempWord.end());
                }


        }

    }

    setWords(words);
    setAndWords(andWords);
    setOrWords(orWords);
    setNotWords(notWords);





    for(unsigned int i = 0; i < words.size(); i++)
    {
        cout << getWords()[i] << endl;
    }

    cout << endl <<"AND prefix: " << endl;

    for(unsigned int i = 0; i < andWords.size(); i++)
    {        cout <<getAndWords()[i] << endl; //andWords[i] << endl;
    }

    cout << endl <<"OR prefix: " << endl;

    for(unsigned int i = 0; i < orWords.size(); i++)
    {
        cout << getOrWords()[i] << endl;//orWords[i] << endl;
    }

    cout << endl <<"NOT prefix: " << endl;

    for(unsigned int i = 0; i < notWords.size(); i++)
    {
        cout << getNotWords()[i] << endl;  //notWords[i] << endl;
    }




    getAndWords();
    getOrWords();
    return true;
}



bool queryEngine::nestedCheck(string temp) //finds start/end of nested query
{

    char * writable = new char[temp.size() + 1];// + 1];
    std::copy(temp.begin(), temp.end(), writable);
    //writable[temp.size()] = '\0';

    int x = strlen(writable);

    for(int i = 0; i <= x ; i++)
    {
        if(writable[i] == '(')
        {
            //cout << "FOUND IT "<< writable<< endl;

            return true;
        }
        if(writable[i] == ')')
        {
            //cout << "FOUND IT "<< writable<< endl;

            return true;
        }

    }
    delete[] writable;
    return false;
}

bool queryEngine::wrongCheck(string temp)
{
    char * writable = new char[temp.size() + 1];// + 1];
    std::copy(temp.begin(), temp.end(), writable);
    //writable[temp.size()] = '\0';

    int x = strlen(writable);

    for(int i = 0; i <= x ; i++)
    {
        if(writable[i] == '(' && (i != 0))
        {
            //cout << "FOUND IT "<< writable<< endl;
            misspelled.push_back(temp);
            return true;
        }
        if(writable[i] == ')' && (i!= x-1))
        {
            //cout << "FOUND IT "<< writable<< endl;
            misspelled.push_back(temp);
            return true;
        }

    }
    delete[] writable;
    return false;
}

void queryEngine::setWords(vector<string> &w)
{
    this -> words = w;
}

vector<string> queryEngine::getWords()
{
    return this -> words;
}

void queryEngine::setAndWords( vector<string> &a)
{
  this -> andWords = a;

}

vector<string> queryEngine::getAndWords()
{

    return this -> andWords;

}

void queryEngine::setOrWords( vector<string> &o)
{
    this -> orWords =  o;
}

vector<string> queryEngine::getOrWords()
{

    return this -> orWords;
}

void queryEngine::setNotWords( vector<string> &n)
{
    this -> notWords = n;
}

vector<string> queryEngine::getNotWords()
{
    return this -> notWords;
}

void queryEngine::setW(vector<string> &x)
{
    this -> testw = x;
}

vector<string> queryEngine::getW()
{
    return this -> testw;
}


queryEngine::~queryEngine()
{

}
