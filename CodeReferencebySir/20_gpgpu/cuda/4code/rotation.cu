#include "../common.cuh"

#include "../bmpfuncs.h"

__global__ void Kernel_Rotation(float *destData, float *srcData, int width, int height, float sinTheta, float cosTheta)
{
	/* 블럭, 스레드 기준 각각 x축, y축 옵셋 */
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	/* 우리가 원하는 아웃풋 이미지 기준 옵셋 */
	int offset = y * width + x;
	
	/*
	 * 일을 하지 않아도 되는 스레드는 제외하기 위해 if 문을 사용
	 * (해당 범위 내의 스레드만 일을 하도록 함)
	 * 호스트 코드에서 커널 함수로 인자를 전달할 때
	 * 이미지 가로 x 세로 사이즈와 동일한 스레드 갯수로 전달하여 if 문 없이 사용하는 것이 좋음
	 */
	if (x < width && y < height) 
	{
		/* 로테이션 기능 구현 */
		float x0 = width / 2.0f;
		float y0 = height / 2.0f;

		float xOffset = x - x0;
		float yOffset = y - y0;

		int xPos = (int)(xOffset * cosTheta + yOffset * sinTheta + x0);
		int yPos = (int)(yOffset * cosTheta - xOffset * sinTheta + y0);

		if ((xPos >= 0) && (xPos < width) && (yPos >= 0) && (yPos < height))
		{
			destData[offset] = srcData[yPos * width + xPos];
		}
	}
}

