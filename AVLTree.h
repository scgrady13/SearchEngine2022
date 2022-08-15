//
// Created by Sean Grady on 8/2/2022.
//

#ifndef INC_22S_FINAL_PROJECT_SEAM_GRADY_AVLTREE_H
#define INC_22S_FINAL_PROJECT_SEAM_GRADY_AVLTREE_H
#include <string>
#include <iostream>
#include <set>
using namespace std;
class AVLTree {
private:
    struct Node {

        string word;
        int count = 1;
        int height = 0;
        Node* right;
        Node* left;
        set<string> titles;
        Node(){

        }
        Node(string wordIn){
            word = wordIn;
            left = nullptr;
            right = nullptr;
        }
        ~Node(){

        }
//        void setDocID(string& title) {titles.insert(title);}
    };
    Node* root = nullptr;
    int nodeCount{0};

    void PrivateInsert(string &data, Node*& t, string& title){

        if(t == nullptr) {
            t = new Node(data);
            t->titles.insert(title);
            nodeCount++;
        } else if(data < t->word) {
            PrivateInsert(data, t->left, title);
        } else if(data > t->word) {
            PrivateInsert(data, t->right, title);
        } else {
            t->count++;
            t->titles.insert(title);
        }
        balance(t);
    }
    int getHeight(Node*& t){
        if(root == nullptr) {
            return -1;
        }
        else return root->height;
    }
    void balance(Node*& t){
        //case 1or2
        if(getHeight(t->left) - getHeight(t->right) > 1) {
            if(getHeight(t->left->left) >= getHeight(t->left->right)) {
                Node *temp = new Node();
                temp = t->left;
                t->left = temp->right;
                temp->right = t;
                t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
                t = temp;
                //case2
            } else {
                Node *temp = new Node();
                temp = t->left->right;
                t->left->right = temp->left;
                temp->left = t->right;
                t->left->height = max(getHeight(t->left->right), getHeight(t->left->left)) + 1;
                t->left = temp;
                temp = t->left;
                t->left = temp->right;
                temp->right = t;
                t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
                t = temp;
            }
        }
        else if(getHeight(t->right) - getHeight(t->left) > 1) {
            //case 3
            if(getHeight(t->right->left) >= getHeight(t->right->right)) {
                Node *temp = new Node();
                temp = t->right->left;
                t->right->left = temp->right;
                temp->right = t->right;
                t->right->height = max(getHeight(t->right->left), getHeight(t->right->right)) + 1;
                t->right = temp;
                temp = t->right;
                t->right = temp->left;
                temp->left = t;
                t->height = max(getHeight(t->right), getHeight(t->left));
                t = temp;
            }
            else {
                Node *temp = new Node();
                temp = t->right;
                t->right = temp->left;
                temp->left = t;
                t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
                t = temp;
            }
        }
        t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
    }
    void privatePrint(Node *& t){

        if(t != nullptr) {
            privatePrint(t->left);
            cout << t->word << " " << t->count << endl;
            privatePrint(t->right);
        }
    }
    Node* privateSearch(Node*& root, string& term){
        if(root == nullptr) return nullptr;
        if(root->word == term){
            return root;
        }
        else if(term < root->word){
            return privateSearch(root->left, term);
        }
        else {
            return privateSearch(root->right, term);
        }
    }
public:
    AVLTree(){
        root = nullptr;
    }
    AVLTree(const AVLTree&);
    void Insert(string&, string&);
    void printTree(){
        //privatePrint(root);
        cout << "qty: " <<  nodeCount << endl;
    }
    Node* search(string& term){
        return privateSearch(root, term);
    }
};


#endif //INC_22S_FINAL_PROJECT_SEAM_GRADY_AVLTREE_H
