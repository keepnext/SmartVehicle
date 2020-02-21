__kernel void dataParallel(__global int* A, __global int* B, __global int* C)
{

	int idx = get_global_id(0);
	C[idx] = A[idx] + B[idx];

	// To do 다른연산을 추가해보세요.
}

//
//index 공간의 function
//- 차원(dimensions) : uint get_work_dim()
//- 전체 크기 : size_t get_global_size(uint dimindx)
//- work - group 크기 : size_t get_local_size(uint dimindx)
//- work - group 개수 : size_t get_num_groups(uint dimindx)
//
//
//현재 work - item의 function
//- global id : size_t get_global_id(uint dimindx)
//- local id : size_t get_local_id(uint dimidx)
//
//현재 work - group의 function
//- work - group id : size_t get_group_id(uint dimidx)