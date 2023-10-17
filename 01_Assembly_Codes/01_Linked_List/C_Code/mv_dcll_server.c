
/**
 * File   : mv_dcll_server.c
 * Brief  : Contains all function definitions for DCLL 
 * Author : Janhavi Khisti(janhavikhisti@gmail.com)
 * Date   : 02/02/2023
 */

// Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_dcll.h"


//	DCLL Helper Functions

static void* Xmalloc(size_t no_of_bytes)
{
	//	Code
	void* p = malloc(no_of_bytes);

	if( NULL == p )
	{
		fprintf(stderr, "ERROR: Out Of Memory\n");
		exit(FAILURE);
	}

	return(p);
}

static ret_t list_generic_insert(p_mv_dcll_t plist, p_node_t first, p_node_t mid, p_node_t last)
{
	// Code

	mid->p_next = last;
	mid->p_prev = first;

	first->p_next = mid;
	last->p_prev = mid;

	plist->size++;

	plist->p_tail = plist->p_head->p_prev;

	return(SUCCESS);
}

static data_t list_generic_remove(p_mv_dcll_t plist, p_node_t d_node)
{
	// Code
	p_node_t first = d_node->p_prev;
	p_node_t last = d_node->p_next;

	first->p_next = last;
	last->p_prev = first;

	d_node->p_next = d_node->p_prev = NULL;

	data_t to_return_data = d_node->data;

	free(d_node);

	plist->size--;

	plist->p_tail = plist->p_head->p_prev;

	return( to_return_data );
}

static p_node_t create_node(data_t new_data)
{
	// Code
	p_node_t pnode = (p_node_t) Xmalloc(SIZE_NODE);

	pnode->data = new_data;
	pnode->p_next = pnode;
	pnode->p_prev = pnode;

	return(pnode);
}


//	DCLL Interface functions 
extern p_mv_dcll_t create_list()
{
	// Code
	p_mv_dcll_t plist = (p_mv_dcll_t) Xmalloc(SIZE_LIST);

	plist->p_head = create_node(NULL);
	plist->p_tail = plist->p_head;

	plist->size = 0;

	return(plist);
}


//	List Insertion functions
extern ret_t list_insert_front(p_mv_dcll_t plist, data_t new_data)
{
	// Code
	if( NULL == plist )
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(FAILURE);
	}

	p_node_t new_node = create_node(new_data);

	return( list_generic_insert(plist, plist->p_head, new_node, plist->p_head->p_next) );
}

extern ret_t list_insert_back(p_mv_dcll_t plist, data_t new_data)
{
	// Code
	if( NULL == plist )
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(FAILURE);
	}

	p_node_t new_node = create_node(new_data);

	return( list_generic_insert(plist, plist->p_tail, new_node, plist->p_tail->p_next) );
}

extern ret_t list_insert_before(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	if( NULL == plist ||
		0 == plist->size)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(FAILURE);
	}

	p_node_t prunner = plist->p_head->p_next;

	while( 1 )
	{
		if( SUCCESS == pcomparedataproc(prunner->data, e_data) )
			break;

		prunner = prunner->p_next;

		if( plist->p_head == prunner )
		{
			fprintf(stderr, "ERROR: Existing data not found.\n");
			return(FAILURE);
		}
	}

	p_node_t new_node = create_node(new_data);

	return( list_generic_insert(plist, prunner->p_prev, new_node, prunner) );
}

extern ret_t list_insert_after(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	if( NULL == plist ||
		0 == plist->size)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(FAILURE);
	}

	p_node_t prunner = plist->p_head->p_next;

	while( 1 )
	{
		if( SUCCESS == pcomparedataproc(prunner->data, e_data) )
			break;

		prunner = prunner->p_next;

		if( plist->p_head == prunner )
		{
			fprintf(stderr, "ERROR: Existing data not found.\n");
			return(FAILURE);
		}
	}

	p_node_t new_node = create_node(new_data);

	return( list_generic_insert(plist, prunner, new_node, prunner->p_next) );
}

extern ret_t list_insert_at(p_mv_dcll_t plist, data_t new_data, long index)
{
	// Code
	if( NULL == plist)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(FAILURE);
	}

	if( 0 == index )
	{
		return( list_insert_front(plist, new_data) );
	}
	else if( index == plist->size)
	{
		return( list_insert_back(plist, new_data) );
	}

	if( index > plist->size )
	{
		fprintf(stderr, "ERROR: Index out of bound.\n");
		return(FAILURE);
	}

	p_node_t prunner = plist->p_head;

	for( long le = 0; le < index; ++le )
	{
		prunner = prunner->p_next;
	}

	p_node_t new_node = create_node(new_data);

	return( list_generic_insert(plist, prunner, new_node, prunner->p_next) );
}


