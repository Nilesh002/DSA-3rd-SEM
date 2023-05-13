#include<stdio.h>
#include<time.h>

#define SIZE 10


int main()
{
    int random;
    int arr[SIZE];
    int top=-1;
    int pos=0;
    int i,j,n,m,c;
    FILE *fp1,*fp2,*fp3,*fp4,*fp5;
    fp1=fopen("file.txt","w");
    for(i=0;i<SIZE;i++)
    {
        random =rand()%(101);
        fprintf(fp1,"%d\n",random);
    }
    fclose(fp1);

    fp3=fopen("Pop.txt","w");
    fp4=fopen("Operations.txt","w");
    fp5=fopen("Push.txt","w");

    printf("Enter the number of operations to be performed:");
    scanf("%d",&n);

   for(j=0;j<n;j++)
    {
        printf("Enter the operation to be performed(Enter 0 to push and 1 to pop):");
        scanf("%d",&m);

        if(m==0)
        {
         fp1=fopen("file.txt","r");
         fseek(fp1,pos,SEEK_SET);
         fscanf(fp1, "%d", &c);
         top++;
         arr[top]=c;
         fprintf(fp5,"%d\n",c);
         fprintf(fp4,"Pushed %d\n",c);
         pos=ftell(fp1);
         fclose(fp1);
        }
        else
        {
         c=arr[top];
         top--;
         fprintf(fp3,"%d\n",c);
         fprintf(fp4,"Popped %d\n",c);

        }
    }

    fp2=fopen("Stack.txt","w");

    for (int k = 0; k <=top; k++)
                {
                    fprintf(fp2, "%d\n", arr[k]);
                }

fclose(fp2);
fclose(fp3);
fclose(fp4);
fclose(fp5);
    return 0;
}



