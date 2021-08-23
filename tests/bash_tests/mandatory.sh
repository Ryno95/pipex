#!/bin/bash

SUCCESS_COLOR="\033[01;32m"
ERROR_COLOR="\033[01;31m"
NORMAL_COLOR="\033[0m"

error_string="USAGE: ./pipex file1 cmd1 cmd2 file2: Undefined error: 0"

var="$(./pipex cmd1)" 

# ./pipex cmd1 
# if [[ $var =~ "USAGE: ./pipex file1 cmd1 cmd2 file2: Undefined error: 0\n" ]]; then
#     printf "$SUCCESS_COLOR [OK]\n"
# else
#      printf "$ERROR_COLOR [KO]\n"
# fi
# rm -f err
echo "$var"
echo "$var"
echo "$var"
echo "$var"

printf "$NORMAL_COLOR Basic test: "
./pipex tests/bash_tests/small "cat -e" "wc -l" res1 
< tests/bash_tests/small cat -e | wc -l > res2 
if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Bonus with one pipe: "
./pipex tests/bash_tests/small "cat -e" "wc -l" res1 
< tests/bash_tests/small cat -e | wc -l > res2 
if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2