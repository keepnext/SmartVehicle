/*
*	Hello World! ��� Ŀ�� �Լ� �ǽ�
*/

////////////////////////////////////////////////////////////////////////////////

#include "../common.cuh"

__constant__ char share[] = "Hello CUDA!";

__device__ void CopyString(char *dest, const char *source)
{
	int i = 0;
	while (source[i] != '\0')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
}

__global__ void Kernel_Hello(char *arg)
{
	printf("\n");
	printf("We arrived in Kernel: %s\n", share);

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
	
	printf("Kernel is writing \"Hello, World!\" ...");

	const char *buff = "Good-bye CUDA!";
	CopyString(share, buff);

	printf("\n");
	printf("Now we are leaving Kernel: %s\n", share);
}

// [To do1]
// Ŀ�� �Լ� hello2(__global__, int arg)�� �߰��ϰ�
// Host �ڵ忡�� hello2 Ŀ���� ȣ���ϼ���
// �׸��� ���� arg���� ȭ�鿡 ����ϼ���
__global__ void Kernel_Hello2(int arg)
{
	printf("hello2 in Kernel: %s\n", share);
	printf("hello2 in Kernel: %d\n", arg);
}

#define MAX_BUFFER_SIZE		(0x100)

void Hello()
{
	/* ȣ��Ʈ ���ڿ� ���� */
	char hostArg[MAX_BUFFER_SIZE] = "Before cudaMemcpy";

	/* �޸� ���� �� Ȯ�� */
	printf("�޸� ���� ��\n");
	printf("hostArg: \"%s\"\n", hostArg);

	/* ����̽� ���� ���� */
	char *devArg;

	/* ����̽� �޸� �Ҵ� */
	CheckCudaError(cudaMalloc((void **)&devArg, MAX_BUFFER_SIZE));

	/* ȣ��Ʈ -> ����̽� �Է� ������ ���� */
	CheckCudaError(cudaMemcpy(devArg, hostArg, MAX_BUFFER_SIZE, cudaMemcpyHostToDevice));

	Kernel_Hello<<<1,1>>>(devArg);

	/* ����̽� -> ȣ��Ʈ ��� ������ ���� */
	CheckCudaError(cudaMemcpy(hostArg, devArg, MAX_BUFFER_SIZE, cudaMemcpyDeviceToHost));

	printf("\n");

	printf("Host -> Device / Device -> Host �޸� ���� �Ϸ�...\n");

	printf("\n");

	/* ��� ��� �� ���� */
	printf("�޸� ���� ��\n");
	printf("hostArg: \"%s\"\n", hostArg);
}