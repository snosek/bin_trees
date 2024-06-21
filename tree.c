#include <stdio.h>
#include <stdlib.h>

//#define update_height(A) (A->height = 1 + (height(A->left) > height(A->right) ? height(A->left) : height(A->right)))

typedef struct Node_{
    int data;
    struct Node_ *left, *right;
    int height;
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
    new_node->height = 1;
    return new_node;
}

int height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

void update_height(Node *A) {
    A->height = 1 + (height(A->left) > height(A->right) ? height(A->left) : height(A->right));
}

Node *rotate_right(Node* A) {
    Node* B = A->left;
    Node* C = B->right;

    // rotation
    B->right = A;
    A->left = C;

    update_height(A);
    update_height(B);

    return B;
}

Node *rotate_left(Node* A) {
    Node *B = A->right;
    Node *T2 = B->left;

    // rotation
    B->left = A;
    A->right = T2;

    update_height(A);
    update_height(B);
    return B;
}

int get_balance(Node* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

Node *balance_tree(Node* node, int data) {
    int balance = get_balance(node);
    // cases
    if (balance > 1 && data < node->left->data) {
        node = rotate_right(node);
    } else if (balance < -1 && data > node->right->data) {
        node = rotate_left(node);
    } else if (balance > 1 && data > node->left->data) {
        node->left = rotate_left(node->left);
        node = rotate_right(node);
    } else if (balance < -1 && data < node->right->data) {
        node->right = rotate_right(node->right);
        node = rotate_left(node);
    }
    return node;
}

Node *insert(Node* node, int data) {
    if (node == NULL) {
        return init_node(data);
    }
    if (data == node->data) {
        return node;
    }
    if (data < node->data){
        node->left = insert(node->left, data);
    } else if (data > node->data) {
        node->right = insert(node->right, data);
    }
    update_height(node);
    node = balance_tree(node, data);

    return node;
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
