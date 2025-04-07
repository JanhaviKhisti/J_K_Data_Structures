

//	Headers

#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_graph.h"


//	Graph Helper Functions

static	void*	Xmalloc(size_t no_of_bytes)
{
	// Code
	void* p = malloc(no_of_bytes);

	if( NULL == p )
	{
		fprintf(stderr, "ERROR: Out of Memory\n");
		exit(FAILURE);
	}

	return(p);
}

static p_vertex_t	create_vertex(data_t data)
{
	// Code
	p_vertex_t	pvertex = (p_vertex_t)Xmalloc(SIZE_VERTEX);

	pvertex->vertex_data = data;
	pvertex->edges = create_list();

	return(pvertex);
}

static	p_edge_t	create_edge(p_vertex_t pvertex, size_t edge_weight)
{
	//	Code

	p_edge_t pedge = (p_edge_t)Xmalloc(SIZE_EDGE);

	pedge->vertex = pvertex;
	pedge->weight = edge_weight;

	return(pedge);
}

static	p_vertex_t	locate_vertex(p_mv_graph_t pgraph, data_t new_data, COMPAREPROC pcompareproc)
{
	//	Code
	long size = list_size(pgraph->vertices);

	for( long le = 0; le < size; ++le)
	{
		p_vertex_t pvertex = list_data_at(pgraph->vertices, le);

		if( SUCCESS == pcompareproc(new_data, pvertex->vertex_data) )
			return(pvertex);
	}

	return(NULL);
}

static	ret_t 		generic_insert_directed_edge(p_vertex_t pvertex1, p_vertex_t pvertex2, size_t edge_weight)
{
		// Code
	p_edge_t edge_1 = create_edge(pvertex2, edge_weight);
	list_insert_back( pvertex1->edges, edge_1);

	return(SUCCESS);
}

static	ret_t 		generic_insert_undirected_edge(p_vertex_t pvertex1, p_vertex_t pvertex2, size_t edge_weight)
{
	// Code
	p_edge_t edge_1 = create_edge(pvertex2, edge_weight);
	list_insert_back( pvertex1->edges, edge_1);

	p_edge_t edge_2 = create_edge(pvertex1, edge_weight);
	list_insert_back( pvertex2->edges, edge_2);

	return(SUCCESS);
}

static 	void	delete_edge(data_t data)
{
	p_edge_t pedge = (p_edge_t) data;

	free(pedge);
	pedge = NULL;
}

static	data_t	generic_remove_vertex_directed_graph(p_mv_graph_t pgraph, data_t e_data, COMPAREPROC pcompareproc)
{
	//	Code

	data_t to_return_data = NULL;

	p_vertex_t to_be_delete_vertex = locate_vertex(pgraph, e_data, pcompareproc);

	if( !to_be_delete_vertex )
	{
		fprintf(stderr, "ERROR: to remove vertex not present.\n");
		return(to_return_data);
	}

	long vertices_size = list_size( pgraph->vertices );

	// Traverse to each edge of to_be_removed vertex to remove its entry from other vertices
	for( long le = 0; le < vertices_size; ++le )
	{
		p_vertex_t vertex = list_data_at(pgraph->vertices, le);

		if( vertex == to_be_delete_vertex )
			continue;

		// Check for entry of to_be_deleted_vertex in each vertex's edges

		long edges_size = list_size(vertex->edges);

		for( long ile = 0; ile < edges_size; ++ile )
		{
			p_edge_t edge = list_data_at( vertex->edges, ile);

			//if( SUCCESS == pcompareproc(to_be_delete_vertex->vertex_data, inner_edge->vertex->vertex_data) )
			
			//	OR

			if( to_be_delete_vertex == edge->vertex )
			{
				free( list_remove_at(vertex->edges, ile) );
				break;
			}
		}		
	}

	//	Here we destroy the edges list
	list_destroy( &(to_be_delete_vertex->edges), delete_edge );

	//	Here we delete the to_be_removed vertex from the main vertices list 
	vertices_size = list_size( pgraph->vertices );
	for( long le = 0; le < vertices_size; ++le )
	{
		//p_vertex_t vertex_2 = list_data_at(pgraph->vertices, le);
		//if( SUCCESS == pcompareproc(to_be_delete_vertex->vertex_data, vertex_2->vertex_data) )

		//	OR
		
		if( to_be_delete_vertex == list_data_at(pgraph->vertices, le) )
		{
			to_return_data = to_be_delete_vertex->vertex_data;
			free( list_remove_at(pgraph->vertices, le) );
			break;
		}
	}

	return(to_return_data);
}


