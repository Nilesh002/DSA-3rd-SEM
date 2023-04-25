#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {                       // Defining the structure of a linked list node
    int data;
    struct Node* next;
};

int main()
{
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* new_node;
    clock_t start, end;
    double elapsed_time;

    for (int i = 0; i < 1000; i++)       // Generatimg 1000 random no's and adding them to linked list
    {
        new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = rand() % 1001;
        new_node->next = NULL;
        if (head == NULL)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
             tail->next = new_node;
             tail = new_node;
        }
    }


    start = clock();
    struct Node* current;

for (int i = 0; i < 999; i++)
{                                     // Performing bubble sort on  linked list
   current = head;
    for (int j = 0; j < 999 - i; j++)
    {
        if (current->data > current->next->data)
        {
            int temp = current->data;
            current->data = current->next->data;
            current->next->data = temp;
        }
        current = current->next;

    }
}
    end = clock();


    FILE* fp;                                       // file pointer
    fp = fopen("sorted.txt", "w");                      // opening file in write mode
    current = head;
    while (current != NULL)                            // putting sorted no's to file
    {
        fprintf(fp, "%d\n", current->data);
        current = current->next;
    }
    fclose(fp);


    elapsed_time = ((double)(end - start) / CLOCKS_PER_SEC);      // time calculation
    printf("Time taken to sort: %f seconds\n", elapsed_time);

    return 0;
}


