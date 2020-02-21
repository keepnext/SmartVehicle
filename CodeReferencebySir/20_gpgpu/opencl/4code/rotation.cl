__kernel
void img_rotate(__global float* dest_data,
				__global float* src_data,
				int  W,
				int  H,
				float  sinTheta,
				float  cosTheta) 
{
	const int ix = get_global_id(0);
	const int iy = get_global_id(1);

	float x0 = W / 2.0f;
	float y0 = H / 2.0f;

	float xOff = ix - x0;
	float yOff = iy - y0;

	int xpos = (int)(xOff*cosTheta + yOff*sinTheta + x0);
	int ypos = (int)(yOff*cosTheta - xOff*sinTheta + y0);

	if ((xpos >= 0) && (xpos< W) && (ypos >= 0) && (ypos< H)) {
		dest_data[iy*W + ix] = src_data[ypos*W + xpos];
	}

	if (iy*W + ix == 0)
	{
		printf("get_work_dim : %d\n", get_work_dim());
		printf("get_global_size 1 : %d\n", get_global_size(0));
		printf("get_global_size 2 : %d\n", get_global_size(1));
		printf("get_local_size 1 : %d\n", get_local_size(0));
		printf("get_local_size 2 : %d\n", get_local_size(1));
		printf("get_num_groups 1 : %d\n", get_num_groups(0));
		printf("get_num_groups 2 : %d\n", get_num_groups(1));
		printf("get_global_id 1 : %d\n", get_global_id(0));
		printf("get_global_id 2 : %d\n", get_global_id(1));
		printf("get_local_id 1 : %d\n", get_local_id(0));
		printf("get_local_id 2 : %d\n", get_local_id(1));
		printf("get_group_id 1 : %d\n", get_group_id(0));
		printf("get_group_id 2 : %d\n", get_group_id(1));
	}


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
}