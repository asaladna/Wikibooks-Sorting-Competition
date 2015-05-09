#ifndef CLEANTEXT_H
#define CLEANTEXT_H

#include "AvlTree.h"

#include "stem/stemming.h"
#include "stem/common_lang_constants.h"
#include "stem/english_stem.h"
#include "stem/meta.h"
#include "stem/punctuation.h"
#include "stem/string_util.h"
#include "stem/utilities.h"

#include <sstream>

#include <ctype.h>
#include <stdio.h>
#include <sstream>
#include <string>
#include <unordered_map>




class cleantext
{
public:
    cleantext();
    ~cleantext();

    bool formatText(std::string text);
    std::string stem(std::string stemWord);

    void setWord(std::string stemmedWord);
    std::string getWord();



private:
    //AvlTree<string, char*, std::unordered_map<char*,unsigned int>>* t;
    std::unordered_map<string,string> stopWords;

    std::string stemmedWord;



};

#endif // CLEANTEXT_H
