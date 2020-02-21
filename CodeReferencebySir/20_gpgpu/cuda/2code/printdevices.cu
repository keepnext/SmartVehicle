/*
*	CUDA ����̽� ���� ȹ�� ���� �Լ� �� �ڵ� �м�
*/

////////////////////////////////////////////////////////////////////////////////

#include "../common.cuh"

// SM (Streaming Multiprocessor) �������� SM �ϳ��� �ھ� ���� ��ȯ
int ConvertSMVerToCores(int major, int minor)
{
	typedef struct {
		int SM; // 16���� 0 x (SM major version) (SM minor version)
		int Cores;
	} SM2Cores;

	SM2Cores coresPerSM[] =
	{
		/* ���÷� */
		{ 0x30, 192 },
		{ 0x32, 192 },
		{ 0x35, 192 },
		{ 0x37, 192 },

		/* �ƽ��� */
		{ 0x50, 128 },
		{ 0x52, 128 },
		{ 0x53, 128 },

		/* �Ľ�Į */
		{ 0x60, 64 },
		{ 0x61, 128 },
		{ 0x62, 128 },

		/* ��Ÿ */
		{ 0x70, 64 },

		{ -1, -1 }
	};

	int i = 0;

	while (coresPerSM[i].SM != -1)
	{
		if (coresPerSM[i].SM == ((major << 4) + minor))
		{
			return coresPerSM[i].Cores;
		}

		i++;
	}

return coresPerSM[i - 1].Cores;
}

