#include "ctest.h"
#include "../pipex.h"

CTEST(check_arguments, invalid_amount)
{
    printf("YOOOOOOOH\n");
    int     argc = 2;
    char    *argv[] = {"./pipex", "infile", "ls -l" ,"wc -l", "outfile"};
    ASSERT_FALSE(is_valid_arguments(argc, argv));
}


CTEST(check_arguments, valid_amount)
{
    int     argc = 5;
    char    *argv[] = {"./pipex", "infile", "ls -l" ,"wc -l", "outfile"};
    ASSERT_TRUE(is_valid_arguments(argc, argv));
}
