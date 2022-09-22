#! /bin/bash
for k in {1..10}
do
    for size in 10000000 12000000 14000000
    do
        for steps in 100 200 250
        do
            echo "iteracion $k"
            ./process $i $j >> process.txt
            for threads in 2 4 6

            do
        done
    done
done