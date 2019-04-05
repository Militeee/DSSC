#!/bin/bash
cd ./my_fork/Lab/Day2

for i in 1 2 4 8 16 20; do
	echo \#$i
	printf "reduce\t"
	./pi_reduce.x $i
	printf "Atomic\t"
	./pi_atom.x $i
	printf "Critical1\t"
	./pi_crit.x $i
done;
