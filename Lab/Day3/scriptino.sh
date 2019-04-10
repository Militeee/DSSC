#!/bin/bash
module load openmpi
for i in 1 2 4 8 16 20 32 40; do
    echo \#$i
    mpirun -n $i pi_MPI.x |& grep time
done

for i in 1 2 4 6 8 10 15 20; do
    echo \#$i
    mpirun -np 2 -pernode  -bind-to none pi_hybrid.x $i |& grep time


done