//	List Removal Functions
extern data_t list_remove_front(p_mv_dcll_t plist)
{
	// Code
	if( NULL == plist ||
		0 == plist->size)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return((data_t)NULL);
	}

	return( list_generic_remove(plist, plist->p_head->p_next) );
}

extern data_t list_remove_back(p_mv_dcll_t plist)
{
	// Code
	if( NULL == plist ||
		0 == plist->size)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return((data_t)NULL);
	}

	return( list_generic_remove(plist, plist->p_tail) );
}

extern data_t list_remove_before(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	if( NULL == plist ||
		0 == plist->size)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return((data_t)NULL);
	}

	p_node_t prunner = plist->p_head->p_next;

	while( 1 )
	{
		if( SUCCESS == pcomparedataproc(prunner->data, e_data) )
			break;

		prunner = prunner->p_next;

		if( plist->p_head == prunner )
		{
			fprintf(stderr, "ERROR: Existing data not found.\n");
			return((data_t)NULL);
		}
	}

	return( list_generic_remove(plist, prunner->p_prev) );
}

extern data_t list_remove_after(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
	// Code
	if( NULL == plist ||
		0 == plist->size)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return((data_t)NULL);
	}

	p_node_t prunner = plist->p_head->p_next;

	while( 1 )
	{
		if( SUCCESS == pcomparedataproc(prunner->data, e_data) )
			break;

		prunner = prunner->p_next;

		if( plist->p_head == prunner )
		{
			fprintf(stderr, "ERROR: Existing data not found.\n");
			return((data_t)NULL);
		}
	}

	return( list_generic_remove(plist, prunner->p_next) );
}

extern data_t list_remove_at(p_mv_dcll_t plist, long index)
{
	// Code
	if( NULL == plist	)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return((data_t)NULL);
	}

	if( 0 == index )
	{
		return( list_remove_front(plist) );
	}
	else if( index == plist->size)
	{
		return( list_remove_back(plist) );
	}

	if( index > plist->size )
	{
		fprintf(stderr, "ERROR: Index out of bound.\n");
		return((data_t)NULL);
	}

	p_node_t prunner = plist->p_head->p_next;

	for( long le = 0; le < index; ++le )
	{
		prunner = prunner->p_next;
	}

	return( list_generic_remove(plist, prunner) );
}


//	List Get Data Functions
extern	ret_t 	list_show(p_mv_dcll_t plist, PRINTDATAPROC pprintdataproc)
{
	//Code
	if( NULL == plist )
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(FAILURE);
	}	

	fprintf(stdout, "Doubly Circular Linked List:\n");

	fprintf(stdout, "{START}->");
	for( p_node_t prunner = plist->p_head->p_next;
		 prunner != plist->p_head; 
		 prunner = prunner->p_next )
	{
		pprintdataproc( prunner->data );
	}
	fprintf(stdout, "{END}\n");

	return(SUCCESS);
}

extern	data_t	list_data_at(p_mv_dcll_t plist, long index)
{
	// Code
	if( NULL == plist	||
		0 == plist->size)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return((data_t)NULL);
	}

	if( index >= plist->size )
	{
		fprintf(stderr, "ERROR: Index out of bound.\n");
		return((data_t)NULL);
	}

	p_node_t prunner = plist->p_head->p_next;

	for( long le = 0; le < index; ++le )
	{
		prunner = prunner->p_next;
	}

	return( prunner->data );
}

extern	size_t	list_size(p_mv_dcll_t plist)
{
	// Code
	if( NULL == plist)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(0);
	}

	return(plist->size);
}


// list Destroy
extern ret_t list_destroy( pp_mv_dcll_t pplist,  DELETEDATAPROC pdeletedataproc)
{
	// Code
	if( NULL == pplist)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(FAILURE);
	}

	p_mv_dcll_t plist = *pplist;

	if( NULL == plist)
	{
		fprintf(stderr, "ERROR: List not found.\n");
		return(FAILURE);
	}

	p_node_t prunner = plist->p_head->p_next;

	for( prunner; prunner != plist->p_head; )
	{
		p_node_t prunner_next = prunner->p_next;

		pdeletedataproc(prunner->data);
		prunner->data = NULL;

		free(prunner);

		prunner = prunner_next;
	}

	if( plist->p_head )
	{
		free(plist->p_head);
		plist->p_head = NULL;
	}

	if( plist )
	{
		free(plist);
		plist = NULL;
	}

	*pplist = NULL;

	return(SUCCESS);
}

