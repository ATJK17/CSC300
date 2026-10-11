#include "bstP.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Usage: ./a <filename>" << endl;
        return 1;
    }

    string filename = argv[1];
    BST tree;

    ifstream infile(filename);
    if (!infile) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        int command, data;

        if (!(iss >> command)) {
            cerr << "Invalid command format." << endl;
            continue;
        }

        switch (command) {
            case 0:
                cout << "Exiting...!" << endl;
                return 0;
            case 1:
                if (iss >> data) {
                    tree.insertNode(tree.root, data);
                    cout << "Insert: " << data << endl;
                } else {
                    cerr << "Invalid insert command." << endl;
                }
                break;
            case 2:
                if (iss >> data) {
                    node* result = tree.searchNode(tree.root, data);
                    cout << (result ? "Found: " + to_string(data) : "Not found") << endl;
                } else {
                    cerr << "Invalid search command." << endl;
                }
                break;
            case 3:
                if (iss >> data) {
                    tree.deleteNode(tree.root, data);
                    cout << "Deleted: " << data << endl;
                } else {
                    cerr << "Invalid delete command." << endl;
                }
                break;
            case 4:
                cout << "Inorder traversal: ";
                tree.inorder(tree.root);
                cout << endl;
                break;
            case 5:
                cout << "Preorder traversal: ";
                tree.preorder(tree.root);
                cout << endl;
                break;
            case 6:
                cout << "Postorder traversal: ";
                tree.postorder(tree.root);
                cout << endl;
                break;
            case 7:
                cout << "Binary Search Tree" << endl;
                tree.printTree(tree.root, 0);
                cout << endl;
                break;
            case 8:
                cout << "Height: " << tree.height(tree.root) << endl;
                break;
            case 9:
                cout << "Node count: " << tree.countNodes(tree.root) << endl;
                break;
            case 10:
                cout << "Balanced: " << tree.isBalanced(tree.root) << endl;
                break;
            default:
                cerr << "Invalid command." << endl;
        }
    }

    return 0;
}
