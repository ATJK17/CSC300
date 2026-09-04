#include "ll.h"

void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;

    if(index == 0)
    {
        newNode->next = head;
        head = newNode;
    }
    else
    {
        node* walker = head;
        int wIndex = 0;
        while(walker != NULL && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }
        if(walker == nullptr)
        {
            cout << "Index is too large, can't insert" << endl;
            return;
        }
        else
        {
            newNode->next = walker->next;
            walker->next = newNode;
        }

    }
}

void deleteNode(node *&head, int index) 
{
    // Check if the list is empty and there's nothing to delete
    //If theres no value at the first node then entire list is empty 
    if(head == nullptr)
    {
        cout << "List is Empty";
        return;
    }

    // Check if were are deleting at index 0 and handle accordingly
    if(index == 0)
    {
        node* temp = head;
        head = head->next;
        delete temp;
    }
    // Handle other index deletions
    else
    {
        //We walk to each node value
        node* walker = head;
        int wIndex = 0;

        //While we increment throguh the list while there are nodes and not att the ned of the index 
        while(walker != nullptr && wIndex < index-1)
        {
            walker = walker->next;
            wIndex++;
        }

        //If we encounter an empty space or out of bound from the list, there is nothing to delete
        if(walker == nullptr || walker->next == nullptr)
        {
            cout << "Index is too large, can't delete" << endl;
            return;
        }

        //If our index is not ) or out of range we delete the node
        else
        {
            node* temp = walker->next;
            walker->next = walker->next->next;
            delete temp;
        }
    }
}

void displayList(node *head) 
{
    node* walker = head;

    while(walker != nullptr)
    {
        cout << walker->data<<" ";
        walker = walker->next;
    }
    cout<<endl;

}

node* searchNode(node *head, int key) 
{
    //Start walker pointer so we mark the front of the list
    node* walker = head;

    //Go through the list oen node at a time unless we hit an empty space
    while(walker != nullptr)
    {

        //Check if the current node matches the value asked by user
        if(walker->data == key)
        {
            return walker;
        }
        //No match found we move to the next node to keep lookinh
        walker = walker->next;
    }

    return nullptr;
}

void reverseList(node *&head)
{
    //We use the three pointer strategy to have a node to track our initial node, 
    //then keep prev and next empty
    node* prev = nullptr;
    node* curr = head;
    node* next = nullptr;

    //While we have a node available we run the while loop
    while(curr != nullptr)
    {
        //Save the next node as our next node overwriting the nullptr
        next = curr->next;

        //Reverse the direction of pointer by pointing current node to prev
        curr->next = prev;

        //Shift both our pointers one step forward
        prev = curr;
        curr = next;
    }

    //Loop exits as prev now sits on the old last node
    head = prev;
}

