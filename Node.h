/* 
 * File:   Node.h
 * Author: Shawn Garello
 * Created on June 11, 2025, 6:14 PM
 *           
 */
#ifndef NODE_H
#define NODE_H

struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 1;
    Node(int k){
        key = k;
    }
};

#endif