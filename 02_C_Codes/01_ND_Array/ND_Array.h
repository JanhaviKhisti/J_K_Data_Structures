
/**
 * @File: ND_Array.h
 * @Brief: Header file contains function declarations as well as type definitions
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 07/06/2024 (Monday)
 */

#ifndef _ND_ARRAY_H
#define _ND_ARRAY_H

// Constants Literals
#define SUCCESS 0 
#define FAILURE 1

// Type Definition  (simple meaning is changing names of objects)

struct array;

typedef struct  array 	array_t;
typedef struct  array* 	p_array_t;
typedef struct  array** pp_array_t;

typedef void* data_t;
typedef int	  ret_t;

// Structure Type Defination
struct array
{
	data_t*	ptr;				// actual array
	size_t	no_of_dimensions;	// total number of dimenssions
	long*	pdimension;			// array of storing size of each dimension
	size_t* to_jump_dimension;
};

#define SIZE_ARRAY (sizeof(array_t))

// ND Array Interface Functions			(function given to client to use ND Array)
/*
	identifier	:	create_array
	input		:	1)	size of element
					2)	no of dimension(size_t)
						size of each dimension(variadic function)
					3)	...(ellipses)

	output		:	pointer to struct
*/
extern p_array_t  create_array(size_t  no_of_dimensions, ...);


/*
	identifier	:	array_set_data
	input		:	1)	array
					2)	data
					3)	...(Index)
	output		:	status(success or failure)
*/
extern ret_t  array_set_data(p_array_t  parray, data_t  data, ...);


/*
	identifier	:	array_get_data
	input		:	1) array
					2) ...
	output		:	data
*/
extern data_t  array_get_data(p_array_t parray, ...);


/*
	identifier	:	array_get_size_of_dimension
	input		:	1) array
					2) index
	output		:	long
*/
extern long array_get_size_of_dimension(p_array_t  parray, long  index);


/*
	identifier	:	array_destroy
	input		:	double pointer to array
	output		:	status(success or failure)
*/
extern ret_t array_destroy(pp_array_t  pparray);

#endif  /* _NA_ARRAY_H */


