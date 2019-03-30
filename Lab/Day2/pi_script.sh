#!/bin/bash
cd ./my_fork/Lab/Day2

for i in 1 2 4 8 16 20; do
	echo \#$i
	./pi_reduce.x $i
	./pi_atom.x $i
	./pi_crit.x $i
done;
