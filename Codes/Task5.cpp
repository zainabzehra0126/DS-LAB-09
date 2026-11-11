#include <iostream>
using namespace std;

class Node{
public:
    int data;
    Node* left;
    Node* right;

    Node(int d){
        data = d;
        left = NULL;
        right = NULL;
    }
};

int arr[100];
int n = 0;

int height(Node* root){
    if (root == NULL)
        return 0;

    int lh = height(root->left);
    int rh = height(root->right);
    if (lh > rh)
        return lh + 1;
    else
        return rh + 1;
}

bool isBalanced(Node* root){
    if (root == NULL)
        return true;

    int diff = height(root->left) - height(root->right);

    if (diff > 1 || diff < -1)
        return false;

    return isBalanced(root->left) && isBalanced(root->right);
}

void inorder(Node* root){
    if (root == NULL)
        return;

    inorder(root->left);
    arr[n] = root->data;
    n++;
    inorder(root->right);
}

void sortArray(){
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

Node* buildTree(int start, int end){
    if (start > end)
        return NULL;

    int mid = (start + end) / 2;

    Node* root = new Node(arr[mid]);
    root->left = buildTree(start, mid - 1);
    root->right = buildTree(mid + 1, end);

    return root;
}

void preorder(Node* root){
    if (root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

Node* balanceBST(Node* root){
    n = 0;
    inorder(root);
    sortArray();

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return buildTree(0, n - 1);
}

void solve(Node* root, string name){
    cout << name << endl;

    cout << "Preorder initial tree: ";
    preorder(root);
    cout << endl;

    if (isBalanced(root))
        cout << "Tree is balanced" << endl;
    else
        cout << "Tree is unbalanced" << endl;

    Node* newRoot = balanceBST(root);

    cout << "Preorder final tree: ";
    preorder(newRoot);
    cout << endl;

    if (isBalanced(newRoot))
        cout << "Tree is balanced now" << endl;
    else
        cout << "Tree is still unbalanced" << endl;

    cout << endl;
}

int main() {
    Node* treeA = new Node(10);
    treeA->left = new Node(8);
    treeA->left->left = new Node(4);
    treeA->left->right = new Node(6);

    Node* treeB = new Node(10);
    treeB->right = new Node(16);
    treeB->right->left = new Node(12);
    treeB->right->right = new Node(18);

    solve(treeA, "Tree A");
    solve(treeB, "Tree B");

    return 0;
}