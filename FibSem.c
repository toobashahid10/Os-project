#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include <semaphore.h>

sem_t sem ;
int n;
void *fibonacci(void* arg){
long int first=1,second=0,a;
printf("\nFIBONACCI SERIES: \n");
for(int i=2;i<n;i++){
sem_wait(&sem) ;
a=first+second;
first=second;
second=a;
printf("%ld ",a);
sem_post(&sem) ;
}
printf("\n") ;
}


int main(){

sem_init(&sem,0,1) ;
pthread_t nid;
printf("ENTER A NUMBER: ");
scanf("%d" ,&n);
pthread_create (&nid,NULL,fibonacci,(void*)&n);
pthread_join (nid,(void*)&n);

return (0);
}