static	data_t	generic_remove_vertex_undirected_graph(p_mv_graph_t pgraph, data_t	e_data,	COMPAREPROC pcompareproc)
{
	//	Code

	data_t to_return_data = NULL;

	p_vertex_t to_be_delete_vertex = locate_vertex(pgraph, e_data, pcompareproc);

	if( !to_be_delete_vertex )
	{
		fprintf(stderr, "ERROR: to remove vertex not present.\n");
		return(to_return_data);
	}

	long edges_size = list_size( to_be_delete_vertex->edges );

	// Traverse to each edge of to_be_removed vertex to remove its entry from other vertices
	for( long le = 0; le < edges_size; ++le )
	{
		p_edge_t pedge = list_data_at(to_be_delete_vertex->edges, le);

		long inner_edges_size = list_size(pedge->vertex->edges);

		for( long ile = 0; ile < inner_edges_size; ++ile )
		{
			p_edge_t inner_edge = list_data_at( pedge->vertex->edges, ile);

			//if( SUCCESS == pcompareproc(to_be_delete_vertex->vertex_data, inner_edge->vertex->vertex_data) )
			
			//	OR

			if( to_be_delete_vertex == inner_edge->vertex )
			{
				free( list_remove_at(pedge->vertex->edges, ile) );
				break;
			}
		}		
	}

	//	Here we destroy the edges list
	list_destroy( &(to_be_delete_vertex->edges), delete_edge );

	//	Here we delete the to_be_removed vertex from the main vertices list 
	long vertices_size = list_size( pgraph->vertices );
	for( long le = 0; le < vertices_size; ++le )
	{
		//p_vertex_t vertex_2 = list_data_at(pgraph->vertices, le);
		//if( SUCCESS == pcompareproc(to_be_delete_vertex->vertex_data, vertex_2->vertex_data) )

		//	OR
		
		if( to_be_delete_vertex == list_data_at(pgraph->vertices, le) )
		{
			to_return_data = to_be_delete_vertex->vertex_data;
			free( list_remove_at(pgraph->vertices, le) );
			break;
		}
	}

	return(to_return_data);
}
//	Graph Interface Functions
extern	p_mv_graph_t	create_graph(int graph_type)
{
	// Code
	p_mv_graph_t pgraph = (p_mv_graph_t)Xmalloc(SIZE_GRAPH);

	pgraph->vertices = create_list();
	pgraph->type = graph_type;

	return(pgraph);
}

//	Graph Vertex manipulators
extern	ret_t 	mv_graph_insert_vertex(p_mv_graph_t pgraph, data_t	new_data, COMPAREPROC pcompareproc)
{
	//	Code
	if( !pgraph )
	{
		fprintf(stderr, "ERROR: Graph not found to insert vertex.\n");
		return(FAILURE);
	}

	if( !list_size(pgraph->vertices) )
	{
		p_vertex_t new_vertex = create_vertex(new_data);
		list_insert_back(pgraph->vertices, new_vertex);
	}
	else
	{
		p_vertex_t pvertex = locate_vertex(pgraph, new_data, pcompareproc);

		if( pvertex )
		{
			fprintf(stderr, "ERROR: Data already exists\n");
			return(FAILURE);
		}

		pvertex = create_vertex(new_data);
		list_insert_back(pgraph->vertices, pvertex);
	}

	return(SUCCESS);
}

