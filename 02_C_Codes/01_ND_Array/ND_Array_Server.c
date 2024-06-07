
/**
 * @File: ND_Array_Server.c
 * @Brief: This file contains function definitions for N-Dimensional Array
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 07/06/2024 (Monday)
 */

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>

#include "ND_Array.h"

// Array Helper Functions
static void* xmalloc(size_t  no_of_bytes)
{
	// Code
	void* p = malloc(no_of_bytes);
	if( NULL == p )
	{
		fprintf(stderr, "ERROR : Out Of Memory\n");
		exit(FAILURE);
	}
	return(p);
}

static void* xcalloc(size_t  no_of_elements, size_t  no_of_bytes)
{
	// Code
	void* p = calloc(no_of_elements, no_of_bytes);
	if( NULL == p )
	{
		fprintf(stderr, "ERROR : Out Of Memory\n");
		exit(FAILURE);
	}
	return(p);
}


// Array Interface function (given to client to use ND Array)

/*
  Function
	identifier	:	create_array
	input		:	1)	size of element
					2)	no of dimension(size_t)
						size of each dimension(variadic function)
					3)	...(ellipses)

	output		:	pointer to struct
*/
extern p_array_t  create_array(size_t no_of_dimensions, ...)
{
	// Code
	// Test Case 			(Conditional Compilation)
	#ifdef MY_DEBUG
		assert( 0 != no_of_dimensions); 	// For Developer
	#else
		if( 0 == no_of_dimensions )			// For Client
		{
			fprintf(stderr, "0 dimension array not possible\n");
			return(NULL);
		}
	#endif

	p_array_t  parray = (p_array_t)xmalloc(SIZE_ARRAY);

	/*
	 * Step 1 : Initialize the number of dimensions for array
	 */
	parray->no_of_dimensions = no_of_dimensions;


	/*
	 * Step 2 : Allocate an array to store the size of every dimension with
	 			'no_of_dimension' as no of elements.
	 */
	// Initialize size of each dimension
	parray->pdimension = (long*)xcalloc( no_of_dimensions, sizeof(long));


	/*
	 * Step 3 : Get the size of every dimension from variadic input parameters
	 			and store it in the allocated from step 2
	 */
	// Storing all the sizes of each dimension
	va_list arg;

	va_start(arg, no_of_dimensions);
	for( long le = 0; le < no_of_dimensions; ++le )
	{
		parray->pdimension[le] = va_arg(arg,long);
	}
	va_end(arg);


	/*
	 * Step 4 : Calculate the total number of elements for the data array 
	 			by multiplying size of each dimension
	 */
	// Allocating memory to array
	size_t  no_of_elements = parray->pdimension[0];

	// Calulating number of elements
	for( long le = 1; le < no_of_dimensions; ++le )
		no_of_elements *= parray->pdimension[le];


	/*
	 * Step 5 : Allocate the data array
	 */
	parray->ptr = (data_t*)xcalloc(no_of_elements, sizeof(void*));


	/*
	 * Step 6 : Initialize all the bytes of allocated array to '0'
	 */
	memset(parray->ptr, 0, no_of_elements * sizeof(void*));

	parray->to_jump_dimension = (size_t*)xcalloc( no_of_dimensions, sizeof(size_t));

	parray->to_jump_dimension[no_of_dimensions - 1] = 1;

	for( long le = no_of_dimensions - 2; le >= 0; --le)
	{
		parray->to_jump_dimension[le] = parray->pdimension[le+1] * parray->to_jump_dimension[le+1];
	}

	return(parray);
}


