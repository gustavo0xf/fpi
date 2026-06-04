#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* createNode(int value) {
    Node* newNode = (Node *) malloc(sizeof(Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int value) {
    if (root == NULL) return createNode(value);
    if (value < root->data) root->left = insertNode(root->left, value);
    else if (value > root->data) root->right = insertNode(root->right, value);
    return root;
}

void preOrder(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

void postOrder(Node* root) {
    if (root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

int treeHeight(Node* root) {
    if (!root) return -1;
    int leftHeight = treeHeight(root->left);
    int rightHeight = treeHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int getMin(Node* root) {
    while (root->left) root = root->left;
    return root->data;
}

int getMax(Node* root) {
    while (root->right) root = root->right;
    return root->data;
}

void printReport(Node *root) {
    if (!root) {
            printf("ARVORE VAZIA\n");
    } else {
            printf("PREORDEM: "); preOrder(root); printf("\n");
            printf("EMORDEM: "); inOrder(root); printf("\n");
            printf("POSORDEM: "); postOrder(root); printf("\n");
            printf("NOS: %d\n", countNodes(root));
            printf("FOLHAS: %d\n", countLeaves(root));
            printf("ALTURA: %d\n", treeHeight(root));
            printf("MENOR: %d\n", getMin(root));
            printf("MAIOR: %d\n", getMax(root));
    }
}

int main() {
    Node *root = NULL;
    int value;

    while (scanf("%d", &value) == 1 && value != -1) {
        root = insertNode(root, value);
    }

    printReport(root);

    return 0;
}
