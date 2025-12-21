/* 
 * File:   AVL.h
 * Author: Shawn Garello
 * Created on June 11, 2025, 6:14 PM
 *           
 */
#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <queue> // for level order trav.
#include "Node.h"
using namespace std;

class AVL {
public:
    Node* root = nullptr;

    Node* insert(Node*, int);
    Node* remove(Node*, int);
    Node* findMin(Node*);

    // rotate and balance
    Node* rLeft(Node*);
    Node* rRight(Node*);
    Node* balance(Node*);

    // Traversals
    void inorder(Node*);
    void preordr(Node*);
    void pstordr(Node*);
    void lvlordr(Node*);

    void display(Node*, int);
    int height(Node*);
    int blncFcr(Node*);   
    void updtHt(Node*);
};

int AVL::height(Node* n){ return n ? n->height : 0; }

int AVL::blncFcr(Node* n){ return n ? height(n->left) - height(n->right) : 0; }
// update height
void AVL::updtHt(Node* n){ if(n) n->height = 1 + max(height(n->left), height(n->right)); }

Node* AVL::rRight(Node* y){
    Node* x = y->left;
    Node* t2 = x->right;
    x->right = y;
    y->left = t2;
    updtHt(y);
    updtHt(x);
    return x;
}

Node* AVL::rLeft(Node* x){
    Node* y = x->right;
    Node* t2 = y->left;
    y->left = x;
    x->right = t2;
    updtHt(x);
    updtHt(y);
    return y;
}

Node* AVL::balance(Node* n){
    if(!n) return n;
    updtHt(n);
    int bf = blncFcr(n);
    if(bf > 1){ // left heavy
        if(blncFcr(n->left) < 0) n->left = rLeft(n->left);
        return rRight(n);
    }
    if(bf < -1){ // right heavy
        if(blncFcr(n->right) > 0) n->right = rRight(n->right);
        return rLeft(n);
    }
    return n;
}

Node* AVL::insert(Node* node, int key){
    if(!node) return new Node(key);
    if(key < node->key) node->left = insert(node->left, key);
    else if(key > node->key) node->right = insert(node->right, key);
    return balance(node);
}

Node* AVL::findMin(Node* node){ 
    while(node && node->left) node = node->left; 
    return node; 
}

Node* AVL::remove(Node* node, int key){
    if(!node) return nullptr;
    if(key < node->key) node->left = remove(node->left, key);
    else if(key > node->key) node->right = remove(node->right, key);
    else{ // node has 0 or 1 child
        if(!node->left || !node->right){
            Node* temp = node->left ? node->left : node->right;
            if(!temp){
                delete node; 
                return nullptr;
            }
            else{
                delete node;
                return temp; 
            }
        }
        // node has 2 children
        Node* succ = findMin(node->right);
        node->key = succ->key;
        node->right = remove(node->right, succ->key);
    }
    return balance(node);
}

// Traversals
void AVL::inorder(Node* n){
    if(!n) return;
    inorder(n->left);
    cout << n->key << " ";
    inorder(n->right);
}

void AVL::preordr(Node* n){
    if(!n) return;
    cout << n->key << " ";
    preordr(n->left);
    preordr(n->right);
}

void AVL::pstordr(Node* n){
    if(!n) return;
    pstordr(n->left);
    pstordr(n->right);
    cout << n->key << " ";
}

void AVL::lvlordr(Node* n){
    if(!n) return;
    queue<Node*> q;
    q.push(n);
    while (!q.empty()) {
        Node* cur = q.front(); 
        q.pop();
        cout << cur->key << " ";
        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}
#endif