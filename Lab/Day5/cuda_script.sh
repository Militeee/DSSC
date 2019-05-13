#!/bin/bash

module load cudatoolkit/10.0


for i in `seq 10`; do
  ~/my_fork/Lab/Day5/Test/fast_transpose_64.x 8 8 >> ft_64.txt
  ~/my_fork/Lab/Day5/Test/fast_transpose_128.x 8 16 >> ft_128.txt
  ~/my_fork/Lab/Day5/Test/fast_transpose_256.x 16 16 >> ft_256.txt
  ~/my_fork/Lab/Day5/Test/fast_transpose_512.x 16 32 >> ft_512.txt
  ~/my_fork/Lab/Day5/Test/fast_transpose_1024.x 32 32 >> ft_1024.txt
done