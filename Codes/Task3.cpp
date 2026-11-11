/* NOTE: I WAS NOT SURE WHETHER TO ONLY DRY RUN OR WRITE C++ CODE, SO I AM DOING BOTH.
Tree values: 10, 5, 15, 3, 7, then insert 12

After insertion of 10:
    10
After insertion of 5:
      10
     /
    5
After insertion of 15:
      10
     /  \
    5    15
After insertion of 3:
      10
     /  \
    5    15
   /
  3
After insertion of 7:
      10
     /  \
    5    15
   / \
  3   7
(All balance factors are 0. No rotation.)
Now for inserting 12:
Steps:
12 > 10, so go right.
12 < 15, so go left. 15 has no left child, so 12 becomes the left child of 15.
      10
     /  \
    5    15
   / \   /
  3   7 12


Balance factor of every node
Node 3: left height 0, right height 0, factor 0.
Node 7: left height 0, right height 0, factor 0.
Node 12: left height 0, right height 0, factor 0.
Node 5: left height 1, right height 1, factor 0.
Node 15: left height 1, right height 0, factor +1.
Node 10: left height 2, right height 2, factor 0.

Height of the tree
Height: 2
*/
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

        if (balance > 1 && val < node->left->value){
            cout << "Unbalanced at " << node->value << ": right rotation" << endl;
            return rotateRight(node);
        }

        if (balance < -1 && val > node->right->value){
            cout << "Unbalanced at " << node->value << ": left rotation" << endl;
            return rotateLeft(node);
        }

        if (balance > 1 && val > node->left->value){
            cout << "Unbalanced at " << node->value << ": left-right rotation" << endl;
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && val < node->right->value){
            cout << "Unbalanced at " << node->value << ": right-left rotation" << endl;
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void insert(int val){
        root = insert(root, val);
        cout << "Inserted " << val << endl;
    }

    void printBalanceFactors(Node* node){
        if (node == nullptr) return;
        printBalanceFactors(node->left);
        cout << "Node " << node->value << " : balance factor: " << getBalance(node) << endl;
        printBalanceFactors(node->right);
    }

    void printPreorder(Node* node){
        if (node == nullptr) return;
        cout << node->value << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
};

int main(){
    AVLTree tree;

    int values[] = {10, 5, 15, 3, 7};
    for (int i=0; i<5; i++) {
        tree.insert(values[i]);
    }

    cout << endl << "Inserting 12" << endl;
    tree.insert(12);

    cout << endl;
    tree.printBalanceFactors(tree.root);

    cout << endl << "Edges: " << tree.getHeight(tree.root) - 1 << endl;
    cout << "Nodes: " << tree.getHeight(tree.root) << endl;

    cout << endl << "Final Tree Preorder: ";
    tree.printPreorder(tree.root);
    cout << endl;

    return 0;
}