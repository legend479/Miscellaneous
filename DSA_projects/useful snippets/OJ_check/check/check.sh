#!/bin/bash
flag=0
for (( i=0; i<$1; ++i ))
do
    python3 case.py > input.txt
    gcc -g  ../OJ.c
    ./a.out < input.txt > output_P.txt 2> error.txt
    gcc ../main.c
    ./a.out < input.txt > output_D.txt 

    if [[ ! -s error.txt ]]
    then
        if [[ -z $(diff output_D.txt output_P.txt) ]]
        then
            echo "Test case $i passed"
            rm input.txt output_P.txt output_D.txt a.out error.txt
        else
            echo "Test case $i failed"
            flag=1
            rm a.out error.txt
            break
        fi

    else
        echo "error at $i test case"
        valgrind -s --leak-check=full ./a.out < input.txt > output_P.txt 2> error.txt
        rm a.out 
        flag=1
        break
    fi
done

if [[ $flag -eq 0 ]]
then 
    echo "passed"
fi
