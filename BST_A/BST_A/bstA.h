#ifndef BSTA_H
#define BSTA_H
#include "sqll.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <climits>

using namespace std;

class BST
{
    private:
        int* tree;
        int capacity;

        int leftChild(int index);
        int rightChild(int index);
        int parent(int index);

        void deleteHelper(int index, int data);
        void removeAt(int index);
        void moveSubtree(int from, int to);

    public:
        BST(int size);
        ~BST();

        void BFS();

        void insertI(int data);
        void insertR(int data);
        void insertRhelper(int index, int data);

        bool searchI(int data);
        bool searchR(int data);
        bool searchRhelper(int index, int data);

        void preorder(int index = 0);
        void inorder(int index = 0);
        void postorder(int index = 0);

        void printTree(int index, int depth);
        
        int height(int index = 0);
        int countNodes(int index = 0);

        string isBalanced(int index = 0);

        bool deleteNode(int data);
};

#endif