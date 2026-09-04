#include "dll.h"

void insertNode(node *&head, int index, int data)
{
    node* newNode = new node;
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    //Inserting at the front
    if(index == 0)
    {
        newNode->next = head;

        //If list isnt empty then we can add the previous address
        if(head != nullptr)
        {
            head->prev = newNode;
        }

        head = newNode;
    }
    else
    {
        //Walk to the node of our target
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
        
        //Points our newNode forward to what the walker point to next
        newNode->next= walker->next;
        newNode->prev = walker;

        if(walker->next != nullptr)
        {
            walker->next->prev = newNode;
        }
        
        walker->next = newNode;
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
        
        //We will only delete if there are still nodes available
        if(head != nullptr)
        {
            head->prev = nullptr;
        }

        delete temp;
    }
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

        if(walker == nullptr)
        {
            cout << "Index is too large, can't delete" << endl;
            return;
        }

        //Helps reconnect the nodes around our delted node
        if(walker->prev != nullptr)
        {
            walker->prev->next = walker->next;
        }
        //If our index is not ) or out of range we delete the node
        if(walker->next != nullptr)
        {
            walker->next->prev = walker->prev;
        }
        delete walker;
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


