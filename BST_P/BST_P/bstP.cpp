#include "bstP.h"

node::node(int value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

void BST::clearTree(node* node)
{
    if(node == nullptr)
        return;
    
    clearTree(node->leftChild);
    clearTree(node->rightChild);
    delete node;
}

void BST::insertNode(node*& root, int data)
{
    if(root == nullptr)
    {
        root = new node(data);
        return;
    }

    if(data < root->data)
        insertNode(root->leftChild, data);
    else if(data > root->data)
        insertNode(root->rightChild, data);
    else   
        cout << data << " is a duplicate, not inserted" << endl;
}

node* BST::searchNode(node*& root, int data)
{
    if (root == nullptr || root->data == data)
        return root;
    if (data < root->data)
        return searchNode(root->leftChild, data);
    return searchNode(root->rightChild, data);
}

void BST::deleteNode(node*& root, int data)
{
    if (root == nullptr)
        return;

    if (data < root->data)
        deleteNode(root->leftChild, data);
    else if (data > root->data)
        deleteNode(root->rightChild, data);
    else {
        if (root->leftChild == nullptr) {
            node* temp = root->rightChild;
            delete root;
            root = temp;
        }
        else if (root->rightChild == nullptr) {
            node* temp = root->leftChild;
            delete root;
            root = temp;
        }
        else {
            node* temp = root->rightChild;
            while (temp->leftChild != nullptr)
                temp = temp->leftChild;
            root->data = temp->data;
            deleteNode(root->rightChild, temp->data);
        }
    }
}

void BST::preorder(node* root)
{
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->leftChild);
    preorder(root->rightChild);
}

void BST::inorder(node* root)
{
    if (root == nullptr)
        return;
    inorder(root->leftChild);
    cout << root->data << " ";
    inorder(root->rightChild);
}

void BST::postorder(node* root)
{
    if (root == nullptr)
        return;
    postorder(root->leftChild);
    postorder(root->rightChild);
    cout << root->data << " ";
}


void BST::printTree(node* root, int space)
{
    const int COUNT = 10;
    if (root == nullptr)
        return;
    space += COUNT;
    printTree(root->rightChild, space);
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->data << endl;
    printTree(root->leftChild, space);
}

int BST::height(node* root)
{
    if(root == nullptr)
        return -1;
    return 1 + max(height(root->leftChild), height(root->rightChild));

}

//Counts nodes recursively by traversing the tree
int BST::countNodes(node * root)
{

    //Base Case
    if(root == nullptr)
        return  0;

    //Recursive Case
    return 1 + countNodes(root->leftChild) + countNodes(root->rightChild);

}

// Checks balance at every node using freshly computed heights.
// Returns Yes, Left-heavy, or Right-heavy
string BST::isBalanced(node* root)
{

    //Base Case
    if(root == nullptr)
        return "Yes";

    int leftH = height(root->leftChild);
    int rightH = height(root->rightChild);

    if(leftH - rightH > 1)
        return "Left-Heavy";
    if(rightH - leftH > 1)
        return "Right-Heavy";

    string leftResult = isBalanced(root->leftChild);

    if(leftResult != "Yes")
        return leftResult;

    return isBalanced(root->rightChild);
}

//Breadth first traversal
void BST::BFS(node* root)
{
    if(root == nullptr)
    {
        cout << "Tree is empty";
        return;
    }

    Queue q;
    string rootVal = to_string(root->data);
    q.enqueue(rootVal);

    while(!q.isEmpty())
    {
        int value = stoi(q.dequeue());
        node* current = searchNode(root, value);
        cout << current->data << " ";

        if(current->leftChild != nullptr)
        {
            string ls = to_string(current->leftChild->data);
            q.enqueue(ls);
        }
        if(current->rightChild != nullptr)
        {
            string rs = to_string(current->rightChild->data);
            q.enqueue(rs);
        }
    }
}