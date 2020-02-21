#include "../common.h"

void printDeviceInfo(cl_device_id* Device, bool bNameOnly)
{
	char*			device_name;
	size_t 			device_name_len;
	cl_device_type	device_type;
	cl_uint			device_max_compute_units;
	size_t			device_max_work_group_size;
	cl_ulong		device_global_mem_size;
	cl_ulong		device_local_mem_size;
	cl_ulong		device_max_group_size;
	cl_ulong		device_max_mem_alloc_size;
	cl_bool			device_host_unified_memory;
	cl_uint			ret;

	clGetDeviceInfo(*Device, CL_DEVICE_NAME, 0, NULL, &device_name_len);
	device_name = (char*)malloc(device_name_len);
	clGetDeviceInfo(*Device, CL_DEVICE_NAME, device_name_len, device_name, NULL);
	clGetDeviceInfo(*Device, CL_DEVICE_TYPE, sizeof(cl_device_type), &device_type, NULL);
	ret = clGetDeviceInfo(*Device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &device_max_compute_units, NULL);
	ret = clGetDeviceInfo(*Device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &device_max_work_group_size, NULL);
	ret = clGetDeviceInfo(*Device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(cl_ulong), &device_max_group_size, NULL);
	ret = clGetDeviceInfo(*Device, CL_DEVICE_LOCAL_MEM_SIZE, sizeof(cl_ulong), &device_local_mem_size, NULL);
	ret = clGetDeviceInfo(*Device, CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(cl_ulong), &device_max_mem_alloc_size, NULL);
	ret = clGetDeviceInfo(*Device, CL_DEVICE_HOST_UNIFIED_MEMORY, sizeof(cl_ulong), &device_host_unified_memory, NULL);

	if (device_type & CL_DEVICE_TYPE_CPU)
		printf("CL_DEVICE_TYPE : CL_DEVICE_TYPE_CPU\n");
	if (device_type & CL_DEVICE_TYPE_GPU)
		printf("CL_DEVICE_TYPE : CL_DEVICE_TYPE_GPU\n");

	printf("CL_DEVICE_NAME : %s\n", device_name);
	if (bNameOnly == true) { return; }

	printf("CL_DEVICE_MAX_COMPUTE_UNITS : %d\n", device_max_compute_units);
	printf("CL_DEVICE_MAX_WORK_GROUP_SIZE : %d\n", device_max_work_group_size);
	printf("CL_DEVICE_GLOBAL_MEM_SIZE : %lu\n", device_max_group_size / 1024);
	printf("CL_DEVICE_LOCAL_MEM_SIZE : %lu\n", device_local_mem_size / 1024);
	printf("CL_DEVICE_MAX_MEM_ALLOC_SIZE : %lu\n", device_max_mem_alloc_size / 1024);
	printf("CL_DEVICE_HOST_UNIFIED_MEMORY : %lu\n\n", device_host_unified_memory / 1024);

	free(device_name);
}

void printPlatformList()
{
	cl_platform_id*		PlatformList = NULL;
	cl_uint				Platform_TotalCnt = 0;
	cl_device_id*		DeviceList = NULL;
	cl_uint				Device_TotalCnt = 0;
	cl_uint				ret = CL_SUCCESS;

	int i = 0, j = 0;

	// 플랫폼 갯수 가져오기
	ret = clGetPlatformIDs(0, NULL, &Platform_TotalCnt);
	CHK_ERR(ret); // - 에러처리가 필요한 곳에 사용

	cout << "--- 호스트와 연결 가능한 플랫폼 수 : " << Platform_TotalCnt << " ---\n" << endl;
	if (Platform_TotalCnt == 0) {
		PRINT_ERROR("연결 가능한 장치가 없습니다");
	}

	// 플랫폼 정보 메모리 할당
	PlatformList = (cl_platform_id*)malloc(sizeof(cl_platform_id) * Platform_TotalCnt);

	// 플랫폼 객체 할당
	ret = clGetPlatformIDs(Platform_TotalCnt, PlatformList, NULL);

	printf("\n============================================\n");
	for (i = 0; i < Platform_TotalCnt; i++) {
		printf("플랫폼 %d번------------------------------- \n", i + 1);

		// get all devices
		clGetDeviceIDs(PlatformList[i], CL_DEVICE_TYPE_ALL, 0, NULL, &Device_TotalCnt);

		DeviceList = (cl_device_id*)malloc(sizeof(cl_device_id) * Device_TotalCnt);
		clGetDeviceIDs(PlatformList[i], CL_DEVICE_TYPE_ALL, Device_TotalCnt, DeviceList, NULL);

		// for each device print critical attributes
		for (j = 0; j < Device_TotalCnt; j++) {
			printDeviceInfo(&DeviceList[j]);
		}
		printf("-------------------------------------- \n");
	}
	printf("============================================\n");
}