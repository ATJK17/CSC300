#ifndef SQLL_H
#define SQLL_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>

using namespace std;

struct node 
{
    string data;
    node* next;
    
    node(string &value) 
    {
        data = value; 
        next = nullptr;
    }
};

class Stack 
{
    private:
        node* top;
    public:
        Stack();
        ~Stack();

        void push(string &value);
        string pop();
        string peek();
        bool isEmpty();
        void display();
};

class Queue 
{
    private:
        node* front;
        node* rear;
    public:
        Queue();
        ~Queue();
        
        void enqueue(string &value);
        string dequeue();
        bool isEmpty();
        void display();
};


void josephus(int n, int k);
double evaluateExpression(string& expr);

#endif