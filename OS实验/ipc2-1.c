

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int *list; 
double average; 
int maximum; 
int minimum; 


void *calculate_average(void *param);
void *calculate_maximum(void *param);
void *calculate_minimum(void *param);

int main(int argc, char *argv[]) {
    int i;
    int num_of_args = argc - 1;

    pthread_t tid_1;
    pthread_t tid_2;
    pthread_t tid_3;


    list = malloc(sizeof(int) * num_of_args);

    for (i = 0; i < num_of_args; i++)

        list[i] = atoi(argv[i + 1]);



    pthread_create(&tid_1, NULL, calculate_average, &num_of_args);
    pthread_create(&tid_2, NULL, calculate_maximum, &num_of_args);
    pthread_create(&tid_3, NULL, calculate_minimum, &num_of_args);


    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    pthread_join(tid_3, NULL);


    printf("The average is %f\n", average);
    printf("The maximum is %d\n", maximum);
    printf("The minimum is %d\n", minimum);

    return 0;
}


void *calculate_average(void *param) {
    int count = *(int *)param;
    int i, total = 0;
    for (i = 0; i < count; i++) {
        total += list[i];
    }
    average = total / (double)count; 
    pthread_exit(0);
}


void *calculate_maximum(void *param) {
    int count = *(int *)param;
    int i;
    maximum = list[0];

    for (i = 1; i < count; i++) {
        if (list[i] > maximum) {
            maximum = list[i];
        }
    }
    pthread_exit(0);
}


void *calculate_minimum(void *param) {
    int count = *(int *)param;
    int i;
    minimum = list[0];

    for (i = 1; i < count; i++) {
        if (list[i] < minimum) {
            minimum = list[i];
        }
    }
    pthread_exit(0);
}
