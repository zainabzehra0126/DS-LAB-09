#include <iostream>
using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;

    Node(int val){
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree{
public:
    Node* root;

    AVLTree(){
        root = nullptr;
    }

    int getHeight(Node* node){
        if (node == nullptr) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getBalance(Node* node){
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateRight(Node* unbalancedNode){
        Node* newRoot = unbalancedNode->left;
        Node* movedSubtree = newRoot->right;

        newRoot->right = unbalancedNode;
        unbalancedNode->left = movedSubtree;

        return newRoot;
    }

    Node* rotateLeft(Node* unbalancedNode){
        Node* newRoot = unbalancedNode->right;
        Node* movedSubtree = newRoot->left;

        newRoot->left = unbalancedNode;
        unbalancedNode->right = movedSubtree;

        return newRoot;
    }

    Node* insert(Node* node, int val){
        if (node == nullptr) return new Node(val);

        if (val < node->value)
            node->left = insert(node->left, val);
        else if (val > node->value)
            node->right = insert(node->right, val);
        else
            return node;

        int balance = getBalance(node);

        if (balance > 1 && val < node->left->value)
            return rotateRight(node);

        if (balance < -1 && val > node->right->value)
            return rotateLeft(node);

        if (balance > 1 && val > node->left->value){
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && val < node->right->value){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    void insert(int val){
        root = insert(root, val);
    }

    void rotateRootLeft(){
        if (root != nullptr && root->right != nullptr){
            root = rotateLeft(root);
        }
    }

    void printPreorder(Node* node){
        if (node == nullptr) return;
        cout << node->value << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }

    void printInorder(Node* node){
        if (node == nullptr) return;
        printInorder(node->left);
        cout << node->value << " ";
        printInorder(node->right);
    }
};

int main(){
    AVLTree tree;

    int values[] = {10, 5, 15, 3, 7};
    for (int i=0; i<5; i++) {
        tree.insert(values[i]);
    }

    cout << "preorder" << endl;
    cout << "Before inserting 55: ";
    tree.printPreorder(tree.root);
    cout << endl;

    tree.insert(55);
    cout << "preorder" << endl;
    cout << "After inserting 55: ";
    tree.printPreorder(tree.root);
    cout << endl;

    tree.rotateRootLeft();
    cout << "preorder" << endl;
    cout << "After left rotation: ";
    tree.printPreorder(tree.root);
    cout << endl;

    cout << "preorder" << endl;
    cout << "After left rotation: ";
    tree.printInorder(tree.root);
    cout << endl;

    return 0;
}