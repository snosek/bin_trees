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

void shuffle(int *array, size_t n)
{
    if (n <= 1) {
        return;
    }
    size_t i;
    for (i = 0; i < n - 1; i++) {
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

int main(void) {
    size_t size = 50;
    int a[size];
    for (int i = 0; i<size; i++){
        a[i] = i;
    }
    shuffle(a, size);
    Node *root = init_node(1);
    for (int i = 1; i<size; i++){
        root = insert(root, a[i]);
    }
    print_tree(root);
    return 0;
}
