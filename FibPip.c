#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
 int pid , len ;
 int pipfd1[2] , pipfd2[2] ;
 pipe(pipfd1) ;
 pipe(pipfd2) ;
 
 printf("Enter length of a series : ");
 scanf("%d",&len) ;
 
 long int arr1[len] , arr2[len] ;
 long int a=1 , b=0 ;

 pid = fork() ;
 
 if (pid == 0)
 {
  for (int i=0 ; i<len ; i++)
  {
   arr1[i] = a+b ;
   a = b ;
   b = arr1[i] ;
  }
  write(pipfd1[1],arr1,len*sizeof(long int)) ;
 }

 else if (pid > 0)
 {
  read(pipfd1[0],arr2,len*sizeof(long int)) ;
  printf("\nFibonacci Series\n") ;
  for (int i=0 ; i<len ; i++) 
   printf("%ld ",arr2[i]) ;
  printf("\n\n") ;
 }

 return 0 ;
}

