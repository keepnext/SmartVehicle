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

	// return ����� ������������
	// CPU Mem -> GPU Mem
	// GPU Mem -> GPU Mem
	//__kernel void func(int *data)
	//__kernel int func(int *data);
}

// [To do1]
// Ŀ�� �Լ��� hello2(__global int arg)�� �߰��ϰ�
// Host �ڵ忡�� �޼��� ť�� hello2 Ŀ���� �ڽ��ϼ���
// �׸��� ���� arg���� ȭ�鿡 ����ϼ���
__kernel
void hello2(int arg)
{
	printf("hello2 in Kernel: %s\n", share);
}