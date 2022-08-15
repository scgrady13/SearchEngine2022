//
// Created by Sean Grady on 8/9/2022.
//
#include "ParcerNew.h"

using namespace rapidjson;
void ParcerNew::readJSON(const string& path){
    loadStop();
    /*for each folder in jsons:
     * for each json file in folder:
     * load and parse title and content using the functions we alreay made
     */
//    int whenToStop = 0;
    for(const auto &fileName: filesystem::directory_iterator(path)) {
        if(fileName.path().extension() == ".json") {
            ifstream file(fileName.path().c_str());
            if (!file.is_open()) {
                cout << "didnt open input file" << endl;
                return;
            }
            ostringstream tmp;
            tmp << file.rdbuf();
            string content = tmp.str();
            Document d;
            d.Parse(content.c_str());
            //cout << d["title"].GetString() << endl;
            string title = d["title"].GetString();
            transform(title.begin(), title.end(), title.begin(), [](unsigned char c) {return tolower(c);});
            insertWords(title, title);
            string text = d["text"].GetString();
            transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {return tolower(c);});
            insertWords(text, title);
//            if(whenToStop++ == 10) break;
        }

    }
    wordsAVL.printTree();
}

void ParcerNew::loadStop() {
    ifstream inputStop;
    inputStop.open("../stopWords.txt");
    if(!inputStop.is_open()){
        cout << "didnt open stop words" << endl;
        return;
    }
    string word;
    while(getline(inputStop, word)){
        stopWords.insert(word);
    }
    //cout << "stopWordsSize: " << stopWords.size();
}
//void ParcerNew::insertPerson(string& data){
//    string current = "";
//    for(auto x : data) {
//        if(x == ' '){
//            personAVL.Insert(current, 0);
//            current = "";
//        } else current += x;
//    }
//}
//void ParcerNew::insertOrg(string& data){
//    string current = "";
//    for(auto x : data){
//        if(x == ' '){
//            orgAVL.Insert(current,0);
//            current = "";
//
//        } else current += x;
//    }
//}
void ParcerNew::insertWords(string& data, string title) {
    string current = "";
    for(auto x : data){
        if(x == ' '){
            if(stopWords.count(current) == 0){
                Porter2Stemmer::stem(current);
                wordsAVL.Insert(current, title);
            }
            current = "";
        } else current += x;
    }
    if(stopWords.count(current) == 0){
        Porter2Stemmer::stem(current);
        wordsAVL.Insert(current, title);
    }
}

void ParcerNew::searchParser(string &term) {
    auto answer = wordsAVL.search(term);
    if(answer == nullptr){
        cout << "No Documents Found Containing " << term << endl;
    }
    else{
        for(const auto& doc : answer->titles){
            cout << doc << endl;
        }
    }
}

void ParcerNew::andSearch(string &term1, string &term2) {
    unordered_map<string, int> overlap;
    auto answer1 = wordsAVL.search(term1);
    auto answer2 = wordsAVL.search(term2);
    if(answer1 == nullptr || answer2 == nullptr){
        cout << "No Documents Found Containing both " << term1 << " and " << term2 << endl;
    }
    else{
        for(const auto& doc : answer1->titles){
            overlap[doc]++;
        }
        for(const auto& doc : answer2->titles){
            overlap[doc]++;
        }
        for(const auto& entry : overlap){
            if(entry.second == 2){
                cout << entry.first << endl;
            }
        }
    }
}
