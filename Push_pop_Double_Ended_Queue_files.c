#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int main()
{
    int random;
    int deque[SIZE];
    int front = -1;
    int rear = -1;
    int i, j, n, m, c;
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;

    fp1 = fopen("file.txt", "w");
    for (i = 0; i < SIZE; i++)
    {
        random = rand() % 101;
        fprintf(fp1, "%d\n", random);
    }
    fclose(fp1);

    fp3 = fopen("De.txt", "w");
    fp4 = fopen("Opes.txt", "w");
    fp5 = fopen("Ee.txt", "w");

    printf("Enter the number of operations to be performed: ");
    scanf("%d", &n);

    fp1 = fopen("file.txt", "r");

    for (j = 0; j < n; j++)
    {
        printf("Enter the operation to be performed (0 to enqueue from front, 1 to enqueue from rear, 2 to dequeue from front, 3 to dequeue from rear): ");
        scanf("%d", &m);

        if (m == 0) // Enqueue from front
        {
            if ((front == 0 && rear == SIZE - 1) || (rear == (front - 1 + SIZE) % SIZE))
            {
                printf("Deque is full. Cannot enqueue from front.\n");
                continue;
            }

            fscanf(fp1, "%d", &c);

            if (front == -1)
                front = 0;

            if (front == 0)
                front = SIZE - 1;
            else
                front--;

            deque[front] = c;
            fprintf(fp5, "%d\n", c);
            fprintf(fp4, "Enqueued %d from front\n", c);
        }
        else if (m == 1) // Enqueue from rear
        {
            if ((front == 0 && rear == SIZE - 1) || (rear == (front - 1 + SIZE) % SIZE))
            {
                printf("Deque is full. Cannot enqueue from rear.\n");
                continue;
            }

            fscanf(fp1, "%d", &c);

            if (rear == -1)
            {
                front = 0;
                rear = 0;
            }
            else
                rear = (rear + 1) % SIZE;

            deque[rear] = c;
            fprintf(fp5, "%d\n", c);
            fprintf(fp4, "Enqueued %d from rear\n", c);
        }
        else if (m == 2) // Dequeue from front
        {
            if (front == -1)
            {
                printf("Deque is empty. Cannot dequeue from front.\n");
                continue;
            }

            c = deque[front];
            fprintf(fp3, "%d\n", c);
            fprintf(fp4, "Dequeued %d from front\n", c);

            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            else
                front = (front + 1) % SIZE;
        }
        else if (m == 3) // Dequeue from rear
        {
            if (rear == -1)
            {
                printf("Deque is empty. Cannot dequeue from rear.\n");
                continue;
            }

            c = deque[rear];
            fprintf(fp3, "%d\n", c);
            fprintf(fp4, "Dequeued %d from rear\n", c);

            if (front == rear)
            {
                front = -1;
                rear = -1;
            }
            else
                rear = (rear - 1 + SIZE) % SIZE;
        }
    }

    fclose(fp1);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    fp2 = fopen("Deque.txt", "w");
    if (front <= rear)
    {
        for (int k = front; k <= rear; k++)
            fprintf(fp2, "%d\n", deque[k]);
    }
    else
    {
        for (int k = front; k < SIZE; k++)
            fprintf(fp2, "%d\n", deque[k]);
        for (int k = 0; k <= rear; k++)
            fprintf(fp2, "%d\n", deque[k]);
    }
    fclose(fp2);

    return 0;
}
