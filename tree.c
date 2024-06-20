#include <stdio.h>
#include <stdlib.h>

typedef struct Node_{
    int data;
    struct Node_ *left, *right;
} Node;

Node *init_node(int data) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("Error in creating new node");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Node *insert(Node *root, int data) {
    if (root == NULL) {
        return init_node(data);
    }
    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else if (data >= root->data){
        root->right = insert(root->right, data);
    }
    return root;
}

void print_tree(Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        print_tree(root->left);
        print_tree(root->right);
    }
}

int main(void) {
    Node *root = init_node(7);
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 9);
    root = insert(root, 8);
    root = insert(root, 10);
    print_tree(root);
    return 0;
}
