#! /bin/bash
echo "iteration,size,steps,threads,time" >> datos.csv
for k in 1 2 3 4 5 6 7 8 9 10
do
    for size in 10000000 12000000 14000000
    do
        for steps in 100 200 250
        do
            for threads in 2 4 6
            do
                echo -n "$k,$size,$steps,$threads," >> datos.csv
                ./openmp $steps $size $threads >> datos.csv
            done  
        done
    done
done