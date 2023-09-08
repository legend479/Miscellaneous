#!/bin/bash
# $1 is the name of the file to be checked
# $2 is the number of test cases
flag=0
for (( i = 1; i <= $2; ++i ));
do
    python3 case.py >input.txt
    python3 sort.py <input.txt >true_output.txt
    gcc ../$1 
    ./a.out <input.txt >test_output.txt
    if [[ $(diff true_output.txt test_output.txt) ]];then
        echo "Wrong output in" $i "case"
        echo "ponits of difference:"
        diff true_output.txt test_output.txt
        flag=1
        echo "Input">output.txt
        cat input.txt>>output.txt
        echo "Actual Sorted output">>output.txt
        cat true_output.txt>>output.txt
        echo "Your Sorted output">>output.txt
        cat test_output.txt>>output.txt
        rm a.out true_output.txt test_output.txt input.txt
        break
    else
        rm true_output.txt test_output.txt a.out input.txt
    fi
done
if [[ $flag -eq 0 ]];then
    echo "All cases passed"
fi