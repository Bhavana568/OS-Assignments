#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void sstf(int n, int a[], int x)
{
    bool done[n];
    int sum = 0;
    int index, min;
    printf("%d", x); //print current
    for (int i = 0; i < n; i++)
    {
        index = 0;
        min = INT_MAX;
        for (int j = 0; j < n; j++)
        { //check for min difference and if the position is already traversed
            if (abs(x - a[j]) < min && !done[j])
            {
                index = j; //store the index of min value
                min = abs(x - a[j]);
            }
        }
        done[index] = true;
        sum += min;   //add the sum
        x = a[index]; //set pointer to that index
        printf("-> %d", x);
    }
    printf("\nTotal head movements = %d\n", sum);
    return;
}
void scan(int n, int a[], int length, int x)
{
    int sum = 0;
    int total_movement = length - 1 - x; //calc length from end to current
    qsort(a, n, sizeof(int), compare);
    if (x > a[0])
    {
        total_movement += length - 1 - a[0]; //calc length from first elemnt to current
    }
    printf("%d", x);
    for (int i = 0; i < n; i++)
    { //print all elements greater than current
        if (a[i] > x)
        {
            printf("-> %d", a[i]);
        }
    }

    for (int i = n - 1; i >= 0; i--)
    { //print all elemnts less than current in rev order
        if (a[i] < x)
        {
            printf("-> %d", a[i]);
        }
    }
    printf("\nTotal head movements = %d\n", total_movement);
}
void c_look(int n, int a[], int x)
{
    int total_movement = 0;
    qsort(a, n, sizeof(int), compare);
    total_movement = a[n - 1] - x; //calc total movement from max number to current
    if (a[0] < x)
    {
        total_movement += (a[n - 1] - a[0]); //calc movement from max to min
    }
    printf("%d", x);
    for (int i = 0; i < n; i++)
    { //print all the values greater than current
        if (a[i] > x)
        {
            printf("-> %d", a[i]);
        }
    }
    int i;
    for (i = 0; a[i] < x; i++)
    { //print all values from start till current
        printf("-> %d", a[i]);
    }

    if (a[0] < x)
    {
        total_movement += (a[i - 1] - a[0]); //calc movement from first element to the one before current
    }
    printf("\nTotal head movements = %d\n", total_movement);
}
int main()
{
    int n;

    int ch;
    printf("Enter the number of order requests\n");
    scanf("%d", &n);
    int a[n];
    printf("Enter the values\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    int l;
    printf("Enter track length\n");
    scanf("%d", &l);
    printf("Enter current position\n");
    int x;
    scanf("%d", &x);
    do
    {
        printf("-------------MENU-------------\n1)SSTF\n2)SCAN\n3)C-Look\n4)Exit\n------------------------------\n");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            sstf(n, a, x);
            break;
        case 2:
            scan(n, a, l, x);
            break;
        case 3:
            c_look(n, a, x);
            break;
        }
    } while (ch != 4);

    return 0;
}