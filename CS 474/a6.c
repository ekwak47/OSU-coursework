#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define GARAGE_SIZE 15  // 15 available parking spots


int garage[GARAGE_SIZE];
int in = 0, out = 0;

sem_t empty; 

sem_t full;   

sem_t mutex; 


void* park_car(void* arg) { // entering

    int num = *(int*)arg;

    for (int car = 1; car <= 15; car++) {;

        sem_wait(&empty);    

        sem_wait(&mutex);     

        garage[in] = num;

        printf("car #%d parked in parking slot %d\n", num, in);

        in = (in + 1) % GARAGE_SIZE;

        sem_post(&mutex);   
        sem_post(&full);      


        num++;
        sleep(1);

    }

    return NULL;

}



void* leave_spot(void* arg) {

    for (int i = 1; i <= 45; i++) {

        sem_wait(&full);      
        sem_wait(&mutex);    

        int spot = garage[out];

        printf("car #%d exits garage from spot %d\n", spot, out);

        out = (out + 1) % GARAGE_SIZE;

        sem_post(&mutex);     

        sem_post(&empty);    


        sleep(2);

    }

    return NULL;

}


int main() {

    pthread_t carThread1, carThread2, carThread3, garageThread; // producer, consumer

    int row1 = 1;
    int row2 = 16;
    int row3 = 31;

    sem_init(&empty, 0, GARAGE_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&carThread1, NULL, park_car, &row1);
    pthread_create(&carThread2, NULL, park_car, &row2);
    pthread_create(&carThread3, NULL, park_car, &row3);

    pthread_create(&garageThread, NULL, leave_spot, NULL);

    pthread_join(carThread1, NULL);
    pthread_join(carThread2, NULL);
    pthread_join(carThread3, NULL);

    pthread_join(garageThread, NULL);

    sem_destroy(&empty);

    sem_destroy(&full);

    sem_destroy(&mutex);

    printf("\nAll cars have exited, the parking garage is empty.\n");


    return 0;

}