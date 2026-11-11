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

class AVLTree {
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

    int countNodes(Node* node){
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
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

    void findKthSmallest(Node* node, int k, int& count, Node*& result){
        if (node == nullptr || result != nullptr) return;

        findKthSmallest(node->left, k, count, result);

        count++;
        if (count == k){
            result = node;
            return;
        }

        findKthSmallest(node->right, k, count, result);
    }

    void findKthLargest(Node* node, int k, int& count, Node*& result){
        if (node == nullptr || result != nullptr) return;

        findKthLargest(node->right, k, count, result);

        count++;
        if (count == k){
            result = node;
            return;
        }

        findKthLargest(node->left, k, count, result);
    }

    void printPreorder(Node* node){
        if (node == nullptr) return;
        cout << node->value << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
};

int main() {
    AVLTree tree;

    int values[] = {10, 5, 15, 3, 7, 12, 23, 100, 25};
    for (int v : values) {
        tree.insert(v);
    }
    int totalNodes = tree.countNodes(tree.root);

    cout << "Tree (preorder): ";
    tree.printPreorder(tree.root);
    cout << endl;
    cout << "Total nodes: " << totalNodes << endl << endl;

    int k;
    cout << "Enter the value of k (1 to " << totalNodes << "): ";
    cin >> k;

    if (k < 1 || k > totalNodes){
        cout << "Invalid k. It must be between 1 and " << totalNodes << "." << endl;
        return 0;
    }

    int smallestCount = 0;
    Node* smallestNode = nullptr;
    tree.findKthSmallest(tree.root, k, smallestCount, smallestNode);

    int largestCount = 0;
    Node* largestNode = nullptr;
    tree.findKthLargest(tree.root, k, largestCount, largestNode);

    cout << endl;
    cout << k << "th smallest key: " << smallestNode->value << endl;
    cout << k << "th largest key : " << largestNode->value << endl;

    cout << endl;
    cout << "Left side height of root : " << tree.getHeight(tree.root->left) << endl;
    cout << "Right side height of root: " << tree.getHeight(tree.root->right) << endl;

    return 0;
}