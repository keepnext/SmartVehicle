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

	// 메모리 객체 추가
	cl_mem				Amemobj = NULL;
	cl_mem				Bmemobj = NULL;
	cl_mem				Cmemobj = NULL;

	cl_context			context = NULL;
	cl_command_queue	command_queue = NULL;

	cl_program			program = NULL;

	// 데이터병렬은 task 1개이므로 커널 1개 생성
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

	// 시퀀셜 결과 출력
	printf("\n");
	printf("=== 시퀀셜 결과출력===\n");
	for (i = 0; i < MEM_SIZE; i++) {
		printf("%d ", C_Seq[i]);
	}
	printPerfCounter();

	//////////////////////////////////////////////////////////////////
	printPlatformList(&platform_id, &device_id, 0, 0);

	// .cl변경
	loadKernelCode("./3code/dataParallel.cl", &strCode, &strCodeSize);

	cout << "\n------------------- 시작 --------------------\n" << endl;

	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);

	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

	Amemobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);
	Bmemobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);
	Cmemobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(float), NULL, &ret);

	program = clCreateProgramWithSource(context, 1, (const char **)&strCode,
		(const size_t *)&strCodeSize, &ret);

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);

	// 데이터 병렬 작업을 실행하는 OpenCL 커널 생성
	kernel = clCreateKernel(program, "dataParallel", &ret);

	// OpenCL 커널 파라미터 설정
	// data 병렬 시 커널 설정
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&Amemobj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *)&Bmemobj);
	ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void *)&Cmemobj);

	printf("=== A: 입력값 ===\n");
	for (i = 0; i < MEM_SIZE; i++) {
		printf("%d ", A[i]);
	}
	printf("\n=== B: 입력값 ===\n");
	for (i = 0; i < MEM_SIZE; i++) {
		printf("%d ", B[i]);
	}

	////////////////////////////////////////////////////
	// 병렬 처리 구역 시작

	// 입력 데이터를 메모리 버퍼에 복사
	ret = clEnqueueWriteBuffer(command_queue, Amemobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), A, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(command_queue, Bmemobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), B, 0, NULL, NULL);

	perfCounter(true);

	// OpenCL 커널로 데이터 병렬을 실행
	// 데이터 병렬 시 큐잉 방법
	size_t global_item_size = MEM_SIZE; // 4 * 1
	size_t local_item_size = 5;
	ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_item_size, &local_item_size, 0, NULL, NULL);

	// 결과를 호스트에 복사 
	ret = clEnqueueReadBuffer(command_queue, Cmemobj, CL_TRUE, 0, MEM_SIZE * sizeof(float), C, 0, NULL, NULL);

	perfCounter();
	// 병렬 처리 구역 끝
	////////////////////////////////////////////////////

	// 결과 출력
	printf("\n");
	printf("=== 결과출력===\n");
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

	cout << "\n----------------- 정상종료 -----------------\n" << endl;
	printPerfCounter();
}