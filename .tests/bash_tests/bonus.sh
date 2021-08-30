#!/bin/bash

SUCCESS_COLOR="\033[01;32m"
ERROR_COLOR="\033[01;31m"
NORMAL_COLOR="\033[0m"

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

printf "$NORMAL_COLOR Bonus with two pipes: "
./../../pipex small "cat -e" "grep a" "wc -l" res1 
< small cat -e | grep a | wc -l > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Bonus with 3 pipes: "
./../../pipex small "cat" "grep a" "cat -e" "wc -l" res1 
< small cat -e | grep a | cat -e | wc -l > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Bonus with 10 pipes: "
./../../pipex small "cat" "cat" "cat" "cat" "cat" "cat" "cat" "grep a" "wc -l "  res1 
< small cat | cat | cat |cat | cat | cat | cat | cat | cat |grep a | wc -l  > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2


printf "$NORMAL_COLOR Bigfile with one pipe: "
./../../pipex bigtext "cat -e" "wc -l" res1 
< bigtext cat -e | wc -l > res2

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Bigfile with two pipes: "
./../../pipex bigtext "cat -e" "grep a" "wc -l" res1 
< bigtext cat -e | grep a | wc -l > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Bigfile with 3 pipes: "
./../../pipex bigtext "cat" "grep a" "cat -e" "wc -l" res1 
< bigtext cat -e | grep a | cat -e | wc -l > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Bigfile with 10 pipes: "
./../../pipex bigtext "cat" "cat" "cat" "cat" "cat" "cat" "cat" "grep a" "wc -l "  res1 
< bigtext cat | cat | cat |cat | cat | cat | cat | cat | cat |grep a | wc -l  > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2




printf "$NORMAL_COLOR Emptyfile with one pipe: "
./../../pipex bigtext "cat -e" "wc -l" res1 
< bigtext cat -e | wc -l > res2

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Emptyfile with two pipes: "
./../../pipex bigtext "cat -e" "grep a" "wc -l" res1 
< bigtext cat -e | grep a | wc -l > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Emptyfile with 3 pipes: "
./../../pipex bigtext "cat" "grep a" "cat -e" "wc -l" res1 
< bigtext cat -e | grep a | cat -e | wc -l > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Emptyfile with 10 pipes: "
./../../pipex bigtext "echo hallo" "echo hallo" "echo hallo" "echo hallo" "echo hallo" "echo hallo" "echo hallo" "grep a" "wc -l "  res1 
< bigtext echo hallo | echo hallo | echo hallo |echo hallo | echo hallo | echo hallo | echo hallo | echo hallo | echo hallo |grep a | wc -l  > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2

printf "$NORMAL_COLOR Multi echo: "
./../../pipex bigtext "cat" "cat" "cat" "cat" "cat" "cat" "cat" "grep a" "wc -l "  res1 
< bigtext cat | cat | cat |cat | cat | cat | cat | cat | cat |grep a | wc -l  > res2 

if cmp -s "res1" "res2"
then
   printf "$SUCCESS_COLOR [OK]\n"
else
   printf "$ERROR_COLOR [KO]\n"
fi
rm -f res1 res2