#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    char data;
    struct  node* left,*right;
};

struct node* insertnode(struct node* root, char data);
struct node* create(char key);

int main()
{
    RandomGen("input.txt", 12);

    FILE* ipfile = fopen("input.txt", "r");
    char data;
    struct node* root = NULL;

    while (fscanf(ipfile, " %c", &data) != EOF)
    {
        root = insertnode(root, data);
    }
    fclose(ipfile);

    FILE* inorderFile = fopen("inorder1.txt", "w");
    printf("2.Inorder file Craeted Successfully\n");
    inorder(root, inorderFile);
    fclose(inorderFile);

    FILE* prefile = fopen("preorder1.txt", "w");
    printf("3.Preorder file Created Successfully\n");
    preorder(root, prefile);
    fclose(prefile);

    FILE* pofile = fopen("postorder1.txt", "w");
    printf("4.Postorder file Created Successfully\n");
    postorder(root, pofile);
    fclose(pofile);

    return 0;
}

void RandomGen(FILE* fp, int n)
{
    FILE* fp1 = fopen(fp, "w");
    for (int i = 0; i < n; i++)
        {
        char r = 'A'+(rand() % 26);
        fprintf(fp1, "%c ", r);
        }
    fclose(fp1);
    printf("1.Input File Created Successfully\n");
}


struct node* insertnode(struct node* root, char data)
{
    if (root == NULL)
        root = create(data);

    else
        {
        if (data < root->data)
        root->left = insertnode(root->left, data);

        else if (data > root->data)
        root->right = insertnode(root->right, data);
        }
    return root;
}


struct node* create(char key)
{
    struct node* newnode =(struct node*)malloc(sizeof(struct node));
    newnode->data =key;
    newnode->left = newnode->right = NULL;
    return newnode;
}


void inorder(struct node* root, FILE* fp)
{
    if (root != NULL)
        {
        inorder(root->left, fp);
        fprintf(fp, "%c ", root->data);
        inorder(root->right, fp);
        }
}

void preorder(struct node* root, FILE* fp)
{
    if (root != NULL)
        {
        fprintf(fp, "%c ", root->data);
        preorder(root->left, fp);
        preorder(root->right, fp);
        }
}

void postorder(struct node* root, FILE* fp)
{
    if (root != NULL)
        {
        postorder(root->left, fp);
        postorder(root->right, fp);
        fprintf(fp, "%c ", root->data);
        }
}
