
/**
 * @File: mv_vector_client.c
 * @Brief: This file contains interface function calls made by client
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 08-06-2024
 */

//	Headers

#include	<stdio.h>
#include	<stdlib.h>
#include	<assert.h>

#include	"mv_vector.h"

// p_mv_vector_t  pvector =  NULL;
// p_mv_vector_t  pvector = NULL;

void print_data(data_t data)
{
		fprintf(stdout, "{%lld}-", (long long)data);
}

void delete_data(data_t data)
{
	fprintf(stdout, "Popped Data : %lld\n",(long long)data);
}

int main(void)
{
	// Code
	p_mv_vector_t pvector = create_vector();

	mv_vector_push_back(pvector, (size_t)5, (data_t)100, (data_t)200, (data_t)300, (data_t)400, (data_t)500);

	forward_print_data(pvector);

	backward_print_data(pvector);
	// printf("pvector size = %llu\n", mv_vector_size(mypvector));
	// printf("pvector Capacity = %llu\n", mv_vector_capacity(mypvector));

	// mv_vector_push_back(pvector, (data_t)50);
	// mv_vector_push_back(pvector, (data_t)60);
	// mv_vector_push_back(pvector, (data_t)70);
	// mv_vector_push_back(pvector, (data_t)80);
	// mv_vector_push_back(pvector, (data_t)90);
	// mv_vector_push_back(pvector, (data_t)100);

	// print_data(pvector);
	// printf("pvector size = %llu\n", mv_vector_size(pvector));
	// printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector));

	 mv_vector_pop_back(pvector, 2);
	// // mv_vector_pop_back(pvector);
	// // mv_vector_pop_back(pvector);

	 forward_print_data(pvector);

	 backward_print_data(pvector);
	// printf("pvector size = %llu\n", mv_vector_size(pvector));
	// printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector));

	// mv_vector_destroy(&pvector);

	exit(0);
}


