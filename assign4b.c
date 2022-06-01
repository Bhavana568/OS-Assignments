#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

int var = 0;
pthread_mutex_t mutex; // mutex variable
sem_t wrt;             // grants exclusive access to the writer
int rcnt;              // readers count

// writer function
void *writer(void *i)
{
    int val;
    sem_getvalue(&wrt, &val);
    if (val <= 0)
    {
        if (rcnt >= 0)
        {
            printf("Writer waiting..\n");
        }
    }
    sem_wait(&wrt);

    var += 1;
    printf("Writer %ld writes %d\n", (long)i, var);
    sleep(3);
    sem_post(&wrt);
    pthread_exit(NULL);
}

// reader func
void *reader(void *i)

{

    int val;

    pthread_mutex_lock(&mutex);
    rcnt++;
    if (rcnt == 1)
    {

        sem_getvalue(&wrt, &val);
        if (val <= 0)
        {
            printf("Reader waiting!\n");
        }
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %ld reads %d\n", (long)i, var);
    sleep(5);

    pthread_mutex_lock(&mutex);
    rcnt--;

    if (rcnt == 0)
    {
        sem_post(&wrt);
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main()
{
    int read, writ = 5;

    pthread_mutex_init(&mutex, NULL); // initiate mutex
    sem_init(&wrt, 0, 1);

    long int i = 0, j = 0;

    // array of producers
    pthread_t readers[read],
        writers[writ];

    int op;
    int t;

    do

    {
        printf("Enter 0 for reader\n");
        printf("Enter 1 for writer\n");

        scanf("%d", &op);

        switch (op)
        {
        case 0:
            if (i < 5)
            {
                t = pthread_create(&readers[i], NULL, reader, (void *)i);

                if (t != 0)
                {
                    printf("Error in thread creation : %d\n", t);
                }

                //t = pthread_join(readers[i], NULL);

                if (t != 0)
                {
                    printf("Error while joining threads : %d\n", t);
                }
                //}

                i++;
            }
            else
            {
                printf("Reader out of capacity!\n");
            }
            break;

        case 1:

            if (j < 5)
            {
                t = pthread_create(&writers[j], NULL, writer, (void *)j);
                if (t != 0)
                {
                    printf("Error in thread creation : %d\n", t);
                }

                if (t != 0)
                {
                    printf("Error while joining threads : %d\n", t);
                }
                //}

                j++;
            }
            else
            {
                printf("Writer out of capacity!\n");
            }

            break;

        default:
            return 0;
            break;
        }

    } while (1);

    for (int i = 0; i < read; i++)
    {
        t = pthread_join(readers[j], NULL);
    }

    for (int j = 0; j < writ; i++)
    {
        t = pthread_join(writers[j], NULL);
    }

    pthread_mutex_destroy(&mutex); // destroy mutex
    sem_destroy(&wrt);
}