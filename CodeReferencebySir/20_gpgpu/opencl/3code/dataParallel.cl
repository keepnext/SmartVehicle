__kernel void dataParallel(__global int* A, __global int* B, __global int* C)
{

	int idx = get_global_id(0);
	C[idx] = A[idx] + B[idx];

	// To do �ٸ������� �߰��غ�����.
}

//
//index ������ function
//- ����(dimensions) : uint get_work_dim()
//- ��ü ũ�� : size_t get_global_size(uint dimindx)
//- work - group ũ�� : size_t get_local_size(uint dimindx)
//- work - group ���� : size_t get_num_groups(uint dimindx)
//
//
//���� work - item�� function
//- global id : size_t get_global_id(uint dimindx)
//- local id : size_t get_local_id(uint dimidx)
//
//���� work - group�� function
//- work - group id : size_t get_group_id(uint dimidx)