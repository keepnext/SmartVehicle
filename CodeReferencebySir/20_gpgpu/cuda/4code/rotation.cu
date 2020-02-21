#include "../common.cuh"

#include "../bmpfuncs.h"

__global__ void Kernel_Rotation(float *destData, float *srcData, int width, int height, float sinTheta, float cosTheta)
{
	/* ��, ������ ���� ���� x��, y�� �ɼ� */
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int y = blockIdx.y * blockDim.y + threadIdx.y;

	/* �츮�� ���ϴ� �ƿ�ǲ �̹��� ���� �ɼ� */
	int offset = y * width + x;
	
	/*
	 * ���� ���� �ʾƵ� �Ǵ� ������� �����ϱ� ���� if ���� ���
	 * (�ش� ���� ���� �����常 ���� �ϵ��� ��)
	 * ȣ��Ʈ �ڵ忡�� Ŀ�� �Լ��� ���ڸ� ������ ��
	 * �̹��� ���� x ���� ������� ������ ������ ������ �����Ͽ� if �� ���� ����ϴ� ���� ����
	 */
	if (x < width && y < height) 
	{
		/* �����̼� ��� ���� */
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
	/* ȣ��Ʈ ������ �Է� */
	float theta = 3.14159f / 6.0f;
	float cosTheta = cosf(theta);
	float sinTheta = sinf(theta);
	printf("theta = %f (cos theta = %f, sin theta = %f)\n", theta, cosTheta, sinTheta);

	int imageWidth, imageHeight;
	const char *inputFile = ".\\4code\\input.bmp";
	const char *outputFile = ".\\4code\\output.bmp";

	/* �̹��� �ε� */
	float *inputImage = ReadImage(inputFile, &imageWidth, &imageHeight);
	int imageSize = imageWidth * imageHeight;
	
	/* ȣ��Ʈ �޸� �Ҵ� */
	float *outputImage = (float *)malloc(imageSize * sizeof(float));
	
	/* ȣ��Ʈ �޸� �Ҵ� ���� ó�� */
	if (outputImage == NULL)
	{
		fprintf(stderr, "ȣ��Ʈ �޸� �Ҵ� ����... ����\n");
		exit(EXIT_FAILURE);
	}

	printf("%d\n", imageWidth);
	printf("%d\n", imageHeight);
	printf("%f\n", sinTheta);
	printf("%f\n", cosTheta);

	/* ����̽� ���� ���� */
	float *devOutput = NULL;
	float *devInput = NULL;

	/* ����̽� �޸� �Ҵ� */
	CheckCudaError(cudaMalloc((void **)&devOutput, imageSize * sizeof(float)));
	CheckCudaError(cudaMalloc((void **)&devInput, imageSize * sizeof(float)));

	/* ȣ��Ʈ -> ����̽� �Է� ������ ���� */
	CheckCudaError(cudaMemcpy(devInput, inputImage, imageSize * sizeof(float), cudaMemcpyHostToDevice));

	/***********************************************************************************************************************************
	/ ��� ���� �� ��ϴ� �������� ������ �����ϴ� ����� ������ ���� �� ������ ������ �� �� �ִ�.
	/***********************************************************************************************************************************
	/ (1) ���귮�� �˰� GPU ���� �������� ���� ����
	/ �ٶ����� ����� ��� ������ ������ ���� ���̴�.
	/ 
	/ imageWidth �Ǵ� imageHeight �� 0 �� �� dimGrid �� (0, 0)
	/ imageWidth �Ǵ� imageHeight �� 1 �̻� dimBlock.x, dimBlock.y ������ �� dimGrid �� (1, 1) (��� 1 ��)
	/ imageWidth �Ǵ� imageHeight �� dimBlock.x + 1, dimBlock.y + 1 �̻� 2 * dimBlock.x, 2 * dimBlock.y ������ �� dimGrid �� (2, 2) (��� 2 x 2 ��)
	/ ...
	/
	/ �׷���, ���� ��� ���� ���𹮿���, �ܼ��� dim3 dimGrid(imageWidth / dimBlock.x, imageHeight / dimBlock.y) �� ������ ��� ������ �߻��Ѵ�.
	/ ������ "(������) / (������)" ���� ���� ���ϴ� �����̱� ������ ������ ���� ������ ������ 1 �� �۴��� �������� �� �������Ƿ� ������ ����� �ݿ����� ���Ѵ�.
	/ 
	/ ���� ���, ����ڰ� "(���� 1 �̻� imageWidth �̸�) x (���� 1 �̻� imageHeight �̸�)" ������ �����带 ����ϰ��� �� �� ����� ������ 0 �� �Ǿ������.
	/ �ᱹ ����ϰ��� �ϴ� �������� ������ imageWidth(imageHeight) �� ����� �ƴ� ��� ����� ������ ���ڶ�� �ȴ�.
	/ 
	/ ���� �̷��� �������� �����ϱ� ���� ������ ���� ó���� �� �ִ� ���� �ٶ����ϴ�.
	/ (�̷��� �ϸ� �� ������ �ʴµ��� �ұ��ϰ� �� ���� ������ �����尡 ���Ե� �� �ְ� �Ǵµ�, �̴� Ŀ�� �Լ� ������ if ������ ������ �ش�.)
	/***********************************************************************************************************************************
	/ (2) ���귮�� �𸣰ų�, ���귮�� ������ GPU ������ �ʰ��ϴ� �뷮�� ���� ����
	/ ���� ������� ���� '����'���� ��� ����� ����ڰ� ��� ���� GPU ������ �ִ� ��� ���� �� �ִ� �������� ������ �ʰ����� �ʵ���
	/ ����� ������ ��ϴ� �������� ������ ������ �׸��� ��Ȯ�� ����ϰ�, Ŀ�� �Լ� ������ while ������ �������� �۾� ������ �����ϴ� ���� ���� ����.
	/***********************************************************************************************************************************/
	
	/*
	 * �̹��� ����� �˰� �ְ�, �� �̹��� ����� GPU ����� ����� �ִ� ������ ���� �����Ƿ� (1) ��� ���
	 * ���⿡��, ������ ���� �̹����� ���ο� ���� �����ŭ ��Ȯ�� ������ �ָ� Ŀ�� �Լ� ������ if ���� ����� �ʿ䰡 ������,
	 * ���� �ִ� ��� ������ �ʰ����� ���� ��� while ���� ����� �ʿ䰡 ����.
	 * (�ִ� ��� ������ �ʰ��ϴ� �뷮 ������ ��� Ŀ�� �Լ� ������ while ���� ���� �� ������� ���� �� ���� �ϵ��� ó���ؾ� ��
	 * 
	 * ������, ������ ����: 30 x 20 / ��� ����: 20 x 20
	 */
	int xN = 30; // ��ϴ� ����� x�� �������� ����
	int yN = 20; // ��ϴ� ����� y�� �������� ����
	dim3 dimBlock(xN, yN);
	dim3 dimGrid((imageWidth + dimBlock.x - 1) / dimBlock.x, (imageHeight + dimBlock.y - 1) / dimBlock.y);
	
	/* �̹��� �����̼� Ŀ�� �Լ� ���� */
	Kernel_Rotation<<<dimGrid,dimBlock>>>(devOutput, devInput, imageWidth, imageHeight, sinTheta, cosTheta);

	/* Ŀ�� �Լ� ���� ó�� */
	cudaError_t err = cudaGetLastError();
	if (err != cudaSuccess)
	{
		fprintf(stderr, "���� �ڵ�: %s ... ����\n", cudaGetErrorString(err));
		if (err == cudaErrorInvalidConfiguration)
		{
			printf("��ϴ� ��� ������ �ִ� ������ ������ �ʰ��߽��ϴ�!\n\
�ǽ� 2code �� 'Maximum number of threads per block' �׸��� �����Ͽ�\n\
dimBlock �� �Ķ���͸� �˸��� ������ �ٲټ���.\n");
		}
		exit(EXIT_FAILURE);
	}

	/* ����̽� -> ȣ��Ʈ ��� ������ ���� */
	CheckCudaError(cudaMemcpy(outputImage, devOutput, imageSize * sizeof(float), cudaMemcpyDeviceToHost));

	/* ��� �̹��� ���� */
	StoreImage(outputImage, outputFile, imageHeight, imageWidth, inputFile);

	/* ����̽� �޸� ���� */
	CheckCudaError(cudaFree(devOutput));
	CheckCudaError(cudaFree(devInput));

	/* ȣ��Ʈ �޸� ���� */
	free(outputImage);
}