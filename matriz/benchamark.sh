#! /bin/bash
for k in {4..10}
do
    for i in 1000 2000 2500 5000 6000
    do
        for j in 2 4 6 8 16
        do
            echo "iteracion $k procesos $i con $j"
            echo "iteration $k $i $j" >> process.txt
            ./process $i $j >> process.txt
        done
    done
done