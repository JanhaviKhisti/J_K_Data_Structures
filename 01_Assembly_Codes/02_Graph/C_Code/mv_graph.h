

#ifndef _MV_GRAPH_H
#define _MV_GRAPH_H

// Header
#include "mv_dcll.h"

// Constant Literals and MACROS
#ifndef SUCCESS 
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE 1
#endif

// enum
enum
{
	GRAPH_NONE = 0,
	GRAPH_DIRECTED,
	GRAPH_UNDIRECTED
};

// Typedefs

struct mv_graph;
typedef struct mv_graph    mv_graph_t;
typedef struct mv_graph*   p_mv_graph_t;
typedef struct mv_graph**  pp_mv_graph_t;

struct vertex;
typedef struct vertex    vertex_t;
typedef struct vertex*   p_vertex_t;
typedef struct vertex**  pp_vertex_t;

struct edge;
typedef struct edge    edge_t;
typedef struct edge*   p_edge_t;
typedef struct edge**  pp_edge_t;

typedef void* data_t;
typedef int ret_t;

typedef ret_t(*COMPAREPROC)(data_t, data_t);
typedef void(*SHOWVERTEXDATAPROC)(data_t);
typedef void(*SHOWEDGEDATAPROC)(data_t, size_t);
typedef void(*DELETEDATAPROC)(data_t);

// struct type definition
struct vertex
{
	data_t vertex_data;
	p_mv_dcll_t edges;

};
#define SIZE_VERTEX (sizeof(vertex_t))

struct edge
{
	p_vertex_t vertex;
	size_t weight;
};
#define SIZE_EDGE (sizeof(edge_t))

struct mv_graph
{
	p_mv_dcll_t vertices;
	int type;
};
#define SIZE_GRAPH (sizeof(mv_graph_t))

// Graph Interface Functions
extern p_mv_graph_t create_graph(int graph_type);

// Graph Vertex Manipulators
extern ret_t mv_graph_insert_vertex(p_mv_graph_t pgraph, data_t new_data, COMPAREPROC pcompareproc);
extern data_t mv_graph_remove_vertex(p_mv_graph_t pgraph, data_t e_data, COMPAREPROC pcompareproc);

// Graph Edge Manipulators
extern ret_t mv_graph_insert_edge(p_mv_graph_t pgraph, data_t vertex1, data_t vertex2, size_t weight, COMPAREPROC pcompareproc);
extern ret_t mv_graph_remove_edge(p_mv_graph_t pgraph, data_t vertex1, data_t vertex2, COMPAREPROC pcompareproc);

// Show Graph 
extern ret_t mv_graph_show(p_mv_graph_t pgraph, SHOWVERTEXDATAPROC pshowvertexdataproc, SHOWEDGEDATAPROC pshowedgedataproc);

// Destroy Graph
extern void mv_graph_destroy(pp_mv_graph_t ppgraph, DELETEDATAPROC pdeletedataproc);

#endif /* _MV_GRAPH_H */



