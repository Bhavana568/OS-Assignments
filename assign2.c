#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int arr[100], n;

// ascending order
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// descending order
int Rcompare(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}

// display array
void printarray()
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}
void forkSorting()
{
    pid_t pid = fork();
    // parent process because return value non-zero.
    if (pid > 0)
    {
        //wait(NULL);
        printf("\n\nParent process : START");
        printf("\nPID : %d ", pid);
        printf("\nSorting array in ascending order!\n");
        qsort(arr, n, sizeof(int), compare);
        printarray();
        printf("\nParent process : END\n\n");
    }
    // child process because return value zero
    else if (pid == 0)
    {
        printf("\n\nChild process : START");
        printf("\nPID : %d ", pid);
        printf("\nSorting array in descending order!\n");
        qsort(arr, n, sizeof(int), Rcompare);
        printarray();
        printf("\nChild process : END\n\n\n");
    }
    else
    {
        printf("\nExecution failed!");
    }
}

// zombie process
void zombie(int arr[], int n)
{
    printf("In zombie process \n");
    pid_t pid = fork();
    system("ps -al | grep a.out");
    if (pid == 0)
    {
        printf("Into child process\nid= %d \n", pid);
        printf("Sorting with Quick sort !!! \n");
        qsort(arr, n, sizeof(int), Rcompare);
        printf("Sorted array::\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("Child in zombie mode\n ");
    }
    else if (pid > 0)
    {
        sleep(5);
        system("ps -al | grep a.out");
        printf("Into parent process\nid=%d\n", pid);
        printf("Sorting using qsort\n");
        qsort(arr, n, sizeof(int), compare);
        printf("Sorted array :\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n\n");
    }
    else
    {
        printf("Execution failed !");
    }
}

// orphan process
void orphan(int arr[], int n)
{
    printf("In orphan process\n");
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Into child process\nid= %d \n", pid);
        sleep(5);

        printf("Sorting with Quick sort !!! \n");
        qsort(arr, n, sizeof(int), Rcompare);
        printf("Sorted array::\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("\n\n");
        exit(0);
    }
    else if (pid > 0)
    {
        printf("Into parent process\nid=%d\n", pid);
        printf("Sorting using qsort\n");
        qsort(arr, n, sizeof(int), compare);
        printf("Sorted array :\n");

        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
        printf("Parent process terminated !\n");
        exit(0);
        printf("\n\n");
    }
    else
    {
        printf("Execution failed!");
    }
}

int main()
{
    printf("Enter no. of elements : ");
    scanf("%d", &n);
    printf("Enter elements :");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("\nElements before sorting : ");
    printarray();
    int op;
    printf("\n\n");
    printf("-------------------Menu---------------------\n");
    printf("1. forksorting\n");
    printf("2. Zombie process\n");
    printf("3. Orphan process\n");
    printf("4. Exit\n");
    printf("Choose an option\n");
    scanf("%d", &op);
    printf("%d", op);

    switch (op)
    {
    case 1:
        forkSorting();
        break;

    case 2:
        zombie(arr, n);
        break;

    case 3:
        orphan(arr, n);
        break;

    case 4:
        printf("Exit");
        break;

    default:
        printf("Invalid option chosen !");
    }

    return 0;
}