extern	data_t 	mv_graph_remove_vertex(p_mv_graph_t pgraph, data_t	e_data,	COMPAREPROC pcompareproc)
{
	//	Code

	if( !pgraph 	||
		!list_size(pgraph->vertices))
	{
		fprintf(stderr, "ERROR: Graph not found\n");
		return(NULL);
	}
	
	switch( pgraph->type )
	{
		case GRAPH_UNDIRECTED:
			return( generic_remove_vertex_undirected_graph(pgraph, e_data, pcompareproc) );
			break;

		case GRAPH_DIRECTED:
			return( generic_remove_vertex_directed_graph(pgraph, e_data, pcompareproc) );
			break;  
	}
	
	return(NULL);
}

//	Graph Edge manipulators
extern	ret_t 	mv_graph_insert_edge(p_mv_graph_t pgraph, data_t vertex1, data_t vertex2, size_t weight, COMPAREPROC pcompareproc)
{
	//	Code

	if( !pgraph	||
		!list_size(pgraph->vertices) )
	{
		fprintf(stderr, "ERROR: Graph not found.\n");
		return(FAILURE);
	}

	if( SUCCESS == pcompareproc(vertex1, vertex2) )
	{
		fprintf(stderr, "ERROR: Self loop not allowed.\n");
		return(FAILURE);
	}

	p_vertex_t pvertex1 = locate_vertex(pgraph, vertex1, pcompareproc);
	p_vertex_t pvertex2 = locate_vertex(pgraph, vertex2, pcompareproc);

	//	If vertex not present to add edge then insert the vertex first in the graph 
	if( !pvertex1 )
	{
		mv_graph_insert_vertex(pgraph, vertex1, pcompareproc);
		pvertex1 = locate_vertex(pgraph, vertex1, pcompareproc);
	}

	if( !pvertex2 )
	{
		mv_graph_insert_vertex(pgraph, vertex2, pcompareproc);
		pvertex2 = locate_vertex(pgraph, vertex2, pcompareproc);
	}


	// Check for if edge already present

	//	Below both checking will work for only undirected graph
	//	and the first one will only work for directed graph
	long long edges_size = list_size(pvertex1->edges);

	for( long le = 0; le < edges_size; ++le )
	{
		p_edge_t pedge = list_data_at(pvertex1->edges, le);

		if( SUCCESS == pcompareproc(vertex2, pedge->vertex->vertex_data) )
		{
			fprintf(stderr, "ERRORL: Edge already present.\n");
			return(FAILURE);
		}
	}

	edges_size = list_size(pvertex2->edges);

	for( long le = 0; le < edges_size; ++le )
	{
		p_edge_t pedge = list_data_at(pvertex2->edges, le);

		if( SUCCESS == pcompareproc(vertex1, pedge->vertex->vertex_data) )
		{
			fprintf(stderr, "ERRORL: Edge already present.\n");
			return(FAILURE);
		}
	}

	switch( pgraph->type )
	{

		case GRAPH_DIRECTED:
			return(generic_insert_directed_edge(pvertex1, pvertex2, weight));

		case GRAPH_UNDIRECTED:
			return(generic_insert_undirected_edge(pvertex1, pvertex2, weight));

		default:
			fprintf(stderr, "ERROR: Such kind of graph does not exists.\n");
			break;
	}

	return(FAILURE);
}

