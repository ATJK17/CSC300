#include "bstA.h"

BST::BST(int size)
{
    capacity = size;
    tree = new int[capacity];
    for(int i = 0; i < size; i++)
        tree[i] = INT_MIN;
}

BST::~BST()
{
    delete[] tree;
}

int BST::leftChild(int index)
{
    return 2 * index + 1;
}

int BST::rightChild(int index)
{
    return 2 * index + 2;
}

int BST::parent(int index)
{
    return (index - 1) / 2;
}

void BST::insertI(int data)
{
    if(tree[0] == INT_MIN)
    {
        tree[0] = data;
        return;
    }

    int index = 0;

    while(index < capacity)
    {
        //duplicate check
        if(data == tree[index])
        {
            cout << data << " is a duplicate, not inserted" << endl;
            return;
        }

        if(data < tree[index])
        {
            if(leftChild(index) < capacity && tree[leftChild(index)] == INT_MIN)
            {
                tree[leftChild(index)] = data;
                return;
            }
            index = leftChild(index);
        } else {
            if(rightChild(index) < capacity && tree[rightChild(index)] == INT_MIN)
            {
                tree[rightChild(index)] = data;
                return;
            }
            index = rightChild(index);
        }
    }
}

void BST::insertR(int data)
{
    insertRhelper(0, data);
}

void BST::insertRhelper(int index, int data)
{
    // Base case
    if(index >= capacity)
        return;
    if(tree[index] == INT_MIN)
    {
        tree[index] = data;
        return;
    }

    if(data == tree[index])
    {
        cout << data << " is a duplicate, not inserted" << endl;
        return;
    }

    // Recursive case
    if (data < tree[index])
        insertRhelper(leftChild(index), data);
    else
        insertRhelper(rightChild(index), data);
}

bool BST::searchI(int data)
{
    int index = 0;

    while(index < capacity)
    {
        if(tree[index] == INT_MIN)
            return false;
        if(tree[index] == data)
            return true;
        if(data < tree[index])
            index = leftChild(index); 
        else
            index = rightChild(index);
    }

    return false;
}

bool BST::searchR(int data)
{
    return searchRhelper(0, data);
}

bool BST::searchRhelper(int index, int data)
{
    // Base case
    if(index >= capacity || tree[index] == INT_MIN)
        return false;
    if(tree[index] == data)
        return true;

    // Recursive case
    if(data < tree[index])
        return searchRhelper(leftChild(index), data);
    else
        return searchRhelper(rightChild(index), data);
}

void BST::preorder(int index) // C-L-R
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    cout << tree[index] << " ";
    preorder(leftChild(index));
    preorder(rightChild(index));
}

void BST::inorder(int index) // L-C-R
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    inorder(leftChild(index));
    cout << tree[index] << " ";
    inorder(rightChild(index));
}

void BST::postorder(int index) // L-R-C
{
    // base case
    if (index >= capacity || tree[index] == INT_MIN)
        return;

    // recursive case
    postorder(leftChild(index));
    postorder(rightChild(index));
    cout << tree[index] << " ";
}

void BST::printTree(int index, int depth = 0)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;
    
    printTree(rightChild(index), depth + 1);

    for(int i = 0; i < depth; i++)
        cout << "   "; // for indentation
    cout << tree[index] << endl;

    printTree(leftChild(index), depth + 1);
    
}

int BST::height(int index)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return -1;

    return 1 + max(height(leftChild(index)), height(rightChild(index)));
}

//Counts the nodes recursively by traversing the tree
int BST::countNodes(int index)
{

    //Base Case
    if(index >= capacity || tree[index] == INT_MIN)
        return 0;

    //Recursive Case
    return 1 + countNodes(leftChild(index)) + countNodes(rightChild(index));

}

//Checks the balance at every node using our heights
//Give Yes, Left-heavy or Right Heavy

string BST::isBalanced(int index)
{

    //Base Code
    if(index >= capacity || tree[index] == INT_MIN)
        return "Yes";
    
    int leftH = height(leftChild(index));
    int rightH = height(rightChild(index));

    //Imbalances at the nodes
    if(leftH - rightH > 1)
        return "Left-Heavy";
    if(rightH - leftH > 1)
        return "Right-Heavy";

    string leftResults = isBalanced(leftChild(index));

    if(leftResults != "Yes")
        return leftResults;

    return isBalanced(rightChild(index));
}

//Deletes data if present. Returns true if node was deleted
bool BST::deleteNode(int data)
{
    if(!searchR(data))
        return false;

    deleteHelper(0, data);
    return true;
}

//Recursively find the node holding the data, then we remove it
void BST::deleteHelper(int index, int data)
{
    if(index >= capacity || tree[index] == INT_MIN)
        return;

    if(data < tree[index])
        deleteHelper(leftChild(index), data);
    else if(data > tree[index])
        deleteHelper(rightChild(index), data);
    else   
        removeAt(index);
}

//Remove the node at the given index
void BST::removeAt(int index)
{
    int l = leftChild(index);
    int r = rightChild(index);

    bool hasLeft = (l < capacity && tree[l] != INT_MIN);
    bool hasRight = (r < capacity && tree[r] != INT_MIN);

    if(!hasLeft && !hasRight)
    {
        tree[index] = INT_MIN;
    }
    else if(!hasLeft)
    {
        moveSubtree(r, index);
    }
    else if(!hasRight)
    {
        moveSubtree(l,index);
    }
    else{
        //the leftmost node of the right subtree
        int succ = r;
        while(leftChild(succ) < capacity && tree [leftChild(succ)] != INT_MIN)
            succ = leftChild(succ);

        tree[index] = tree[succ];
        removeAt(succ);
    }
}

//Move the subtree rooted at the from so it is rooted at the to
void BST::moveSubtree(int from, int to)
{

    //Empty the source
    if(from >= capacity || tree[from] == INT_MIN)
    {
        tree[to] = INT_MIN;
        return;
    }

    int value = tree[from];
    tree[from] = INT_MIN;
    tree[to] = value;

    moveSubtree(leftChild(from), leftChild(to));
    moveSubtree(rightChild(from), rightChild(to));
}

//Breadth first traversal using custom string queue
void BST::BFS()
{

    if(tree[0] == INT_MIN)
    {
        cout << "Tree is empty";
        return;
    }

    Queue q;
    string start = to_string(0);
    q.enqueue(start);

    while(!q.isEmpty())
    {
        int index = stoi(q.dequeue());
        cout << tree[index] << " ";

        int l = leftChild(index);
        int r = rightChild(index);

        if(l < capacity && tree[l] != INT_MIN)
        {
            string ls = to_string(l);
            q.enqueue(ls);
        }

        if(r < capacity && tree[r] != INT_MIN)
        {
            string rs = to_string(r);
            q.enqueue(rs);
        }
    }
}