void PrintDeviceInfo(int device)
{
	int driverVersion = 0, runtimeVersion = 0;

	// CUDA ���� �Լ� / GPU �ڿ� ����� ���� �ش� ��ȣ�� ����̽� �Ҵ�
	cudaSetDevice(device);

	// CUDA ���� ����ü / ����̽� ���� ���� ����
	cudaDeviceProp deviceProp;

	// CUDA ���� �Լ��� ���� ����̽� ���� �ε�
	cudaGetDeviceProperties(&deviceProp, device);
	
	// CUDA ���� �Լ��� ���� ����̹� ����, ��Ÿ�� ���� �ε�
	cudaDriverGetVersion(&driverVersion);
	cudaRuntimeGetVersion(&runtimeVersion);

	// CUDA ���� ����ü cudaDeviceProp �� ����� ���� ���
	printf("Device %d: \"%s\"\n", device, deviceProp.name);
	printf("  CUDA Driver Version / Runtime Version:         %d.%d / %d.%d\n", driverVersion / 1000, (driverVersion % 100) / 10, runtimeVersion / 1000, (runtimeVersion % 100) / 10);
	printf("  CUDA Compute Capability version:               %d.%d\n", deviceProp.major, deviceProp.minor);
	
	printf("  Total amount of global memory:                 %.0f MBytes (%llu bytes)\n",
		(float)deviceProp.totalGlobalMem / (1024.0f * 1024.0f), (unsigned long long)deviceProp.totalGlobalMem);

	printf("  (%2d) Multiprocessors, (%3d) CUDA Cores/MP:     %d CUDA Cores\n",
		deviceProp.multiProcessorCount,
		ConvertSMVerToCores(deviceProp.major, deviceProp.minor),
		ConvertSMVerToCores(deviceProp.major, deviceProp.minor) * deviceProp.multiProcessorCount);
	
	printf("  GPU Max Clock rate:                            %.0f MHz (%0.2f GHz)\n", deviceProp.clockRate * 1e-3f, deviceProp.clockRate * 1e-6f);

#if CUDART_VERSION >= 5000
	// ��� ��Ÿ�� 5.0 �̻���� cudaDeviceProp ����ü ���� ����
	printf("  Memory Clock rate:                             %.0f MHz\n", deviceProp.memoryClockRate * 1e-3f);
	printf("  Memory Bus Width:                              %d-bit\n", deviceProp.memoryBusWidth);

	if (deviceProp.l2CacheSize)
	{
		printf("  L2 Cache Size:                                 %d bytes\n", deviceProp.l2CacheSize);
	}
#endif //CUDART_VERSION >= 5000

	printf("  Maximum Texture Dimension Size (x,y,z)         1D=(%d), 2D=(%d, %d), 3D=(%d, %d, %d)\n",
		deviceProp.maxTexture1D, deviceProp.maxTexture2D[0], deviceProp.maxTexture2D[1],
		deviceProp.maxTexture3D[0], deviceProp.maxTexture3D[1], deviceProp.maxTexture3D[2]);
	printf("  Maximum Layered 1D Texture Size, (num) layers  1D=(%d), %d layers\n",
		deviceProp.maxTexture1DLayered[0], deviceProp.maxTexture1DLayered[1]);
	printf("  Maximum Layered 2D Texture Size, (num) layers  2D=(%d, %d), %d layers\n",
		deviceProp.maxTexture2DLayered[0], deviceProp.maxTexture2DLayered[1], deviceProp.maxTexture2DLayered[2]);

	printf("  Total amount of constant memory:               %lu bytes\n", deviceProp.totalConstMem);
	printf("  Total amount of shared memory per block:       %lu bytes\n", deviceProp.sharedMemPerBlock);
	printf("  Total number of registers available per block: %d\n", deviceProp.regsPerBlock);
	printf("  Warp size:                                     %d\n", deviceProp.warpSize);
	printf("  Maximum number of threads per multiprocessor:  %d\n", deviceProp.maxThreadsPerMultiProcessor);
	printf("  Maximum number of threads per block:           %d\n", deviceProp.maxThreadsPerBlock);
	printf("  Max dimension size of a thread block (x,y,z):  (%d, %d, %d)\n",
		deviceProp.maxThreadsDim[0],
		deviceProp.maxThreadsDim[1],
		deviceProp.maxThreadsDim[2]);
	printf("  Max dimension size of a grid size    (x,y,z):  (%d, %d, %d)\n",
		deviceProp.maxGridSize[0],
		deviceProp.maxGridSize[1],
		deviceProp.maxGridSize[2]);
	printf("  Maximum memory pitch:                          %lu bytes\n", deviceProp.memPitch);
	printf("  Texture alignment:                             %lu bytes\n", deviceProp.textureAlignment);
	printf("  Concurrent copy and kernel execution:          %s with %d copy engine(s)\n", (deviceProp.deviceOverlap ? "Yes" : "No"), deviceProp.asyncEngineCount);
	printf("  Run time limit on kernels:                     %s\n", deviceProp.kernelExecTimeoutEnabled ? "Yes" : "No");
	printf("  Integrated GPU sharing Host Memory:            %s\n", deviceProp.integrated ? "Yes" : "No");
	printf("  Support host page-locked memory mapping:       %s\n", deviceProp.canMapHostMemory ? "Yes" : "No");
	printf("  Alignment requirement for Surfaces:            %s\n", deviceProp.surfaceAlignment ? "Yes" : "No");
	printf("  Device has ECC support:                        %s\n", deviceProp.ECCEnabled ? "Enabled" : "Disabled");

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
	printf("  CUDA Device Driver Mode (TCC or WDDM):         %s\n", deviceProp.tccDriver ? "TCC (Tesla Compute Cluster Driver)" : "WDDM (Windows Display Driver Model)");
#endif

	printf("  Device supports Unified Addressing (UVA):      %s\n", deviceProp.unifiedAddressing ? "Yes" : "No");
	printf("  Supports Cooperative Kernel Launch:            %s\n", deviceProp.cooperativeLaunch ? "Yes" : "No");
	printf("  Supports MultiDevice Co-op Kernel Launch:      %s\n", deviceProp.cooperativeMultiDeviceLaunch ? "Yes" : "No");
	printf("  Device PCI Domain ID / Bus ID / location ID:   %d / %d / %d\n", deviceProp.pciDomainID, deviceProp.pciBusID, deviceProp.pciDeviceID);

	const char *computeMode[] =
	{
		"Default (multiple host threads can use ::cudaSetDevice() with device simultaneously)",
		"Exclusive (only one host thread in one process is able to use ::cudaSetDevice() with this device)",
		"Prohibited (no host thread can use ::cudaSetDevice() with this device)",
		"Exclusive Process (many threads in one process is able to use ::cudaSetDevice() with this device)",
		"Unknown",
		NULL
	};
	printf("  Compute Mode:\n");
	printf("     < %s >\n", computeMode[deviceProp.computeMode]);
}

void PrintCUDADeviceList()
{
	// CUDA ����̽� ���� ��������
	int deviceCount;

	// CUDA ���� ����̽��� ���� ��� 'cudaErrorNoDevice' ��ȯ
	// ���� �׷��� ����̹��� ���� ��� 'cudaErrorInsufficientDriver' ��ȯ
	CheckCudaError(cudaGetDeviceCount(&deviceCount));

	printf("--- CUDA ���� ����̽� ����: %d\n", deviceCount);
	printf("\n");
	printf("============================================\n");

	for (int i = 0; i < deviceCount; i++)
	{
		printf("CUDA ����̽� %d��\n", i + 1);
		printf("-------------------------------------- \n");

		// �� CUDA ����̽��� ���� ��� �Լ� ȣ��
		PrintDeviceInfo(i);

		printf("-------------------------------------- \n");
	}

	printf("============================================\n");
}