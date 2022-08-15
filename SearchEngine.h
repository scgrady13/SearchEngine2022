//
// Created by Sean Grady on 8/2/2022.
//

#ifndef SEARCHENGINE_SEARCHENGINE_H
#define SEARCHENGINE_SEARCHENGINE_H
#include "include/rapidjson/document.h"
#include "ParcerNew.h"
#include <string>
class SearchEngine {
private:
    ParcerNew parser;
public:
    void startEngine();
    void query();
};


#endif //SEARCHENGINE_SEARCHENGINE_H
