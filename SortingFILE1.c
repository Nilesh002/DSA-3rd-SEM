#include<stdio.h>
#include<time.h>

#define SIZE 1000

int main()
{
    int arr[SIZE],i,j,temp;
    clock_t start,end;
    FILE *fp;
    fp=fopen("data.txt","w");           // opening data.txt file
    for(i=0;i<1000;i++)                   // generating random no's in array and writing it in data.txt file
    {
        arr[i]=rand()%(1001);
        fprintf(fp,"%d\n",arr[i]);
    }

    start=clock();
    for(i=0;i<SIZE-1;i++)                // Bubble sort
    {
        for(j=0;j<SIZE-1-i;j++)
        {
            if(arr[j+1]<arr[j])
            {
                temp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;
            }
        }
    }
    end=clock();

    double elapsed=((double)(end-start)/CLOCKS_PER_SEC);             // calculating sorting time
    printf("Time taken to sort: %f seconds\n",elapsed);

    fclose(fp);                                                        // closing file
    fp=fopen("sorted.txt","w");                         // opening sorted.txt file
    for(i=0;i<SIZE;i++)                                     // writing sorted no's to sorted.txt file
    {
        fprintf(fp,"%d\n",arr[i]);
    }
    fclose(fp);

    return 0;
}
