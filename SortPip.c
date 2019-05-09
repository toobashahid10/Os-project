#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

void Print(int m , long int arr[])
{
 for (int i=0 ; i<m ; i++)
  printf("%ld ",arr[i]) ;
 printf("\n") ;
}

void Input(int m , long int arr[])
{
 for (int i=0 ; i<m ; i++)
   arr[i] = rand()%500+1 ;
}

void SelectionSort(int m , long int arr[])
{
 int minIndex ;
 long int temp ;
 for (int i=0 ; i<m ; i++)
 {
  minIndex = i ;
  for (int j=i+1 ; j<m ; j++)
  {
    if (arr[j]<arr[minIndex])
     minIndex = j ;
  }  
  temp = arr[i] ;
  arr[i] = arr[minIndex] ;
  arr[minIndex] = temp ;
 }
}

int main()
{
 int pid , len ;
 int pipfd1[2] , pipfd2[2] ;
 pipe(pipfd1) ;
 pipe(pipfd2) ;
 
 printf("Enter length of an array : ");
 scanf("%d",&len) ;
 
 long int arr1[len] , arr2[len] ;

 pid = fork() ;

 if (pid == 0)
 {
  //Child process taking input and passes array to parent process through pipe
  Input(len,arr1) ;
  write(pipfd1[1],arr1,len*sizeof(long int)) ;

  //Child process reading sorted array that will be sent by parent process
  read(pipfd2[0],arr2,len*sizeof(long int)) ;
  printf("After Sorting\n") ;
  Print(len,arr2) ;
 }
 else if (pid > 0)
 {
  //Parent process reading unsorted array that was sent by child process
  read(pipfd1[0],arr1,len*sizeof(long int)) ;
  printf("Before Sorting\n") ;
  Print(len,arr1) ;
  
  //Parent process will sort array and passes it to child process through pipe
  SelectionSort(len,arr1) ;
  write(pipfd2[1],arr1,len*sizeof(long int)) ;
 
 }
 return 0 ;
}
