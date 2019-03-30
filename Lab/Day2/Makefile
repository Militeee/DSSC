all:	loop.x pi_atom.x pi_crit.x pi_reduce.x


loop.x:
	gcc loop_schedule.c -o loop.x -fopenmp

pi_atom.x:
	gcc -O3 pi_atom.c -o pi_atom.x -fopenmp

pi_crit.x:
	gcc -O3 pi_crit.c -o pi_crit.x -fopenmp

pi_reduce.x:
	gcc -O3 pi_reduce.c -o pi_reduce.x -fopenmp


clean:
	rm approx_pi.x pi.x