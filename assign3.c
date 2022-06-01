#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct process
{
    int id;
    int btime;
    int atime;
    int comp_time;
    int burst_time;
    int tat;
    int wt;
} p[100];
int context_switches = 0;

void sort(int np)
{
    struct process temp;
    for (int i = 0; i < np; i++)
    {
        for (int j = 0; j < np - i - 1; j++)
        {
            if (p[j].atime > p[j + 1].atime)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int sum_btime(int np)
{
    int tot = 0;
    for (int i = 0; i < np; i++)
    {
        tot += p[i].burst_time;
    }

    return tot;
}

int min_btime(int time, int np)
{
    int min = 999;
    int index = -1;

    for (int i = 0; i < np; i++)
    {

        if (time >= p[i].atime && p[i].btime < min && p[i].btime != 0)
        {
            min = p[i].btime;
            index = i;
        }
    }

    return index;
}

void preemptive(int np)
{
    int context = 0;

    int curr;
    sort(np);
    for (int i = 0; i < np; i++)
    {
        printf("%d, %d, %d\n", p[i].id, p[i].atime, p[i].btime);
    }
    int i = 0;
    int temp;
    // clock
    for (int time = p[0].atime; time <= sum_btime(np); time++)
    {

        printf("Printing current time : %d ", time);
        curr = min_btime(time, np);

        if (context != curr)
        {
            context_switches++;
        }
        temp = p[curr].btime;
        if (temp - 1 > 0)
        {
            p[curr].btime--;
        }
        else if (temp - 1 == 0)
        {
            p[curr].btime = 0;
            p[curr].comp_time = time + 1;
            printf("comp time : %d\n", p[curr].comp_time);
            p[curr].tat = p[curr].comp_time - p[curr].atime;
            p[curr].wt = p[curr].tat - p[curr].burst_time;
        }
        printf("Current process : %d\n", p[curr].id);

        context = curr;
    }
}

void results(int np)
{
    printf("\nScheduling\n");
    printf("\n----------------------------------");
    printf("\n%-5s%-8s%-6s%-4s%-5s%-4s", "ID", "AT", "BT", "CT", "TAT", "WT");
    printf("\n----------------------------------");
    for (int i = 0; i < np; i++)
    {
        printf("\n%-5d%-8d%-6d%-4d%-5d%-4d", p[i].id, p[i].atime, p[i].burst_time, p[i].comp_time, p[i].tat, p[i].wt);
    }
    printf("\n-----------------------------------\n");
}

// number of available processes
int av_process(int np, int time)
{
    for (int i = 0; i < np; i++)
    {
        if (time < p[i].atime)
        {
            return i - 1;
            break;
        }
    }
    return np - 1;
}

void round_robin(int np, int qtime)
{
    int time = 0; // 0 5    1 4   2 2     3 1
    int rtime;
    int av_pr = -1;
    int old_pr = 0; // processes executed once

    int context = 0;
    for (int i = 0; i < np; i++)
    {
        printf("id,at,bt: %d %d %d\n", p[i].id, p[i].atime, p[i].btime);
    }

    int queue[100];
    int front = 0;
    int rear = 0;

    // time increments till first arrival time
    while (true)
    {
        if (av_process(np, time) == 0)
        {
            av_pr = av_process(np, time);
            break;
        }
        time++;
    }

    queue[rear] = 0; // index of the processes
    rear++;

    while (front < rear)
    {
        if (context != queue[front])
        {
            context_switches++;
        }

        for (int i = 0; i < np; i++)
        {
            printf("pid , at , bt :%d, %d, %d\n", p[i].id, p[i].btime, p[i].atime);
        }
        // 5 4 3 2 1
        // 1
        rtime = qtime;
        printf("Front, rear :%d %d\n", front, rear);
        printf("p[q[Front]].btime ,qtime: %d %d", p[queue[front]].btime, qtime);
        if (p[queue[front]].btime < qtime)
        {
            rtime = p[queue[front]].btime;
        }
        printf("rtime :%d\n", rtime);
        p[queue[front]].btime -= rtime;
        time += rtime;

        printf("time :%d\n", time);
        av_pr = av_process(np, time);
        printf("%d\n", av_pr);

        if (av_pr != old_pr)
        {
            for (int i = old_pr + 1; i <= av_pr; i++)
            {
                queue[rear] = i;
                rear++;
            }
        }

        // print queue
        for (int i = front; i < rear; i++)
        {
            printf("%d ", queue[i]);
        }
        printf("\n");

        printf("btime ,index : %d %d\n", p[queue[front]].btime, queue[front]);

        // process not completed push at the end of the queue
        if (p[queue[front]].btime != 0)
        {
            queue[rear] = queue[front];
            rear++;
        }
        // burst time = 0 , calc completion time
        else
        {
            p[queue[front]].comp_time = time;
            p[queue[front]].tat = p[queue[front]].comp_time - p[queue[front]].atime;
            p[queue[front]].wt = p[queue[front]].tat - p[queue[front]].burst_time;
            ;
        }

        // print queue
        for (int i = front; i < rear; i++)
        {
            printf("%d ", queue[i]);
        }
        printf("Front, rear :%d %d\n", front, rear);
        old_pr = av_pr;

        context = queue[front];
        front++;

        for (int i = 0; i < np; i++)
        {
            printf("pid , at , bt :%d, %d, %d\n", p[i].id, p[i].btime, p[i].atime);
        }
    }

    for (int i = 0; i < rear; i++)
    {
        printf("%d ", queue[i]);
    }
}

int main()
{

    printf("Enter number of processes\n");
    int np;
    scanf("%d", &np);

    for (int i = 0; i < np; i++)
    {
        printf("Enter process id , arrival time, burst time\n");
        scanf("%d %d %d", &p[i].id, &p[i].atime, &p[i].btime);
        p[i].burst_time = p[i].btime;
    }
    printf("-----------------MENU-----------------\n");
    printf("1. SJF Preemptive\n");
    printf("2. Round robin\n");
    printf("----------------------------------------\n");
    printf("Enter option\n");
    int option;
    scanf("%d", &option);

    double sum_tat = 0;
    double sum_wt = 0;
    int qtime;

    switch (option)
    {
    case 1:
        printf("SJF preemptive\n");
        for (int i = 0; i < np; i++)
        {
            printf("%d, %d, %d\n", p[i].id, p[i].btime, p[i].atime);
        }
        preemptive(np);
        results(np);

        for (int i = 0; i < np; i++)
        {
            sum_tat += p[i].tat;
            sum_wt += p[i].wt;
        }
        printf("Average Turn around time : %f\n ", sum_tat / np);
        printf("Average Waiting time :%f \n", sum_wt / np);
        printf("Total context switches : %d\n", context_switches);
        break;

    case 2:

        printf("Round robin\n");
        printf("Enter quantum time \n");
        scanf("%d", &qtime);
        sort(np);

        round_robin(np, qtime);
        results(np);
        for (int i = 0; i < np; i++)
        {
            sum_tat += p[i].tat;
            sum_wt += p[i].wt;
        }
        printf("Average Turn around time : %f\n ", sum_tat / np);
        printf("Average Waiting time :%f \n", sum_wt / np);
        printf("Total context switches : %d\n", context_switches);
        break;

    default:

        printf("Invalid option\n");
        break;
    }

    return 0;
}