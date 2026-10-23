#include "reserve.h"

// Helper: size of a subtree (0 for an empty subtree)
// Defined before use so insert() and countPlanes() can call it
static int sizeOf(reservation* node)
{
    return node == nullptr ? 0 : node->subtreeSize;
}

reservation::reservation(int t) {
    time = t;
    left = nullptr;
    right = nullptr;
    subtreeSize = 1; // a new node is a leaf, so its subtree has 1 node
}

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clearTree(root);
}

// Post-order deletion of every node
void BST::clearTree(reservation* node)
{
    if (node == nullptr)
        return;

    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

// Reserve new landing time
bool BST::reserve(int time)
{
    if (checkConflict(root, time)) {
        return false; // conflict - reservation fails
    }

    insert(root, time);
    return true; // no conflict - reservation successful
}

// Check for landing time conflicts within 3 minutes (uses recursion)
bool BST::checkConflict(reservation* node, int time)
{
    // Base case: reached the end of the path with no conflict found
    if (node == nullptr)
        return false;

    // Catches duplicates and any time within 3 minutes of this node
    int diff = node->time - time;

    if (diff < 0)
        diff = -diff;

    if (diff < 3)
        return true;

    // Recursive case: follow the single path where a conflict could exist
    if (time < node->time)
        return checkConflict(node->left, time);

    return checkConflict(node->right, time);
}

// Insert new reservation and update subtree sizes (ignores duplicates)
void BST::insert(reservation*& node, int time)
{
    // Base case: found the spot, create the node (subtreeSize starts at 1)
    if (node == nullptr) {
        node = new reservation(time);
        return;
    }

    // Duplicate does nothing
    if (time == node->time)
        return;

    if (time < node->time)
        insert(node->left, time);
    else
        insert(node->right, time);

    // Update this node's subtree size on the way back up
    node->subtreeSize = 1 + sizeOf(node->left) + sizeOf(node->right);
}

// Count nodes with times <= t (uses recursion and subtree sizes)
int BST::countPlanes(reservation* node, int t)
{
    // Base case
    if (node == nullptr)
        return 0;

    // This node and its entire left subtree are <= t; check the right side
    if (node->time <= t)
        return 1 + sizeOf(node->left) + countPlanes(node->right, t);

    // This node is too late, so its right subtree is too; check the left side
    return countPlanes(node->left, t);
}

void BST::inorder(reservation* root)
{
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->time << " ";
    inorder(root->right);
}