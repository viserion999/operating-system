#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define seats 10
 
void *customer_pointer();
void *barber_shop();
void *waiting_room();
void check();
 
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wait_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sleep_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t barberSleep_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t barberWorking_cond = PTHREAD_COND_INITIALIZER;
 
int r_time=9,curr=0, sleeping=0, hl;
 
int main(int argc, char *argv[])
{
        hl=time(NULL);
        srand(hl);
        //declare barber thread;
        pthread_t barber,customerM,timer_thread;
        pthread_attr_t barberAttr, timerAttr;
        pthread_attr_t customerMAttr;
 
        //define barber, and cutomerMaker default attributes
        pthread_attr_init(&timerAttr);
        pthread_attr_init(&barberAttr);
        pthread_attr_init(&customerMAttr);
 
        printf("\n\n");
        print("……………………………………………………………………………………….");
 
        //create cutomerMaker
        pthread_create(&customerM,&customerMAttr,customer_pointer,NULL);
 
        //create barber
        pthread_create(&barber,&barberAttr,barber_shop,NULL);
 
        pthread_join(barber,NULL);
        pthread_join(customerM,NULL);
 
        return 0;
}
 
void *customer_pointer()
{
        int i=0;
        printf("*Customer Pointer Created*\n\n");
        fflush(stdout);
        pthread_t customer[seats+1];
        pthread_attr_t customerAttr[seats+1];
        while(i<(seats+1))
        {
                 while(rand()%2!=1)
                {
                        sleep(1);
                }
                pthread_create(&customer[i],&customerAttr[i],waiting_room,NULL);
        }
        pthread_exit(0);
}
 
void *waiting_room()
{
        //take seat
        pthread_mutex_lock(&queue_mutex);
        check();
 
        sleep(r_time);
        waiting_room();
}
 
void *barber_shop()
{
        int loop=0;
        printf("The barber has opened the shop.\n");
        fflush(stdout);
        while(loop==0)
        {
                if(curr==0)
                {
                        printf("\tThe shop is empty, barber is sleeping.\n");
                        fflush(stdout);
                        pthread_mutex_lock(&sleep_mutex);
                        sleeping=1;
                        pthread_cond_wait(&barberSleep_cond,&sleep_mutex);
                        sleeping=0;
                        pthread_mutex_unlock(&sleep_mutex);
                        printf("\t\t\t\tBarber wakes up.\n");
                        fflush(stdout);
                }
                
                else
                {
                        printf("\t\t\tBarber begins cutting hair.\n");
                        fflush(stdout);
                        sleep((rand()%20)/5);
                        curr--;
                        printf("\t\t\t\tHair cut complete, customer leaving store.\n");
                        pthread_cond_signal(&barberWorking_cond);
                }
                
        }
        pthread_exit(0);
}
 
void check()
{
        curr++;
       
        if(curr<seats)
        {
                printf("\t\tCustomer takes a seat.\n");
                fflush(stdout);
                pthread_mutex_unlock(&queue_mutex);
                pthread_mutex_lock(&wait_mutex);
                pthread_cond_wait(&barberWorking_cond,&wait_mutex);
                pthread_mutex_unlock(&wait_mutex);
                return;
        }
        if(curr>=seats)
        {
                printf("\t\tAll chairs full, leaving store.\n");
                fflush(stdout);
                curr--;
                pthread_mutex_unlock(&queue_mutex);
                return;
        }
}

