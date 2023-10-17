
/**
 * File   : mv_dcll.h
 * Brief  : Header file contains all function declarations for DCLL 
 * Author : Janhavi Khisti(janhavikhisti@gmail.com)
 * Date   : 02/02/2023
 */


// Conditional Compilation

#ifndef	_MV_DCLL_H
#define	_MV_DCLL_H

//	Headers
#include	<stdio.h>
#include	<stdlib.h>

//	Constant Literals / MACROS

#ifndef	SUCCESS
#define	SUCCESS	0
#endif

#ifndef	FAILURE	
#define	FAILURE 1
#endif

//	Typedefs 

//	Struct Type Declaration
struct list_node; 

typedef	struct list_node	node_t;
typedef	struct list_node*	p_node_t;
typedef	struct list_node**	pp_node_t;

struct doubly_circular_linked_list;

typedef	struct doubly_circular_linked_list		mv_dcll_t;
typedef	struct doubly_circular_linked_list*		p_mv_dcll_t;
typedef	struct doubly_circular_linked_list**	pp_mv_dcll_t;

typedef	int 	ret_t;				
typedef	void* 	data_t;

typedef	ret_t(*COMPAREDATAPROC)(data_t, data_t);
typedef	void (*PRINTDATAPROC)(data_t);
typedef	void (*DELETEDATAPROC)(data_t);

//	Struct Type Definitions
struct list_node
{
	data_t	data;		
	p_node_t p_next;	
	p_node_t p_prev;
};
#define	SIZE_NODE	(sizeof(node_t))

struct doubly_circular_linked_list
{
	p_node_t	p_head;
	p_node_t 	p_tail;
	size_t 		size;
};
#define	SIZE_LIST	(sizeof(mv_dcll_t))

//	DCLL Interface functions declarations
extern p_mv_dcll_t create_list();

//	List Insertion functions
extern ret_t list_insert_front(p_mv_dcll_t plist, data_t new_data);
extern ret_t list_insert_back(p_mv_dcll_t plist, data_t new_data);
extern ret_t list_insert_before(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc);
extern ret_t list_insert_after(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc);
extern ret_t list_insert_at(p_mv_dcll_t plist, data_t new_data, long index);

//	List Removal Functions
extern data_t list_remove_front(p_mv_dcll_t plist);
extern data_t list_remove_back(p_mv_dcll_t plist);
extern data_t list_remove_before(p_mv_dcll_t, data_t e_data, COMPAREDATAPROC pcomparedataproc);
extern data_t list_remove_after(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc);
extern data_t list_remove_at(p_mv_dcll_t plist, long index);

//	List Get Data Functions
extern ret_t  list_show(p_mv_dcll_t plist, PRINTDATAPROC pprintdataproc);
extern data_t list_data_at(p_mv_dcll_t plist, long index);
extern size_t list_size(p_mv_dcll_t plist);

// List Destroy
extern ret_t list_destroy( pp_mv_dcll_t pp_list,  DELETEDATAPROC pdeletedataproc);

#endif	/* _MV_DCLL_H */

