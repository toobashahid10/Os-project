#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include <semaphore.h>
#include<string.h>

#define MAX 1000

long int arr[MAX] ;
int len ;
sem_t sem ;

void Print()
{
 for (int i=0 ; i<len ; i++)
  printf("%ld ",arr[i]) ;
 printf("\n\n") ;
}

void Input()
{
 for (int i=0 ; i<len ; i++)
   arr[i] = rand()%500+1 ;
}

void *SelectionSort()
{
 int minIndex ;
 long int temp ;
 for (int i=0 ; i<len ; i++)
 {
  minIndex = i ;
  sem_wait(&sem) ;
  for (int j=i+1 ; j<len ; j++)
  {
    if (arr[j]<arr[minIndex])
     minIndex = j ;
  } 
  sem_post(&sem) ; 
  temp = arr[i] ;
  arr[i] = arr[minIndex] ;
  arr[minIndex] = temp ;
 }
}


int main(){

  sem_init(&sem,0,1) ;

  printf("Enter length of an array : ");
  scanf("%d",&len) ;
 
  srand(time(NULL));

  Input() ;

  pthread_t thread ;

  printf("\nBefore Sorting\n") ;
  Print() ;

  pthread_create(&thread,NULL,SelectionSort,NULL);

  pthread_join(thread,NULL);

  printf("\nAfter Sorting\n") ;
  Print() ;

  return(0);
}