/*
  Function
	identifier	:	array_set_data
	input		:	1)	array
					2)	data
					3)	...(Index)
	output		:	status(success or failure)
*/
extern ret_t  array_set_data(p_array_t  parray, data_t  data, ...)
{
	// Code
	long* indices = NULL;

	// Error Checking		(Conditional Compilation)
	#ifdef MY_DEBUG
		assert( NULL != parray )
	#else
		if( NULL == parray )
		{
			fprintf(stderr, "ERROR : No Array Found\n");
			return(FAILURE);
		}
	#endif

	// Allocate array to store indices
	indices = (long*)xcalloc( parray->no_of_dimensions, sizeof(long));

	// Get indices from input parameters
	va_list arg;

	va_start(arg, data);
	for( long le = 0; le < parray->no_of_dimensions; ++le)
	{
		long index = va_arg(arg, long);

		// (Conditional Compilation)
		#ifdef MY_DEBUG
			assert( index >= 0 && index < parray->pdimension[le] );
		#else
			if( index < 0 || index >= parray->pdimension[le] )
			{
				fprintf(stderr, "ERROR : Index Out Of Bound\n");
				va_end(arg);
				free(indices);
				return(FAILURE);
			}
		#endif

		indices[le] = index;
	}
	va_end(arg);

	// Calculate the final index
	size_t final_index = 0;
	for( long le = 0; le < parray->no_of_dimensions; ++le )
	{
		final_index = final_index + parray->to_jump_dimension[le] * indices[le];
	}

	// Set the value (*** YA SATHI KELA HOTA ATTAHAS ***)
	parray->ptr[ final_index ] = data;

	// Free the indices array
	free(indices);

	return(SUCCESS);
}


/*
  Function
	identifier	:	array_get_data
	input		:	1) array
					2) ...
	output		:	data
*/
extern data_t  array_get_data(p_array_t  parray, ...)
{
	// Code
	long* indices = NULL;

	// Error Checking			(Conditional Compilation)
	#ifdef MY_DEBUG
		assert( NULL != parray );
	#else
		if( NULL == parray )
		{
			fprintf(stderr, "ERROR : No Array Found\n");
			return(NULL);
		}
	#endif

	// Allocate array to store indices
	indices = (long*)xcalloc(parray->no_of_dimensions, sizeof(long));

	// Assign indices value
	va_list arg;

	va_start(arg, parray);
	for( long le = 0; le < parray->no_of_dimensions; ++le)
	{
		long index = va_arg(arg, long);

		// (Conditional Compilation)
		#ifdef MY_DEBUG
			assert( index >= 0 && index < parray->pdimension[le] );
		#else
			if( index < 0 || index >= parray->pdimension[le] )
			{
				fprintf(stderr, "ERROR : Index Out Of Bound\n");
				va_end(arg);
				free(indices);
				return(NULL);
			}
		#endif

		indices[le] = index;
	}
	va_end(arg);

	// Calculate the final index
	size_t final_index = 0;
	for( long le = 0; le < parray->no_of_dimensions; ++le )
	{
		final_index = final_index + parray->to_jump_dimension[le] * indices[le];
	}

	// Get the value
	data_t to_return_data = parray->ptr[final_index];

	// Free the indices array
	free(indices);

	return(to_return_data);
}


/*
  Function
	identifier	:	array_get_size_of_dimension
	input		:	1) array
					2) index
	output		:	long
*/
extern long  array_get_size_of_dimension(p_array_t  parray, long  index)
{
	//Code				(Conditional Compilation)
	#ifdef MY_DEBUG
		assert( NULL != parray );
		assert( index < parray->no_of_dimensions )
	#else
		if( NULL == parray )
		{
			fprintf(stderr, "ERROR : No array found to destroy\n");
			return(0);
		}

		if( index >= parray->no_of_dimensions )
		{
			fprintf(stderr, "ERROR : Dimension does not exits\n");
			return(0);
		}
	#endif

	return( parray->pdimension[index] );
}


/*
  Function
	identifier	:	array_destroy
	input		:	double pointer to array
	output		:	status(success or failure)
*/
extern ret_t  array_destroy(pp_array_t pparray)
{
	// Code
	p_array_t parray = *pparray;

	#ifdef MY_DEBUG
		assert( NULL != parray );

	#else
		if( NULL == parray )
		{
			fprintf(stderr, "ERROR : No array found to destroy\n");
			return(FAILURE);
		}
	#endif

	// Free the to jump dimension
	if( parray->to_jump_dimension )
	{
		free( parray->to_jump_dimension );
		parray->to_jump_dimension = NULL;
	}

	// Free the data array
	if( parray-> ptr )
	{
		free( parray->ptr );
		parray->ptr = NULL;
	}

	// Free the size of each dimension array
	if( parray->pdimension )
	{
		free( parray->pdimension );
		parray->pdimension = NULL;
	} 

	// Free the struct object
	if( parray )
	{
		free(parray);
		parray = NULL;
	}

	// Assign NULL to the client side pointer
	*pparray = NULL;

	return(SUCCESS);
}


