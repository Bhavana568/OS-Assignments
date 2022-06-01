#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define BufferSize 5   // Size of the buffer
pthread_mutex_t mutex; // mutex variable
sem_t full;            // no of full slots in the buffer
sem_t empty;           // no of empty slots in the buffer

int buffer[BufferSize]; // buffer
int in = 0, out = 0;
int item_no = 0;

// producer func
void *producer(void *i)
{

    int val;
    sem_getvalue(&empty, &val);
    if (val <= 0) // not empty
    {
        printf("Producer waiting...\n");
        return NULL;
    }
    sem_wait(&empty); // wait if not empty

    pthread_mutex_lock(&mutex); // lock the critical section

    buffer[in] = item_no;
    item_no++;
    printf("Producer %ld: Insert Item %d at %d\n", ((long)i), buffer[in], in);
    in = (in + 1) % BufferSize;

    pthread_mutex_unlock(&mutex); // unlock

    sem_post(&full); // signal to increment full
}

// consumer func
void *consumer(void *i)

{

    int val;
    sem_getvalue(&full, &val);
    if (val <= 0)
    {
        printf("Consumer waiting...\n");
        return NULL;
    }

    sem_wait(&full);

    pthread_mutex_lock(&mutex);

    printf("Consumer %ld: Consumed Item %d at %d\n", (long)i, buffer[out], out);
    out = (out + 1) % BufferSize;

    pthread_mutex_unlock(&mutex);

    sem_post(&empty);
    //}
}

int main()
{
    int prod = 5, cons = 5;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BufferSize);
    sem_init(&full, 0, 0);

    long int i = 0, j = 0;

    // array of producers
    pthread_t producers[prod],
        consumers[cons];

    int op;
    int t;

    do

    {
        printf("Enter 0 for consumer\n");
        printf("Enter 1 for producer\n");

        scanf("%d", &op);

        switch (op)
        {
        case 0:

            t = pthread_create(&consumers[i], NULL, consumer, (void *)i);

            if (t != 0)
            {
                printf("Error in thread creation : %d\n", t);
            }

            t = pthread_join(consumers[i], NULL);

            if (t != 0)
            {
                printf("Error while joining threads : %d\n", t);
            }

            i++;

            break;

        case 1:

            t = pthread_create(&producers[j], NULL, producer, (void *)j);
            if (t != 0)
            {
                printf("Error in thread creation : %d\n", t);
            }

            t = pthread_join(producers[j], NULL);
            if (t != 0)
            {
                printf("Error while joining threads : %d\n", t);
            }

            j++;

            break;

        default:
            return 0;
            break;
        }

    } while (1);

    pthread_mutex_destroy(&mutex); // destroy mutex
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}