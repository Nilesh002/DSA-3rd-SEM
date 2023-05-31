#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int main()
{
    int random;
    int queue[SIZE];
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

    fp3 = fopen("Dequeue.txt", "w");
    fp4 = fopen("Operations.txt", "w");
    fp5 = fopen("Enqueue.txt", "w");

    printf("Enter the number of operations to be performed: ");
    scanf("%d", &n);

    fp1 = fopen("file.txt", "r");

    for (j = 0; j < n; j++)
    {
        printf("Enter the operation to be performed (0 to enqueue, 1 to dequeue): ");
        scanf("%d", &m);

        if (m == 0) // Enqueue
        {
            if ((front == 0 && rear == SIZE - 1) || (rear == (front - 1) % SIZE - 1))
            {
                printf("Queue is full. Cannot enqueue.\n");
                continue;
            }

            fscanf(fp1, "%d", &c);

            if (front == -1)
                front = 0;

            rear = (rear + 1) % SIZE;
            queue[rear] = c;
            fprintf(fp5, "%d\n", c);
            fprintf(fp4, "Enqueued %d\n", c);
        }
        else // Dequeue
        {
            if (front == -1)
            {
                printf("Queue is empty. Cannot dequeue.\n");
                continue;
            }

            c = queue[front];
            fprintf(fp3, "%d\n", c);
            fprintf(fp4, "Dequeued %d\n", c);

            if (front == rear)                           //when only one element is present in queue
            {
                front = -1;
                rear = -1;
            }
            else
                front = (front + 1) % SIZE;
        }
    }

    fclose(fp1);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    fp2 = fopen("Queue.txt", "w");
    if (front <= rear)
    {
        for (int k = front; k <= rear; k++)
            fprintf(fp2, "%d\n", queue[k]);
    }
    else
    {
        for (int k = front; k < SIZE; k++)
            fprintf(fp2, "%d\n", queue[k]);
        for (int k = 0; k <= rear; k++)
            fprintf(fp2, "%d\n", queue[k]);
    }
    fclose(fp2);

    return 0;
}
