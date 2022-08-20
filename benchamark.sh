#! /bin/bash
for i in 1000 1500 2000 2500 5000 6000 7000 8000 10000
do
echo "running sequential"
./sequential $i >> sequential.txt 
done

for j in 2 4 6 8 16
do
for i in 1000 1500 2000 2500 5000 6000 7000 8000 10000
do
echo "running threads $j"
./$j $i >> $j.txt 
done
done