#!/bin/bash


gcc timeSort.c
./a.out

python3 graph.py
for i in {0..6}
do
    rm time_complexity_$i.dat
done
rm a.out
