all:	loop.x pi.x
	

loop.x:
	gcc loop_schedule.c -o loop.x -fopenmp

pi.x:
	gcc pi_par.c -o pi.x -fopenmp

clean:
	rm approx_pi.x pi.x