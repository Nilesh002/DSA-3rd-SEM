#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define the structure of a linked list node
struct Node {
    int data;
    struct Node* next;
};

int main() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    struct Node* new_node;
    clock_t start, end;
    double elapsed_time;

    // Generate 1000 random integers and add them to the linked list
    srand(time(NULL));
    for (int i = 0; i < 1000; i++) {
        new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->data = rand() % 1001;
        new_node->next = NULL;
        if (head == NULL) {
            head = new_node;
            tail = new_node;
        }
        else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    // Perform bubble sort on the linked list
    start = clock();
    int swapped;
    struct Node* current;
    struct Node* previous = NULL;
    do {
        swapped = 0;
        current = head;
        while (current->next != previous) {
            if (current->data > current->next->data) {
                int temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
        }
        previous = current;
    } while (swapped);
    end = clock();

    // Print the sorted linked list to a file
    FILE* fp;
    fp = fopen("gigi.txt", "w");
    current = head;
    while (current != NULL) {
        fprintf(fp, "%d\n", current->data);
        current = current->next;
    }
    fclose(fp);

    // Calculate and print the time taken to sort the linked list
    elapsed_time = ((double)(end - start) / CLOCKS_PER_SEC);
    printf("Time taken to sort: %f seconds\n", elapsed_time);

    // Free the memory used by the linked list
    current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
