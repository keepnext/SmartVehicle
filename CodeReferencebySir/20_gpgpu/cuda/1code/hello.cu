/*
*	Hello World! 출력 커널 함수 실습
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
// 커널 함수 hello2(__global__, int arg)를 추가하고
// Host 코드에서 hello2 커널을 호출하세요
// 그리고 받은 arg값을 화면에 출력하세요
__global__ void Kernel_Hello2(int arg)
{
	printf("hello2 in Kernel: %s\n", share);
	printf("hello2 in Kernel: %d\n", arg);
}

#define MAX_BUFFER_SIZE		(0x100)

void Hello()
{
	/* 호스트 문자열 선언 */
	char hostArg[MAX_BUFFER_SIZE] = "Before cudaMemcpy";

	/* 메모리 복사 전 확인 */
	printf("메모리 복사 전\n");
	printf("hostArg: \"%s\"\n", hostArg);

	/* 디바이스 변수 선언 */
	char *devArg;

	/* 디바이스 메모리 할당 */
	CheckCudaError(cudaMalloc((void **)&devArg, MAX_BUFFER_SIZE));

	/* 호스트 -> 디바이스 입력 데이터 복사 */
	CheckCudaError(cudaMemcpy(devArg, hostArg, MAX_BUFFER_SIZE, cudaMemcpyHostToDevice));

	Kernel_Hello<<<1,1>>>(devArg);

	/* 디바이스 -> 호스트 출력 데이터 복사 */
	CheckCudaError(cudaMemcpy(hostArg, devArg, MAX_BUFFER_SIZE, cudaMemcpyDeviceToHost));

	printf("\n");

	printf("Host -> Device / Device -> Host 메모리 복사 완료...\n");

	printf("\n");

	/* 결과 출력 및 검증 */
	printf("메모리 복사 후\n");
	printf("hostArg: \"%s\"\n", hostArg);
}