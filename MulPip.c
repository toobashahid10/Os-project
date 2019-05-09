#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

//Function to take matrix input
void input(int m , int n , long int arr[m][n])
{
 for (int i=0 ; i<m ; i++)
  for (int j=0 ; j<n ; j++)
   arr[i][j] = rand()%500+1 ;
}

//Function that prints matrix
void print(int m , int n , long int arr[m][n])
{ 
 for (int i=0 ; i<m ; i++)
 {
  for (int j=0 ; j<n ; j++)
   printf("%ld ",arr[i][j]) ;
  printf("\n") ;
 }
}

int main()
{
 int m , n , s , t , sum=0 ;
 int pid ; 
 int pipefd1[2],pipefd2[2] ,pipefd[2] ;
 pipe(pipefd1) ;
 pipe(pipefd2) ;
 pipe(pipefd) ;

 printf("Enter no. of rows & columns of matrix1\n") ;
 scanf("%d %d",&m,&n) ;
 printf("Enter no. of rows & columns of matrix2\n") ;
 scanf("%d %d",&s,&t) ;
 
 if (n!=s)
 {
  printf("Multiplication is not possible\n") ;
  exit(0) ;
 }
 
 long int mat1[m][n] , mat2[s][t] , product[m][t];
 pid = fork() ;

 if (pid == 0)
 {
  input(m,n,mat1) ;
  input(s,t,mat2) ;

  //Child process Writing matrices in pipes
  write(pipefd1[1],mat1,m*n*sizeof(long int)) ;
  write(pipefd2[1],mat2,s*t*sizeof(long int)) ;
  
  //Child Process reading answer in product matrix
  read(pipefd[0],product,m*t*sizeof(long int)) ;
  printf("\nProduct of matrices\n") ;
  print(m,t,product) ;

 }
 else if (pid > 0 ) 
 {
  //Parent process reading matrix from pipe
  read(pipefd1[0],mat1,m*n*sizeof(long int)) ;
  read(pipefd2[0],mat2,s*t*sizeof(long int)) ;

  printf("\nMatrix 1\n") ;
  print(m,n,mat1) ;
  printf("\nMatrix 2\n") ;
  print(s,t,mat2) ;

  for (int i=0 ; i<m ; i++)
   for (int j=0 ; j<t ; j++,sum=0)
   {
    for (int k=0 ; k<s ; k++)
      sum = sum + mat1[i][k]*mat2[k][j] ;

    product[i][j] = sum ;
   } 

  //Parent process writing matrix to pipe

  write(pipefd[1],product,m*t*sizeof(long int)) ;
 }
 return 0 ;
}
