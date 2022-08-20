#! /bin/bash
for k {1..10}
    for i in 1000 1500 2000 2500 5000 6000 7000 8000 10000
    do
        echo "iteration $k" >> sequential.txt
        ./sequential $i >> sequential.txt 
        for j in 2 4 6 8 16
        do
            echo "iteration $k" >> $k.txt
            ./$j $i >> $j.txt
        done
    done
done