void Rotation()
{
	/* 호스트 데이터 입력 */
	float theta = 3.14159f / 6.0f;
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);
	printf("theta = %f (cos theta = %f, sin theta = %f)\n", theta, cosTheta, sinTheta);

	int imageWidth, imageHeight;
	const char *inputFile = ".\\4code\\input.bmp";
	const char *outputFile = ".\\4code\\output.bmp";

	/* 이미지 로드 */
	float *inputImage = ReadImage(inputFile, &imageWidth, &imageHeight);
	int imageSize = imageWidth * imageHeight;
	
	/* 호스트 메모리 할당 */
	float *outputImage = (float *)malloc(imageSize * sizeof(float));
	
	/* 호스트 메모리 할당 에러 처리 */
	if (outputImage == NULL)
	{
		fprintf(stderr, "호스트 메모리 할당 실패... 종료\n");
		exit(EXIT_FAILURE);
	}

	printf("%d\n", imageWidth);
	printf("%d\n", imageHeight);
	printf("%f\n", sinTheta);
	printf("%f\n", cosTheta);

	/* 디바이스 변수 선언 */
	float *devOutput = NULL;
	float *devInput = NULL;

	/* 디바이스 메모리 할당 */
	CheckCudaError(cudaMalloc((void **)&devOutput, imageSize * sizeof(float)));
	CheckCudaError(cudaMalloc((void **)&devInput, imageSize * sizeof(float)));

	/* 호스트 -> 디바이스 입력 데이터 복사 */
	CheckCudaError(cudaMemcpy(devInput, inputImage, imageSize * sizeof(float), cudaMemcpyHostToDevice));

	/***********************************************************************************************************************************
	/ 블록 갯수 및 블록당 스레드의 갯수를 지정하는 방식은 다음과 같이 두 가지로 생각해 볼 수 있다.
	/***********************************************************************************************************************************
	/ (1) 연산량을 알고 GPU 스펙 내에서의 연산 수행
	/ 바람직한 블록의 사용 갯수는 다음과 같을 것이다.
	/ 
	/ imageWidth 또는 imageHeight 가 0 일 때 dimGrid 는 (0, 0)
	/ imageWidth 또는 imageHeight 가 1 이상 dimBlock.x, dimBlock.y 이하일 때 dimGrid 는 (1, 1) (블록 1 개)
	/ imageWidth 또는 imageHeight 가 dimBlock.x + 1, dimBlock.y + 1 이상 2 * dimBlock.x, 2 * dimBlock.y 이하일 때 dimGrid 는 (2, 2) (블록 2 x 2 개)
	/ ...
	/
	/ 그러나, 다음 블록 갯수 선언문에서, 단순히 dim3 dimGrid(imageWidth / dimBlock.x, imageHeight / dimBlock.y) 로 선언할 경우 문제가 발생한다.
	/ 문제는 "(정수형) / (정수형)" 식은 몫을 구하는 연산이기 때문에 나뉘는 값이 나누는 값보다 1 만 작더라도 나머지가 다 버려지므로 갯수를 제대로 반영하지 못한다.
	/ 
	/ 예를 들어, 사용자가 "(가로 1 이상 imageWidth 미만) x (세로 1 이상 imageHeight 미만)" 갯수의 스레드를 사용하고자 할 때 블록의 갯수가 0 이 되어버린다.
	/ 결국 사용하고자 하는 스레드의 갯수가 imageWidth(imageHeight) 의 배수가 아닌 경우 블록의 갯수가 모자라게 된다.
	/ 
	/ 따라서 이러한 문제점을 보완하기 위해 다음과 같이 처리를 해 주는 것이 바람직하다.
	/ (이렇게 하면 또 사용되지 않는데도 불구하고 더 많은 갯수의 스레드가 포함될 수 있게 되는데, 이는 커널 함수 내에서 if 문으로 제어해 준다.)
	/***********************************************************************************************************************************
	/ (2) 연산량을 모르거나, 연산량을 알지만 GPU 스펙을 초과하는 대량의 연산 수행
	/ 위의 방법보다 더욱 '정석'적인 사용 방식은 사용자가 사용 중인 GPU 스펙의 최대 블록 갯수 및 최대 스레드의 갯수를 초과하지 않도록
	/ 블록의 갯수와 블록당 스레드의 갯수를 적절히 그리고 정확히 명시하고, 커널 함수 내에서 while 문으로 스레드의 작업 수행을 제어하는 것이 가장 좋다.
	/***********************************************************************************************************************************/
	
	/*
	 * 이미지 사이즈를 알고 있고, 또 이미지 사이즈가 GPU 스펙상 블록의 최대 갯수를 넘지 않으므로 (1) 방식 사용
	 * 여기에서, 다음과 같이 이미지의 가로와 세로 사이즈만큼 정확히 지정해 주면 커널 함수 내에서 if 문을 사용할 필요가 없으며,
	 * 또한 최대 블록 갯수를 초과하지 않을 경우 while 문도 사용할 필요가 없음.
	 * (최대 블록 갯수를 초과하는 대량 연산의 경우 커널 함수 내에서 while 문을 통해 한 스레드당 여러 번 일을 하도록 처리해야 함
	 * 
	 * 예컨대, 스레드 갯수: 30 x 20 / 블록 갯수: 20 x 20
	 */
	int xN = 30; // 블록당 사용할 x축 스레드의 갯수
	int yN = 20; // 블록당 사용할 y축 스레드의 갯수
	dim3 dimBlock(xN, yN);
	dim3 dimGrid((imageWidth + dimBlock.x - 1) / dimBlock.x, (imageHeight + dimBlock.y - 1) / dimBlock.y);
	
	/* 이미지 로테이션 커널 함수 실행 */
	Kernel_Rotation<<<dimGrid,dimBlock>>>(devOutput, devInput, imageWidth, imageHeight, sinTheta, cosTheta);

	/* 커널 함수 에러 처리 */
	cudaError_t err = cudaGetLastError();
	if (err != cudaSuccess)
	{
		fprintf(stderr, "에러 코드: %s ... 종료\n", cudaGetErrorString(err));
		if (err == cudaErrorInvalidConfiguration)
		{
			printf("블록당 사용 가능한 최대 스레드 갯수를 초과했습니다!\n\
실습 2code 의 'Maximum number of threads per block' 항목을 참조하여\n\
dimBlock 의 파라미터를 알맞은 값으로 바꾸세요.\n");
		}
		exit(EXIT_FAILURE);
	}

	/* 디바이스 -> 호스트 출력 데이터 복사 */
	CheckCudaError(cudaMemcpy(outputImage, devOutput, imageSize * sizeof(float), cudaMemcpyDeviceToHost));

	/* 결과 이미지 저장 */
	StoreImage(outputImage, outputFile, imageHeight, imageWidth, inputFile);

	/* 디바이스 메모리 해제 */
	CheckCudaError(cudaFree(devOutput));
	CheckCudaError(cudaFree(devInput));

	/* 호스트 메모리 해제 */
	free(outputImage);
}