#!/bin/bash

SUCCESS_COLOR="\033[01;32m"
ERROR_COLOR="\033[01;31m"
NORMAL_COLOR="\033[0m"

error_string="USAGE: ./pipex file1 cmd1 cmd2 file2: Undefined error: 0"

printf "$NORMAL_COLOR Basic test: "
./../../pipex small "cat -e" "wc -l" res1 
< small cat -e | wc -l > res2 
if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Bonus with one pipe: "
./../../pipex small "cat -e" "wc -l" res1 
< small cat -e | wc -l > res2 
if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2