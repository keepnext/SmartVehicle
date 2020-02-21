/*
*	���� ������ ó�� Ŀ�� �Լ� ���� �� ȣ��Ʈ �ڵ� �ۼ�
*/

////////////////////////////////////////////////////////////////////////////////

#include "../common.cuh"

#define MEM_SIZE 10

__global__ void Kernel_DataParallel(int *A, int *B, int *C, int numElements)
{
	/*
	 * Ŀ�� ȣ��� ���� <<<����� ����,��ϴ� �������� ����>>> �� ����
	 * ��ü �����带 �Ϸķ� �� ����� (���� ��ȣ �ο�)
	 */
	int tid = blockDim.x * blockIdx.x + threadIdx.x;

	/*
	 * tid < numElements �� �ǹ�
	 * ���� �������� ������ �� �´� ������ �����带 ����ϴ� ���� ���� �����Ƿ�,
	 * �������� ������ ����� �ֵ� ���� ������ ������ŭ�� ������鸸 ������ �����ϵ��� ��
	 */
	if (tid < numElements)
	{
		C[tid] = A[tid] + B[tid];
	}

	// To do �ٸ� ������ �߰��� ������.
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

	/* ȣ��Ʈ �޸� �Ҵ� */
	int *A = (int *)malloc(bufferSize);
	int *B = (int *)malloc(bufferSize);
	int *C = (int *)malloc(bufferSize);
	int *CSeq = (int *)malloc(bufferSize);

	/* ȣ��Ʈ �޸� �Ҵ� ���� ó�� */
	if (A == NULL || B == NULL || C == NULL)
	{
		fprintf(stderr, "ȣ��Ʈ �޸� �Ҵ� ����... ����\n");
		exit(EXIT_FAILURE);
	}

	/* ȣ��Ʈ ������ �Է� */
	for (int i = 0; i < numElements; i++)
	{
		A[i] = i;
		B[i] = i;
		C[i] = 0;
	}

	/* ȣ��Ʈ �Է� ������ Ȯ�� */
	printf("=== A �Է� �� ===\n");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");

	printf("\n");
	printf("=== B �Է� �� ===\n");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d ", B[i]);
	}
	printf("\n");

	/* ������ �� */
	SequentialAdd(A, B, CSeq, numElements);

	/* ������ ��� ��� */
	printf("\n");
	printf("=== ������ ��� ��� ===\n");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d ", CSeq[i]);
	}
	printf("\n");

	//////////////////////////////////////////////////////////////////
	
	printf("\n");
	printf("------------------- ���� --------------------\n");

	/* ����̽� ���� ���� */
	int *devA = NULL;
	int *devB = NULL;
	int *devC = NULL;

	/* ����̽� �޸� �Ҵ� */
	CheckCudaError(cudaMalloc((void **)&devA, bufferSize));
	CheckCudaError(cudaMalloc((void **)&devB, bufferSize));
	CheckCudaError(cudaMalloc((void **)&devC, bufferSize));

	/* ȣ��Ʈ -> ����̽� �Է� ������ ���� */
	CheckCudaError(cudaMemcpy(devA, A, bufferSize, cudaMemcpyHostToDevice));
	CheckCudaError(cudaMemcpy(devB, B, bufferSize, cudaMemcpyHostToDevice));

	/* ������ ���� ���� Ŀ�� �Լ� ���� */
	int threadsPerBlock = 5;
	int blocksPerGrid = numElements;
	Kernel_DataParallel<<<blocksPerGrid,threadsPerBlock>>>(devA, devB, devC, numElements);

	cudaError_t err = cudaGetLastError();
	if (err != cudaSuccess)
	{
		fprintf(stderr, "���� �ڵ�: %s ... ����\n", cudaGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	/* ����̽� -> ȣ��Ʈ ��� ������ ���� */
	CheckCudaError(cudaMemcpy(C, devC, bufferSize, cudaMemcpyDeviceToHost));

	/* ��� ��� */
	printf("\n");
	for (int i = 0; i < numElements; i++)
	{
		printf("%d ", C[i]);
	}
	printf("\n");

	/* ����̽� �޸� ���� */
	CheckCudaError(cudaFree(devA));
	CheckCudaError(cudaFree(devB));
	CheckCudaError(cudaFree(devC));

	/* ȣ��Ʈ �޸� ���� */
	free(A);
	free(B);
	free(C);
	free(CSeq);

	printf("\n");
	printf("----------------- ���� ���� -----------------\n");
	printf("\n");
}