extern	ret_t 	mv_graph_remove_edge(p_mv_graph_t pgraph, data_t vertex1, data_t vertex2, COMPAREPROC pcompareproc)
{
	// Code

	if( !pgraph ||
		!list_size(pgraph->vertices) )
	{
		fprintf(stderr, "ERROR: Graph not found.\n");
		return(FAILURE);
	}

	p_vertex_t pvertex1 = locate_vertex(pgraph, vertex1, pcompareproc);
	p_vertex_t pvertex2 = locate_vertex(pgraph, vertex2, pcompareproc);

	if( !pvertex1 ||
		!pvertex2)
	{
		fprintf(stdout, "ERROR: One of the vertex not found.\n");
		return(FAILURE);
	}

	long edges_size = 0;

	switch(pgraph->type)
	{
		case GRAPH_DIRECTED:

			edges_size = list_size(pvertex1->edges);

			for( long le = 0; le < edges_size; ++le )
			{
				p_edge_t pedge = list_data_at(pvertex1->edges, le);

				if( pvertex2 == pedge->vertex )
				{
					free( list_remove_at(pvertex1->edges, le) );
					break;
				}
			}

			break;

		case GRAPH_UNDIRECTED:

			edges_size = list_size(pvertex1->edges);

			for( long le = 0; le < edges_size; ++le )
			{
				p_edge_t pedge = list_data_at(pvertex1->edges, le);

				if( pvertex2 == pedge->vertex )
				{
					free( list_remove_at(pvertex1->edges, le) );
					break;
				}
			}

			edges_size = list_size(pvertex2->edges);

			for( long le = 0; le < edges_size; ++le )
			{
				p_edge_t pedge = list_data_at(pvertex2->edges, le);

				if( pvertex1 == pedge->vertex )
				{
					free( list_remove_at(pvertex2->edges, le) );
					break;
				}
			}

			break;

		default:
			return(FAILURE);
	}


	return(SUCCESS);
}

//	Show Graph
extern	ret_t  	mv_graph_show(p_mv_graph_t pgraph, SHOWVERTEXDATAPROC pshowvertexdataproc, SHOWEDGEDATAPROC pshowedgedataproc)
{
	// Code
	if( !pgraph ||
		!list_size(pgraph->vertices) )
	{
		fprintf(stderr, "ERROR: Graph not found.\n");
		return(FAILURE);
	}

	long vertices_size = list_size(pgraph->vertices);

	fprintf(stdout, "\nGRAPH:\n");

	fprintf(stdout, "{START}");
	fprintf(stdout, "\n  |\n");
	//	This loop will show the vertices present in the graph
	for( long ole = 0; ole < vertices_size; ++ole)
	{
		// Get the vertex present of ole index
		p_vertex_t pvertex = list_data_at(pgraph->vertices, ole);

		fprintf(stdout, "{");
		pshowvertexdataproc( pvertex->vertex_data );
		fprintf(stdout, "}->");

		//	This loop will show the edges of the present vertex
		long edges_size = list_size(pvertex->edges); 
		for( long ile = 0; ile < edges_size; ++ile )
		{
			// Get the edge present of ile index
			p_edge_t pedge = list_data_at(pvertex->edges, ile);
			fprintf(stdout, "{");
			pshowedgedataproc(pedge->vertex->vertex_data, pedge->weight);
			fprintf(stdout, "}->");
		}
		fprintf(stdout, "{END}");

		fprintf(stdout, "\n  |\n");
	}
	fprintf(stdout, "{END}\n\n");

	return(SUCCESS);
}

//	Destroy Graph
extern	void	mv_graph_destroy(pp_mv_graph_t ppgraph, DELETEDATAPROC pdeletedataproc)
{
	// Code

	if( !ppgraph	||
		!*ppgraph)
	{
		fprintf(stderr, "ERROR: Graph not found.\n");
		return;
	}

	p_mv_graph_t pgraph = *ppgraph;

	while( list_size(pgraph->vertices) )
	{
		p_vertex_t pvertex = list_remove_back(pgraph->vertices);

		// Destroy edges list
		list_destroy( &(pvertex->edges), delete_edge );

		//	Delete data present in vertex
		pdeletedataproc(pvertex->vertex_data);

		pvertex->vertex_data = NULL;

		//	Delete the vertex
		free(pvertex);
		pvertex = NULL;
	}

	free(pgraph);
	pgraph = NULL;

	*ppgraph = NULL;

	return((void)(int) SUCCESS); 
}

