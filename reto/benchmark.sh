#! /bin/bash
for k in {1..10}
do
    for size in 10000000 12000000 14000000
    do
        for steps in 100 200 250
        do
            echo "iteracion $k $steps $size" >> sequential.txt
            ./sequential $steps $size >> sequential.txt
            for threads in 2 4 6
            do
                echo "iteracion $k $steps $size $threads" >> process.txt
                ./process $steps $size $threads >> process.txt
                echo "iteracion $k $steps $size $threads" >> threads.txt
                ./threads $steps $size $threads >> process.txt
            done  
        done
    done
done