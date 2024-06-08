
/**
 * @File: mv_vector.h
 * @Brief: This header file contains all the interface function declaration
 * @Author: Janhavi Sunil Khisti(janhavikhisti@gmail.com)
 * @Date: 08-06-2024
 */

#ifndef  	_MV_VECTOR_H
#define 	_MV_VECTOR_H

#ifndef  	SUCCESS 	
#define  	SUCCESS 	0
#endif

#ifndef  	FAILURE  	
#define   	FAILURE  	1
#endif

// Type Definations

struct mv_vector;

typedef  	struct mv_vector  	mv_vector_t;
typedef  	struct mv_vector*  	p_mv_vector_t;
typedef  	struct mv_vector** 	pp_mv_vector_t;

typedef  	void*  	data_t;
typedef  	data_t* p_data_t;

#define  	SIZE_DATA  	(sizeof(data_t))

typedef  	int  	ret_t;

// Struct Type Defination
struct mv_vector
{
	p_data_t 	array;
	size_t  	nr_of_elements;
	size_t  	capacity;
};

#define  	SIZE_MV_VECTOR  sizeof(mv_vector_t)

//  Vector Interface Fuctions 		( given to client to use vector )

/*
  Function
	identifier	:	create_vector
	input		:	void
	output		:	pointer to struct
*/
extern  	p_mv_vector_t  	create_vector(void);


/*
  Function
	identifier	:	mv_vector_push_back
	input		:	1) vector
					2) data
					3) ...
	output		:	status(success or failure)
*/
extern 		ret_t 	 mv_vector_push_back(p_mv_vector_t , size_t , ...);


/*
  Function
  	identifier	:	mv_vector_pop_back
  	input		:	vector
  	output		:	return popped data
*/
extern 		data_t    mv_vector_pop_back(p_mv_vector_t , size_t );


/*
  Function
  	identifier	:	mv_vector_data_at
  	input		:	1) vector
  					2) index
  	output		:	returns data at given index 
*/
extern  	data_t    mv_vector_data_at(p_mv_vector_t, size_t);


/*
  Function
 	identifier	:	mv_vector_size
 	input		:	vector
 	output		:	size of vector
*/
extern  	size_t    mv_vector_size(p_mv_vector_t);


/*
  Function
	identifier	:	mv_vector_capacity
	input		:	vector
	output		:	capacity of vector
*/
extern  	size_t    mv_vector_capacity(p_mv_vector_t);


/*
  Function
  	identifier	:	forward_print_data
	input		:	vector
	output		:	void
*/
extern 		void	 forward_print_data(p_mv_vector_t pvector);


/*
  Function
  	identifier	:	backward_print_data
	input		:	vector
	output		:	void
*/
extern 		void	 backward_print_data(p_mv_vector_t pvector);


/*
  Function
 	identifier	:	mv_vector_destroy 
 	input		:	double pointer to vector
 	output		:	status(success or failure)
*/
extern  	ret_t  	 mv_vector_destroy(pp_mv_vector_t);

#endif	 /* _MV_VECTOR_H */

