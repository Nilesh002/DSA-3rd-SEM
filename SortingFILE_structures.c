#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

struct record {
    int value;
};


int main()
{
    struct record arr[SIZE];
    FILE* fp;
    int i,j,temp;
    clock_t start, end;
    double elapsed;

    fp = fopen("data.txt", "w");                // opening data.txt file


    for (i = 0; i < SIZE; i++)              // Generating  random no's and writing into file
    {
        arr[i].value = rand() % 1001;
        fprintf(fp, "%d\n", arr[i].value);
    }
    fclose(fp);                                  // closing data.txt file


    start=clock();
    for(i=0;i<SIZE-1;i++)         //bubble sort
    {
        for(j=0;j<SIZE-1-i;j++)
        {
            if(arr[j+1].value<arr[j].value)
            {
                temp=arr[j+1].value;
                arr[j+1].value=arr[j].value;
                arr[j].value=temp;
            }
        }
    }
    end=clock();


    fp = fopen("sorted.txt", "w");                 //opening sorted.txt file

    for (i = 0; i < SIZE; i++)                  // Writing sorted no's to file
    {
        fprintf(fp, "%d\n", arr[i].value);
    }
    fclose(fp);                                      //closing file


    elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;           // Calculate time taken to sort
    printf("Time taken to sort: %f seconds\n", elapsed);


}
