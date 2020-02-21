/*
*	병렬 데이터 처리 커널 함수 이해 및 호스트 코드 작성
*/

////////////////////////////////////////////////////////////////////////////////

#include "../common.cuh"

#define MEM_SIZE 10

__global__ void Kernel_DataParallel(int *A, int *B, int *C, int numElements)
{
	/*
	 * 커널 호출시 받은 <<<블록의 갯수,블록당 스레드의 갯수>>> 를 통해
	 * 전체 스레드를 일렬로 줄 세우기 (고유 번호 부여)
	 */
	int tid = blockDim.x * blockIdx.x + threadIdx.x;

	/*
	 * tid < numElements 의 의미
	 * 연산 데이터의 갯수와 딱 맞는 갯수의 스레드를 사용하는 것은 쉽지 않으므로,
	 * 스레드의 갯수를 충분히 주되 연산 데이터 갯수만큼의 스레드들만 연산을 수행하도록 함
	 */
	if (tid < numElements)
	{
		C[tid] = A[tid] + B[tid];
	}

	// To do 다른 연산을 추가해 보세요.
}

void SequentialAdd(const int *a, const int *b, int *result, int numElements)
{
	for (int i = 0; i < numElements; i++)
	{
		result[i] = a[i] + b[i];
	}
}

void DataParallel()
{
	int numElements = MEM_SIZE;

	size_t bufferSize = numElements * sizeof(int);

	/* 호스트 메모리 할당 */
	int *A = (int *)malloc(bufferSize);
	int *B = (int *)malloc(bufferSize);
	int *C = (int *)malloc(bufferSize);
	int *CSeq = (int *)malloc(bufferSize);

	/* 호스트 메모리 할당 에러 처리 */
	if (A == NULL || B == NULL || C == NULL)
	{
		fprintf(stderr, "호스트 메모리 할당 실패... 종료\n");
		exit(EXIT_FAILURE);
	}

	/* 호스트 데이터 입력 */
	for (int i = 0; i < numElements; i++)
	{
		A[i] = i;
		B[i] = i;
		C[i] = 0;
	}

	/* 호스트 입력 데이터 확인 */
	printf("=== A 입력 값 ===\n");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");

	printf("\n");
	printf("=== B 입력 값 ===\n");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d ", B[i]);
	}
	printf("\n");

	/* 시퀀셜 합 */
	SequentialAdd(A, B, CSeq, numElements);

	/* 시퀀셜 결과 출력 */
	printf("\n");
	printf("=== 시퀀셜 결과 출력 ===\n");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d ", CSeq[i]);
	}
	printf("\n");

	//////////////////////////////////////////////////////////////////
	
	printf("\n");
	printf("------------------- 시작 --------------------\n");

	/* 디바이스 변수 선언 */
	int *devA = NULL;
	int *devB = NULL;
	int *devC = NULL;

	/* 디바이스 메모리 할당 */
	CheckCudaError(cudaMalloc((void **)&devA, bufferSize));
	CheckCudaError(cudaMalloc((void **)&devB, bufferSize));
	CheckCudaError(cudaMalloc((void **)&devC, bufferSize));

	/* 호스트 -> 디바이스 입력 데이터 복사 */
	CheckCudaError(cudaMemcpy(devA, A, bufferSize, cudaMemcpyHostToDevice));
	CheckCudaError(cudaMemcpy(devB, B, bufferSize, cudaMemcpyHostToDevice));

	/* 데이터 병렬 연산 커널 함수 실행 */
	int threadsPerBlock = 5;
	int blocksPerGrid = numElements;
	Kernel_DataParallel<<<blocksPerGrid,threadsPerBlock>>>(devA, devB, devC, numElements);

	cudaError_t err = cudaGetLastError();
	if (err != cudaSuccess)
	{
		fprintf(stderr, "에러 코드: %s ... 종료\n", cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	/* 디바이스 -> 호스트 출력 데이터 복사 */
	CheckCudaError(cudaMemcpy(C, devC, bufferSize, cudaMemcpyDeviceToHost));

	/* 결과 출력 */
	printf("\n");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d ", C[i]);
	}
	printf("\n");

	/* 디바이스 메모리 해제 */
	CheckCudaError(cudaFree(devA));
	CheckCudaError(cudaFree(devB));
	CheckCudaError(cudaFree(devC));

	/* 호스트 메모리 해제 */
	free(A);
	free(B);
	free(C);
	free(CSeq);

	printf("\n");
	printf("----------------- 정상 종료 -----------------\n");
	printf("\n");
}