all: mpi_chain.x parallel_identity.x

mpi_chain.x: mpi_chain.c
	mpicc -fopenmp $^ -o $@ -std=c11
parallel_identity.x: parallel_identity.c
	mpicc -fopenmp $^ -o $@ -std=c11
