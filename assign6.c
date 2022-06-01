#include <stdio.h>

double page_faults = 0;

int push(int frames[], int frame_size, int x, int first)
{

    frames[first] = x;
    first = (first + 1) % frame_size;
    return first;
}

int page_present(int frames[], int frame_size, int x)
{
    for (int i = 0; i < frame_size; i++)
    {
        if (x == frames[i])
        {
            return 1;
        }
    }
    return 0;
}

void display(int frames[], int frame_size, int n)
{
    printf("Frame sequence :-\n");
    for (int i = 0; i < frame_size; i++)
    {
        printf("%d ", frames[i]);
    }
    printf("\n");
    //return page_faults;
}

void FCFS(int frames[], int frame_size, int page_seq[], int n)
{

    int first = 0;
    for (int i = 0; i < n; i++)
    {

        if (page_present(frames, frame_size, page_seq[i]) == 0)
        {
            page_faults++;
            first = push(frames, frame_size, page_seq[i], first);
        }
        printf("Page : %d\n", page_seq[i]);
        display(frames, frame_size, n);
    }
}

int replace_index_lru(int page_seq[], int frames[], int frame_size, int i)
{
    int min = i - 1;
    int result = -1;
    for (int k = 0; k < frame_size; k++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (page_seq[j] == frames[k])
            {
                if (min > j)
                {
                    min = j;
                    result = k;
                }
                break;
            }
        }
    }

    return result;
}

void LRU(int frames[], int frame_size, int page_seq[], int n)
{
    int current = 0;
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        if (page_present(frames, frame_size, page_seq[i]) == 0)
        {
            page_faults++;
            if (j < frame_size)
            {
                frames[j] = page_seq[i];
                j++;
            }
            else
            {

                current = replace_index_lru(page_seq, frames, frame_size, i);
                frames[current] = page_seq[i];
            }
        }
        display(frames, frame_size, n);
    }
}

int replace_index_op(int page_seq[], int frames[], int frame_size, int i, int n)
{
    int max = i + 1;
    int result = -1;

    for (int k = 0; k < frame_size; k++)
    {
        int j;
        for (j = i + 1; j < n; j++)
        {
            if (page_seq[j] == frames[k])
            {
                if (max < j)
                {
                    max = j;
                    result = k;
                }
                break;
            }
        }
        if (j == n)
        {
            return k;
        }
    }

    return result;
}

void optimal_policy(int frames[], int frame_size, int page_seq[], int n)
{
    int current = 0;
    int j = 0;

    for (int i = 0; i < n; i++)
    {
        if (page_present(frames, frame_size, page_seq[i]) == 0)
        {
            page_faults++;
            if (j < frame_size)
            {
                frames[j] = page_seq[i];
                j++;
            }
            else
            {

                current = replace_index_op(page_seq, frames, frame_size, i, n);
                frames[current] = page_seq[i];
            }
        }
        display(frames, frame_size, n);
    }
}
int main()
{
    int n;

    printf("Enter the number of pages\n");
    scanf("%d", &n);
    int page_seq[n];
    int frame_size;

    printf("Enter the frame size\n");
    scanf("%d", &frame_size);

    int frames[frame_size];

    printf("Enter the page sequence\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &page_seq[i]);
    }

    int op;

    // switch case
    do
    {
        page_faults = 0;
        for (int i = 0; i < frame_size; i++)
        {
            frames[i] = -1;
        }

        printf("\n-----------------MENU-----------------\n");
        printf("1. FCFS \n");
        printf("2. LRU \n");
        printf("3. Optimal policy \n");
        printf("--------------------------------------\n");
        printf("Enter your choice :\n");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            FCFS(frames, frame_size, page_seq, n);
            printf("\nTotal page faults : %f\n", page_faults);
            printf("Page Fault ratio : %f\n\n", page_faults / n);
            break;

        case 2:
            LRU(frames, frame_size, page_seq, n);
            printf("\nTotal page faults : %f\n", page_faults);
            printf("Page Fault ratio : %f\n\n", page_faults / n);

            break;

        case 3:
            optimal_policy(frames, frame_size, page_seq, n);
            printf("\nTotal page faults : %f\n", page_faults);
            printf("Page Fault ratio : %f\n\n", page_faults / n);
            break;

        default:
            printf("Invalid option! \n");
            break;
        }

    } while (op != 0);

    return 0;
}