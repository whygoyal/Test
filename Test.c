#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>

pthread_t thread1, thread2, thread3;
sigset_t new;

void *handler1();
void *handler2();
void *handler3();
void interrupt();

int main(int argc, char *argv[]) {
// your code goes here

sigemptyset(&new);
sigaddset(&new, SIGINT);

pthread_sigmask(SIG_BLOCK, &new, NULL);
pthread_create(&thread1, NULL, handler1, argv[1]);
pthread_create(&thread2, NULL, handler2, argv[1]);
pthread_create(&thread3, NULL, handler3, argv[1]);

pthread_join(thread1, NULL);
pthread_join(thread2, NULL);
pthread_join(thread3, NULL);

printf("thread handler, exited\n");
usleep(2000000);
printf("main thread is done\n");
return 0;
}
 
struct sigaction act;

void* handler1(char argv[1]){
while(1){
act.sa_handler= interrupt;
sigaction(SIGINT, &act, NULL);
pthread_sigmask(SIG_UNBLOCK, &new, NULL);
printf("Press CTRL-C to deliver SIGINT\n");
usleep(2000000);
}
return 0;
}

void* handler2(char argv[1]){
while(1){
printf("I am in Handler2\n");
usleep(1000000);
}
return 0;
}
void* handler3(char argv[1]){
while(1){
printf("I am in Handler3\n");
usleep(1000000);
}
return 0;
}

void interrupt(int sig){
printf("thread caught signal %d\n", sig);
pthread_cancel(thread2);
}
