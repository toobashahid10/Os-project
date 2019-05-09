#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#define MAX 100

int m , n , s , t , sum=0 ;
long int mat1[MAX][MAX] , mat2[MAX][MAX] , product[MAX][MAX];
sem_t sem1 ;

//Function to take matrix input
void input(int m , int n , long int arr[MAX][MAX])
{
 for (int i=0 ; i<m ; i++)
  for (int j=0 ; j<n ; j++)
   arr[i][j] = rand()%500+1 ;
}

//Function that prints matrix
void print(int m , int n , long int arr[MAX][MAX])
{ 
 for (int i=0 ; i<m ; i++)
 {
  for (int j=0 ; j<n ; j++)
   printf("%ld ",arr[i][j]) ;
  printf("\n\n") ;
 }
}

void *mul(void *arg){
 sem_wait(&sem) ;
 int i = *(int*)arg ;
 for (int j=0 ; j<t ; j++,sum=0)
 {
  for (int k=0 ; k<s ; k++)
   sum = sum + mat1[i][k]*mat2[k][j] ;

  product[i][j] = sum ;
 } 
 sem_post(&sem) ;
}

int main()
{
 printf("Enter no. of rows & columns of matrix1\n") ;
 scanf("%d %d",&m,&n) ;
 printf("Enter no. of rows & columns of matrix2\n") ;
 scanf("%d %d",&s,&t) ;
 
 if (n!=s)
 {
  printf("Multiplication is not possible\n") ;
  exit(0) ;
 }
 
  input(m,n,mat1) ;
  srand(time(NULL)) ;
  input(s,t,mat2) ;

  printf("\nMatrix 1\n") ;
  print(m,n,mat1) ;
  printf("\nMatrix 2\n") ;
  print(s,t,mat2) ;

  sem_init(&sem,0,1) ;
  
  pthread_t thread[m] ; //m= no.of rows of mat1 or col of mat2
  int tid[m] ;
  
  for(int i=0 ; i<m ; i++){
   tid[i] = i ;
   pthread_create(&thread[i],NULL,mul,&tid[i]) ;
  }

  for (int i=0 ; i<m ; i++){
   pthread_join(thread[i],NULL) ;
  }

  printf("\nProduct of matrices\n") ;
  print(m,t,product) ;

 return 0 ;
}
