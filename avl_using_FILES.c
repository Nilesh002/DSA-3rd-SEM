#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

struct Node *newNode(int key)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left),
                    height(y->right)) +
                1;
    x->height = max(height(x->left),
                    height(x->right)) +
                1;

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left),
                    height(x->right)) +
                1;
    y->height = max(height(y->left),
                    height(y->right)) +
                1;

    return y;
}

int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node *insert(struct Node *node, int key)
{
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void InOrder(struct Node *root, FILE *file)
{
    if (root != NULL)
    {
        InOrder(root->left, file);
        fprintf(file, "%d ", root->key);
        printf( "%d ", root->key);
        InOrder(root->right, file);
    }
}

void PreOrder(struct Node *root, FILE *file)
{
    if (root != NULL)
    {
        fprintf(file, "%d ", root->key);
        printf("%d ", root->key);
        PreOrder(root->left, file);
        PreOrder(root->right, file);
    }
}

void PostOrder(struct Node *root, FILE *file)
{
    if (root != NULL)
    {
        PostOrder(root->left, file);
        PostOrder(root->right, file);
        fprintf(file, "%d ", root->key);
        printf( "%d ", root->key);
    }
}

struct Node *deleteNode(struct Node *root, int val_to_delete, FILE *deleted_file)
{
    if (root == NULL)
    {
        return NULL;
    }
    else
    {
        // node is found and needs to be deleted
        if (val_to_delete == root->key)
        {
            // scenario 1
            if (root->left == NULL && root->right == NULL)
            {
                fprintf(deleted_file, "%d ", root->key);
                free(root);
                return NULL;
            }
            // scenario 2
            else if (root->left == NULL)
            {
                struct Node *temp = root->right;
                fprintf(deleted_file, "%d ", root->key);
                free(root);
                return temp;
            }
            // scenario 2
            else if (root->right == NULL)
            {
                struct Node *temp = root->left;
                fprintf(deleted_file, "%d ", root->key);
                free(root);
                return temp;
            }
            // scenario 3
            else
            {
                // finding the minimum value in the right subtree
                struct Node *min_right_subtree;
                struct Node *current = root->right;
                while (current->left != NULL)
                {
                    current = current->left;
                }
                min_right_subtree = current;

                // switching the values
                root->key = min_right_subtree->key;

                // Deleting the node with val_to_delete now as a leaf node
                root->right = deleteNode(root->right, min_right_subtree->key, deleted_file);
            }
        }
        // keep searching for node
        else
        {
            if (val_to_delete < root->key)
            {
                root->left = deleteNode(root->left, val_to_delete, deleted_file);
            }
            else if (val_to_delete > root->key)
            {
                root->right = deleteNode(root->right, val_to_delete, deleted_file);
            }
        }

        // checking if node needs to be rebalanced after deletion happens
        int balance = getBalance(root);

        if (balance > 1 && val_to_delete < root->left->key)
            return rightRotate(root);

        if (balance < -1 && val_to_delete > root->right->key)
            return leftRotate(root);

        if (balance > 1 && val_to_delete > root->left->key)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && val_to_delete < root->right->key)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
}

int main()
{
    struct Node *root = NULL;
    int data, data1, n, op;
    printf("Enter the number of operations to be inserted: ");
    scanf("%d", &n);

    FILE *inorder_file = fopen("inorder.txt", "w");
    FILE *preorder_file = fopen("preorder.txt", "w");
    FILE *postorder_file = fopen("postorder.txt", "w");
    FILE *deleted_file = fopen("deleted.txt", "w");
    FILE *inserted_file = fopen("inserted.txt", "w");

    for (int i = 0; i < n; i++)
    {
        printf("Enter 1 to insert and 2 to delete: ");
        scanf("%d", &op);

        if (op == 1)
        {
            printf("Enter the data: ");
            scanf("%d", &data);
            root = insert(root, data);
            fprintf(inserted_file, "%d ", data);
        }
        else if (op == 2)
        {
            printf("Enter the key to delete: ");
            scanf("%d", &data1);
            root = deleteNode(root, data1, deleted_file);
        }
    }

    printf("\nInorder: ");
    InOrder(root, inorder_file);
    printf("\nPreorder: ");
    PreOrder(root, preorder_file);
    printf("\nPostorder: ");
    PostOrder(root, postorder_file);

    fclose(inorder_file);
    fclose(preorder_file);
    fclose(postorder_file);
    fclose(deleted_file);
    fclose(inserted_file);

    return 0;
}
