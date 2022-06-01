#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_BUF 1000

int main()
{

    int r, w, c = 0;
    char data[MAX_BUF];
    char countdata[MAX_BUF];
    char *fifo1 = "fifo1";
    char *fifo2 = "fifo2";
    int lines = 0, chars = 0, space = 0, words = 0;
    mkfifo(fifo1, 0666);
    r = open(fifo1, O_RDONLY);
    read(r, data, sizeof(data));
    printf("\nThe data in the file from Pipe 1 is:\n%s", data);
    int i = 0;

    while (data[i] != '\0')
    {
        //Counting spaces
        if (data[i] == ' ')
        {
            space++;
        }
        //Counting lines
        else if (data[i] == '\n')
        {
            lines++;
        }
        //Counting characters
        else
        {
            chars++;
        }
        i++;
    }

    words = space + lines;
    close(r);
    //Open textfile for writing data
    FILE *write_file = fopen("data.txt", "w+");

    //Writing count data to file
    fprintf(write_file, "Number of Characters: %d\n", chars);
    fprintf(write_file, "Number of Spaces: %d\n", space);
    fprintf(write_file, "Number of Words: %d\n", words);
    fprintf(write_file, "Number of Lines: %d\n", lines);

    fclose(write_file);
    FILE *read_file = fopen("data.txt", "r");
    int j = 0;
    char ch = 0;
    while ((ch = fgetc(read_file)) != EOF)
    {

        countdata[j] = ch;
        j++;
    }
    countdata[j] = '\0';
    fclose(read_file);
    //Creating fifo pipeline for sending data
    mkfifo(fifo2, 0666);
    w = open(fifo2, O_WRONLY);
    write(w, countdata, sizeof(countdata));
    close(w);
    unlink(fifo2);
}