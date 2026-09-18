#include "sqll.h"

int main()
{
    Stack stack;
    Queue queue;
    int choice;
    string data, popped, dequeued, expr;
    double result;
    int n, k;

    do {
        cout << "\n===== Pick one =====" << endl;
        cout << "1. Push" << endl;
        cout << "2. Pop" << endl;
        cout << "3. Enqueue" << endl;
        cout << "4. Dequeue" << endl;
        cout << "5. Evaluate an expression" << endl;
        cout << "6. Solve Josephus's Problem" << endl;
        cout << "7. Exit" << endl;

        cin >> choice;
        cin.ignore(); // flush newline

        switch(choice)
        {
            case 1: 
                cout << "Enter value to push: ";
                cin >> data;
                stack.push(data);
                break;
            case 2: 
                if (!stack.isEmpty()) {
                    popped = stack.pop();
                    cout << "Popped: " << popped << endl;
                } else {
                    cout << "Stack is empty." << endl;
                }
                break;
            case 3: 
                cout << "Enter a value to enqueue";
                cin >> data;
                queue.enqueue(data);
                break;
            case 4: 
                if (!stack.isEmpty()) {
                    dequeued = queue.dequeue();
                    cout << "Dequeued: " << dequeued << endl;
                } else {
                    cout << "Queue is empty." << endl;
                }
                break;
            case 5:
                cout << "Enter fully parenthesized expression (space-separated): ";
                getline(cin, expr);
                result = evaluateExpression(expr);
                cout << "Result: " << result << endl;
                break;
            case 6: 
                cout << "Enter number of people (n): ";
                cin >> n;
                cout << "Enter step count (k): ";
                cin >> k;
                cin.ignore();
                josephus(n, k);
                break;
            case 7:
                cout << "Exiting program. Bye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }

        cout << "\nCurrent Stack: ";
        stack.display();
        cout << "\nCurrent Queue: ";
        queue.display();

    } while(choice != 7);

    return 0;
}