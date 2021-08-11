#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(void)
{
    // access returns 0 if file exists, else -1
    printf("Access granted: %d\n", access("/usr/bin/wc", F_OK));
    return (0);
}