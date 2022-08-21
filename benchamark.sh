#! /bin/bash
for k in {1..10}
do
    for i in 100 200 300
    do
        echo "iteration $k $i" >> sequential.txt
        ./sequential $i >> sequential.txt 
        for j in 2 4 6 8 16
        do
            echo "iteration $k $i" >> $j.txt
            ./$j $i >> $j.txt
        done
    done
done