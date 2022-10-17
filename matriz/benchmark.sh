#! /bin/bash
echo "iteration,size,threads,time" >> datos.csv
for threads in 2 4 6
do 
    for k in 1 2 3 4 5 6 7 8 9 10
    do
        for i in 1000 2000 2500 5000 6000
        do
            echo -n "$k,$i,$threads," >> datos.csv
            ./openmp $i $thread>> datos.csv
        done
    done
done