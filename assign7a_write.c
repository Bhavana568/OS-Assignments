#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#define MAX_BUF 1000

int main()
{

    int r, w, c = 0;
    char data[MAX_BUF];
    char countdata[MAX_BUF];
    char *fifo1 = "fifo1";

    char *fifo2 = "fifo2";

    // creating a fifo pipeline
    mkfifo(fifo1, 0666);
    w = open(fifo1, O_WRONLY);

    char st;
    printf("Enter a paragraph and press #:\n");

    //While standard input is not #
    while ((st = getchar()) != '#')
    {

        data[c++] = st;
        data[c] = '\0';
    }

    write(w, data, sizeof(data));
    close(w);
    unlink(fifo1);
    mkfifo(fifo2, 0666);
    r = open(fifo2, O_RDONLY);
    read(r, countdata, sizeof(countdata));
    printf("\n\nContent of the file from Pipe 2 :\n");
    printf("%s", countdata);
    close(r);
}