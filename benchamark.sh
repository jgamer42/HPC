#! /bin/bash
for k in {3..10}
do
    for i in 1000 2000 2500 5000 6000
    do
        echo "iteracion $k probando sequencial $i"
        echo "iteration $k $i" >> sequential.txt
        ./sequential $i >> sequential.txt 
        for j in 2 4 6 8 16
        do
            echo "probando $k hilos $i con $j"
            echo "iteration $k $i" >> $j.txt
            ./$j $i >> $j.txt
        done
    done
done