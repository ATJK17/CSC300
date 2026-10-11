#include "sqll.h"

using namespace std;

//======================= STACK ===========================

Stack::Stack()
{
    top = nullptr; 
}

Stack::~Stack() 
{
    while (!isEmpty()) 
    {
        pop();
    }
}

void Stack::push(string& value) 
{
    //Create a newn ode containing value
    listNode* newNode = new listNode(value);

    //Make new node point to whatever was on the top of the stack
    newNode->next = top;

    //Move the top pointer to the new node
    top = newNode;

}

string Stack::pop() 
{
    
    //Makes sure there is a top to delete 
    peek();

    //Create a temporary pointer to store top node
    listNode* temp = top;

    //Save the value before deleting the node
    string value = top->data;

    //Move the top to the next node
    top = top->next;
    
    //Delete the old node
    delete temp;

    //Returned removed value back
    return value;
}

string Stack::peek() 
{
    if (isEmpty()) 
    {
        throw runtime_error("Stack is empty");
    }

    return top->data;  
}

bool Stack::isEmpty() 
{
    return top == nullptr;
}

void Stack::display()
{
    listNode* current = top;
    cout << "Stack: ";
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

//======================= QUEUE ===========================

Queue::Queue()
{
    front = nullptr;
    rear = nullptr; 
}

Queue::~Queue() 
{
    while (!isEmpty()) 
    {
        dequeue();
    }
}

void Queue::enqueue(string& value) 
{
    
    //Create a new node containing the value
    listNode* newNode = new listNode(value);

    //Check if the queue is empty
    if(isEmpty())
    {
        //If it is empty, then the new node is both our front and rear
        front = newNode;
        rear = newNode;
    }
    //If queue is not empty
    else
    {
        //Connect the rear node to the new node
        rear->next = newNode;

        //Make the new node the new rear
        rear = newNode;
    }


}

string Queue::dequeue() 
{
    //Check if queue is empty
    if(isEmpty())
    {
        cout << "Queue is empty" << endl;
    }

    //Create a temporary pointer to store front node
    listNode* temp = front;

    //Save the value before deleting the node
    string value = front->data;

    //Move to the front of the next node
    front = front->next;

    //If the queue is currently empty, reset the rear pointer
    if(front == nullptr)
    {
        rear = nullptr;
    }

    //Delete the old front node
    delete temp;

    //Return the removed value
    return value;
}

bool Queue::isEmpty() 
{
    return front == nullptr;
}

void Queue::display()
{
    listNode* current = front;
    cout << "Queue: ";
    
    while (current != nullptr) 
    {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}
//======================= DIJKSTRA'S TWO STACK ===========================
double evaluateExpression(string& expr) 
{

    //Create a stack to store the operators    
    Stack operators;

    //Create a stack to store the numeric values
    Stack values;

    //We use stringstream to read each token from the expression
    stringstream ss(expr);
    string token;

    //Process each token in the expression
    while(ss >> token)
    {//Beginning of While Loop
        
        //We ignore the openning parenthesis
        if(token == "(")
        {

        }

        else if(token == "+" || token == "-" ||
                token == "*" || token == "/" ||
                token == "^")
        {
            //We push our operator token in the expression
            operators.push(token);
        }

        else if(token == ")")
        {

            string oper = operators.pop();

            double right = stod(values.pop());
            double left = stod(values.pop());

            double results;

            if(oper == "+")
                results = left + right;
            else if(oper == "-")
                results = left - right;
            else if(oper == "*")
                results = left * right;
            else if(oper == "/")
                results = left / right;
            else if(oper == "^")
                results = pow(left, right);

            string resultString = to_string(results);
            values.push(resultString);

        }

        else
        {
            values.push(token);
        }
    }//End of While Loop

    return stod(values.pop());
}

// ============= JOSEPHUS PROBLEM ===========================
void josephus(int n, int k) 
{
    
    //Create a new queue to store our soldiers
    Queue soldiers;

    //Add all soldiers to the queue
    for(int i = 1; i <=n; i++)
    {
        //Convert soldier number to a string
        string soldier = to_string(i);

        //Add the soldier to the queue
        soldiers.enqueue(soldier);
    }

    //Track how many soldiers are still alive
    int remaining = n;

    //Elimates soldiers until only one remains
    while(remaining > 1)
    {

        //Move the first k-1 soldiers to the back of the queue
        for(int i = 1; i < k; i++)
        {
            //Remove the soldier from the front
            string soldier = soldiers.dequeue();

            //Add the soldier to the back of the queue
            soldiers.enqueue(soldier);
        }

        //Remove the kth soldier from the queue
        string eliminated = soldiers.dequeue();

        //Display the soldier that was eliminated
        cout << "Soldier " << eliminated << " is eliminated." << endl;
 
        //Eliminates one soldier
        remaining--;

    }

    //Last soldier remaining is our survivor
    if(!soldiers.isEmpty())
    {
        cout << "Soldier " << soldiers.dequeue() << " survives." << endl;
    }
}