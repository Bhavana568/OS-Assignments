#include <stdio.h>
#include <unistd.h>

struct process
{
    int id;       // process id
    int alloc[5]; // allocations already made
    int max[5];
    int need[5];
    int finished; // process finished

} pr[10];

void display_table(int p, int resources)
{
    printf("\n%-7s%-13s%-5s%-6s", "Pr id", "Allocations", "Max", "Need");
    for (int i = 0; i < p; i++)

    {
        for (int j = 0; j < resources; j++)
        {
            printf("\n%-7d%-13d%-5d%-6d", pr[i].id, pr[i].alloc[j], pr[i].max[j], pr[i].need[j]);
        }
    }
}

void safe_sequence(int p, int avail[], int resources)
{
    int sseq[p]; // safe seq array
    int ind = 0;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {

            if (pr[j].finished == 0) // not finished
            {
                int flag = 0;
                for (int k = 0; k < resources; k++)
                {
                    if (pr[j].need[k] > avail[k])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    sseq[ind] = j + 1;
                    ind++;
                    for (int y = 0; y < resources; y++)
                        avail[y] += pr[j].alloc[y];
                    pr[j].finished = 1;
                }
            }
        }
    }

    printf("\nSafe sequence :\n");

    if (ind == 0)
    {
        printf("Unsafe state!!!\n");
    }
    else
    {
        for (int i = 0; i < p; i++)
        {
            printf("%d ", sseq[i]);
        }
        printf("\n");
    }
}

int main()
{
    int p;         // no of processes
    int resources; // no of resources
    int avail[3];  // available resources A B C
    printf("Enter number of processes\n");
    scanf("%d", &p);
    printf("Enter number of resources\n");
    scanf("%d", &resources);

    for (int i = 0; i < p; i++)
    {
        printf("Enter process id\n");
        scanf("%d", &pr[i].id);
        pr[i].finished = 0; // process not finished
        printf("Enter number of allocations A B C..\n");
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &pr[i].alloc[j]);
        }
        printf("Enter number of maximum allocations A B C..\n");
        for (int j = 0; j < resources; j++)
        {
            scanf("%d", &pr[i].max[j]);
            pr[i].need[j] = pr[i].max[j] - pr[i].alloc[j];
        }
    }

    printf("Enter the available number of resources A B C..\n");
    for (int j = 0; j < resources; j++)
    {
        scanf("%d", &avail[j]);
    }

    display_table(p, resources);
    safe_sequence(p, avail, resources);
}