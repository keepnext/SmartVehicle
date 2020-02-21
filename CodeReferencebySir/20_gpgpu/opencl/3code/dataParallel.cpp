#include "../common.h"

#define MEM_SIZE 10

void scalar_add(int n, const int *a, const int *b, int *result)
{
	int i;
	for (i = 0; i < n; i++) {
		result[i] = a[i] + b[i];
	}
}

void dataParallel()
{
	cl_int				ret;

	cl_platform_id		platform_id = NULL;
	cl_device_id		device_id = NULL;

	// �޸� ��ü �߰�
	cl_mem				Amemobj = NULL;
	cl_mem				Bmemobj = NULL;
	cl_mem				Cmemobj = NULL;

	cl_context			context = NULL;
	cl_command_queue	command_queue = NULL;

	cl_program			program = NULL;

	// �����ͺ����� task 1���̹Ƿ� Ŀ�� 1�� ����
	cl_kernel			kernel;

	char*				strCode = NULL;
	size_t				strCodeSize = 0;

	int i, j;
	int* A;
	int* B;
	int* C;

	A = (int*)malloc(MEM_SIZE * sizeof(int));
	B = (int*)malloc(MEM_SIZE * sizeof(int));
	C = (int*)malloc(MEM_SIZE * sizeof(int));

	for (i = 0; i < MEM_SIZE; i++) {
		A[i] = i;
		B[i] = i;
	}
	
	int* C_Seq;
	C_Seq = (int*)malloc(MEM_SIZE * sizeof(int));
	perfCounter(true);
	scalar_add(MEM_SIZE, A, B, C_Seq);
	perfCounter();

	// ������ ��� ���
	printf("\n");
	printf("=== ������ ������===\n");
	for (i = 0; i < MEM_SIZE; i++) {
		printf("%d ", C_Seq[i]);
	}
	printPerfCounter();

	//////////////////////////////////////////////////////////////////
	printPlatformList(&platform_id, &device_id, 0, 0);

	// .cl����
	loadKernelCode("./3code/dataParallel.cl", &strCode, &strCodeSize);

	cout << "\n------------------- ���� --------------------\n" << endl;

	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	Amemobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);
	Bmemobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);
	Cmemobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);

	program = clCreateProgramWithSource(context, 1, (const char **)&strCode,
		(const size_t *)&strCodeSize, &ret);

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	// ������ ���� �۾��� �����ϴ� OpenCL Ŀ�� ����
	kernel = clCreateKernel(program, "dataParallel", &ret);

	// OpenCL Ŀ�� �Ķ���� ����
	// data ���� �� Ŀ�� ����
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&Amemobj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&Bmemobj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&Cmemobj);

	printf("=== A: �Է°� ===\n");
	for (i = 0; i < MEM_SIZE; i++) {
		printf("%d ", A[i]);
	}
	printf("\n=== B: �Է°� ===\n");
	for (i = 0; i < MEM_SIZE; i++) {
		printf("%d ", B[i]);
	}

	////////////////////////////////////////////////////
	// ���� ó�� ���� ����

	// �Է� �����͸� �޸� ���ۿ� ����
	ret = clEnqueueWriteBuffer(command_queue, Amemobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, Bmemobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), B, 0, NULL, NULL);

	perfCounter(true);

	// OpenCL Ŀ�η� ������ ������ ����
	// ������ ���� �� ť�� ���
	size_t global_item_size = MEM_SIZE; // 4 * 1
	size_t local_item_size = 5;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

	// ����� ȣ��Ʈ�� ���� 
	ret = clEnqueueReadBuffer(command_queue, Cmemobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), C, 0, NULL, NULL);

	perfCounter();
	// ���� ó�� ���� ��
	////////////////////////////////////////////////////

	// ��� ���
	printf("\n");
	printf("=== ������===\n");
	for (i = 0; i < MEM_SIZE; i++) {
		printf("%d ", C[i]);
	}

	printf("\n");
	ret = clFlush(command_queue);
	ret = clFinish(command_queue);

	ret = clReleaseKernel(kernel);
	ret = clReleaseMemObject(Amemobj);
	ret = clReleaseMemObject(Bmemobj);
	ret = clReleaseMemObject(Cmemobj);

	ret = clReleaseProgram(program);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	cout << "\n----------------- �������� -----------------\n" << endl;
	printPerfCounter();
}