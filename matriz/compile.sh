#! /bin/bash
for k in 1 2 3 4 5
do
    gcc "-O$k" -o optimization_$k matrix_multiplication_sequential.c
done
gcc -o cache_line cache_line.c