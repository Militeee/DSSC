#!/bin/bash

module load cudatoolkit/10.0


for i in `seq 10`; do
  ~/my_fork/Lab/Day5/Test/fast_transpose2_64.x >> ft2_64.txt
  ~/my_fork/Lab/Day5/Test/fast_transpose2_128.x >> ft2_128.txt
  ~/my_fork/Lab/Day5/Test/fast_transpose2_256.x >> ft2_256.txt
  ~/my_fork/Lab/Day5/Test/fast_transpose2_512.x >> ft2_512.txt
  ~/my_fork/Lab/Day5/Test/fast_transpose2_1024.x >> ft2_1024.txt
done
