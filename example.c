#include <stdio.h>

int main(int argc, char **argv)
{
    char *buffer = NULL;
    FILE *fl = fopen("some_non_existing_file", "rt");

    // [ 1 ] oops: forgot to check if fl == NULL ...
    // [ 2 ] oops: forgot to allocate memory for buffer ...
    fscanf(fl, "%s", buffer);

    char *p = strchr(buffer, ":");

    // [ 3 ] oops: forgot to check if p == NULL
    strcpy(dst, p);

    // [ 4 ] oops: forgot to close the open file ...
    // [ 5 ] oops: forgot to explictly return a value from main ...
}
