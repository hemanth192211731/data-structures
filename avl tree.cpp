#include <stdio.h>
#include <stdlib.h>

// Structure for AVL Tree Node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

// Function to get the height of a node
int getHeight(struct Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int getBalance(struct Node* node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to create a new node
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->height = 1; // New node is initially at height 1
    return newNode;
}

// Function to perform a right rotation
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));

    return x;
}

// Function to perform a left rotation
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));

    return y;
}

// Function to insert a node into the AVL tree
struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else // Duplicate keys are not allowed
        return root;

    // Update height of current node
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    // Get balance factor and balance the tree
    int balance = getBalance(root);

    // Left Heavy
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    // Right Heavy
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    // Left Right Heavy
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Heavy
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to find the node with the minimum key value in a tree
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node from the AVL tree
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update height of current node
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    // Get balance factor and balance the tree
    int balance = getBalance(root);

    // Left Heavy
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Heavy
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Heavy
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Heavy
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function to search for a key in the AVL tree
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return search(root->left, key);

    return search(root->right, key);
}

// Function to print inorder traversal of the AVL tree
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, key;

    while (1) {
        printf("\nAVL Tree Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display Inorder Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                printf("Key %d inserted.\n", key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                root = deleteNode(root, key);
                printf("Key %d deleted.\n", key);
                break;

            case 3:
                printf("Enter key to search: ");
                scanf("%d", &key);
                struct Node* searchResult = search(root, key);
                if (searchResult)
                    printf("Key %d found in the tree.\n", key);
                else
                    printf("Key %d not found in the tree.\n", key);
                break;

            case4:
                printf("Inorder traversal: ");
                inorder(root);
                printf("\n");
                break;

            case5:
                printf("Exiting program.\n");
                exit(0);

case6:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}
