#include<stdio.h>

   void Sort(int start[],int finish[],int n)
   {
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
          if(finish[i]>finish[j])
          {
            int temp=start[i];
            start[i]=start[j];
            start[j]=temp;
            temp=finish[i];
            finish[i]=finish[j];
            finish[j]=temp;
          }
        }
    }
   } 
   
   int main()
   {
    int n;
    printf("Enter the activity number:");
    scanf("%d",&n);
    int start[n],finish[n];
    printf("Enter the start time:");
    for(int i=0;i<n;i++){
        scanf("%d",&start[i]);
    }
    
    printf("Enter the finishing time:");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&finish[i]);
    }
    Sort(start,finish,n);
    printf("Selected activities:");
    int i = 0;
    printf("(%d, %d) ", start[i], finish[i]);
    
    for (int j = 1; j < n; j++) {
        if (start[j] >= finish[i]) {
            printf("(%d, %d) ", start[j], finish[j]);
            i = j;
        }
    }
    
    printf("\n");
    return 0;
   }
   