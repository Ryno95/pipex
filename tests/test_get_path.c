#include "ctest.h"
#include "../pipex.h"

CTEST(test_get_path, does_not_exist)
{
    ASSERT_NULL(get_executable_path(NULL, "ls"));
}

CTEST(test_get_path, returns_ls_path)
{
    ASSERT_STR("/bin/ls", get_executable_path("PATH=/Users/rmeiboom/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/rmeiboom/.brew/bin", "ls"));
}

CTEST(test_get_path, returns_wc_path)
{
    ASSERT_STR("/usr/bin/wc", get_executable_path("PATH=/Users/rmeiboom/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/rmeiboom/.brew/bin", "wc"));
}