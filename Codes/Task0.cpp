/*A normal Binary Search Tree (BST) can become unbalanced if values are inserted in sorted order, making it look like a linked list.
In that case, searching for a value becomes slower because we may have to check every node, taking O(n) time.
An AVL tree solves this problem by automatically balancing itself whenever a new value is inserted or deleted.
It uses rotations to make sure that the height difference between the left and right subtrees of every node is at most 1.
This keeps the tree balanced and ensures that searching, inserting and deleting values remain efficient, taking O(log n) time.*/

#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class AVLConverter{
public:
    int getHeight(Node* node){
        if (node == nullptr) return 0;
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
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

    Node* convertToAVL(Node* root){
        if (root == nullptr) return nullptr;

        root->left = convertToAVL(root->left);
        root->right = convertToAVL(root->right);

        int balance = getBalance(root);

        if (balance > 1) {
            if (getBalance(root->left) < 0){
                root->left = rotateLeft(root->left);
            }
            return rotateRight(root);
        }

        if (balance < -1) {
            if (getBalance(root->right) > 0){
                root->right = rotateRight(root->right);
            }
            return rotateLeft(root);
        }
        return root;
    }

    void printPreorder(Node* node){
        if (node == nullptr) return;
        cout << node->value << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
};

int main() {
    AVLConverter converter;

    Node* treeA = new Node(10);
    treeA->left = new Node(8);
    treeA->left->left = new Node(4);
    treeA->left->right = new Node(6);

    cout << "Tree A before: ";
    converter.printPreorder(treeA);
    cout << endl;

    treeA = converter.convertToAVL(treeA);
    cout << "Tree A after : ";
    converter.printPreorder(treeA);
    cout << endl;

    Node* treeB = new Node(10);
    treeB->right = new Node(16);
    treeB->right->left = new Node(12);
    treeB->right->right = new Node(18);

    cout << "Tree B before: ";
    converter.printPreorder(treeB);
    cout << endl;

    treeB = converter.convertToAVL(treeB);
    cout << "Tree B after : ";
    converter.printPreorder(treeB);
    cout << endl;

    return 0;
}

/* The recursion reaches 4 and 6 first.
They are leaves (height 1, balance 0), so each returns itself.
At 8, the left height is 1 and the right height is 1, so the balance is 0. It returns itself.
At 10, the left height is 2 and the right height is 0, so the balance is 2 (left heavy).
The left child 8 has balance 0, which is not negative, so this is a left-left case. It needs a single right rotation.
Inside rotateRight(10):
1. unbalancedNode = 10
2. newRoot = 8 (left child of 10).
3. movedSubtree = 6 (right child of 8).
4. Make 10 the right child of 8.
5. Make 6 the left child of 10..
Result:

      8
     / \
    4   10
        /
       6

Returned node: 8 (newRoot) is returned because it is now the root of this subtree.
main stores it with treeA = converter.convertToAVL(treeA), so the tree starts from 8 instead of the old root 10.       

*/