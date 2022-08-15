//
// Created by Sean Grady on 8/9/2022.
//

#ifndef SEARCHENGINE_PARCERNEW_H
#define SEARCHENGINE_PARCERNEW_H
#include "AVLTree.h"
#include <unordered_set>
#include <experimental/filesystem>
#include "include/rapidjson/filereadstream.h"
#include "porter2_stemmer.h"
#include <string>
#include <fstream>
#include "ParcerNew.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include "include/rapidjson/document.h"
#include <unordered_map>
class ParcerNew {
public:
    ParcerNew(){

    }
    void readFiles(string fileName);
    void readJSON(const string& fileName);
    void searchParser(string& term);
    void andSearch(string& term1, string& term2);
private:
    AVLTree wordsAVL;
    AVLTree personAVL;
    AVLTree orgAVL;
    unordered_set<string> stopWords;

//    void readJSON(string& fileName, string& title);
    inline void insertWords(string& data, string title);
    void loadStop();

    void insertOrg(string &data);

    void insertPerson(string &data);


};


#endif //SEARCHENGINE_PARCERNEW_H
