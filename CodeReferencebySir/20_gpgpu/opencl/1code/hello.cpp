#include "../common.h"

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)

void hello()
{
	cl_device_id device_id = NULL;
	cl_context context = NULL;
	cl_command_queue command_queue = NULL;
	cl_mem memobj = NULL;
	cl_program program = NULL;
	cl_kernel kernel = NULL;
	cl_platform_id platform_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;

	size_t global;                      // global domain size = data size
	size_t local;                       // local domain size

	char retGPU[MEM_SIZE];

	FILE *fp;
	char fileName[] = "./1code/hello.cl";
	char *source_str;
	size_t source_size;

	fp = fopen(fileName, "r");
	if (!fp) {
		fprintf(stderr, "Failed to load kernel.\n");
		exit(1);
	}
	source_str = (char*)malloc(MAX_SOURCE_SIZE);
	source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	fclose(fp);

	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	//cl_uint          /* num_entries */,
	//cl_platform_id * /* platforms */,
	//cl_uint *        /* num_platforms */)

	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	//cl_platform_id   /* platform */,
	//cl_device_type   /* device_type */,
	//cl_uint          /* num_entries */,
	//cl_device_id *   /* devices */,
	//cl_uint *        /* num_devices */)

	context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	//const cl_context_properties * /* properties */,
	//cl_uint                 /* num_devices */,
	//const cl_device_id *    /* devices */,
	//void (CL_CALLBACK * /* pfn_notify */)(const char *, const void *, size_t, void *),
	//void *                  /* user_data */,
	//cl_int *                /* errcode_ret */)

	command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	//cl_context                     /* context */,
	//cl_device_id                   /* device */,
	//cl_command_queue_properties    /* properties */,
	//cl_int *                       /* errcode_ret */

	memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), NULL, &ret);
	//cl_context   /* context */,
	//cl_mem_flags /* flags */,
	//size_t       /* size */,
	//void *       /* host_ptr */,
	//cl_int *     /* errcode_ret */

	program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	//cl_context        /* context */,
	//cl_uint           /* count */,
	//const char **     /* strings */,
	//const size_t *    /* lengths */,
	//cl_int *          /* errcode_ret */)

	ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	//cl_program           /* program */,
	//cl_uint              /* num_devices */,
	//const cl_device_id * /* device_list */,
	//const char *         /* options */,
	//void (CL_CALLBACK *  /* pfn_notify */)(cl_program /* program */, void * /* user_data */),
	//void *               /* user_data */)
	if (ret != CL_SUCCESS)
	{
		size_t len;
		char buffer[2048];
		printf("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		printf("%s\n", buffer);
		exit(1);
	}
	
	kernel = clCreateKernel(program, "hello", &ret);
	//cl_program      /* program */,
	//const char *    /* kernel_name */,
	//cl_int *        /* errcode_ret */)

	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
	//cl_kernel    /* kernel */,
	//cl_uint      /* arg_index */,
	//size_t       /* arg_size */,
	//const void * /* arg_value */)
	
	ret = clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
	//cl_command_queue  /* command_queue */,
	//cl_kernel         /* kernel */,
	//cl_uint           /* num_events_in_wait_list */,
	//const cl_event *  /* event_wait_list */,
	//cl_event *        /* event */)

	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), retGPU, 0, NULL, NULL);
	//cl_command_queue    /* command_queue */,
	//cl_mem              /* buffer */,
	//cl_bool             /* blocking_read */,
	//size_t              /* offset */,
	//size_t              /* size */,
	//void *              /* ptr */,
	//cl_uint             /* num_events_in_wait_list */,
	//const cl_event *    /* event_wait_list */,
	//cl_event *          /* event */)

	puts(retGPU);

	// To do 1 추가할 곳------------
	kernel = clCreateKernel(program, "hello2", &ret);
	//cl_program      /* program */,
	//const char *    /* kernel_name */,
	//cl_int *        /* errcode_ret */)
	
	int iValue = 1;
	ret = clSetKernelArg(kernel, 0, sizeof(cl_int), (void *)&iValue);
	//cl_kernel    /* kernel */,
	//cl_uint      /* arg_index */,
	//size_t       /* arg_size */,
	//const void * /* arg_value */)
	CHK_ERR(ret);

	ret = clEnqueueTask(command_queue, kernel, 0, NULL, NULL);
	//cl_command_queue  /* command_queue */,
	//cl_kernel         /* kernel */,
	//cl_uint           /* num_events_in_wait_list */,
	//const cl_event *  /* event_wait_list */,
	//cl_event *        /* event */)

	ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, MEM_SIZE * sizeof(char), retGPU, 0, NULL, NULL);
	//cl_command_queue    /* command_queue */,
	//cl_mem              /* buffer */,
	//cl_bool             /* blocking_read */,
	//size_t              /* offset */,
	//size_t              /* size */,
	//void *              /* ptr */,
	//cl_uint             /* num_events_in_wait_list */,
	//const cl_event *    /* event_wait_list */,
	//cl_event *          /* event */)
	//------------

	ret = clFlush(command_queue);	// Queue가 비었는지
	ret = clFinish(command_queue);	// 모든 처리가 다 끝났는지

	ret = clReleaseKernel(kernel);
	ret = clReleaseProgram(program);
	ret = clReleaseMemObject(memobj);
	ret = clReleaseCommandQueue(command_queue);
	ret = clReleaseContext(context);

	free(source_str);
}