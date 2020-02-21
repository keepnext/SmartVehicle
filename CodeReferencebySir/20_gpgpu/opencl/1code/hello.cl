#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable

__constant char share[] = "Hello OpenCL!\n";

__kernel 
void hello(__global char* arg)
{
	arg[0] = 'H';
	arg[1] = 'e';
	arg[2] = 'l';
	arg[3] = 'l';
	arg[4] = 'o';
	arg[5] = ',';
	arg[6] = ' ';
	arg[7] = 'W';
	arg[8] = 'o';
	arg[9] = 'r';
	arg[10] = 'l';
	arg[11] = 'd';
	arg[12] = '!';
	arg[13] = '\0';

	printf("in Kernel: %s\n", share);

	// return 기능이 존재하지않음
	// CPU Mem -> GPU Mem
	// GPU Mem -> GPU Mem
	//__kernel void func(int *data)
	//__kernel int func(int *data);
}

// [To do1]
// 커널 함수를 hello2(__global int arg)를 추가하고
// Host 코드에서 메세지 큐에 hello2 커널을 자시하세요
// 그리고 받은 arg값을 화면에 출력하세요
__kernel
void hello2(int arg)
{
	printf("hello2 in Kernel: %s\n", share);
}