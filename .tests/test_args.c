#include "ctest.h"
#include "../srcs/headers/pipex.h"

// CTEST(check_arguments, invalid_amount)
// {
//     int     argc = 2;
//    const char    *argv[] = {"./pipex", "infile", "ls -l" ,"wc -l", "outfile"};
//     ASSERT_FALSE(is_valid_arguments(argc, argv));
// }

CTEST(check_arguments, valid_amount)
{
    int     argc = 5;
    const char    *argv[] = {"./pipex", "infile", "ls -l" ,"wc -l", "outfile"};
    ASSERT_TRUE(is_valid_arguments(argc, argv));
}
