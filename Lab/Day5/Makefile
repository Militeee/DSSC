exe:
	nvcc -O3 fast_transpose.cu -o fast_transpose.x
	nvcc -O3 fast_transpose2.cu -o fast2_transpose.x
all:
	make exe
	nvcc -O3 Test/fast_transpose_64.cu -o Test/fast_transpose_64.x
	nvcc -O3 Test/fast_transpose_128.cu -o Test/fast_transpose_128.x
	nvcc -O3 Test/fast_transpose_256.cu -o Test/fast_transpose_256.x
	nvcc -O3 Test/fast_transpose_512.cu -o Test/fast_transpose_512.x
	nvcc -O3 Test/fast_transpose_1024.cu -o Test/fast_transpose_1024.x
	nvcc -O3 Test/fast_transpose2_64.cu -o Test/fast_transpose2_64.x
	nvcc -O3 Test/fast_transpose2_128.cu -o Test/fast_transpose2_128.x
	nvcc -O3 Test/fast_transpose2_256.cu -o Test/fast_transpose2_256.x
	nvcc -O3 Test/fast_transpose2_512.cu -o Test/fast_transpose2_512.x
	nvcc -O3 Test/fast_transpose2_1024.cu -o Test/fast_transpose2_1024.x

