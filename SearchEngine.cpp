//
// Created by Sean Grady on 8/2/2022.
//

#include "SearchEngine.h"

void SearchEngine::startEngine() {
    cout << "Please give the direct path to the file" << endl;
    string path;
    getline(cin, path);
    parser.readJSON(path);
}

void SearchEngine::query() {
    cout << "Enter a search or 'q' to quit" << endl;
    string term;
    getline(cin, term);
    transform(term.begin(), term.end(), term.begin(), [](unsigned char c) {return tolower(c);});

    while(term != "q"){
        //search logic
        if(term.substr(0,4) == "and "){
            int spot = 4;
            while(term[++spot] != ' ' && spot < term.length());
            string term1 = term.substr(4, spot-4);
            string term2 = term.substr(spot+1, term.length()-spot-1);
            Porter2Stemmer::stem(term1);
            Porter2Stemmer::stem(term2);
            parser.andSearch(term1, term2);
        } else{
            Porter2Stemmer::stem(term);
            parser.searchParser(term);
        }
        cout << "Enter a search or 'q' to quit" << endl;
        getline(cin, term);
    }
}
