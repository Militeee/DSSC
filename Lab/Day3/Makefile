all: pi_MPI.x pi_hybrid.x

pi_MPI.x: pi_MPI.c
	mpicc -fopenmp pi_MPI.c -o pi_MPI.x
pi_hybrid.x: pi_hybrid.c
	mpicc -fopenmp pi_hybrid.c -o pi_hybrid.x