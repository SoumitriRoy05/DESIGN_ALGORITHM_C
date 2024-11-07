#include <stdio.h>
#include <string.h>
 int main()
 {
 	char pattern[20]="abcaccdba";
 	printf("Pattern:%s\n",pattern);
 	int p=strlen(pattern);
     printf("Pattern length:%d\n",p);
 	char text[]="dba";
 	printf("Text:%s\n",text);
 	int t=strlen(text);
     printf("Text length:%d\n",t);
     for(int i=0; i<=p-t;i++)
     {    
         int j;
         for( j=0; j<t;j++)
         {
             if(pattern[i+j]!=text[j])
             break;
         }if(j==t){
         printf("Index found:%d",i);
         }
     }
 }

