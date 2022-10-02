#! /bin/bash
echo "iteration,size,time,algorithm" >> datos.csv
for algorithm in cache_line optimization_1 optimization_2 optimization_3 optimization_4 optimization_5
do
    for k in 1 2 3 4 5 6 7 8 9 10
    do
        for i in 1000 2000 2500 5000 6000
        do
            echo -n "$k,$i," >> datos.csv
            ./$algorithm $i >> datos.csv
            echo -n ",$algorithm" >> datos.csv
            echo -e "" >> datos.csv
        done
    done
done