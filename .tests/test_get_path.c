#include "ctest.h"
#include "../srcs/headers/get_exe_path.h"

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

CTEST(test_get_path, check_null_input)
{
    ASSERT_NULL(get_executable_path(NULL, NULL));
    ASSERT_NULL(get_executable_path("PATH=/Users/rmeiboom/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/rmeiboom/.brew/bin", NULL));
    ASSERT_NULL(get_executable_path(NULL, "wc"));
}

CTEST(test_get_env_var, get_path)
{
    const char    *env[] = 
    {
        "USER=rmeiboom",
        "SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.KG2bmVSEAq/Listeners",
        "__CF_USER_TEXT_ENCODING=0x12412:0x0:0x0",
        "PAGER=less",
        "HOMEBREW_CACHE=/tmp/rmeiboom/Homebrew/Caches",
        "LSCOLORS=Gxfxcxdxbxegedabagacad",
        "PATH=/Users/rmeiboom/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/rmeiboom/.brew/bin",
        "PWD=/Users/rmeiboom/Desktop/pipex",
        "LANG=en_US.UTF-8",
        "ITERM_PROFILE=Default",
        "XPC_FLAGS=0x0",
        "XPC_SERVICE_NAME=0",
        "SHLVL=3",
        "HOME=/Users/rmeiboom",
        NULL
    };
    ASSERT_STR("/Users/rmeiboom/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/rmeiboom/.brew/bin", ft_get_env_var(env, "PATH="));
}

CTEST(test_get_env_var, get_path_same_name_test)
{
    const char    *env[] = 
    {
        "USER=rmeiboom",
        "SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.KG2bmVSEAq/Listeners",
        "__CF_USER_TEXT_ENCODING=0x12412:0x0:0x0",
        "PAGER=less",
        "HOMEBREW_CACHE=/tmp/rmeiboom/Homebrew/Caches",
        "LSCOLORS=Gxfxcxdxbxegedabagacad",
        "PATH=/Users/rmeiboom/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/rmeiboom/.brew/bin",
        "PATHTest=/Users/rmeiboom/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/rmeiboom/.brew/bin",
        "PWD=/Users/rmeiboom/Desktop/pipex",
        "LANG=en_US.UTF-8",
        "ITERM_PROFILE=Default",
        "XPC_FLAGS=0x0",
        "XPC_SERVICE_NAME=0",
        "SHLVL=3",
        "HOME=/Users/rmeiboom",
        NULL
    };
    ASSERT_STR("/Users/rmeiboom/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Users/rmeiboom/.brew/bin", ft_get_env_var(env, "PATH="));
}

CTEST(test_get_env_var, check_null_input)
{
    const char    *env[] = 
    {
        "USER=rmeiboom",
        "SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.KG2bmVSEAq/Listeners",
        NULL
    };

    ASSERT_NULL(ft_get_env_var(NULL, PATH_ID));
    ASSERT_NULL(ft_get_env_var(NULL, NULL));
    ASSERT_NULL(ft_get_env_var(env, PATH_ID));
    ASSERT_NULL(ft_get_env_var(env, NULL));
}